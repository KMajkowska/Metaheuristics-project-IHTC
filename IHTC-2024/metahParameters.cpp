#include "metahParameters.h"

Ui_metahParameters::Ui_metahParameters(QWidget* parent) :
	QWidget(parent)
{
	_centralwidget = new QWidget();
	_maxIterationSlider = new QSlider(_centralwidget);
	_neighbourSizeDoubleSpinBox = new QDoubleSpinBox(_centralwidget);
	_increaseTempItersDoubleSpinBox = new QDoubleSpinBox(_centralwidget);
	_genderGroupIterDoubleSpinBox = new QDoubleSpinBox(_centralwidget);
	_neighbourGeneratorCombobox = new QComboBox(_centralwidget);
	_initSolverCombobox = new QComboBox(_centralwidget);
	_startingTemperatureSlider = new QSlider(_centralwidget);
	_simplexCoolingMulitplierDoubleSpinBox = new QDoubleSpinBox(_centralwidget);
	_stopTemperatureSlider = new QSlider(_centralwidget);
	_prizeSizeDoubleSpinBox = new QDoubleSpinBox(_centralwidget);
	_maxIterationLabel = new QLabel(_centralwidget);
	_neighbourSizeLabel = new QLabel(_centralwidget);
	_prizeSizeLabel = new QLabel(_centralwidget);
	_increaseTempIterLabel = new QLabel(_centralwidget);
	_genderGroupLabel = new QLabel(_centralwidget);
	_coolingMultiplier = new QLabel(_centralwidget);
	_startingTemperatureLabel = new QLabel(_centralwidget);
	_stopTemperatureLabel = new QLabel(_centralwidget);
	_initSolverLabel = new QLabel(_centralwidget);
	_neigbourGeneratorLabel = new QLabel(_centralwidget);
	_startGameButton = new QPushButton(_centralwidget);
	_minValueMaxIterationSliderLabel = new QLabel(_centralwidget);
	_maxValueMaxIterationSliderLabel = new QLabel(_centralwidget);
	_currentValueMaxIterationSliderLabel = new QLabel(_centralwidget);
	_minValueStartingTemperatureSliderLabel = new QLabel(_centralwidget);
	_maxValueStartingTemperatureSliderLabel = new QLabel(_centralwidget);
	_currentValueStartingTemperatureSliderLabel = new QLabel(_centralwidget);
	_minValueStopTemperatureSliderLabel = new QLabel(_centralwidget);
	_maxValueStopTemperatureSliderLabel = new QLabel(_centralwidget);
	_currentValueStopTemperatureSliderLabel = new QLabel(_centralwidget);
	_gridLayout = new QGridLayout(_centralwidget);
	_font = new QFont();

	connect(_maxIterationSlider, &QSlider::valueChanged, [this](int value) {
		_currentValueMaxIterationSliderLabel->setText(QString("Value: %1").arg(value));
		});

	connect(_startingTemperatureSlider, &QSlider::valueChanged, [this](int value) {
		_currentValueStartingTemperatureSliderLabel->setText(QString("Value: %1").arg(value));
		});

	connect(_stopTemperatureSlider, &QSlider::valueChanged, [this](int value) {
		_currentValueStopTemperatureSliderLabel->setText(QString("Value: %1").arg(value));
		});

	connect(_neighbourGeneratorCombobox, &QComboBox::currentTextChanged, this, &Ui_metahParameters::updatePrizeSizeDoubleSpinBox);

	connect(_maxIterationSlider, &QSlider::valueChanged, this, &Ui_metahParameters::updateStopTemperatureSlider);
	connect(_stopTemperatureSlider, &QSlider::valueChanged, this, &Ui_metahParameters::updateMaxIterationSlider);

	connect(_startGameButton, &QPushButton::clicked, this, &Ui_metahParameters::onStartGameButtonClicked);

	setupUi(this);
}

Ui_metahParameters::~Ui_metahParameters() = default;

