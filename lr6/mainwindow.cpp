#include "drawer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include "stuff.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Drawer* drawer = new Drawer();

    ui->setupUi(this);
    ui->horizontalLayout->insertWidget(0, drawer, 1);
    QObject::connect(ui->showEdgesCheckbox, SIGNAL(clicked()), this, SLOT(showEdgesClicked()));
    QObject::connect(ui->orthoCheckbox, SIGNAL(clicked()), this, SLOT(projectionChanged()));

    QObject::connect(ui->xRotatePlus, SIGNAL(clicked()), this, SLOT(xRotatePlus()));
    QObject::connect(ui->yRotatePlus, SIGNAL(clicked()), this, SLOT(yRotatePlus()));
    QObject::connect(ui->zRotatePlus, SIGNAL(clicked()), this, SLOT(zRotatePlus()));
    QObject::connect(ui->xRotateMinus, SIGNAL(clicked()), this, SLOT(xRotateMinus()));
    QObject::connect(ui->yRotateMinus, SIGNAL(clicked()), this, SLOT(yRotateMinus()));
    QObject::connect(ui->zRotateMinus, SIGNAL(clicked()), this, SLOT(zRotateMinus()));

    QObject::connect(ui->xScalePlus, SIGNAL(clicked()), this, SLOT(xScalePlus()));
    QObject::connect(ui->yScalePlus, SIGNAL(clicked()), this, SLOT(yScalePlus()));
    QObject::connect(ui->zScalePlus, SIGNAL(clicked()), this, SLOT(zScalePlus()));
    QObject::connect(ui->xScaleMinus, SIGNAL(clicked()), this, SLOT(xScaleMinus()));
    QObject::connect(ui->yScaleMinus, SIGNAL(clicked()), this, SLOT(yScaleMinus()));
    QObject::connect(ui->zScaleMinus, SIGNAL(clicked()), this, SLOT(zScaleMinus()));

    QObject::connect(ui->xTranslatePlus, SIGNAL(clicked()), this, SLOT(xTranslatePlus()));
    QObject::connect(ui->yTranslatePlus, SIGNAL(clicked()), this, SLOT(yTranslatePlus()));
    QObject::connect(ui->zTranslatePlus, SIGNAL(clicked()), this, SLOT(zTranslatePlus()));
    QObject::connect(ui->xTranslateMinus, SIGNAL(clicked()), this, SLOT(xTranslateMinus()));
    QObject::connect(ui->yTranslateMinus, SIGNAL(clicked()), this, SLOT(yTranslateMinus()));
    QObject::connect(ui->zTranslateMinus, SIGNAL(clicked()), this, SLOT(zTranslateMinus()));

    QObject::connect(ui->densitySpacer, SIGNAL(valueChanged(int)), this, SLOT(densityChanged(int)));
    QObject::connect(ui->lightSlider, SIGNAL(valueChanged(int)), this, SLOT(lightChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateConfig() {
    Config& config = *Config::instance;
    config.is3D = !ui->showEdgesCheckbox->isChecked();
    config.light = static_cast<float>(ui->lightSlider->value()) / 100;
    config.isOrtho = ui->orthoCheckbox->isChecked();
    config.notify();
}

void MainWindow::showEdgesClicked() {
    updateConfig();
}

void MainWindow::densityChanged(int density) {
    Config& config = *Config::instance;
    static_cast<Stuff*>(config.figure)->generate(density);
}

void MainWindow::lightChanged(int light) {
    updateConfig();
}

void MainWindow::projectionChanged() {
    updateConfig();
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

const float scalePlus = 1.2f;
const float scaleMinus = 1.0f / scalePlus;

void MainWindow::xScalePlus(){
    Config& config = *Config::instance;
    config.figure->scale(QVector3D(scalePlus, 1, 1));
    config.figure->markNeedsPaint();
}
void MainWindow::yScalePlus(){
    Config& config = *Config::instance;
    config.figure->scale(QVector3D(1, scalePlus, 1));
    config.figure->markNeedsPaint();
}
void MainWindow::zScalePlus(){
    Config& config = *Config::instance;
    config.figure->scale(QVector3D(1, 1, scalePlus));
    config.figure->markNeedsPaint();
}
void MainWindow::xScaleMinus(){
    Config& config = *Config::instance;
    config.figure->scale(QVector3D(scaleMinus, 1, 1));
    config.figure->markNeedsPaint();
}
void MainWindow::yScaleMinus(){
    Config& config = *Config::instance;
    config.figure->scale(QVector3D(1, scaleMinus, 1));
    config.figure->markNeedsPaint();
}
void MainWindow::zScaleMinus(){
    Config& config = *Config::instance;
    config.figure->scale(QVector3D(1, 1, scaleMinus));
    config.figure->markNeedsPaint();
}

const float translation = 0.4f;

void MainWindow::xTranslatePlus(){
    Config& config = *Config::instance;
    config.figure->translate(QVector3D(translation, 0, 0));
    config.figure->markNeedsPaint();
}
void MainWindow::yTranslatePlus(){
    Config& config = *Config::instance;
    config.figure->translate(QVector3D(0, translation, 0));
    config.figure->markNeedsPaint();
}
void MainWindow::zTranslatePlus(){
    Config& config = *Config::instance;
    config.figure->translate(QVector3D(0, 0, translation));
    config.figure->markNeedsPaint();
}
void MainWindow::xTranslateMinus(){
    Config& config = *Config::instance;
    config.figure->translate(QVector3D(-translation, 0, 0));
    config.figure->markNeedsPaint();
}
void MainWindow::yTranslateMinus(){
    Config& config = *Config::instance;
    config.figure->translate(QVector3D(0, -translation, 0));
    config.figure->markNeedsPaint();
}
void MainWindow::zTranslateMinus(){
    Config& config = *Config::instance;
    config.figure->translate(QVector3D(0, 0, -translation));
    config.figure->markNeedsPaint();
}
