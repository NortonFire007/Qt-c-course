#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(440, 175);
    this->setMaximumSize(440, 175);
    clear = new QPushButton("Clear", this);
    clear->move(330, 130);
    clear->setFixedSize(85, 30);

    convert = new QPushButton("Convert", this);
    convert->move(235, 130);
    convert->setFixedSize(90, 30);

    intValidator = new QIntValidator(this);
    doubleValidator = new QDoubleValidator(this);

    input = new QLineEdit(this);
    input->setMinimumSize(132, 21);
    input->setMaximumSize(132, 21);
    input->setValidator(doubleValidator);
    input->move(20, 15);

    output = new QLineEdit(this);
    //output->setAutoFillBackground(false);
    //output->setAttribute(Qt::WA_NoSystemBackground);
    //output->setAttribute(Qt::WA_TranslucentBackground);
    //output->setStyleSheet("background-color: rgba(15, 8, 45, 10);");
    output->setMinimumSize(132, 21);
    output->setMaximumSize(132, 21);
    output->setValidator(doubleValidator);
    output->move(235, 15);
    output->setReadOnly(true);


    comboBox1 = new QComboBox(this);
    comboBox1->setMinimumSize(15, 15);
    comboBox1->move(155, 15);


    comboBox2 = new QComboBox(this);
    comboBox2->setMinimumSize(15, 15);
    comboBox2->move(370, 15);

    textSize = new QSpinBox(this);
    textSize->setMinimumSize(40, 24);
    textSize->move(295, 44);
    textSize->setMinimum(3);
    textSize->setMaximum(15);
    textSize->setSingleStep(3);
    textSize->setValue(9);


    radioBtnGroupTColor = new QGroupBox("Text color", this);
    radioBtnGroupTColor->move(20, 40);

    //radioVBoxTColor = new QVBoxLayout(radioBtnGroupTColor);
    radioHBoxTColor = new QHBoxLayout(radioBtnGroupTColor);

    for (int i = 0; i < 3; ++i) {
        radioButtonsTColor[i] = new QRadioButton(btnTextColorLabels[i], this);
        radioHBoxTColor->addWidget(radioButtonsTColor[i]);

        connect(radioButtonsTColor[i], SIGNAL(toggled(bool)), this, SLOT(changeTextColor()));
    }

    radioButtonsTColor[1]->setChecked(true);
    radioBtnGroupTColor->setMaximumWidth(180);
    radioBtnGroupTColor->setLayout(radioHBoxTColor);

    radioBtnGroupBgColor = new QGroupBox("Background color", this);
    radioBtnGroupBgColor->move(20, 105);

    radioHBoxBgColor = new QHBoxLayout(radioBtnGroupBgColor);

    for (int i = 0; i < 3; ++i) {
        radioButtonsBgColor[i] = new QRadioButton(btnBgLabels[i], this);
        radioHBoxBgColor->addWidget(radioButtonsBgColor[i]);

        connect(radioButtonsBgColor[i], SIGNAL(toggled(bool)), this, SLOT(changeBackgroundColor()));
    }
    radioButtonsBgColor[0]->setChecked(true);
    radioBtnGroupBgColor->setMaximumWidth(180);
    radioBtnGroupBgColor->setLayout(radioHBoxBgColor);


    radioBtnGroupDimensions = new QGroupBox("Dimensions", this);
    radioBtnGroupDimensions->move(235, 67);
    radioBtnGroupDimensions->setMinimumSize(180, 40);

    radioHBoxDimensions = new QHBoxLayout(radioBtnGroupDimensions);

    for (int i = 0; i < 2; ++i) {
        radioButtonsDimensions[i] = new QRadioButton(dimensions[i], this);
        radioHBoxDimensions->addWidget(radioButtonsDimensions[i]);

        connect(radioButtonsDimensions[i], SIGNAL(toggled(bool)), this, SLOT(changeDimension()));
    }
    radioButtonsDimensions[0]->setChecked(true);
    radioBtnGroupDimensions->setLayout(radioHBoxDimensions);


    convertDirection = new QLabel("-->", this);
    convertDirection->move(210, 15);

    checkBox = new QCheckBox("Invert", this);
    checkBox->move(210, 40);
    checkBox->setMinimumSize(30, 30);

    currentTextSize = new QProgressBar(this);
    currentTextSize->move(350, 44);
    currentTextSize->setRange(3, 15);
    currentTextSize->setValue(textSize->value());
    currentTextSize->setMaximumSize(65, 40);
    currentTextSize->setStyleSheet(
        "QProgressBar::chunk { background-color: #ADD8E6;} "
        "QProgressBar {text-align: center;}"
    );

    connect(textSize, SIGNAL(valueChanged(int)), currentTextSize, SLOT(setValue(int)));
    connect(checkBox, SIGNAL(clicked()), this, SLOT(invert()));
    connect(textSize, SIGNAL(valueChanged(int)), this, SLOT(changeTextSize(int)));
    connect(clear, SIGNAL(clicked()), this, SLOT(labelsClear()));
    connect(convert, SIGNAL(clicked()), this, SLOT(performLengthConversion()));
}

