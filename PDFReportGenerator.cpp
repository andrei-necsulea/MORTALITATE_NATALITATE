#include "PDFReportGenerator.h"
#include "SimulationModel.h"
#include <QProcess>
#include <QImage>
#include <QPainter>
#include <QPdfWriter>
#include <QDate>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>


PDFReportGenerator::PDFReportGenerator(QWidget* parent)
    : m_parent(parent), m_currentPage(0)
{
}

// ——— Antet + translate pentru conținut ———
void PDFReportGenerator::startPage(
    QPdfWriter& writer,
    QPainter& painter,
    const QString& title)
{
    if (m_currentPage > 0)
        writer.newPage();
    m_currentPage++;
    painter.begin(&writer);

    const int pageW = writer.pageLayout().fullRect().width();

    QFont hf("Times New Roman", 12, QFont::Bold);
    painter.setFont(hf);
    QRectF headerRect(0, 0, pageW, 40);
    QString header = title;
    if (m_currentPage == 1)
        header += " - " + QDate::currentDate().toString("dd MMMM yyyy");
    painter.drawText(headerRect, Qt::AlignCenter, header);

    // Mut origin pentru conținut
    painter.translate(0, 60);
}

// ——— Plot matplotlib și desen PNG ———
void PDFReportGenerator::drawMatplotlibGraph(
    QPainter& painter,
    const QVector<QPointF>& data,
    const QString& title,
    const QString& imagePath,
    int x, int y, int w, int h)
{
    if (data.isEmpty()) return;

    QStringList args{ "plot.py", title, imagePath };
    for (auto& pt : data) {
        args << QString::number(pt.x()) << QString::number(pt.y());
    }
    QProcess proc;
    proc.start("python", args);
    proc.waitForFinished(-1);

    QImage img(imagePath);
    painter.drawImage(QRect(x, y, w, h), img);
}


// ================= Detalii țară =================
void PDFReportGenerator::generateDetailsReport(
    const Country& c,
    const QString& filePath)
{
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(85);
    QPainter painter;
    m_currentPage = 0;
    startPage(writer, painter, "Detalii țară");

    const int pageW = writer.pageLayout().fullRect().width();
    const int pageH = writer.pageLayout().fullRect().height();
    const int margin = 50;
    const int lineH = 28;
    int       y = 0;

    // Titlu principal
    QFont fnt("Times New Roman", 20, QFont::Bold);
    painter.setFont(fnt);
    painter.drawText(QRect(margin, y += lineH, pageW - 2 * margin, lineH),
        Qt::AlignCenter, "Detalii țară");

    // Date text linie cu linie
    painter.setFont(QFont("Times New Roman", 12));
    painter.drawText(margin, y += lineH * 8, QString("Țară : %1").arg(c.name()));
    painter.drawText(margin, y += lineH, QString("Populație inițială : %1").arg(c.population()));
    painter.drawText(margin, y += lineH, QString("Rata natalitate : %1").arg(c.birthRate()));
    painter.drawText(margin, y += lineH, QString("Rata mortalitate : %1").arg(c.deathRate()));

    // Grafic centrat sub text
    QVector<QPointF> data;
    for (int i = 0; i <= 10; ++i)
        data.append({ qreal(i),
                      qreal(SimulationModel::exponential(c, c.birthRate() - c.deathRate(), i)) });
    QString img = QFileInfo(filePath).completeBaseName() + "_details.png";
    int gW = 400, gH = 250;
    int gX = (pageW - gW) / 2;
    drawMatplotlibGraph(painter, data, "Model Exponențial (0–10 ani)", img,
        gX, y += lineH * 2, gW, gH);

    // Footer
    painter.setFont(QFont("Times New Roman", 14));
    painter.drawText(
        QRect(10, writer.pageLayout().fullRect().height() + 45, pageW, 20),
        Qt::AlignCenter,
        QString("Page %1").arg(m_currentPage)
    );

    painter.end();
}

