#pragma once

#include <QTimer>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

/**
 * @brief Class to represents plot and allows to update it real time
*/
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
    QLineSeries* _ourResultSeries;
    QChart* _ourResultChart;
    QLineSeries* _opponentSeries;
    QChart* _opponentChart;
    QValueAxis* _ourResultAxisX;
    QValueAxis* _ourResultAxisY;
    QValueAxis* _opponentAxisX;
    QValueAxis* _opponentAxisY;
    QChartView* _ourResultChartView;
    QChartView* _opponentChartView;
    QHBoxLayout* _layout;

    void setUpAxisX();
    void setUpAxisY();

    void drawPoint(QLineSeries* series, QValueAxis* xAxis, QValueAxis* yAxis, double x, double y);
};
