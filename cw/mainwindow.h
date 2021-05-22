#pragma once

#include "drawer.h"

#include <QMainWindow>
#include <table.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void lightClicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Drawer *drawer;
    Ui::MainWindow *ui;
    Table table = Table(10.0f, 25.0f ,12.0f);
};
