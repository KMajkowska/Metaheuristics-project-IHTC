#include "RealTimePlot.h"

RealTimePlot::RealTimePlot(QWidget* parent) : QChartView(parent)
{
    series = new QLineSeries();
    chart = new QChart();
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    chartView = new QChartView(chart);
    layout = new QVBoxLayout(this);
}

void RealTimePlot::setUpChart()
{
    setUpAxisX();
    setUpAxisY();

    chart->addSeries(series);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
    setLayout(layout);
}

void RealTimePlot::drawSeries(double x, double y)
{
    series->append(x, y);

    if (!series->points().isEmpty()) 
    {
        QVector<QPointF> points = series->points();
        qreal minX = points.first().x();
        qreal maxX = points.first().x();
        qreal minY = points.first().y();
        qreal maxY = points.first().y();

        for (const QPointF& point : points) {
            minX = std::min(minX, point.x());
            maxX = std::max(maxX, point.x());
            minY = std::min(minY, point.y());
            maxY = std::max(maxY, point.y());
        }

        qreal xMargin = (maxX - minX) * 0.05;
        qreal yMargin = (maxY - minY) * 0.05;

        axisX->setRange(minX - xMargin, maxX + xMargin);
        axisY->setRange(minY - yMargin, maxY + yMargin);
    }
}

void RealTimePlot::setUpAxisX()
{
    axisX->setTitleText("X Axis");
    axisX->setLabelFormat("%.1f");
}

void RealTimePlot::setUpAxisY()
{
    axisY->setTitleText("Y Axis");
    axisY->setLabelFormat("%.1f");
}
