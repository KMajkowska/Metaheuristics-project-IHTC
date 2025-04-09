#include "gameParameters.h"

void Ui_gameParameters::setupUi(QWidget* MainWindow) {
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName("MainWindow");

    centralwidget->setParent(MainWindow);
    centralwidget->setObjectName("centralwidget");
    
    setUpTimeLabel();
    setUpGameLevelLabel();
    setUpWinningModeLabel();
    setUpRoundNumberLabel();
    setUpGameTimeCombobox();
    setUpGameLevelCombobox();
    setUpWinningModeCombobox();
    setUpRoundNumberDoubleSpinBox();
    setUpReadyButton();

    mainLayout->addLayout(gameTimeLayout);
    mainLayout->addLayout(gameLevelLayout);
    mainLayout->addLayout(gameWinningModeLayout);
    mainLayout->addLayout(roundNumberLayout);

    mainLayout->addWidget(readyButton, 0, Qt::AlignHCenter);

    MainWindow->setLayout(mainLayout);

    retranslateUi(this);

    QMetaObject::connectSlotsByName(MainWindow);
}

Ui_gameParameters::Ui_gameParameters(QStackedWidget* stackedWidget, QWidget* parent, std::shared_ptr<AllGameParameters> allGameParameters) : 
    QWidget(parent),
    stackedWidget(stackedWidget),
    allGameParameters(allGameParameters)
{
    centralwidget = new QWidget();
    timeLabel = new QLabel(centralwidget);
    gameLevelLabel = new QLabel(centralwidget);
    winningModeLabel = new QLabel(centralwidget);
    roundNumberLabel = new QLabel(centralwidget);

    gameLevelComboBox = new QComboBox(centralwidget);
    winningModeComboBox = new QComboBox(centralwidget);
    gameTimeComboBox = new QComboBox(centralwidget);
    roudNumberDoubleSpinBox = new QDoubleSpinBox(centralwidget);

    readyButton = new QPushButton(centralwidget);

    font = new QFont();

    mainLayout = new QVBoxLayout(centralwidget);
    gameTimeLayout = new QHBoxLayout(centralwidget);
    gameWinningModeLayout = new QHBoxLayout(centralwidget);
    gameLevelLayout = new QHBoxLayout(centralwidget);
    roundNumberLayout = new QHBoxLayout(centralwidget);

    connect(readyButton, &QPushButton::clicked, this, &Ui_gameParameters::onReadyButtonClicked);
    connect(gameLevelComboBox, &QComboBox::currentTextChanged, this, &Ui_gameParameters::updateButtonState);
    connect(winningModeComboBox, &QComboBox::currentTextChanged, this, &Ui_gameParameters::updateButtonState);

    setupUi(this);

}

