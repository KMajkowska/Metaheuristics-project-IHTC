#pragma once

#include <QTimer>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

class RealTimePlot : public QChartView {
    Q_OBJECT

public:
    RealTimePlot(QWidget* parent = nullptr);
    void setUpChart();

    void drawSeries(double x, double y);

private slots:

private:
    QLineSeries* ourResultSeries;
    QChart* ourResultChart;
    QLineSeries* opponentSeries;
    QChart* opponentChart;
    QValueAxis* axisX;
    QValueAxis* axisY;
    QChartView* ourResultChartView;
    QChartView* opponentChartView;
    QHBoxLayout* layout;

    void setUpAxisX();
    void setUpAxisY();
};
