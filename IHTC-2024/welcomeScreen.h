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
#include <qboxlayout.h>
#include <QtWidgets/QApplication>

#include "consts.h"
#include "StateController.h"

class Ui_welcomeScreen : public QWidget {

    Q_OBJECT

public:

    explicit Ui_welcomeScreen(QWidget* parent = nullptr);
    ~Ui_welcomeScreen();
    
private:
    QWidget* _centralwidget;
    QLineEdit* _nameTextfield;
    QLabel* _welcomeText;
    QFont* _font;
    QPushButton* _startGameButton;
    QVBoxLayout* _mainLayout;

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