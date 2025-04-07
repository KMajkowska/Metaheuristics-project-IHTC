/********************************************************************************
** Form generated from reading UI file 'sessions.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <qstackedwidget.h>
#include <qpushbutton.h>
#include <consts.h>
#include <ScreensNumber.h>
#include <qboxlayout.h>


class Ui_sessions : public QWidget
{
public:
    Ui_sessions(QStackedWidget* stackedWidget, QWidget* parent = nullptr);
    ~Ui_sessions() = default;

private:
    QWidget *centralwidget;
    QListWidget *listOfSessions;
    QStackedWidget* stackedWidget;
    QPushButton* createSessionButton;
    QFont* font;
    QVBoxLayout* layout;
    QHBoxLayout* listLayout;
    QHBoxLayout* buttonLayout;

    void setUpListOfSessions();
    void setUpCreateSessionButton();
    QFont setUpFont(int points);

    void setupUi(QWidget* MainWindow);

    void retranslateUi(QWidget* MainWindow);

private slots:
    void onCreateSessionButtonClicked();

};
