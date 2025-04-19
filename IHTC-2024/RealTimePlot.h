#pragma once

#include "qcustomplot.h"
#include <QTimer>
#include <QVBoxLayout>
#include <QRandomGenerator>

class RealTimePlot : public QWidget {
    Q_OBJECT

public:
    RealTimePlot(QWidget* parent = nullptr) : QWidget(parent), x(0) {
        QVBoxLayout* layout = new QVBoxLayout(this);
        customPlot = new QCustomPlot(this);
        layout->addWidget(customPlot);

        // Create a graph
        graph = customPlot->addGraph();
        graph->setPen(QPen(Qt::blue));
        customPlot->xAxis->setLabel("Time");
        customPlot->yAxis->setLabel("Value");
        customPlot->xAxis->setRange(0, 100);
        customPlot->yAxis->setRange(0, 100);

        // Timer to simulate real-time data
        QTimer* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &RealTimePlot::addData);
        timer->start(1000); // 1 second intervals
    }

private slots:
    void addData() {
        double y = QRandomGenerator::global()->bounded(100);
        graph->addData(x, y);
        x++;

        // Auto-scroll
        customPlot->xAxis->setRange(x - 100, x);
        customPlot->replot();
    }

private:
    QCustomPlot* customPlot;
    QCPGraph* graph;
    double x;
};
