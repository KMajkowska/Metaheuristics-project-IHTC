#include "gameParameters.h"

Ui_gameParameters::Ui_gameParameters(QWidget* parent) : 
    QWidget(parent)
{
    _centralwidget = new QWidget();
    _timeLabel = new QLabel(_centralwidget);
    _gameLevelLabel = new QLabel(_centralwidget);
    _winningModeLabel = new QLabel(_centralwidget);
    _inputParametersLevelLabel = new QLabel(_centralwidget);
    _roundNumberLabel = new QLabel(_centralwidget);

    _gameLevelComboBox = new QComboBox(_centralwidget);
    _winningModeComboBox = new QComboBox(_centralwidget);
    _gameTimeComboBox = new QComboBox(_centralwidget);
    _inputParametersLevelComboBox = new QComboBox(_centralwidget);
    _roundNumberDoubleSpinBox = new QDoubleSpinBox(_centralwidget);

    _readyButton = new QPushButton(_centralwidget);

    _font = new QFont();

    _mainLayout = new QVBoxLayout(_centralwidget);
    _gameTimeLayout = new QHBoxLayout(_centralwidget);
    _gameWinningModeLayout = new QHBoxLayout(_centralwidget);
    _gameLevelLayout = new QHBoxLayout(_centralwidget);
    _inputParametersLevelLayout = new QHBoxLayout(_centralwidget);
    _roundNumberLayout = new QHBoxLayout(_centralwidget);

    connect(_readyButton, &QPushButton::clicked, this, &Ui_gameParameters::onReadyButtonClicked);
    connect(_gameLevelComboBox, &QComboBox::currentTextChanged, this, &Ui_gameParameters::updateButtonState);
    connect(_winningModeComboBox, &QComboBox::currentTextChanged, this, &Ui_gameParameters::updateButtonState);
    connect(_inputParametersLevelComboBox, &QComboBox::currentTextChanged, this, &Ui_gameParameters::updateButtonState);

    setupUi(this);
}

Ui_gameParameters::~Ui_gameParameters() = default;

