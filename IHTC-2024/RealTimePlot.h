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

    void setUpYourOpponentPlot();
    void setUpOurResultPlot();

    void drawSeriesOurResult(double x, double y);
    void drawSeriesOpponentResult(double x, double y);

    void clearOurPlot();
    void clearOpponentPlot();

private:
    QLineSeries* ourResultSeries;
    QChart* ourResultChart;
    QLineSeries* opponentSeries;
    QChart* opponentChart;
    QValueAxis* ourResultAxisX;
    QValueAxis* ourResultAxisY;
    QValueAxis* opponentAxisX;
    QValueAxis* opponentAxisY;
    QChartView* ourResultChartView;
    QChartView* opponentChartView;
    QHBoxLayout* layout;

    void setUpAxisX();
    void setUpAxisY();

    void drawPoint(QLineSeries* series, QValueAxis* xAxis, QValueAxis* yAxis, double x, double y);
};
