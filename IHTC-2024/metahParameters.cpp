#include "metahParameters.h"

void Ui_metahParameters::setupUi(QWidget* MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName("MainWindow");
    centralwidget->setParent(MainWindow);
    centralwidget->setObjectName("centralwidget");

    gridLayout->setVerticalSpacing(10);
    int row = 0;

    // Max Iteration
    setUpMaxIterationLabel();
    setUpMaxIterationSlider();
    gridLayout->addWidget(maxIterationLabel, row, 0);
    gridLayout->addWidget(maxIterationSlider, row, 1);
    row+=2;

    // Neighbour Size
    setUpNeighbourSizeLabel();
    setUpNeighbourSizeDoubleSpinBox();
    gridLayout->addWidget(neighbourSizeLabel, row, 0);
    gridLayout->addWidget(neighbourSizeDoubleSpinBox, row, 1);
    row++;

    // Prize Size
    setUpPrizeSizeLabel();
    setUpPrizeSizeDoubleSpinBox();
    gridLayout->addWidget(prizeSizeLabel, row, 0);
    gridLayout->addWidget(prizeSizeDoubleSpinBox, row, 1);
    row++;

    // Increase Temp Iter
    setUpIncreaseTempIterLabel();
    setUpIncreaseTempItersDoubleSpinBox();
    gridLayout->addWidget(increaseTempIterLabel, row, 0);
    gridLayout->addWidget(increaseTempItersDoubleSpinBox, row, 1);
    row++;

    // Gender Group
    setUpGenderGroupLabel();
    setUpGenderGroupIterDoubleSpinBox();
    gridLayout->addWidget(genderGroupLabel, row, 0);
    gridLayout->addWidget(genderGroupIterDoubleSpinBox, row, 1);
    row++;

    // Cooling Multiplier
    setUpCoolingMultiplierLabel();
    setUpSimplexCoolingMultiplierDoubleSpinBox();
    gridLayout->addWidget(coolingMultiplier, row, 0);
    gridLayout->addWidget(simplexCoolingMulitplierDoubleSpinBox, row, 1);
    row++;

    // Starting Temperature
    setUpStartingTemperatureLabel();
    setUpStartingTemperatureSlider();
    gridLayout->addWidget(startingTemperatureLabel, row, 0);
    gridLayout->addWidget(startingTemperatureSlider, row, 1);
    row+=2;

    // Stop Temperature
    setUpStopTemperatureLabel();
    setUpStopTemperatureSlider();
    gridLayout->addWidget(stopTemperatureLabel, row, 0);
    gridLayout->addWidget(stopTemperatureSlider, row, 1);
    row+=2;

    // Init Solver
    setUpInitSolverLabel();
    setUpInitSolverCombobox();
    gridLayout->addWidget(initSolverLabel, row, 0);
    gridLayout->addWidget(initSolverCombobox, row, 1);
    row++;

    // Neighbour Generator
    setUpNeighbourGeneratorLabel();
    setUpNeighbourGeneratorCombobox();
    gridLayout->addWidget(neigbourGeneratorLabel, row, 0);
    gridLayout->addWidget(neighbourGeneratorCombobox, row, 1);
    row++;

    // Przycisk Start Game
    setUpStartGameButton();
    gridLayout->addWidget(startGameButton, row, 0, 1, 2, Qt::AlignCenter); // Przycisk zajmuje ca³¹ szerokoœæ

    MainWindow->setLayout(gridLayout);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
}

//Parametry
void Ui_metahParameters::setUpStartGameButton()
{
    startGameButton->setObjectName("startGameButton");
    startGameButton->setStyleSheet("background-color: pink; color: black");
    startGameButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
}