Widget::~Widget()
{

}

void Widget::labelsClear()
{
    input->clear();
    output->clear();
}

void Widget::performLengthConversion()
{
    QString sourceUnit = comboBox1->currentText();
    QString targetUnit = comboBox2->currentText();
    bool t =checkBox->isChecked();
    double conversionFactor = 1.0;
    double inputValue;
    QList<QString> unitsList;
    if(t){
        inputValue = output->text().toDouble();
        unitsList = {targetUnit, sourceUnit};
    }
    else {
        inputValue = input->text().toDouble();
        unitsList = {sourceUnit, targetUnit};
    }

    if (conversionTable.contains({sourceUnit, targetUnit})) {
        conversionFactor = conversionTable[unitsList];
    }

    double convertedValue = inputValue * conversionFactor;
    if(t){
        input->setText(QString::number(convertedValue));
    }
    else output->setText(QString::number(convertedValue));
}

void Widget::invert()
{
    convertDirection->setText(directions[checkBox->isChecked()]);
    input->setReadOnly(checkBox->isChecked());
    output->setReadOnly(!checkBox->isChecked());
    labelsClear();
}

void Widget::changeDimension()
{
    input->clear();
    output->clear();
    comboBox1->clear();
    comboBox2->clear();
    QRadioButton *selectedRadio = qobject_cast<QRadioButton*>(sender());
    if(selectedRadio) {
        QString buttonText = selectedRadio->text();
        if (buttonText == "length") {
            for(int i=0; i<5; i++){
                comboBox1->addItem(units[i]);
                comboBox2->addItem(units[i]);
            }
        }
        else if(buttonText == "weight"){
            for(int i=0; i<5; i++){
                comboBox1->addItem(weightUnits[i]);
                comboBox2->addItem(weightUnits[i]);
            }
        }
    }
    comboBox2->setCurrentIndex(1);
}

void Widget::changeTextSize(int size)
{
    QFont font = input->font();
    font.setPointSize(size);
    input->setFont(font);
    output->setFont(font);
}

void Widget::changeTextColor()
{
    QRadioButton *selectedRadio = qobject_cast<QRadioButton*>(sender());
    if (selectedRadio) {
        QString buttonText = selectedRadio->text();
        if (buttonText == "Blue") {
            input->setStyleSheet("color: blue;");
            output->setStyleSheet("color: blue;");
        } else if (buttonText == "Black") {
            input->setStyleSheet("color: black;");
            output->setStyleSheet("color: black;");
        } else if (buttonText == "Green") {
            input->setStyleSheet("color: green;");
            output->setStyleSheet("color: green;");
        }
    }
}

void Widget::changeBackgroundColor()
{
    QRadioButton *selectedRadio = qobject_cast<QRadioButton*>(sender());
    if (selectedRadio) {
        QString buttonText = selectedRadio->text();
        if (buttonText == "White") {
            this->setStyleSheet("background-color: white;");
        } else if (buttonText == "Grey") {
            this->setStyleSheet("background-color: none;");
        } else if (buttonText == "Pink") {
            this->setStyleSheet("background-color: pink;");
        }
    }
}
