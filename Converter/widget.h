#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QRadioButton>
#include <QProgressBar>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QBrush>
#include <QColor>
#include <QFont>
#include <QIntValidator>
#include <QDoubleValidator>

class Widget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *clear;
    QPushButton *convert;
    QLineEdit *input;
    QLineEdit *output;
    QComboBox *comboBox1;
    QComboBox *comboBox2;
    QSpinBox *textSize;
    QLabel *convertDirection;
    QCheckBox *checkBox;
    QProgressBar *currentTextSize;

    QGroupBox *radioBtnGroupTColor;
    QRadioButton *radioButtonsTColor[3];
    QVBoxLayout *radioVBoxTColor;
    QHBoxLayout *radioHBoxTColor;

    QGroupBox *radioBtnGroupBgColor;
    QRadioButton *radioButtonsBgColor[3];
    QVBoxLayout *radioVBoxBgColor;
    QHBoxLayout *radioHBoxBgColor;

    QGroupBox *radioBtnGroupDimensions;
    QRadioButton *radioButtonsDimensions[2];
    QHBoxLayout *radioHBoxDimensions;

    QString btnTextColorLabels[3] = {"Blue", "Black", "Green"};
    QString btnBgLabels[3] = {"White", "Grey", "Pink"};
    QString units[5] = {"km", "m", "cm", "dm", "mm"};
    QString weightUnits[5] = {"kg", "g", "lb", "oz", "st"};
    QString directions[2] = {"-->", "<--"};
    QString dimensions[2] = {"length", "weight"};

    QIntValidator *intValidator;
    QDoubleValidator *doubleValidator;


    QMap<QStringList, double> conversionTable = {
        {{"km", "m"}, 1000.0},
        {{"km", "cm"}, 100000.0},
        {{"km", "dm"}, 10000.0},
        {{"km", "mm"}, 1000000.0},
        {{"m", "cm"}, 100.0},
        {{"m", "dm"}, 10.0},
        {{"m", "mm"}, 1000.0},
        {{"cm", "dm"}, 10.0},
        {{"cm", "mm"}, 100.0},
        {{"dm", "mm"}, 10.0},
        {{"m", "km"}, 0.001},
        {{"cm", "km"}, 0.00001},
        {{"dm", "km"}, 0.0001},
        {{"mm", "km"}, 0.000001},
        {{"cm", "m"}, 0.01},
        {{"dm", "m"}, 0.1},
        {{"mm", "m"}, 0.001},
        {{"dm", "cm"}, 0.1},
        {{"mm", "cm"}, 0.01},
        {{"mm", "dm"}, 0.1},
        {{"kg", "g"}, 1000.0},
        {{"kg", "lb"}, 2.20462},
        {{"kg", "oz"}, 35.27396},
        {{"kg", "st"}, 0.15747},
        {{"g", "lb"}, 0.00220462},
        {{"g", "oz"}, 0.03527396},
        {{"g", "st"}, 0.00015747},
        {{"lb", "oz"}, 16.0},
        {{"g", "kg"}, 0.001},
        {{"lb", "kg"}, 0.453592},
        {{"oz", "kg"}, 0.0283495},
        {{"st", "kg"}, 6.35029},
        {{"lb", "g"}, 453.592},
        {{"oz", "g"}, 28.3495},
        {{"st", "g"}, 6350.29},
        {{"oz", "lb"}, 0.0625},
        {{"oz", "st"}, 0.00446},
        {{"st", "oz"}, 224},
        {{"lb", "st"}, 0.0714286},
        {{"st", "lb"}, 14},
    };

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void labelsClear();
    void performLengthConversion();
    void invert();
    void changeDimension();
    void changeTextSize(int size);
    void changeTextColor();
    void changeBackgroundColor();
};
#endif // WIDGET_H
