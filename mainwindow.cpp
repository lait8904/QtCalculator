#include "mainwindow.h"
#include "./ui_mainwindow.h"


double calcVal = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for (int i = 0; i < 10; i++) {
        QString butName = "pushButton" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton*>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    connect(MainWindow::findChild<QPushButton*>("Equals"),
            SIGNAL(released()), this, SLOT(EqualButton()));

    connect(MainWindow::findChild<QPushButton*>("Divide"),
            SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(MainWindow::findChild<QPushButton*>("Multiply"),
            SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(MainWindow::findChild<QPushButton*>("Substract"),
            SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(MainWindow::findChild<QPushButton*>("Add"),
            SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(MainWindow::findChild<QPushButton*>("Clear"),
            SIGNAL(released()), this, SLOT(ClearButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed() {
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if ((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)) {
        ui->Display->setText(butVal);
    } else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void MainWindow::MathButtonPressed() {
    subTrigger = false;
    mulTrigger = false;
    divTrigger = false;
    addTrigger = false;
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    } else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0) {
        mulTrigger = true;
    } else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    } else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    }
    ui->Display->setText("");
}

void MainWindow::EqualButton() {
    double solution = 0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if (divTrigger || mulTrigger || addTrigger || subTrigger) {
        if (divTrigger) {
            if (dblDisplayVal != 0 && dblDisplayVal != 0.0)
                solution = calcVal / dblDisplayVal;
        } else if (mulTrigger) {
            solution = calcVal * dblDisplayVal;
        } else if (subTrigger) {
            solution = calcVal - dblDisplayVal;
        } else if (addTrigger) {
            solution = calcVal + dblDisplayVal;
        }
        ui->Display->setText(QString::number(solution));
    }
}

void MainWindow::ClearButton() {
    subTrigger = false;
    mulTrigger = false;
    divTrigger = false;
    addTrigger = false;
    calcVal = 0;
    ui->Display->setText("0");
}

