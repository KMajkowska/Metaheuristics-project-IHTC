#include "endGame.h"
#pragma once

Ui_endGameScreen::Ui_endGameScreen(QWidget* parent) : QWidget(parent)
{
	centralWidget = new QWidget(this);
    font = new QFont();
    endButton = new QPushButton(centralWidget);
    returnButton = new QPushButton(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);
    gameResultLabel = new QLabel(centralWidget);
    buttonLayout = new QHBoxLayout(centralWidget);

    setupUi(this);
}

void Ui_endGameScreen::setupUi(QWidget* mainWindow)
{
    if (mainWindow->objectName().isEmpty())
        mainWindow->setObjectName("MainWindow");

    centralWidget->setParent(mainWindow);
    centralWidget->setObjectName("centralwidget");

    setUpGameResultLabel();
    setUpReturnButton();
    setUpEndButton();

    mainLayout->addLayout(buttonLayout);

    mainWindow->setLayout(mainLayout);

    connect(returnButton, &QPushButton::clicked, this, &Ui_endGameScreen::onReturnButtonClicked);
    connect(endButton, &QPushButton::clicked, this, &QApplication::quit);

    retranslateUi(this);
}

void Ui_endGameScreen::retranslateUi(QWidget* mainWindow)
{
    mainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Your result", nullptr));
    gameResultLabel->setText(QCoreApplication::translate("MainWindow", "You", nullptr));
    endButton->setText(QCoreApplication::translate("MainWindow", "End game and close app", nullptr));
    returnButton->setText(QCoreApplication::translate("MainWindow", "Return to choose opponent", nullptr));
}

void Ui_endGameScreen::setUpEndButton()
{
    endButton->setObjectName("endButton");
    endButton->setFixedSize(400, 100);
    endButton->setStyleSheet("background-color: pink; color: black");
    endButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    buttonLayout->addWidget(endButton, 0, Qt::AlignHCenter);
}

QFont Ui_endGameScreen::setUpFont(int points)
{
    font->setPointSize(points);
    return *font;
}

void Ui_endGameScreen::setUpReturnButton()
{
    returnButton->setObjectName("returnButton");
    returnButton->setFixedSize(400, 100);
    returnButton->setStyleSheet("background-color: pink; color: black");
    returnButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    buttonLayout->addWidget(returnButton, 0, Qt::AlignHCenter);
}

void Ui_endGameScreen::setUpGameResultLabel()
{
    gameResultLabel->setObjectName("gameResultLabel");
    gameResultLabel->setFont(setUpFont(MAIN_TEXT_FONT));
    mainLayout->addWidget(gameResultLabel, 0, Qt::AlignCenter);
}

void Ui_endGameScreen::onReturnButtonClicked()
{
    StateController::instance().navigate(ScreensNumber::CHOOSE_OPPONENT);
}
