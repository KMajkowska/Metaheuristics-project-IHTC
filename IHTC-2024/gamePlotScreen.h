/********************************************************************************
** Form generated from reading UI file 'chooseOpponent.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <qboxlayout.h>
#include <memory>
#include <QtWidgets/QApplication>

#include "consts.h"
#include "StateController.h"
#include "ScreensNumber.h"
#include "RealTimePlot.h"

class Ui_gamePlotScreen : public QWidget
{
    Q_OBJECT

public:
    Ui_gamePlotScreen(QWidget* parent = nullptr);
    ~Ui_gamePlotScreen() = default;

    void connectPlot(std::shared_ptr<ICGame> game);

private:
    QWidget* centralWidget;
    QLabel* infoLabel;
    RealTimePlot* plot;
    QFont* font;
    QVBoxLayout* layout;
    QHBoxLayout* plotLayout;
    QHBoxLayout* resultInfoLayout;
    QLabel* ourScoreLabel;
    QLabel* opponentScoreLabel;
    QLabel* separateResultLabel;

    void setupUi(QWidget* mainWindow);
    void retranslateUi(QWidget* MainWindow);

    void setUpInfoLabel();
    void setUpChart();
    QFont setUpFont(int points);

    void setUpOurResultLabel();
    void setUpOpponentResultLabel();


private slots:
    void handleDrawSeries(int idx, double fitness);
    void handleOpponentDrawSeries(int idx, double fitness);

signals:
    void requestDrawSeries(int idx, double fitness);

signals:
    void requestDrawOpponentSeries(int idx, double fitness);
};