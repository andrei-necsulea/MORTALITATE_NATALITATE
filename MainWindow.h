#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PDFReportGenerator.h"
#include "Country.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onDetailsButton();
    void onCrisisButton();
    void onScenarioButton();
    void onGeneralButton();

private:
    Ui::MainWindow* ui;
    PDFReportGenerator reportGen;
    QVector<Country>   countries;

    void loadCountries(const QString& csvPath);
    Country currentCountry() const;
    static void cleanupPNGs();
};

#endif // MAINWINDOW_H
