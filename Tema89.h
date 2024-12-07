#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tema89.h"

class Tema89 : public QMainWindow
{
    Q_OBJECT

public:
    Tema89(QWidget *parent = nullptr);
    ~Tema89();

private:
    Ui::Tema89Class ui;
};
