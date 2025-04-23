#include "RealTimePlot.h"

RealTimePlot::RealTimePlot(QWidget* parent) : QChartView(parent)
{
	series = new QLineSeries();
	ourResultChart = new QChart();
	axisX = new QValueAxis();
	axisY = new QValueAxis();
	ourResultChartView = new QChartView(ourResultChart);
	layout = new QHBoxLayout(this);
}

void RealTimePlot::setUpChart()
{
	setUpAxisX();
	setUpAxisY();

	ourResultChart->addAxis(axisX, Qt::AlignBottom);
	ourResultChart->addAxis(axisY, Qt::AlignLeft);

	ourResultChartView->setRenderHint(QPainter::Antialiasing);

	layout->addWidget(ourResultChartView);
	setLayout(layout);
}

void RealTimePlot::drawSeries(double x, double y)
{
	series->append(x, y);
	ourResultChart->addSeries(series);
}

void RealTimePlot::setUpAxisX()
{
	axisX->setTitleText("X Axis");
	axisX->setLabelFormat("%.1f");
	axisX->setRange(0, 50000);
}

void RealTimePlot::setUpAxisY()
{
	axisY->setTitleText("Y Axis");
	axisY->setLabelFormat("%.1f");
	axisY->setRange(0, 50000);
}
