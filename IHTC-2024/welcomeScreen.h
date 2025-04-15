/********************************************************************************
** Form generated from reading UI file 'welcomeScreen.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#pragma once 
#include <QtCore/QVariant>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QPushButton>
#include "consts.h"
#include <qboxlayout.h>
#include <QtWidgets/QApplication>
#include "StateController.h"

class Ui_welcomeScreen : public QWidget {

    Q_OBJECT

public:

    explicit Ui_welcomeScreen(QWidget* parent = nullptr);
    ~Ui_welcomeScreen();
    
private:
    QWidget* centralwidget;
    QLineEdit* nameTextfield;
    QLabel* welcomeText;
    QFont* font;
    QPushButton* startGameButton;
    QVBoxLayout* mainLayout;

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