/********************************************************************************
** Form generated from reading UI file 'welcomeScreen.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#pragma once 
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>
#include <QPushButton>
#include <chooseOpponent.h>
#include <qstackedwidget.h>
#include "ScreensNumber.h"
#include "consts.h"
#include <qboxlayout.h>
#include <memory>

class Ui_welcomeScreen : public QWidget {

    Q_OBJECT

public:

    explicit Ui_welcomeScreen(QStackedWidget* stackedWidget, QWidget* parent = nullptr, std::shared_ptr<AllGameParameters> allGameParameters = nullptr);
    ~Ui_welcomeScreen();
    
private:
    std::shared_ptr<AllGameParameters> allGameParameters;
    QWidget* centralwidget;
    QLineEdit* nameTextfield;
    QLabel* welcomeText;
    QFont* font;
    QPushButton* startGameButton;
    QStackedWidget* stackedWidget;
    QVBoxLayout* mainLayout;

    Ui_chooseOpponent *chooseOpponentScreen;

    void setUpNameTextfield();
    void setUpWelcomeText();
    void setUpStartGameButton();
    QFont setUpFont(int points);

    void retranslateUi(QWidget* welcomeScreen);

    void setupUi(QWidget* welcomeScreen);

private slots:
    void openChooseOpponentScreen(); 

    void updateButtonState();
}; 