#ifndef CIRCUIT_MAINWINDOW_H
#define CIRCUIT_MAINWINDOW_H

#include <iostream>
#include <string>
#include <QMainWindow>
#include <QtWidgets>
#include <QPushButton>
#include <QTabWidget>
#include <QTabBar>
#include <QPixmap>
#include <QImage>
#include <QFrame>
#include <QBoxLayout>
#include <QString>

#include "caltulate_circuit.h"


class  MainWindow:public QMainWindow {
Q_OBJECT
public:
    MainWindow();

private slots:
    void calculate_current();

private:
    QWidget *centralWidget = new QWidget(this);
    QDoubleSpinBox *input_emf1 = new QDoubleSpinBox();
    QDoubleSpinBox *input_emf2 = new QDoubleSpinBox();
    QDoubleSpinBox *input_emf3 = new QDoubleSpinBox();
    QDoubleSpinBox *input_source_resistance1 = new QDoubleSpinBox();
    QDoubleSpinBox *input_source_resistance2 = new QDoubleSpinBox();
    QDoubleSpinBox *input_source_resistance3 = new QDoubleSpinBox();
    QDoubleSpinBox *input_branch_resistance1 = new QDoubleSpinBox();
    QDoubleSpinBox *input_branch_resistance2 = new QDoubleSpinBox();
    QDoubleSpinBox *input_branch_resistance3 = new QDoubleSpinBox();
    QTextBrowser *output_om = new QTextBrowser();
    QTextBrowser *output_nem = new QTextBrowser();
    QTextBrowser *output_mnce = new QTextBrowser();
    QTextBrowser *output_lcm = new QTextBrowser();
    QPushButton *calculate_current_btn = new QPushButton("Найти токи");
};

#endif