// ================= Simulare criză globală =================
void PDFReportGenerator::generateCrisisReport(
    const Country& c,
    double extraDeathRate,
    int years,
    const QString& filePath)
{
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(85);
    QPainter painter;
    m_currentPage = 0;
    startPage(writer, painter, "Simulare criză globală");

    const int pageW = writer.pageLayout().fullRect().width();
    const int pageH = writer.pageLayout().fullRect().height();
    const int margin = 50;
    const int lineH = 28;
    int       y = 0;

    // Titlu principal
    QFont fnt("Times New Roman", 20, QFont::Bold);
    fnt.setUnderline(true);
    painter.setFont(fnt);
    painter.drawText(QRect(margin, y += lineH, pageW - 2 * margin, lineH),
        Qt::AlignCenter, "Simulare criză globală");

    // Date text
    painter.setFont(QFont("Times New Roman", 12));
    painter.drawText(margin, y += lineH * 8, QString("Țară : %1").arg(c.name()));
    painter.drawText(margin, y += lineH, QString("Extra mortalitate : %1").arg(extraDeathRate));
    painter.drawText(margin, y += lineH, QString("Durata simulare : %1 ani").arg(years));

    // Grafic
    auto pop = SimulationModel::simulateCrisis(c, extraDeathRate, years);
    QVector<QPointF> pts;
    for (int i = 0; i < pop.size(); ++i)
        pts.append({ qreal(i), qreal(pop[i]) });
    QString img = QFileInfo(filePath).completeBaseName() + "_crisis.png";
    int gW = 400, gH = 250;
    int gX = (pageW - gW) / 2;
    drawMatplotlibGraph(painter, pts, "Populație sub criză", img,
        gX, y += lineH * 2, gW, gH);

    // Footer
    painter.setFont(QFont("Times New Roman", 14));
    painter.drawText(
        QRect(10, writer.pageLayout().fullRect().height() + 45, pageW, 20),
        Qt::AlignCenter,
        QString("Page %1").arg(m_currentPage)
    );

    painter.end();
}

// ================= Analiză scenarii evoluție =================
void PDFReportGenerator::generateScenarioReport(
    const Country& c,
    double rate1,
    double rate2,
    int years,
    long carryingCapacity,
    const QString& filePath)
{
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(85);
    QPainter painter;
    m_currentPage = 0;
    startPage(writer, painter, "Analiză scenarii evoluție");

    const int pageW = writer.pageLayout().fullRect().width();
    const int pageH = writer.pageLayout().fullRect().height();
    const int margin = 50;
    const int lineH = 28;
    int       y = 0;

    // Titlu principal
    QFont fnt("Times New Roman", 20, QFont::Bold);
    fnt.setUnderline(true);
    painter.setFont(fnt);
    painter.drawText(QRect(margin, y += lineH, pageW - 2 * margin, lineH),
        Qt::AlignCenter, "Analiză scenarii evoluție");

    // Date text
    painter.setFont(QFont("Times New Roman", 12));
    painter.drawText(margin, y += lineH * 8, QString("Țară : %1").arg(c.name()));
    painter.drawText(margin, y += lineH, QString("Rata natalitate 1 : %1").arg(rate1));
    painter.drawText(margin, y += lineH, QString("Rata natalitate 2 : %1").arg(rate2));
    painter.drawText(margin, y += lineH, QString("Durata simulare : %1 ani").arg(years));

    // Grafice alăturate
    auto sc = SimulationModel::compareBirthScenarios(c, rate1, rate2, years, carryingCapacity);
    QVector<QPointF> d1, d2;
    for (int i = 0; i <= years; ++i) {
        d1.append({ qreal(i), qreal(sc.first[i]) });
        d2.append({ qreal(i), qreal(sc.second[i]) });
    }
    int gW = 300, gH = 200;
    drawMatplotlibGraph(painter, d1, "Scenariu 1",
        QFileInfo(filePath).completeBaseName() + "_s1.png",
        15, y += lineH * 2, gW, gH);
    drawMatplotlibGraph(painter, d2, "Scenariu 2",
        QFileInfo(filePath).completeBaseName() + "_s2.png",
        pageW - gW + 30, y, gW, gH);

    // Footer
    painter.setFont(QFont("Times New Roman", 14));
    painter.drawText(
        QRect(10, writer.pageLayout().fullRect().height() + 45, pageW, 20),
        Qt::AlignCenter,
        QString("Page %1").arg(m_currentPage)
    );

    painter.end();
}



