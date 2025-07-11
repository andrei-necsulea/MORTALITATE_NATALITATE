#ifndef PDFREPORTGENERATOR_H
#define PDFREPORTGENERATOR_H

#include <QWidget>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include <QVector>
#include <QPointF>
#include <QString>
#include "Country.h"

class PDFReportGenerator {
public:
    explicit PDFReportGenerator(QWidget* parent = nullptr);

    void generateDetailsReport(const Country& c, const QString& filePath);
    void generateCrisisReport(const Country& c, double extraDeathRate, int years, const QString& filePath);
    void generateScenarioReport(const Country& c, double rate1, double rate2, int years, long carryingCapacity, const QString& filePath);
    void generateGeneralReport(const Country& c, int years, long carryingCapacity, const QString& filePath);

private:
    QWidget* m_parent;
    int      m_currentPage;

    // Desenează antetul cu titlu și dată
    void startPage(QPdfWriter& writer, QPainter& painter, const QString& title);

    // Rulează plot.py și desenează PNG-ul generat la poziția (x,y) cu dimensiunea w×h
    void drawMatplotlibGraph(
        QPainter& painter,
        const QVector<QPointF>& data,
        const QString& title,
        const QString& imagePath,
        int x, int y, int w, int h
    );
};

#endif // PDFREPORTGENERATOR_H
