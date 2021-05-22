#include "drawer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <table.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    drawer = new Drawer();

    ui->setupUi(this);
    ui->verticalLayout->addWidget(drawer, 1);

    float splitDensity = 3.0f;
    table.bigPanel->split(splitDensity);
    table.bigPanelSides->split(splitDensity);
    table.smallPanel->split(splitDensity);
    table.smallPanelSides->split(splitDensity);

    for (Figure* f : table.legs)
        f->split(splitDensity);
    for (Figure* f : table.smallLegs)
        f->split(splitDensity);
    for (Figure* f : table.ironLegs)
        f->split(splitDensity);

    for (Figure* f : table.legs)
        drawer->addFigure(f);
    for (Figure* f : table.smallLegs)
        drawer->addFigure(f);
    for (Figure* f : table.ironLegs)
        drawer->addFigure(f);

    drawer->addFigure(table.smallPanel);
    drawer->addFigure(table.smallPanelSides);
    drawer->addFigure(table.bigPanel);
    drawer->addFigure(table.bigPanelSides);
    QObject::connect(ui->attachLightCheckbox, SIGNAL(clicked()), this, SLOT(lightClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lightClicked() {
    if (ui->attachLightCheckbox->isChecked())
        LightConfig::base.attachViewWrapper(&drawer->viewWrapper());
    else
        LightConfig::base.detachViewWrapper();
}