// ================= Raport general =================
void PDFReportGenerator::generateGeneralReport(
    const Country& c,
    int years,
    long carryingCapacity,
    const QString& filePath)
{
    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize::A4);
    writer.setResolution(85);
    QPainter painter;
    m_currentPage = 0;
    startPage(writer, painter, "Raport general");

    const int pageW = writer.pageLayout().fullRect().width();
    const int margin = 50;
    const int lineH = 28;
    int       y = 0;

    QFont font;

    font.setFamily("Times New Roman");
    font.setPointSize(19);
    font.setUnderline(true);
    font.setBold(true);

    painter.setFont(font);
    painter.drawText(QRect(margin, y += lineH, pageW - 2 * margin, lineH),
        Qt::AlignCenter, "Raport general");

    painter.setFont(QFont("Times New Roman", 18, QFont::Bold));
    painter.drawText(margin, y += lineH * 2, "Rezumat");

    painter.setFont(QFont("Times New Roman", 12));
    painter.drawText(margin, y += lineH, QString("Țară : %1").arg(c.name()));
    painter.drawText(margin, y += lineH, QString("Populație inițială : %1").arg(c.population()));
    painter.drawText(margin, y += lineH, QString("Rata natalitate : %1").arg(c.birthRate()));
    painter.drawText(margin, y += lineH, QString("Rata mortalitate: %1").arg(c.deathRate()));
    painter.drawText(margin, y += lineH, QString("Durata (ani) : %1").arg(years));
    painter.drawText(margin, y += lineH, QString("Capacitate K : %1").arg(carryingCapacity));

    painter.setFont(QFont("Times New Roman", 18, QFont::Bold));
    painter.drawText(margin, y += lineH * 3, "Calcule");

    painter.setFont(QFont("Times New Roman", 12));
    double r = c.birthRate() - c.deathRate();
    long pExp = SimulationModel::exponential(c, r, years);
    long pLog = SimulationModel::logistic(c, r, years, carryingCapacity);
    painter.drawText(margin, y += lineH, QString("P_exp(%1) = %2").arg(years).arg(pExp));
    painter.drawText(margin, y += lineH, QString("P_log(%1) = %2").arg(years).arg(pLog));

    painter.setFont(QFont("Times New Roman", 18, QFont::Bold));
    painter.drawText(margin, y += lineH * 2, "Grafice");

    QVector<QPointF> eData, lData;
    for (int i = 0; i <= years; ++i) {
        eData.append({ qreal(i), qreal(SimulationModel::exponential(c, r, i)) });
        lData.append({ qreal(i), qreal(SimulationModel::logistic(c, r, i, carryingCapacity)) });
    }

    int gW = 300, gH = 200;
    int x1 = 15, x2 = pageW - margin - gW;
    drawMatplotlibGraph(painter, eData, "Model Exponențial",
        QFileInfo(filePath).completeBaseName() + "_exp.png",
        x1, y += lineH, gW, gH);
    drawMatplotlibGraph(painter, lData, "Model Logistic",
        QFileInfo(filePath).completeBaseName() + "_log.png",
        x2+=110, y, gW, gH);

    painter.setFont(QFont("Times New Roman", 18, QFont::Bold));
    painter.drawText(margin, y += gH + lineH * 2, "Concluzii");

    painter.setFont(QFont("Times New Roman", 12));
    painter.drawText(margin, y += lineH, "- Exponențial: creștere nelimitată.");
    painter.drawText(margin, y += lineH, "- Logistic: stabilizare la K.");
    painter.drawText(margin, y += lineH,
        QString("- După %1 ani: P_exp=%2, P_log=%3").arg(years).arg(pExp).arg(pLog));

    painter.setFont(QFont("Times New Roman", 14));
    painter.drawText(
        QRect(10, writer.pageLayout().fullRect().height()+45, pageW, 20),
        Qt::AlignCenter,
        QString("Page %1").arg(m_currentPage)
    );

    painter.end();
}
