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

private slots:

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
};