void Ui_gameParameters::setupUi(QWidget* MainWindow)
{
    if (MainWindow->objectName().isEmpty())
    {
        MainWindow->setObjectName("MainWindow");
    }

    _centralwidget->setParent(MainWindow);
    _centralwidget->setObjectName("centralwidget");

    setUpTimeLabel();
    setUpGameLevelLabel();
    setUpWinningModeLabel();
    setUpRoundNumberLabel();
    setUpInputParametersLevelLabel();
    setUpGameTimeCombobox();
    setUpGameLevelCombobox();
    setUpWinningModeCombobox();
    setUpInputParametersLevelCombobox();
    setUpRoundNumberDoubleSpinBox();
    setUpReadyButton();

    _mainLayout->addLayout(_gameTimeLayout);
    _mainLayout->addLayout(_gameLevelLayout);
    _mainLayout->addLayout(_gameWinningModeLayout);
    _mainLayout->addLayout(_inputParametersLevelLayout);
    _mainLayout->addLayout(_roundNumberLayout);

    _mainLayout->addWidget(_readyButton, 0, Qt::AlignHCenter);

    MainWindow->setLayout(_mainLayout);

    retranslateUi(this);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_gameParameters::setUpRoundNumberDoubleSpinBox()
{
    _roundNumberDoubleSpinBox->setObjectName("roudNumberDoubleSpinBox");
    _roundNumberDoubleSpinBox->setDecimals(0);
    _roundNumberDoubleSpinBox->setFixedWidth(261);
    _roundNumberDoubleSpinBox->setSingleStep(1);
    _roundNumberDoubleSpinBox->setRange(1, 15);
    _roundNumberDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    _roundNumberLayout->addWidget(_roundNumberDoubleSpinBox, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpInputParametersLevelLabel()
{
    _inputParametersLevelLabel->setObjectName("inputParametersLevelLabel");
    _inputParametersLevelLabel->setFont(setUpFont(LABEL_FONT_POINTS));
    _inputParametersLevelLayout->addWidget(_inputParametersLevelLabel, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpRoundNumberLabel()
{
    _roundNumberLabel->setObjectName("roundNumberLabel");
    _roundNumberLabel->setFont(setUpFont(LABEL_FONT_POINTS));
    _roundNumberLayout->addWidget(_roundNumberLabel, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpTimeLabel()
{
    _timeLabel->setObjectName("timeLabel");
    _timeLabel->setFont(setUpFont(LABEL_FONT_POINTS));
    _gameTimeLayout->addWidget(_timeLabel, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpGameLevelLabel()
{
    _gameLevelLabel->setObjectName("gameLevelLabel");
    _gameLevelLabel->setFont(setUpFont(LABEL_FONT_POINTS));
    _gameLevelLayout->addWidget(_gameLevelLabel, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpWinningModeLabel()
{
    _winningModeLabel->setObjectName("winningModeLabel");
    _winningModeLabel->setFont(setUpFont(LABEL_FONT_POINTS));
    _gameWinningModeLayout->addWidget(_winningModeLabel, 0, Qt::AlignCenter);
}


void Ui_gameParameters::setUpReadyButton()
{
    _readyButton->setObjectName("readyButton");
    _readyButton->setFixedSize(150, 100);
    _readyButton->setStyleSheet("background-color: pink; color: black");
    _readyButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
    _readyButton->setEnabled(false);
}

void Ui_gameParameters::setUpGameLevelCombobox()
{
    _gameLevelComboBox->setObjectName("gameLevelComboBox");
    _gameLevelComboBox->setFixedWidth(261);
    for (int i = 0; i <= static_cast<int>(GameLevel::HARD); ++i) {
        GameLevel level = static_cast<GameLevel>(i);
        _gameLevelComboBox->addItem(QString::fromStdString(enumToString(level)), i);
    }
    _gameLevelComboBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    _gameLevelLayout->addWidget(_gameLevelComboBox, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpInputParametersLevelCombobox()
{
    _inputParametersLevelComboBox->setObjectName("inputParametersLevelComboBox");
    _inputParametersLevelComboBox->setFixedWidth(261);
    for (int i = 0; i <= static_cast<int>(GameLevel::HARD); ++i) {
        GameLevel level = static_cast<GameLevel>(i);
        _inputParametersLevelComboBox->addItem(QString::fromStdString(enumToString(level)), i);
    }
    _inputParametersLevelComboBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    _inputParametersLevelLayout->addWidget(_inputParametersLevelComboBox, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpWinningModeCombobox()
{
    _winningModeComboBox->setObjectName("winningModeComboBox");
    _winningModeComboBox->setFixedWidth(261);
    for (int i = 0; i <= static_cast<int>(WinnerJudgeType::BEST_OF_N); ++i) {
        WinnerJudgeType mode = static_cast<WinnerJudgeType>(i);
        _winningModeComboBox->addItem(QString::fromStdString(enumToString<WinnerJudgeType>(mode)), i);
    }
    _winningModeComboBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    _gameWinningModeLayout->addWidget(_winningModeComboBox, 0, Qt::AlignCenter);
}

void Ui_gameParameters::setUpGameTimeCombobox()
{
    _gameTimeComboBox->setObjectName("gameTimeComboBox");
    _gameTimeComboBox->setFixedWidth(261);
    for (int i = 0; i <= static_cast<int>(GameTimeValues::_180); ++i) {
        GameTimeValues time = static_cast<GameTimeValues>(i);
        _gameTimeComboBox->addItem(QString::fromStdString(enumToString(time)), i);
    }
    _gameTimeComboBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    _gameTimeLayout->addWidget(_gameTimeComboBox, 0, Qt::AlignCenter);
}


void Ui_gameParameters::retranslateUi(QWidget* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Choose game parameters", nullptr));
    _timeLabel->setText(QCoreApplication::translate("MainWindow", "Time of the game", nullptr));
    _gameLevelLabel->setText(QCoreApplication::translate("MainWindow", "Difficulty of the input data", nullptr));
    _winningModeLabel->setText(QCoreApplication::translate("MainWindow", "Winning mode", nullptr));
    _inputParametersLevelLabel->setText(QCoreApplication::translate("MainWindow", "Input parameters level", nullptr));
    _roundNumberLabel->setText(QCoreApplication::translate("MainWindow", "Round number", nullptr));
    _readyButton->setText(QCoreApplication::translate("MainWindow", "Ready!", nullptr));
} 

QFont Ui_gameParameters::setUpFont(int points)
{
    _font->setPointSize(points);
    return *_font;
};

void Ui_gameParameters::onReadyButtonClicked()
{
    static_cast<Ui_metahParameters*>(StateController::instance().screens()[ScreensNumber::METAH_PARAMETERS])->setSlidersEnabled(_gameTimeComboBox->currentText());
    StateController::instance().allGameParameters().setGameLevel(stringToEnum<GameLevel>(_gameLevelComboBox->currentText()));
    StateController::instance().allGameParameters().setGameTime(toInt(_gameTimeComboBox->currentText()));
    StateController::instance().allGameParameters().setJudgeType(stringToEnum<WinnerJudgeType>(_winningModeComboBox->currentText()));
    StateController::instance().allGameParameters().setRoundNumber(_roundNumberDoubleSpinBox->value());
    StateController::instance().allGameParameters().setInputParametersLevel(stringToEnum<GameLevel>(_inputParametersLevelComboBox->currentText()));

    StateController::instance().navigate(ScreensNumber::METAH_PARAMETERS);
}

void Ui_gameParameters::updateButtonState()
{
    if (_winningModeComboBox->currentText() != QString::fromStdString(enumToString(GameTimeValues::UNKNOWN)) && 
        _gameLevelComboBox->currentText() != QString::fromStdString(enumToString(GameLevel::UNKNOWN)) &&
        _inputParametersLevelComboBox->currentText() != QString::fromStdString(enumToString(GameLevel::UNKNOWN)))
    {
        _readyButton->setEnabled(true); 
    }
    else 
    {
        _readyButton->setEnabled(false);  
    }
}