#include "drawer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"
#include <iostream>

const QStringList lightModelColorControlNames = {
    "GL_SEPARATE_SPECULAR_COLOR",
    "GL_SINGLE_COLOR"
};
const GLint lightModelColorControlValues[] = {
    GL_SEPARATE_SPECULAR_COLOR ,
    GL_SINGLE_COLOR
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Drawer* drawer = new Drawer();
    _lightModelAmbientColorDialog = new QColorDialog();
    _lightModelAmbientColorDialog->setWindowTitle("GL_LIGHT_MODEL_AMBIENT");
    _lightModelAmbientColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    _lightModelAmbientColorDialog->setCurrentColor(QColor(50, 50, 50));
    QObject::connect(ui->lightModelAmbientButton, SIGNAL(clicked()), this, SLOT(lightModelAmbientButtonClicked()));
    QObject::connect(_lightModelAmbientColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(lightModelAmbientColorSelected(const QColor&)));

    _materialAmbientColorDialog = new QColorDialog();
    _materialAmbientColorDialog->setWindowTitle("GL_AMBIENT");
    _materialAmbientColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    _materialAmbientColorDialog->setCurrentColor(QColor(50, 50, 50));
    QObject::connect(ui->materialAmbientButton, SIGNAL(clicked()), this, SLOT(materialAmbientButtonClicked()));
    QObject::connect(_materialAmbientColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(materialAmbientColorSelected(const QColor&)));

    _materialDiffuseColorDialog = new QColorDialog();
    _materialDiffuseColorDialog->setWindowTitle("GL_DIFFUSE");
    _materialDiffuseColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    _materialDiffuseColorDialog->setCurrentColor(QColor(50, 50, 50));
    QObject::connect(ui->materialDiffuseButton, SIGNAL(clicked()), this, SLOT(materialDiffuseButtonClicked()));
    QObject::connect(_materialDiffuseColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(materialDiffuseColorSelected(const QColor&)));

    _materialSpecularColorDialog = new QColorDialog();
    _materialSpecularColorDialog->setWindowTitle("GL_SPECULAR");
    _materialSpecularColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    _materialSpecularColorDialog->setCurrentColor(QColor(0, 0, 0));
    QObject::connect(ui->materialSpecularButton, SIGNAL(clicked()), this, SLOT(materialSpecularButtonClicked()));
    QObject::connect(_materialSpecularColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(materialSpecularColorSelected(const QColor&)));

    _materialEmissionColorDialog = new QColorDialog();
    _materialEmissionColorDialog->setWindowTitle("GL_EMISSION");
    _materialEmissionColorDialog->setOption(QColorDialog::ShowAlphaChannel, true);
    _materialEmissionColorDialog->setCurrentColor(QColor(0, 0, 0));
    QObject::connect(ui->materialEmissionButton, SIGNAL(clicked()), this, SLOT(materialEmissionButtonClicked()));
    QObject::connect(_materialEmissionColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(materialEmissionColorSelected(const QColor&)));

    _lightAmbientColorDialog = new QColorDialog();
    _lightAmbientColorDialog->setWindowTitle("GL_AMBIENT");
    _lightAmbientColorDialog->setOption(QColorDialog::ShowAlphaChannel, false);
    _lightAmbientColorDialog->setCurrentColor(QColor(50, 50, 50));
    QObject::connect(ui->lightAmbientButton, SIGNAL(clicked()), this, SLOT(lightAmbientButtonClicked()));
    QObject::connect(_lightAmbientColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(lightAmbientColorSelected(const QColor&)));

    _lightDiffuseColorDialog = new QColorDialog();
    _lightDiffuseColorDialog->setWindowTitle("GL_DIFFUSE");
    _lightDiffuseColorDialog->setOption(QColorDialog::ShowAlphaChannel, false);
    _lightDiffuseColorDialog->setCurrentColor(QColor(50, 50, 50));
    QObject::connect(ui->lightDiffuseButton, SIGNAL(clicked()), this, SLOT(lightDiffuseButtonClicked()));
    QObject::connect(_lightDiffuseColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(lightDiffuseColorSelected(const QColor&)));

    _lightSpecularColorDialog = new QColorDialog();
    _lightSpecularColorDialog->setWindowTitle("GL_SPECULAR");
    _lightSpecularColorDialog->setOption(QColorDialog::ShowAlphaChannel, false);
    _lightSpecularColorDialog->setCurrentColor(QColor(0, 0, 0));
    QObject::connect(ui->lightSpecularButton, SIGNAL(clicked()), this, SLOT(lightSpecularButtonClicked()));
    QObject::connect(_lightSpecularColorDialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(lightSpecularColorSelected(const QColor&)));

    ui->horizontalLayout->insertWidget(0, drawer, 1);
    ui->lightModelColorControlComboBox->insertItems(0, lightModelColorControlNames);

    QObject::connect(ui->materialShininessSlider, SIGNAL(valueChanged(int)), this, SLOT(materialShininessChanged(int)));
    QObject::connect(ui->lightModelColorControlComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(lightModelColorControlSelected(int)));
    QObject::connect(ui->lightModelLocalViewerCheckBox, SIGNAL(clicked()), this, SLOT(lightModelLocalViewerChanged()));
    QObject::connect(ui->lightModelTwoSideCheckBox, SIGNAL(clicked()), this, SLOT(lightModelTwoSideChanged()));
    QObject::connect(ui->directionalLightCheckBox, SIGNAL(clicked()), this, SLOT(directionalLightClicked()));
    QObject::connect(ui->lightConstantAttenuationSpinBox, SIGNAL(valueChanged(double)), this, SLOT(lightConstantAttenuationChanged(double)));
    QObject::connect(ui->lightLinearAttenuationSpinBox, SIGNAL(valueChanged(double)), this, SLOT(lightLinearAttenuationChanged(double)));
    QObject::connect(ui->lightQuadraticAttenuationSpinBox, SIGNAL(valueChanged(double)), this, SLOT(lightQuadraticAttenuationChanged(double)));
    QObject::connect(ui->lightSpotExponentSpinBox, SIGNAL(valueChanged(double)), this, SLOT(lightSpotExponentChanged(double)));
    QObject::connect(ui->lightSpotCutoffSlider, SIGNAL(valueChanged(int)), this, SLOT(lightSpotCutoffChanged(int)));
    QObject::connect(ui->lightSpotDirectionCheckBox, SIGNAL(clicked()), this, SLOT(lightSpotDirectionChanged()));
    QObject::connect(ui->lightPositionCheckbox, SIGNAL(clicked()), this, SLOT(lightPositionChanged()));
    updateConfig();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateConfig() {
    setIndicator(_lightModelAmbientColorDialog->currentColor(), ui->lightModelAmbientIndicator);
    setIndicator(_materialAmbientColorDialog->currentColor(), ui->materialAmbientIndicator);
    setIndicator(_materialDiffuseColorDialog->currentColor(), ui->materialDiffuseIndicator);
    setIndicator(_materialSpecularColorDialog->currentColor(), ui->materialSpecularIndicator);
    setIndicator(_materialEmissionColorDialog->currentColor(), ui->materialEmissionIndicator);
    setIndicator(_lightAmbientColorDialog->currentColor(), ui->lightAmbientIndicator);
    setIndicator(_lightDiffuseColorDialog->currentColor(), ui->lightDiffuseIndicator);
    setIndicator(_lightSpecularColorDialog->currentColor(), ui->lightSpecularIndicator);

    Config& config = *Config::instance;

    config.lightModelAmbient = _lightModelAmbientColorDialog->currentColor();
    config.lightModelColorControl = lightModelColorControlValues[ui->lightModelColorControlComboBox->currentIndex()];
    config.lightModelLocalViewer = ui->lightModelLocalViewerCheckBox->isChecked() ? GL_TRUE : GL_FALSE;
    config.lightModelTwoSide = ui->lightModelTwoSideCheckBox->isChecked() ? GL_TRUE : GL_FALSE;

    config.materialAmbient = _materialAmbientColorDialog->currentColor();
    config.materialDiffuse = _materialDiffuseColorDialog->currentColor();
    config.materialSpecular = _materialSpecularColorDialog->currentColor();
    config.materialEmission = _materialEmissionColorDialog->currentColor();
    config.materialShininess = ui->materialShininessSlider->value();

    config.isLightDirectional = ui->directionalLightCheckBox->isChecked();
    config.isLightPositionAttached = ui->lightPositionCheckbox->isChecked();
    config.isLightSpotAttached = ui->lightSpotDirectionCheckBox->isChecked();
    config.lightAmbient = _lightAmbientColorDialog->currentColor();
    config.lightDiffuse = _lightDiffuseColorDialog->currentColor();
    config.lightSpecular = _lightSpecularColorDialog->currentColor();
    config.lightConstantAttenuation = ui->lightConstantAttenuationSpinBox->value();
    config.lightLinearAttenuation = ui->lightLinearAttenuationSpinBox->value();
    config.lightQuadraticAttenuation = ui->lightQuadraticAttenuationSpinBox->value();
    config.lightSpotCutoff = ui->lightSpotCutoffSlider->value();
    config.lightSpotExponent = ui->lightSpotExponentSpinBox->value();

    config.notify();

    ui->lightConstantAttenuationSpinBox->setEnabled(!config.isLightDirectional);
    ui->lightLinearAttenuationSpinBox->setEnabled(!config.isLightDirectional);
    ui->lightQuadraticAttenuationSpinBox->setEnabled(!config.isLightDirectional);
    ui->lightSpotDirectionCheckBox->setEnabled(!config.isLightDirectional);
    ui->lightSpotCutoffSlider->setEnabled(!config.isLightDirectional);
    ui->lightSpotExponentSpinBox->setEnabled(!config.isLightDirectional);
}

void MainWindow::setIndicator(const QColor& color, QWidget* indicator) {
    QPalette lightAmbientPalette = indicator->palette();
    lightAmbientPalette.setColor(QPalette::Window, color);
    indicator->setPalette(lightAmbientPalette);
}

void MainWindow::lightModelAmbientButtonClicked() {
    _lightModelAmbientColorDialog->open();
}

void MainWindow::lightModelAmbientColorSelected(const QColor& color) {
    updateConfig();
}

void MainWindow::lightModelColorControlSelected(int control) {
    updateConfig();
}

void MainWindow::lightModelLocalViewerChanged() {
    updateConfig();
}

void MainWindow::lightModelTwoSideChanged() {
    updateConfig();
}

void MainWindow::materialAmbientButtonClicked() {
    _materialAmbientColorDialog->open();
}
void MainWindow::materialAmbientColorSelected(const QColor&) {
    updateConfig();
}
void MainWindow::materialDiffuseButtonClicked() {
    _materialDiffuseColorDialog->open();
}
void MainWindow::materialDiffuseColorSelected(const QColor&) {
    updateConfig();
}
void MainWindow::materialSpecularButtonClicked() {
    _materialSpecularColorDialog->open();
}
void MainWindow::materialSpecularColorSelected(const QColor&) {
    updateConfig();
}
void MainWindow::materialEmissionButtonClicked() {
    _materialEmissionColorDialog->open();
}
void MainWindow::materialEmissionColorSelected(const QColor&) {
    updateConfig();
}
void MainWindow::materialShininessChanged(int) {
    updateConfig();
}

void MainWindow::lightPositionChanged() {
    updateConfig();
}
void MainWindow::lightAmbientButtonClicked() {
    _lightAmbientColorDialog->open();
}
void MainWindow::lightAmbientColorSelected(const QColor&) {
    updateConfig();
}
void MainWindow::lightDiffuseButtonClicked() {
    _lightDiffuseColorDialog->open();
}
void MainWindow::lightDiffuseColorSelected(const QColor&) {
    updateConfig();
}
void MainWindow::lightSpecularButtonClicked() {
    _lightSpecularColorDialog->open();
}
void MainWindow::lightSpecularColorSelected(const QColor&) {
    updateConfig();
}
void MainWindow::directionalLightClicked() {
    updateConfig();
}
void MainWindow::lightConstantAttenuationChanged(double) {
    updateConfig();
}
void MainWindow::lightLinearAttenuationChanged(double) {
    updateConfig();
}
void MainWindow::lightQuadraticAttenuationChanged(double) {
    updateConfig();
}
void MainWindow::lightSpotDirectionChanged() {
    updateConfig();
}
void MainWindow::lightSpotCutoffChanged(int) {
    updateConfig();
}
void MainWindow::lightSpotExponentChanged(double) {
    updateConfig();
}

