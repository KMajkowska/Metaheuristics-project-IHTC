#include "RealTimePlot.h"

RealTimePlot::RealTimePlot(QWidget* parent) : QChartView(parent)
{
    _ourResultSeries = new QLineSeries();
    _ourResultChart = new QChart();
    _ourResultAxisX = new QValueAxis();
    _ourResultAxisY = new QValueAxis();
    _ourResultChartView = new QChartView(_ourResultChart);

    _opponentSeries = new QLineSeries();
    _opponentChart = new QChart();
    _opponentAxisX = new QValueAxis();
    _opponentAxisY = new QValueAxis();
    _opponentChartView = new QChartView(_opponentChart);

    _layout = new QHBoxLayout(this);
}

void RealTimePlot::setUpChart()
{
    setUpAxisX();
    setUpAxisY();

    setUpOurResultPlot();

    setUpYourOpponentPlot();

    _layout->addWidget(_ourResultChartView);
    _layout->addWidget(_opponentChartView);

    setLayout(_layout);
}

void RealTimePlot::setUpYourOpponentPlot()
{
    _opponentChart->addSeries(_opponentSeries);
    _opponentChart->addAxis(_opponentAxisX, Qt::AlignBottom);
    _opponentChart->addAxis(_opponentAxisY, Qt::AlignLeft);

    _opponentSeries->attachAxis(_opponentAxisX);
    _opponentSeries->attachAxis(_opponentAxisY);

    _opponentChart->setTitle("Your opponent plot");

    _opponentChartView->setRenderHint(QPainter::Antialiasing);
}

void RealTimePlot::setUpOurResultPlot()
{
    _ourResultChart->addSeries(_ourResultSeries);
    _ourResultChart->addAxis(_ourResultAxisX, Qt::AlignBottom);
    _ourResultChart->addAxis(_ourResultAxisY, Qt::AlignLeft);

    _ourResultSeries->attachAxis(_ourResultAxisX);
    _ourResultSeries->attachAxis(_ourResultAxisY);

    _ourResultChart->setTitle("Your result plot");

    _ourResultChartView->setRenderHint(QPainter::Antialiasing);
}

void RealTimePlot::drawSeriesOurResult(double x, double y)
{
    drawPoint(_ourResultSeries, _ourResultAxisX, _ourResultAxisY, x, y);
}

void RealTimePlot::drawSeriesOpponentResult(double x, double y)
{
    drawPoint(_opponentSeries, _opponentAxisX, _opponentAxisY, x, y);
}

void RealTimePlot::clearOurPlot()
{
    _ourResultSeries->clear();

    _ourResultAxisX->setRange(1, 1);
    _ourResultAxisY->setRange(1, 1);
}

void RealTimePlot::clearOpponentPlot()
{
    _opponentSeries->clear();

    _opponentAxisX->setRange(1, 1);
    _opponentAxisY->setRange(1, 1);
}

void RealTimePlot::setUpAxisX()
{
    _ourResultAxisX->setTitleText("X Axis");
    _ourResultAxisX->setLabelFormat("%.1f");

    _opponentAxisX->setTitleText("X Axis");
    _opponentAxisX->setLabelFormat("%.1f");
}

void RealTimePlot::setUpAxisY()
{
    _ourResultAxisY->setTitleText("Y Axis");
    _ourResultAxisY->setLabelFormat("%.1f");

    _opponentAxisX->setTitleText("X Axis");
    _opponentAxisX->setLabelFormat("%.1f");
}

void RealTimePlot::drawPoint(QLineSeries* series, QValueAxis* xAxis, QValueAxis* yAxis, double x, double y)
{
    series->append(x, y);

    if (series->points().isEmpty())
    {
        return;
    }

    QVector<QPointF> points = series->points();

    qreal minX = points.first().x();
    qreal maxX = points.first().x();
    qreal minY = points.first().y();
    qreal maxY = points.first().y();

    for (const auto& point : points)
    {
        minX = std::min(minX, point.x());
        maxX = std::max(maxX, point.x());
        minY = std::min(minY, point.y());
        maxY = std::max(maxY, point.y());
    }

    qreal xMargin = (maxX - minX) * 0.05;
    qreal yMargin = (maxY - minY) * 0.05;

    qreal rangeMinX = std::max(0.0, minX - xMargin);
    qreal rangeMinY = std::max(0.0, minY - yMargin);
    qreal rangeMaxX = maxX + xMargin;
    qreal rangeMaxY = maxY + yMargin;

    xAxis->setRange(rangeMinX, rangeMaxX);
    yAxis->setRange(rangeMinY, rangeMaxY);
}