void Ui_metahParameters::setupUi(QWidget* MainWindow)
{
	if (MainWindow->objectName().isEmpty())
	{
		MainWindow->setObjectName("MainWindow");
	}

	_centralwidget->setParent(MainWindow);
	_centralwidget->setObjectName("centralwidget");

	_gridLayout->setVerticalSpacing(10);
	int row = 0;

	// Max Iteration
	setUpMaxIterationLabel();
	setUpMaxIterationSlider();
	_gridLayout->addWidget(_maxIterationLabel, row, 0);
	_gridLayout->addWidget(_maxIterationSlider, row, 1);
	row += 2;

	// Neighbour Size
	setUpNeighbourSizeLabel();
	setUpNeighbourSizeDoubleSpinBox();
	_gridLayout->addWidget(_neighbourSizeLabel, row, 0);
	_gridLayout->addWidget(_neighbourSizeDoubleSpinBox, row, 1);
	row++;

	// Prize Size
	setUpPrizeSizeLabel();
	setUpPrizeSizeDoubleSpinBox();
	_gridLayout->addWidget(_prizeSizeLabel, row, 0);
	_gridLayout->addWidget(_prizeSizeDoubleSpinBox, row, 1);
	row++;

	// Increase Temp Iter
	setUpIncreaseTempIterLabel();
	setUpIncreaseTempItersDoubleSpinBox();
	_gridLayout->addWidget(_increaseTempIterLabel, row, 0);
	_gridLayout->addWidget(_increaseTempItersDoubleSpinBox, row, 1);
	row++;

	// Gender Group
	setUpGenderGroupLabel();
	setUpGenderGroupIterDoubleSpinBox();
	_gridLayout->addWidget(_genderGroupLabel, row, 0);
	_gridLayout->addWidget(_genderGroupIterDoubleSpinBox, row, 1);
	row++;

	// Cooling Multiplier
	setUpCoolingMultiplierLabel();
	setUpSimplexCoolingMultiplierDoubleSpinBox();
	_gridLayout->addWidget(_coolingMultiplier, row, 0);
	_gridLayout->addWidget(_simplexCoolingMulitplierDoubleSpinBox, row, 1);
	row++;

	// Starting Temperature
	setUpStartingTemperatureLabel();
	setUpStartingTemperatureSlider();
	_gridLayout->addWidget(_startingTemperatureLabel, row, 0);
	_gridLayout->addWidget(_startingTemperatureSlider, row, 1);
	row += 2;

	// Stop Temperature
	setUpStopTemperatureLabel();
	setUpStopTemperatureSlider();
	_gridLayout->addWidget(_stopTemperatureLabel, row, 0);
	_gridLayout->addWidget(_stopTemperatureSlider, row, 1);
	row += 2;

	// Init Solver
	setUpInitSolverLabel();
	setUpInitSolverCombobox();
	_gridLayout->addWidget(_initSolverLabel, row, 0);
	_gridLayout->addWidget(_initSolverCombobox, row, 1);
	row++;

	// Neighbour Generator
	setUpNeighbourGeneratorLabel();
	setUpNeighbourGeneratorCombobox();
	_gridLayout->addWidget(_neigbourGeneratorLabel, row, 0);
	_gridLayout->addWidget(_neighbourGeneratorCombobox, row, 1);
	row++;

	// Przycisk Start Game
	setUpStartGameButton();
	_gridLayout->addWidget(_startGameButton, row, 0, 1, 2, Qt::AlignCenter); // Przycisk zajmuje ca³¹ szerokoœæ

	MainWindow->setLayout(_gridLayout);

	retranslateUi(MainWindow);

	QMetaObject::connectSlotsByName(MainWindow);
}

void Ui_metahParameters::setUpStartGameButton()
{
	_startGameButton->setObjectName("startGameButton");
	_startGameButton->setStyleSheet("background-color: pink; color: black");
	_startGameButton->setFont(setUpFont(OTHER_COMPONENTS_FONT));
}

