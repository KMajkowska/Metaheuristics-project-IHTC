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
    ~Ui_gamePlotScreen();

    void connectPlot(std::shared_ptr<ICGame> game);

private:
    QWidget* _centralWidget;
    QLabel* _infoLabel;
    RealTimePlot* _plot;
    QFont* _font;
    QVBoxLayout* _layout;
    QHBoxLayout* _plotLayout;
    QHBoxLayout* _resultInfoLayout;
    QLabel* _ourScoreLabel;
    QLabel* _opponentScoreLabel;
    QLabel* _separateResultLabel;

    void setupUi(QWidget* mainWindow);
    void retranslateUi(QWidget* MainWindow);

    void setUpInfoLabel();
    void setUpChart();
    QFont setUpFont(int points);

    void setUpOurResultLabel();
    void setUpOpponentResultLabel();

    void changeOurScoreLabel(int score);
    void chaneOpponentScoreLabel(int score);


private slots:
    void handleDrawSeries(double idx, double fitness);
    void handleOpponentDrawSeries(double idx, double fitness);

    void handleResetPlots();

signals:
    void requestDrawSeries(double idx, double fitness);
    void requestDrawOpponentSeries(double idx, double fitness);

    void requestResetPlots();
};