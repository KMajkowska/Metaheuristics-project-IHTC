#include "RealTimePlot.h"

RealTimePlot::RealTimePlot(QWidget* parent) : QChartView(parent)
{
    ourResultSeries = new QLineSeries();
    ourResultChart = new QChart();
    ourResultAxisX = new QValueAxis();
    ourResultAxisY = new QValueAxis();
    ourResultChartView = new QChartView(ourResultChart);
    layout = new QHBoxLayout(this);
}

void RealTimePlot::setUpChart()
{
    setUpAxisX();
    setUpAxisY();

	ourResultChart->addAxis(ourResultAxisX, Qt::AlignBottom);
	ourResultChart->addAxis(ourResultAxisY, Qt::AlignLeft);

	ourResultChartView->setRenderHint(QPainter::Antialiasing);

	layout->addWidget(ourResultChartView);
	setLayout(layout);
    ourResultChart->addSeries(ourResultSeries);
    ourResultChart->addAxis(ourResultAxisX, Qt::AlignBottom);
    ourResultChart->addAxis(ourResultAxisY, Qt::AlignLeft);

    ourResultSeries->attachAxis(ourResultAxisX);
    ourResultSeries->attachAxis(ourResultAxisY);

    ourResultChartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(ourResultChartView);
}

void RealTimePlot::drawSeries(double x, double y)
{
    ourResultSeries->append(x, y);

    if (!ourResultSeries->points().isEmpty())
    {
        QVector<QPointF> points = ourResultSeries->points();
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

        ourResultAxisX->setRange(minX - xMargin, maxX + xMargin);
        ourResultAxisY->setRange(minY - yMargin, maxY + yMargin);
    }
}

void RealTimePlot::setUpAxisX()
{
    ourResultAxisX->setTitleText("X Axis");
    ourResultAxisX->setLabelFormat("%.1f");

}

void RealTimePlot::setUpAxisY()
{
    ourResultAxisY->setTitleText("Y Axis");
    ourResultAxisY->setLabelFormat("%.1f");
}
