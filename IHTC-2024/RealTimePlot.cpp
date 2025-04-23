#include "RealTimePlot.h"

RealTimePlot::RealTimePlot(QWidget* parent) : QChartView(parent)
{
    ourResultSeries = new QLineSeries();
    ourResultChart = new QChart();
    ourResultAxisX = new QValueAxis();
    ourResultAxisY = new QValueAxis();
    ourResultChartView = new QChartView(ourResultChart);

    opponentSeries = new QLineSeries();
    opponentChart = new QChart();
    opponentAxisX = new QValueAxis();
    opponentAxisY = new QValueAxis();
    opponentChartView = new QChartView(opponentChart);

    layout = new QHBoxLayout(this);
}

void RealTimePlot::setUpChart()
{
    setUpAxisX();
    setUpAxisY();

    setUpOurResultPlot();

    setUpYourOpponentPlot();

    layout->addWidget(ourResultChartView);
    layout->addWidget(opponentChartView);

    setLayout(layout);
}

void RealTimePlot::setUpYourOpponentPlot()
{
    opponentChart->addSeries(opponentSeries);
    opponentChart->addAxis(opponentAxisX, Qt::AlignBottom);
    opponentChart->addAxis(opponentAxisY, Qt::AlignLeft);

    opponentSeries->attachAxis(opponentAxisX);
    opponentSeries->attachAxis(opponentAxisY);

    opponentChart->setTitle("Your opponent plot");

    opponentChartView->setRenderHint(QPainter::Antialiasing);
}

void RealTimePlot::setUpOurResultPlot()
{
    ourResultChart->addSeries(ourResultSeries);
    ourResultChart->addAxis(ourResultAxisX, Qt::AlignBottom);
    ourResultChart->addAxis(ourResultAxisY, Qt::AlignLeft);

    ourResultSeries->attachAxis(ourResultAxisX);
    ourResultSeries->attachAxis(ourResultAxisY);

    ourResultChart->setTitle("Your result plot");

    ourResultChartView->setRenderHint(QPainter::Antialiasing);
}

void RealTimePlot::drawSeriesOurResult(double x, double y)
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

void RealTimePlot::drawSeriesOpponentResult(double x, double y)
{
    opponentSeries->append(x, y);

    if (!opponentSeries->points().isEmpty())
    {
        QVector<QPointF> points = opponentSeries->points();
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

        opponentAxisX->setRange(minX - xMargin, maxX + xMargin);
        opponentAxisY->setRange(minY - yMargin, maxY + yMargin);
    }
}

void RealTimePlot::setUpAxisX()
{
    ourResultAxisX->setTitleText("X Axis");
    ourResultAxisX->setLabelFormat("%.1f");

    opponentAxisX->setTitleText("X Axis");
    opponentAxisX->setLabelFormat("%.1f");

}

void RealTimePlot::setUpAxisY()
{
    ourResultAxisY->setTitleText("Y Axis");
    ourResultAxisY->setLabelFormat("%.1f");

    opponentAxisX->setTitleText("X Axis");
    opponentAxisX->setLabelFormat("%.1f");
}