void Ui_metahParameters::setUpMaxIterationSlider()
{
	_maxIterationSlider->setObjectName("maxIterationCombobox");
	_maxIterationSlider->setOrientation(Qt::Horizontal);
	_maxIterationSlider->setRange(0, 2500);
	_maxIterationSlider->setTickInterval(10);
	_maxIterationSlider->setTracking(true);

	_gridLayout->setVerticalSpacing(10);

	_maxIterationSlider->setEnabled(false);
	_minValueMaxIterationSliderLabel->setText("Min: 0");
	_minValueMaxIterationSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
	_maxValueMaxIterationSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
	_currentValueMaxIterationSliderLabel->setFont(setUpFont(PARAMETERS_FONT_POINTS));
	_maxValueMaxIterationSliderLabel->setText("Max: 25000");

	_gridLayout->addWidget(_minValueMaxIterationSliderLabel, 1, 0);
	_gridLayout->addWidget(_maxIterationSlider, 0, 2);
	_gridLayout->addWidget(_maxValueMaxIterationSliderLabel, 0, 3);
	_gridLayout->addWidget(_currentValueMaxIterationSliderLabel, 1, 1);

	_currentValueMaxIterationSliderLabel->setText(QString("Value: %1").arg(_maxIterationSlider->value()));
}

