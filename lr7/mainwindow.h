#pragma once

#include <QColorDialog>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QColorDialog *_lightModelAmbientColorDialog;
    QColorDialog *_materialAmbientColorDialog;
    QColorDialog *_materialDiffuseColorDialog;
    QColorDialog *_materialSpecularColorDialog;
    QColorDialog *_materialEmissionColorDialog;
    QColorDialog *_lightAmbientColorDialog;
    QColorDialog *_lightDiffuseColorDialog;
    QColorDialog *_lightSpecularColorDialog;

    void updateConfig();
    void setIndicator(const QColor& color, QWidget* indicator);

private slots:
    void lightModelAmbientButtonClicked();
    void lightModelAmbientColorSelected(const QColor& color);
    void lightModelColorControlSelected(int control);
    void lightModelLocalViewerChanged();
    void lightModelTwoSideChanged();

    void materialAmbientButtonClicked();
    void materialAmbientColorSelected(const QColor&);
    void materialDiffuseButtonClicked();
    void materialDiffuseColorSelected(const QColor&);
    void materialSpecularButtonClicked();
    void materialSpecularColorSelected(const QColor&);
    void materialEmissionButtonClicked();
    void materialEmissionColorSelected(const QColor&);
    void materialShininessChanged(int);

    void lightPositionChanged();
    void lightAmbientButtonClicked();
    void lightAmbientColorSelected(const QColor&);
    void lightDiffuseButtonClicked();
    void lightDiffuseColorSelected(const QColor&);
    void lightSpecularButtonClicked();
    void lightSpecularColorSelected(const QColor&);
    void directionalLightClicked();
    void lightConstantAttenuationChanged(double);
    void lightLinearAttenuationChanged(double);
    void lightQuadraticAttenuationChanged(double);
    void lightSpotDirectionChanged();
    void lightSpotCutoffChanged(int);
    void lightSpotExponentChanged(double);
};
