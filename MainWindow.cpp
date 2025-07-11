#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QCloseEvent>
#include <QDir>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , reportGen(this)
{
    ui->setupUi(this);
    setWindowTitle("Modele de natalitate si mortalitate");
    loadCountries("tari.csv");

    connect(ui->detailsBtn, &QPushButton::clicked, this, &MainWindow::onDetailsButton);
    connect(ui->crisisBtn, &QPushButton::clicked, this, &MainWindow::onCrisisButton);
    connect(ui->scenarioBtn, &QPushButton::clicked, this, &MainWindow::onScenarioButton);
    connect(ui->generalBtn, &QPushButton::clicked, this, &MainWindow::onGeneralButton);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::loadCountries(const QString& csvPath) {
    QFile file(csvPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open countries CSV file.");
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        auto parts = line.split(',');
        if (parts.size() >= 4) {
            QString name = parts[0];
            long pop = parts[1].toLongLong();
            double birth = parts[2].toDouble();
            double death = parts[3].toDouble();
            countries.emplace_back(name, pop, birth, death);
            ui->countryCombo->addItem(name);
        }
    }
    file.close();
}

Country MainWindow::currentCountry() const {
    int idx = ui->countryCombo->currentIndex();
    return countries.value(idx, Country{ "",0,0.0,0.0 });
}

void MainWindow::onDetailsButton() {
    Country c = currentCountry();
    QString path = QFileDialog::getSaveFileName(this,
        "Save Details Report", {}, "PDF Files (*.pdf)");
    if (path.isEmpty()) return;
    reportGen.generateDetailsReport(c, path);
}

void MainWindow::onCrisisButton() {
    Country c = currentCountry();
    double extra = ui->extraDeathRateEdit->text().toDouble();
    int years = ui->durationEdit->text().toInt();
    QString path = QFileDialog::getSaveFileName(this,
        "Save Crisis Report", {}, "PDF Files (*.pdf)");
    if (path.isEmpty()) return;
    reportGen.generateCrisisReport(c, extra, years, path);
}

void MainWindow::onScenarioButton() {
    Country c = currentCountry();
    double r1 = ui->birthRate1Edit->text().toDouble();
    double r2 = ui->birthRate2Edit->text().toDouble();
    int years = ui->durationEdit->text().toInt();
    long cap = ui->capacityEdit->text().toLongLong();
    QString path = QFileDialog::getSaveFileName(this,
        "Save Scenario Report", {}, "PDF Files (*.pdf)");
    if (path.isEmpty()) return;
    reportGen.generateScenarioReport(c, r1, r2, years, cap, path);
}

void MainWindow::onGeneralButton() {
    Country c = currentCountry();
    int years = ui->durationEdit->text().toInt();
    long cap = ui->capacityEdit->text().toLongLong();
    QString path = QFileDialog::getSaveFileName(this,
        "Save General Report", {}, "PDF Files (*.pdf)");
    if (path.isEmpty()) return;
    reportGen.generateGeneralReport(c, years, cap, path);
}

// La închiderea ferestrei principale, şterge toate PNG-urile din folderul de lucru
void MainWindow::closeEvent(QCloseEvent* event) {
    cleanupPNGs();
    QMainWindow::closeEvent(event);
}

void MainWindow::cleanupPNGs() {
    // Foloseşte working directory (de obicei rootul proiectului în Qt Creator)
    QDir dir(QDir::currentPath());
    auto pngs = dir.entryList({ "*.png" }, QDir::Files);
    for (auto& fileName : pngs) {
        dir.remove(fileName);
    }
}
