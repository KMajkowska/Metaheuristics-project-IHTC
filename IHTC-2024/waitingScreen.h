/********************************************************************************
** Form generated from reading UI file 'waitingScreen.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QLabel>
#include <qmovie.h>
#include <QVBoxLayout>
#include <QtWidgets/QApplication>

#include "consts.h"
#include "StateController.h"

class Ui_waitingScreen : public QWidget
{

    Q_OBJECT

public:
    Ui_waitingScreen(QWidget* parent);
    ~Ui_waitingScreen();

private:
    QWidget* _centralwidget;
    QLabel* _waitingForPlayerLabel;
    QFont* _font;
    QLabel* _loadingCircleLabel;
    QMovie* _loadingCircleMovie;
    QVBoxLayout* _layout;

    QFont setUpFont(int points);
    void setUpWaitingForPlayerLabel();
    void setUpLoadingCircle();

    void setupUi(QWidget* MainWindow);

    void retranslateUi(QWidget* MainWindow);

};