void Ui_metahParameters::setUpNeighbourSizeDoubleSpinBox()
{
	_neighbourSizeDoubleSpinBox->setObjectName("nieghbourSizeCombobox");
	_neighbourSizeDoubleSpinBox->setDecimals(0);
	_neighbourSizeDoubleSpinBox->setSingleStep(1);
	_neighbourSizeDoubleSpinBox->setRange(1, 50);
	_neighbourSizeDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpPrizeSizeDoubleSpinBox()
{
	_prizeSizeDoubleSpinBox->setObjectName("prizeSizeCombobox");
	_prizeSizeDoubleSpinBox->setDecimals(0);
	_prizeSizeDoubleSpinBox->setSingleStep(1);
	_prizeSizeDoubleSpinBox->setRange(1, 10);
	_prizeSizeDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
	_prizeSizeDoubleSpinBox->setEnabled(false);
}

void Ui_metahParameters::setUpIncreaseTempItersDoubleSpinBox()
{
	_increaseTempItersDoubleSpinBox->setObjectName("increaseTempItersCombobox");
	_increaseTempItersDoubleSpinBox->setDecimals(0);
	_increaseTempItersDoubleSpinBox->setSingleStep(1);
	_increaseTempItersDoubleSpinBox->setRange(1, 1000);
	_increaseTempItersDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpGenderGroupIterDoubleSpinBox()
{
	_genderGroupIterDoubleSpinBox->setObjectName("genderGroupIterCombobox");
	_genderGroupIterDoubleSpinBox->setDecimals(0);
	_genderGroupIterDoubleSpinBox->setSingleStep(1);
	_genderGroupIterDoubleSpinBox->setRange(1, 1000);
	_genderGroupIterDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpSimplexCoolingMultiplierDoubleSpinBox()
{
	_simplexCoolingMulitplierDoubleSpinBox->setObjectName("simplexCoolingMulitplierCombobox");
	_simplexCoolingMulitplierDoubleSpinBox->setDecimals(3);
	_simplexCoolingMulitplierDoubleSpinBox->setSingleStep(0.001);
	_simplexCoolingMulitplierDoubleSpinBox->setRange(0.900, 0.999);
	_simplexCoolingMulitplierDoubleSpinBox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpNeighbourGeneratorCombobox()
{
	_neighbourGeneratorCombobox->setObjectName("neigbourGeneratorCombobox");
	for (int i = 0; i <= static_cast<int>(NeighbourGeneratorType::TOURNAMENT); ++i) {
		NeighbourGeneratorType mode = static_cast<NeighbourGeneratorType>(i);
		_neighbourGeneratorCombobox->addItem(QString::fromStdString(enumToString<NeighbourGeneratorType>(mode)), i);
	}
	_neighbourGeneratorCombobox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpStartingTemperatureSlider()
{
	_startingTemperatureSlider->setObjectName("startingTemperatureSlider");
	_startingTemperatureSlider->setOrientation(Qt::Horizontal);
	_startingTemperatureSlider->setRange(1, 100000);
	_startingTemperatureSlider->setTickInterval(1000);
	_startingTemperatureSlider->setTracking(true);

	_minValueStartingTemperatureSliderLabel->setText("Min: 0");
	_minValueStartingTemperatureSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
	_maxValueStartingTemperatureSliderLabel->setText("Max: 100000");
	_maxValueStartingTemperatureSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
	_currentValueStartingTemperatureSliderLabel->setFont(setUpFont(PARAMETERS_FONT_POINTS));

	_gridLayout->setVerticalSpacing(10);

	_gridLayout->addWidget(_minValueStartingTemperatureSliderLabel, 8, 0);
	_gridLayout->addWidget(_startingTemperatureSlider, 7, 2);
	_gridLayout->addWidget(_maxValueStartingTemperatureSliderLabel, 7, 3);
	_gridLayout->addWidget(_currentValueStartingTemperatureSliderLabel, 8, 1);

	_currentValueStartingTemperatureSliderLabel->setText(QString("Value: %1").arg(_stopTemperatureSlider->value()));

}

void Ui_metahParameters::setUpStopTemperatureSlider()
{
	_stopTemperatureSlider->setObjectName("stopTemperatureSlider");
	_stopTemperatureSlider->setOrientation(Qt::Horizontal);
	_stopTemperatureSlider->setRange(0, 10000);
	_stopTemperatureSlider->setTickInterval(100);
	_stopTemperatureSlider->setTracking(true);
	_stopTemperatureSlider->setEnabled(false);

	_gridLayout->setVerticalSpacing(10);

	_minValueStopTemperatureSliderLabel->setText("Min: 0");
	_minValueStopTemperatureSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
	_maxValueStopTemperatureSliderLabel->setText("Max: 10000");
	_maxValueStopTemperatureSliderLabel->setFont(setUpFont(SLIDER_LABELS_FONT));
	_currentValueStopTemperatureSliderLabel->setFont(setUpFont(PARAMETERS_FONT_POINTS));

	_gridLayout->addWidget(_minValueStopTemperatureSliderLabel, 10, 0);
	_gridLayout->addWidget(_stopTemperatureSlider, 9, 2);
	_gridLayout->addWidget(_maxValueStopTemperatureSliderLabel, 9, 3);
	_gridLayout->addWidget(_currentValueStopTemperatureSliderLabel, 10, 1);

	_currentValueStopTemperatureSliderLabel->setText(QString("Value: %1").arg(_stopTemperatureSlider->value()));
}

void Ui_metahParameters::setUpInitSolverCombobox()
{
	_initSolverCombobox->setObjectName("initSolverCombobox");

	_initSolverCombobox->addItem(QString::fromStdString(enumToString<SolverType>(SolverType::GREEDY)), 0);
	_initSolverCombobox->addItem(QString::fromStdString(enumToString<SolverType>(SolverType::RAND)), 1);

	_initSolverCombobox->setFont(setUpFont(PARAMETERS_FONT_POINTS));
}

void Ui_metahParameters::setUpMaxIterationLabel()
{
	_maxIterationLabel->setObjectName("maxIterationLabel");
	_maxIterationLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpNeighbourSizeLabel()
{
	_neighbourSizeLabel->setObjectName("neighbourSizeLabel");
	_neighbourSizeLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpPrizeSizeLabel()
{
	_prizeSizeLabel->setObjectName("prizeSizeLabel");
	_prizeSizeLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpIncreaseTempIterLabel()
{
	_increaseTempIterLabel->setObjectName("increaseTempIterLabel");
	_increaseTempIterLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpGenderGroupLabel()
{
	_genderGroupLabel->setObjectName("genderGroupLabel");
	_genderGroupLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpCoolingMultiplierLabel()
{
	_coolingMultiplier->setObjectName("coolingMultiplier");
	_coolingMultiplier->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpStartingTemperatureLabel()
{
	_startingTemperatureLabel->setObjectName("startingTemperatureLabel");
	_startingTemperatureLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpStopTemperatureLabel()
{
	_stopTemperatureLabel->setObjectName("stopTemperatureLabel");
	_stopTemperatureLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpInitSolverLabel()
{
	_initSolverLabel->setObjectName("initSolverLabel");
	_initSolverLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}

void Ui_metahParameters::setUpNeighbourGeneratorLabel()
{
	_neigbourGeneratorLabel->setObjectName("neigboutGeneratorLabel");
	_neigbourGeneratorLabel->setFont(setUpFont(LABEL_FONT_POINTS));
}


QFont Ui_metahParameters::setUpFont(int points)
{
	_font->setPointSize(points);
	return *_font;
}

void Ui_metahParameters::retranslateUi(QWidget* MainWindow)
{
	MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Choose metaheuristic parameters", nullptr));
	_maxIterationLabel->setText(QCoreApplication::translate("MainWindow", "Max Number of iterations", nullptr));
	_neighbourSizeLabel->setText(QCoreApplication::translate("MainWindow", "Neigbourhood size", nullptr));
	_prizeSizeLabel->setText(QCoreApplication::translate("MainWindow", "Prize size", nullptr));
	_increaseTempIterLabel->setText(QCoreApplication::translate("MainWindow", "No Cooling iteration", nullptr));
	_genderGroupLabel->setText(QCoreApplication::translate("MainWindow", "Gender Grouper iteration", nullptr));
	_coolingMultiplier->setText(QCoreApplication::translate("MainWindow", "Cooling Multiplier", nullptr));
	_startingTemperatureLabel->setText(QCoreApplication::translate("MainWindow", "Starting Temperature", nullptr));
	_stopTemperatureLabel->setText(QCoreApplication::translate("MainWindow", "Stop Temperature", nullptr));
	_initSolverLabel->setText(QCoreApplication::translate("MainWindow", "Init Solver", nullptr));
	_neigbourGeneratorLabel->setText(QCoreApplication::translate("MainWindow", "Neighbour generator", nullptr));
	_startGameButton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
}

void Ui_metahParameters::updatePrizeSizeDoubleSpinBox()
{
	if (_neighbourGeneratorCombobox->currentText() == enumToString<NeighbourGeneratorType>(NeighbourGeneratorType::PRIZE_BEST))
	{
		_prizeSizeDoubleSpinBox->setEnabled(true);
	}
	else
	{
		_prizeSizeDoubleSpinBox->setEnabled(false);
	}
}

void Ui_metahParameters::updateStopTemperatureSlider()
{
	if (_maxIterationSlider->value() != 0)
	{
		_stopTemperatureSlider->setValue(0);
		_stopTemperatureSlider->setEnabled(false);
	}
	else
	{
		_stopTemperatureSlider->setEnabled(true);
	}
}

void Ui_metahParameters::onStartGameButtonClicked()
{
	StateController::instance().allGameParameters().setGenderGroupIter(_genderGroupIterDoubleSpinBox->value());
	StateController::instance().allGameParameters().setMaxIteration(_maxIterationSlider->value());
	StateController::instance().allGameParameters().setStartingTemperature(_startingTemperatureSlider->value());
	StateController::instance().allGameParameters().setStopTemperature(_stopTemperatureSlider->value());
	StateController::instance().allGameParameters().setPrizeSize(_prizeSizeDoubleSpinBox->value());
	StateController::instance().allGameParameters().setCoolingMultiplier(_simplexCoolingMulitplierDoubleSpinBox->value());
	StateController::instance().allGameParameters().setIncreaseTempIters(_increaseTempItersDoubleSpinBox->value());
	StateController::instance().allGameParameters().setNeighbourSize(_neighbourSizeDoubleSpinBox->value());
	StateController::instance().allGameParameters().setInitSolver(stringToEnum<SolverType>(_initSolverCombobox->currentText().toStdString()));
	StateController::instance().allGameParameters().setNeighbourGenerator(stringToEnum<NeighbourGeneratorType>(_neighbourGeneratorCombobox->currentText().toStdString()));

	StateController::instance().startGame();
}

void Ui_metahParameters::setSlidersEnabled(const QString& value)
{
	if (value == enumToString(GameTimeValues::UNKNOWN))
	{
		_maxIterationSlider->setEnabled(true);
		_stopTemperatureSlider->setEnabled(true);
	}
}

void Ui_metahParameters::updateMaxIterationSlider()
{
	if (_stopTemperatureSlider->value() != 0)
	{
		_maxIterationSlider->setValue(0);
		_maxIterationSlider->setEnabled(false);
	}
	else
	{
		_maxIterationSlider->setEnabled(true);
	}
}
