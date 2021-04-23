#include "drawer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Drawer* drawer = new Drawer();

    ui->setupUi(this);
    ui->horizontalLayout->insertWidget(0, drawer, 1);
    QObject::connect(ui->typeSlider, SIGNAL(valueChanged(int)), this, SLOT(typeChanged(int)));
    QObject::connect(ui->xRotatePlus, SIGNAL(clicked()), this, SLOT(xRotatePlus()));
    QObject::connect(ui->yRotatePlus, SIGNAL(clicked()), this, SLOT(yRotatePlus()));
    QObject::connect(ui->zRotatePlus, SIGNAL(clicked()), this, SLOT(zRotatePlus()));
    QObject::connect(ui->xRotateMinus, SIGNAL(clicked()), this, SLOT(xRotateMinus()));
    QObject::connect(ui->yRotateMinus, SIGNAL(clicked()), this, SLOT(yRotateMinus()));
    QObject::connect(ui->zRotateMinus, SIGNAL(clicked()), this, SLOT(zRotateMinus()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::typeChanged(int type) {
    updateConfig();
}

void MainWindow::updateConfig() {
    Config& config = *Config::instance;
    config.is3D = ui->typeSlider->value() == 0;
    config.notify();
}

const float rotationAngle = 10.0f;

void MainWindow::xRotatePlus() {
    Config& config = *Config::instance;
    config.figure->rotate(rotationAngle, QVector3D(1, 0, 0));
    config.figure->markNeedsPaint();
}
void MainWindow::yRotatePlus(){
    Config& config = *Config::instance;
    config.figure->rotate(rotationAngle, QVector3D(0, 1, 0));
    config.figure->markNeedsPaint();
}
void MainWindow::zRotatePlus(){
    Config& config = *Config::instance;
    config.figure->rotate(rotationAngle, QVector3D(0, 0, 1));
    config.figure->markNeedsPaint();
}
void MainWindow::xRotateMinus(){
    Config& config = *Config::instance;
    config.figure->rotate(-rotationAngle, QVector3D(1, 0, 0));
    config.figure->markNeedsPaint();
}
void MainWindow::yRotateMinus(){
    Config& config = *Config::instance;
    config.figure->rotate(-rotationAngle, QVector3D(0, 1, 0));
    config.figure->markNeedsPaint();
}
void MainWindow::zRotateMinus(){
    Config& config = *Config::instance;
    config.figure->rotate(-rotationAngle, QVector3D(0, 0, 1));
    config.figure->markNeedsPaint();
}

void MainWindow::xScalePlus(){
    Config& config = *Config::instance;
}
void MainWindow::yScalePlus(){
    Config& config = *Config::instance;
}
void MainWindow::zScalePlus(){
    Config& config = *Config::instance;
}
void MainWindow::xScaleMinus(){
    Config& config = *Config::instance;
}
void MainWindow::yScaleMinus(){
    Config& config = *Config::instance;
}
void MainWindow::zScaleMinus(){
    Config& config = *Config::instance;
}

void MainWindow::xTranslatePlus(){
    Config& config = *Config::instance;
}
void MainWindow::yTranslatePlus(){
    Config& config = *Config::instance;
}
void MainWindow::zTranslatePlus(){
    Config& config = *Config::instance;
}
void MainWindow::xTranslateMinus(){
    Config& config = *Config::instance;
}
void MainWindow::yTranslateMinus(){
    Config& config = *Config::instance;
}
void MainWindow::zTranslateMinus(){
    Config& config = *Config::instance;
}
