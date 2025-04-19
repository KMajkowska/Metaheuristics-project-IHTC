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

	chart->addAxis(axisX, Qt::AlignBottom);
	chart->addAxis(axisY, Qt::AlignLeft);

	chartView->setRenderHint(QPainter::Antialiasing);

	layout->addWidget(chartView);
	setLayout(layout);
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
