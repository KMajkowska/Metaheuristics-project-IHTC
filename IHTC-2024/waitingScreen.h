/********************************************************************************
** Form generated from reading UI file 'waitingScreen.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <qstackedwidget.h>
#include "consts.h"
#include "qmovie.h"
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_waitingScreen : public QWidget
{
public:
    Ui_waitingScreen(QStackedWidget* stackedWidget, QWidget* parent);
    ~Ui_waitingScreen();
private:
    QWidget *centralwidget;
    QLabel *waitingForPlayerLabel;
    QStackedWidget* stackedWidget;
    QFont* font;
    QLabel* loadingCircleLabel;
    QMovie* loadingCircleMovie;
    QVBoxLayout* layout;

    QFont setUpFont(int points);
    void setUpWaitingForPlayerLabel();
    void setUpLoadingCircle();

    void setupUi(QWidget* MainWindow);

    void retranslateUi(QWidget* MainWindow);

};
