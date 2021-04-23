#pragma once

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

    void updateConfig();

private slots:
    void typeChanged(int type);

    void xRotatePlus();
    void yRotatePlus();
    void zRotatePlus();
    void xRotateMinus();
    void yRotateMinus();
    void zRotateMinus();

    void xScalePlus();
    void yScalePlus();
    void zScalePlus();
    void xScaleMinus();
    void yScaleMinus();
    void zScaleMinus();

    void xTranslatePlus();
    void yTranslatePlus();
    void zTranslatePlus();
    void xTranslateMinus();
    void yTranslateMinus();
    void zTranslateMinus();
};
