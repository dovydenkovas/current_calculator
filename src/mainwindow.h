#ifndef CIRCUIT_MAINWINDOW_H
#define CIRCUIT_MAINWINDOW_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

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
#include <QtWebEngineWidgets/QWebEngineView>


#include "caltulate_circuit.h"


class  MainWindow:public QMainWindow {
Q_OBJECT
public:
    MainWindow();
    void keyPressEvent(QKeyEvent *event);

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
    QWebEngineView *output_om = new QWebEngineView(); // QWebEngineView
    QWebEngineView *output_nem = new QWebEngineView();
    QWebEngineView *output_mnce = new QWebEngineView();
    QWebEngineView *output_lcm = new QWebEngineView();
    QPushButton *calculate_current_btn = new QPushButton("Найти токи");
};

#endif
