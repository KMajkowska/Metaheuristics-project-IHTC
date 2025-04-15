#include "sessions.h"

Ui_sessions::Ui_sessions(QWidget* parent) : QWidget(parent)
{
    centralwidget = new QWidget();
    listOfSessions = new QListWidget(centralwidget);
    createSessionButton = new QPushButton(centralwidget);
    font = new QFont();
    layout = new QVBoxLayout(centralwidget);
    buttonLayout = new QHBoxLayout(centralwidget);
    listLayout = new QHBoxLayout(centralwidget);

    setupUi(this);
}

void Ui_sessions::setupUi(QWidget* MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName("MainWindow");

    centralwidget->setParent(MainWindow);

    setUpListOfSessions();
    setUpCreateSessionButton();

    connect(createSessionButton, &QPushButton::clicked, this, &Ui_sessions::onCreateSessionButtonClicked);

    layout->addLayout(listLayout);
    layout->addLayout(buttonLayout);

    MainWindow->setLayout(layout);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_sessions::setUpListOfSessions()
{
    listOfSessions->setObjectName("listWidget");
    listOfSessions->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listOfSessions->setMinimumHeight(700);
    listLayout->addWidget(listOfSessions, 0, Qt::AlignVCenter);
}

void Ui_sessions::setUpCreateSessionButton()
{
    createSessionButton->setObjectName("startGameButton");
    createSessionButton->setStyleSheet("background-color: pink; color: black");
    createSessionButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    buttonLayout->addWidget(createSessionButton, 0, Qt::AlignHCenter);
}

QFont Ui_sessions::setUpFont(int points)
{
    font->setPointSize(points);
    return *font;
}

void Ui_sessions::retranslateUi(QWidget* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Choose session", nullptr));
    createSessionButton->setText(QCoreApplication::translate("MainWindow", "Create own session", nullptr));
}

void Ui_sessions::onCreateSessionButtonClicked()
{
    StateController::instance().navigate(ScreensNumber::GAME_PARAMETERS);
}