void Ui_gameParameters::setUpRoundNumberDoubleSpinBox()
{
    roudNumberDoubleSpinBox->setObjectName("roudNumberDoubleSpinBox");
    roudNumberDoubleSpinBox->setDecimals(0);
    roudNumberDoubleSpinBox->setSingleStep(1);
    roudNumberDoubleSpinBox->setRange(1, 15);
    roudNumberDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    roundNumberLayout->addWidget(roudNumberDoubleSpinBox, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpRoundNumberLabel()
{
    roundNumberLabel->setObjectName("roundNumberLabel");
    roundNumberLabel->setFont(setUpFont(LABEL_FONT_POINTS));
    roundNumberLayout->addWidget(roundNumberLabel, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpTimeLabel()
{
    timeLabel->setObjectName("timeLabel");
    timeLabel->setFont(setUpFont(LABEL_FONT_POINTS));
    gameTimeLayout->addWidget(timeLabel, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpGameLevelLabel()
{
    gameLevelLabel->setObjectName("gameLevelLabel");
    gameLevelLabel->setFont(setUpFont(LABEL_FONT_POINTS));
    gameLevelLayout->addWidget(gameLevelLabel, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpWinningModeLabel()
{
    winningModeLabel->setObjectName("winningModeLabel");
    winningModeLabel->setFont(setUpFont(LABEL_FONT_POINTS));
    gameWinningModeLayout->addWidget(winningModeLabel, 0, Qt::AlignCenter);
}


void Ui_gameParameters::setUpReadyButton()
{
    readyButton->setObjectName("readyButton");
    readyButton->setFixedSize(150, 100);
    readyButton->setStyleSheet("background-color: pink; color: black");
    readyButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    readyButton->setEnabled(false);
}

void Ui_gameParameters::setUpGameLevelCombobox()
{
    gameLevelComboBox->setObjectName("gameLevelComboBox");
    gameLevelComboBox->setFixedWidth(261);
    for (int i = 0; i <= static_cast<int>(GameLevel::HARD); ++i) {
        GameLevel level = static_cast<GameLevel>(i);
        gameLevelComboBox->addItem(QString::fromStdString(enumToString(level)), i);
    }
    gameLevelComboBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    gameLevelLayout->addWidget(gameLevelComboBox, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpWinningModeCombobox()
{
    winningModeComboBox->setObjectName("winningModeComboBox");
    winningModeComboBox->setFixedWidth(261);
    for (int i = 0; i <= static_cast<int>(WinnerJudgeType::BEST_OF_N); ++i) {
        WinnerJudgeType mode = static_cast<WinnerJudgeType>(i);
        winningModeComboBox->addItem(QString::fromStdString(enumToString<WinnerJudgeType>(mode)), i);
    }
    winningModeComboBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    gameWinningModeLayout->addWidget(winningModeComboBox, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpGameTimeCombobox()
{
    gameTimeComboBox->setObjectName("gameTimeComboBox");
    gameTimeComboBox->setFixedWidth(261);
    for (int i = 0; i <= static_cast<int>(GameTimeValues::_180); ++i) {
        GameTimeValues time = static_cast<GameTimeValues>(i);
        gameTimeComboBox->addItem(QString::fromStdString(enumToString(time)), i);
    }
    gameTimeComboBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    gameTimeLayout->addWidget(gameTimeComboBox, 0, Qt::AlignCenter);
}


void Ui_gameParameters::retranslateUi(QWidget* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Choose game parameters", nullptr));
    timeLabel->setText(QCoreApplication::translate("MainWindow", "Time of the game", nullptr));
    gameLevelLabel->setText(QCoreApplication::translate("MainWindow", "Difficulty of the input data", nullptr));
    winningModeLabel->setText(QCoreApplication::translate("MainWindow", "Winning mode", nullptr));
    roundNumberLabel->setText(QCoreApplication::translate("MainWindow", "Round number", nullptr));
    readyButton->setText(QCoreApplication::translate("MainWindow", "Ready!", nullptr));
} 

QFont Ui_gameParameters::setUpFont(int points)
{
    font->setPointSize(points);
    return *font;
};

void Ui_gameParameters::onReadyButtonClicked()
{
    allGameParameters->setGameLevel(stringToEnum<GameLevel>(gameLevelComboBox->currentText()));
    allGameParameters->setGameTime(toInt(gameTimeComboBox->currentText()));
    allGameParameters->setJudgeType(stringToEnum<WinnerJudgeType>(winningModeComboBox->currentText()));
    allGameParameters->setRoundNumber(roudNumberDoubleSpinBox->value());

    Ui_metahParameters* metahParameters = new Ui_metahParameters(stackedWidget, this, allGameParameters);
    stackedWidget->addWidget(metahParameters);
    metahParameters->setSliderEnabled(gameTimeComboBox->currentText());
    stackedWidget->setCurrentIndex(static_cast<int>(ScreensNumber::METAH_PARAMETERS));
}

void Ui_gameParameters::updateButtonState()
{
    if (winningModeComboBox->currentText() != QString::fromStdString(enumToString(GameTimeValues::UNKNOWN)) && 
        gameLevelComboBox->currentText() != QString::fromStdString(enumToString(GameTimeValues::UNKNOWN)))
    {
        readyButton->setEnabled(true); 
    }
    else 
    {
        readyButton->setEnabled(false);  
    }
}