void Ui_metahParameters::setUpMaxIterationSlider()
{
    maxIterationSlider->setObjectName("maxIterationCombobox");
    maxIterationSlider->setOrientation(Qt::Horizontal); 
    maxIterationSlider->setRange(0, 2500);  
    maxIterationSlider->setTickInterval(10);  
    maxIterationSlider->setTracking(true);  

    gridLayout->setVerticalSpacing(10);

    maxIterationSlider->setEnabled(false);
    minValueMaxIterationSliderLabel->setText("Min: 0");
    minValueMaxIterationSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
    maxValueMaxIterationSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
    currentValueMaxIterationSliderLabel->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    maxValueMaxIterationSliderLabel->setText("Max: 25000");
  
    gridLayout->addWidget(minValueMaxIterationSliderLabel, 1, 0);
    gridLayout->addWidget(maxIterationSlider, 0, 2);
    gridLayout->addWidget(maxValueMaxIterationSliderLabel, 0, 3);
    gridLayout->addWidget(currentValueMaxIterationSliderLabel, 1, 1);

    currentValueMaxIterationSliderLabel->setText(QString("Value: %1").arg(maxIterationSlider->value()));
}


void Ui_metahParameters::setUpNeighbourSizeDoubleSpinBox()
{
    neighbourSizeDoubleSpinBox->setObjectName("nieghbourSizeCombobox");
    neighbourSizeDoubleSpinBox->setDecimals(0);
    neighbourSizeDoubleSpinBox->setSingleStep(1);
    neighbourSizeDoubleSpinBox->setRange(1, 50);
    neighbourSizeDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpPrizeSizeDoubleSpinBox()
{
    prizeSizeDoubleSpinBox->setObjectName("prizeSizeCombobox");
    prizeSizeDoubleSpinBox->setDecimals(0);
    prizeSizeDoubleSpinBox->setSingleStep(1);
    prizeSizeDoubleSpinBox->setRange(1, 10);
    prizeSizeDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
    prizeSizeDoubleSpinBox->setEnabled(false);
}

void Ui_metahParameters::setUpIncreaseTempItersDoubleSpinBox()
{
    increaseTempItersDoubleSpinBox->setObjectName("increaseTempItersCombobox");
    increaseTempItersDoubleSpinBox->setDecimals(0);
    increaseTempItersDoubleSpinBox->setSingleStep(1);
    increaseTempItersDoubleSpinBox->setRange(1, 1000);
    increaseTempItersDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpGenderGroupIterDoubleSpinBox()
{
    genderGroupIterDoubleSpinBox->setObjectName("genderGroupIterCombobox");
    genderGroupIterDoubleSpinBox->setDecimals(0);
    genderGroupIterDoubleSpinBox->setSingleStep(1);
    genderGroupIterDoubleSpinBox->setRange(1, 1000);
    genderGroupIterDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpSimplexCoolingMultiplierDoubleSpinBox()
{
    simplexCoolingMulitplierDoubleSpinBox->setObjectName("simplexCoolingMulitplierCombobox");
    simplexCoolingMulitplierDoubleSpinBox->setDecimals(3);
    simplexCoolingMulitplierDoubleSpinBox->setSingleStep(0.001);
    simplexCoolingMulitplierDoubleSpinBox->setRange(0.900, 0.999);
    simplexCoolingMulitplierDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpNeighbourGeneratorCombobox()
{
    neighbourGeneratorCombobox->setObjectName("neigbourGeneratorCombobox");
    for (int i = 0; i <= static_cast<int>(NeighbourGeneratorType::TOURNAMENT); ++i) {
        NeighbourGeneratorType mode = static_cast<NeighbourGeneratorType>(i);
        neighbourGeneratorCombobox->addItem(QString::fromStdString(enumToString<NeighbourGeneratorType>(mode)), i);
    }
    neighbourGeneratorCombobox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpStartingTemperatureSlider()
{
    startingTemperatureSlider->setObjectName("startingTemperatureSlider");
    startingTemperatureSlider->setOrientation(Qt::Horizontal);  
    startingTemperatureSlider->setRange(1, 100000);  
    startingTemperatureSlider->setTickInterval(1000);  
    startingTemperatureSlider->setTracking(true);

    minValueStartingTemperatureSliderLabel->setText("Min: 0");
    minValueStartingTemperatureSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
    maxValueStartingTemperatureSliderLabel->setText("Max: 100000");
    maxValueStartingTemperatureSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
    currentValueStartingTemperatureSliderLabel->setFont(setUpFont(PARAMETERS_FONT_POINTS));

    gridLayout->setVerticalSpacing(10);

    gridLayout->addWidget(minValueStartingTemperatureSliderLabel, 8, 0);
    gridLayout->addWidget(startingTemperatureSlider, 7, 2);
    gridLayout->addWidget(maxValueStartingTemperatureSliderLabel, 7, 3);
    gridLayout->addWidget(currentValueStartingTemperatureSliderLabel, 8, 1);

    currentValueStartingTemperatureSliderLabel->setText(QString("Value: %1").arg(stopTemperatureSlider->value()));

}
void Ui_metahParameters::setUpStopTemperatureSlider()
{
    stopTemperatureSlider->setObjectName("stopTemperatureSlider");
    stopTemperatureSlider->setOrientation(Qt::Horizontal);
    stopTemperatureSlider->setRange(0, 10000);
    stopTemperatureSlider->setTickInterval(100);
    stopTemperatureSlider->setTracking(true);
    stopTemperatureSlider->setEnabled(false);

    gridLayout->setVerticalSpacing(10);

    minValueStopTemperatureSliderLabel->setText("Min: 0");
    minValueStopTemperatureSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
    maxValueStopTemperatureSliderLabel->setText("Max: 10000");
    maxValueStopTemperatureSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
    currentValueStopTemperatureSliderLabel->setFont(setUpFont(PARAMETERS_FONT_POINTS));

    gridLayout->addWidget(minValueStopTemperatureSliderLabel, 10, 0); 
    gridLayout->addWidget(stopTemperatureSlider, 9, 2); 
    gridLayout->addWidget(maxValueStopTemperatureSliderLabel, 9, 3); 
    gridLayout->addWidget(currentValueStopTemperatureSliderLabel, 10, 1); 

    currentValueStopTemperatureSliderLabel->setText(QString("Value: %1").arg(stopTemperatureSlider->value()));
}


void Ui_metahParameters::setUpInitSolverCombobox()
{
    initSolverCombobox->setObjectName("initSolverCombobox");
    for (int i = 0; i <= static_cast<int>(SolverType::GREEDY); ++i) {
        SolverType mode = static_cast<SolverType>(i);
        initSolverCombobox->addItem(QString::fromStdString(enumToString<SolverType>(mode)), i);
    }
    initSolverCombobox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}


// Labelki
void Ui_metahParameters::setUpMaxIterationLabel()
{
    maxIterationLabel->setObjectName("maxIterationLabel");
    maxIterationLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpNeighbourSizeLabel()
{
    neighbourSizeLabel->setObjectName("neighbourSizeLabel");
    neighbourSizeLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpPrizeSizeLabel()
{
    prizeSizeLabel->setObjectName("prizeSizeLabel");
    prizeSizeLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpIncreaseTempIterLabel()
{
    increaseTempIterLabel->setObjectName("increaseTempIterLabel");
    increaseTempIterLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpGenderGroupLabel()
{
    genderGroupLabel->setObjectName("genderGroupLabel");
    genderGroupLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpCoolingMultiplierLabel()
{
    coolingMultiplier->setObjectName("coolingMultiplier");
    coolingMultiplier->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpStartingTemperatureLabel()
{
    startingTemperatureLabel->setObjectName("startingTemperatureLabel");
    startingTemperatureLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpStopTemperatureLabel()
{
    stopTemperatureLabel->setObjectName("stopTemperatureLabel");
    stopTemperatureLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpInitSolverLabel()
{
    initSolverLabel->setObjectName("initSolverLabel");
    initSolverLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpNeighbourGeneratorLabel()
{
    neigbourGeneratorLabel->setObjectName("neigboutGeneratorLabel");
    neigbourGeneratorLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}


QFont Ui_metahParameters::setUpFont(int points)
{
    font->setPointSize(points);
    return *font;
}

void Ui_metahParameters::retranslateUi(QWidget* MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Choose metaheuristic parameters", nullptr));
    maxIterationLabel->setText(QCoreApplication::translate("MainWindow", "Max Number of iterations", nullptr));
    neighbourSizeLabel->setText(QCoreApplication::translate("MainWindow", "Neigbourhood size", nullptr));
    prizeSizeLabel->setText(QCoreApplication::translate("MainWindow", "Prize size", nullptr));
    increaseTempIterLabel->setText(QCoreApplication::translate("MainWindow", "No Cooling iteration", nullptr));
    genderGroupLabel->setText(QCoreApplication::translate("MainWindow", "Gender Grouper iteration", nullptr));
    coolingMultiplier->setText(QCoreApplication::translate("MainWindow", "Cooling Multiplier", nullptr));
    startingTemperatureLabel->setText(QCoreApplication::translate("MainWindow", "Starting Temperature", nullptr));
    stopTemperatureLabel->setText(QCoreApplication::translate("MainWindow", "Stop Temperature", nullptr));
    initSolverLabel->setText(QCoreApplication::translate("MainWindow", "Init Solver", nullptr));
    neigbourGeneratorLabel->setText(QCoreApplication::translate("MainWindow", "Neighbour generator", nullptr));
    startGameButton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
}

Ui_metahParameters::Ui_metahParameters(QWidget* parent) : QWidget(parent)
{
    centralwidget = new QWidget();
    maxIterationSlider = new QSlider(centralwidget);
    neighbourSizeDoubleSpinBox = new QDoubleSpinBox(centralwidget);
    increaseTempItersDoubleSpinBox = new QDoubleSpinBox(centralwidget);
    genderGroupIterDoubleSpinBox = new QDoubleSpinBox(centralwidget);
    neighbourGeneratorCombobox = new QComboBox(centralwidget);
    initSolverCombobox = new QComboBox(centralwidget);
    startingTemperatureSlider = new QSlider(centralwidget);
    simplexCoolingMulitplierDoubleSpinBox = new QDoubleSpinBox(centralwidget);
    stopTemperatureSlider = new QSlider(centralwidget);
    prizeSizeDoubleSpinBox = new QDoubleSpinBox(centralwidget);
    maxIterationLabel = new QLabel(centralwidget);
    neighbourSizeLabel = new QLabel(centralwidget);
    prizeSizeLabel = new QLabel(centralwidget);
    increaseTempIterLabel = new QLabel(centralwidget);
    genderGroupLabel = new QLabel(centralwidget);
    coolingMultiplier = new QLabel(centralwidget);
    startingTemperatureLabel = new QLabel(centralwidget);
    stopTemperatureLabel = new QLabel(centralwidget);
    initSolverLabel = new QLabel(centralwidget);
    neigbourGeneratorLabel = new QLabel(centralwidget);
    startGameButton = new QPushButton(centralwidget);
    minValueMaxIterationSliderLabel = new QLabel(centralwidget);
    maxValueMaxIterationSliderLabel = new QLabel(centralwidget);
    currentValueMaxIterationSliderLabel = new QLabel(centralwidget);
    minValueStartingTemperatureSliderLabel = new QLabel(centralwidget);
    maxValueStartingTemperatureSliderLabel = new QLabel(centralwidget);
    currentValueStartingTemperatureSliderLabel = new QLabel(centralwidget);
    minValueStopTemperatureSliderLabel = new QLabel(centralwidget);
    maxValueStopTemperatureSliderLabel = new QLabel(centralwidget);
    currentValueStopTemperatureSliderLabel = new QLabel(centralwidget);
    gridLayout = new QGridLayout(centralwidget);
    font = new QFont();

    connect(maxIterationSlider, &QSlider::valueChanged, [this](int value) {
        currentValueMaxIterationSliderLabel->setText(QString("Value: %1").arg(value));
    });

    connect(startingTemperatureSlider, &QSlider::valueChanged, [this](int value) {
        currentValueStartingTemperatureSliderLabel->setText(QString("Value: %1").arg(value));
        });

    connect(stopTemperatureSlider, &QSlider::valueChanged, [this](int value) {
        currentValueStopTemperatureSliderLabel->setText(QString("Value: %1").arg(value));
        });

    connect(neighbourGeneratorCombobox, &QComboBox::currentTextChanged, this, &Ui_metahParameters::updatePrizeSizeDoubleSpinBox);
    
    connect(maxIterationSlider, &QSlider::valueChanged, this, &Ui_metahParameters::updateStopTemperatureSlider);
    connect(stopTemperatureSlider, &QSlider::valueChanged, this, &Ui_metahParameters::updateMaxIterationSlider);

    connect(startGameButton, &QPushButton::clicked, this, &Ui_metahParameters::onStartGameButtonClicked);

    setupUi(this);
}

void Ui_metahParameters::updatePrizeSizeDoubleSpinBox()
{
    if (neighbourGeneratorCombobox->currentText() == enumToString<NeighbourGeneratorType>(NeighbourGeneratorType::PRIZE_BEST))
    {
        prizeSizeDoubleSpinBox->setEnabled(true);
    }
    else
    {
        prizeSizeDoubleSpinBox->setEnabled(false);
    }
}

void Ui_metahParameters::updateStopTemperatureSlider()
{
    if (maxIterationSlider->value() != 0)
    {
        stopTemperatureSlider->setValue(0);
        stopTemperatureSlider->setEnabled(false);
    }
    else
    {
        stopTemperatureSlider->setEnabled(true);
    }
}

void Ui_metahParameters::onStartGameButtonClicked()
{
    StateController::instance().allGameParameters().setGenderGroupIter(genderGroupIterDoubleSpinBox->value());
    StateController::instance().allGameParameters().setMaxIteration(maxIterationSlider->value());
    StateController::instance().allGameParameters().setStartingTemperature(startingTemperatureSlider->value());
    StateController::instance().allGameParameters().setStartingTemperature(startingTemperatureSlider->value());
    StateController::instance().allGameParameters().setStopTemperature(stopTemperatureSlider->value());
    StateController::instance().allGameParameters().setPrizeSize(prizeSizeDoubleSpinBox->value());
    StateController::instance().allGameParameters().setCoolingMultiplier(simplexCoolingMulitplierDoubleSpinBox->value());
    StateController::instance().allGameParameters().setIncreaseTempIters(increaseTempItersDoubleSpinBox->value());
    StateController::instance().allGameParameters().setNeighbourSize(neighbourSizeDoubleSpinBox->value());
    StateController::instance().allGameParameters().setNeighbourGenerator(stringToEnum<NeighbourGeneratorType>(neighbourGeneratorCombobox->currentText().toStdString()));

    if (StateController::instance().allGameParameters().isPlayerOpponent()) {

        StateController::instance().createSession(StateController::instance().allGameParameters());
        StateController::instance().navigate(ScreensNumber::WAITING_SCREEN);
    }
    else
    {
        StateController::instance().navigate(ScreensNumber::WAITING_SCREEN);

        StateController::instance().runComputer([]()
            {
                StateController::instance().navigate(ScreensNumber::WELCOME_SCREEN);
            });
    }
}

void Ui_metahParameters::setSlidersEnabled(const QString& value)
{
    if (value == enumToString(GameTimeValues::UNKNOWN))
    {
        maxIterationSlider->setEnabled(true);
        stopTemperatureSlider->setEnabled(true);
    }
}

void Ui_metahParameters::updateMaxIterationSlider()
{
    if (stopTemperatureSlider->value() != 0)
    {
        maxIterationSlider->setValue(0);
        maxIterationSlider->setEnabled(false);
    }
    else
    {       
        maxIterationSlider->setEnabled(true);
    }
}
