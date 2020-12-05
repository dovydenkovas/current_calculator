#include "MainWindow.h"

MainWindow::MainWindow(): QMainWindow() // конструктор
{
    this->setWindowTitle("Нахождение токов цепи");
    this->resize(840, 600);
    this->setFont(QFont("Arial", 11));

    auto *scheme_frame = new QFrame;
    auto *scheme = new QLabel();
    auto *scheme_layout = new QHBoxLayout();
    scheme->setPixmap(QPixmap::fromImage(QImage("circuit.png")));
    scheme_layout->addWidget(new QSplitter);
    scheme_layout->addWidget(scheme);
    scheme_layout->addWidget(new QSplitter);
    scheme_frame->setLayout(scheme_layout);

    auto *input_frame = new QFrame;
    auto *input_layout = new QGridLayout();
    input_layout->addWidget(new QLabel("E1="), 1, 0);
    input_layout->addWidget(new QLabel("E2="), 2, 0);
    input_layout->addWidget(new QLabel("E3="), 3, 0);
    input_layout->addWidget(input_emf1, 1, 1, 1, 2);
    input_layout->addWidget(input_emf2, 2, 1, 1, 2);
    input_layout->addWidget(input_emf3, 3, 1, 1, 2);
    input_layout->addWidget(new QLabel("R01="), 4, 0);
    input_layout->addWidget(new QLabel("R02="), 5, 0);
    input_layout->addWidget(new QLabel("R03="), 6, 0);
    input_layout->addWidget(input_source_resistance1, 4, 1, 1, 2);
    input_layout->addWidget(input_source_resistance2, 5, 1, 1, 2);
    input_layout->addWidget(input_source_resistance3, 6, 1, 1, 2);
    input_layout->addWidget(new QLabel("R1="), 7, 0);
    input_layout->addWidget(new QLabel("R2="), 8, 0);
    input_layout->addWidget(new QLabel("R3="), 9, 0);
    input_layout->addWidget(input_branch_resistance1, 7, 1, 1, 2);
    input_layout->addWidget(input_branch_resistance2, 8, 1, 1, 2);
    input_layout->addWidget(input_branch_resistance3, 9, 1, 1, 2);
    input_layout->addWidget(calculate_current_btn, 10, 0, 1, 3);
    input_frame->setLayout(input_layout);

    auto *output_frame = new QFrame;
    auto *output_layout = new QVBoxLayout;
    auto *output_tab = new QTabWidget();
    output_tab->addTab(output_om, "Метод наложения");
    output_tab->addTab(output_nem, "Метод узлового напряжения");
    output_tab->addTab(output_mnce, "Метод узловых и контурных уравнений");
    output_tab->addTab(output_lcm, "Метод контурных токов");
    output_layout->addWidget(output_tab);
    output_frame->setLayout(output_layout);

    auto *layout = new QVBoxLayout();
    centralWidget->setLayout(layout);

    auto *scheme_input_splitter = new QSplitter(Qt::Vertical);
    scheme_input_splitter->addWidget(scheme_frame);
    scheme_input_splitter->addWidget(input_frame);
    auto *vertical_splitter = new QSplitter(Qt::Horizontal);
    vertical_splitter->addWidget(scheme_input_splitter);
    vertical_splitter->addWidget(output_frame);
    layout->addWidget(vertical_splitter);
    //vertical_splitter->setHandleWidth(7);
    //vertical_splitter->setStyleSheet("QSplitter::handle{background: #a0a0a0}");
    input_frame->setMaximumSize(250, 2000);

    connect(calculate_current_btn, SIGNAL (released()), this, SLOT (calculate_current()));
    output_om->setText("Чтобы появилось решение, введите входные данные и нажмите \"Найти токи\" ");

    input_emf1->setRange(-10000, 10000);
    input_emf2->setRange(-10000, 10000);
    input_emf3->setRange(-10000, 10000);
    input_source_resistance1->setRange(0, 10000);
    input_source_resistance2->setRange(0, 10000);
    input_source_resistance3->setRange(0, 10000);
    input_branch_resistance1->setRange(0, 10000);
    input_branch_resistance2->setRange(0, 10000);
    input_branch_resistance3->setRange(0, 10000);

    setCentralWidget(centralWidget);
};

void MainWindow::calculate_current() {

    // Получение входных значений:
    input_data input_data;
    input_data.E1 = input_emf1->value();
    input_data.E2 = input_emf2->value();
    input_data.E3 = input_emf3->value();
    input_data.R01 = input_source_resistance1->value();
    input_data.R02 = input_source_resistance2->value();
    input_data.R03 = input_source_resistance3->value();
    input_data.R1 = input_branch_resistance1->value();
    input_data.R2 = input_branch_resistance2->value();
    input_data.R3 = input_branch_resistance3->value();

    // Метод наложения
    result_om res_om = calculate_om(input_data);
    std::string out_om = "Первый Этап:\n"
                         "R2=" + std::to_string(res_om.R202) + "  \tI1=" + std::to_string(res_om.I11) + "\n"
                         "R3=" + std::to_string(res_om.R303) + "  \tU=" + std::to_string(res_om.U1) + "\n"
                         "R23=" + std::to_string(res_om.R1o) + "\tI2=" + std::to_string(res_om.I12) + "\n"
                         "Rэ=" + std::to_string(res_om.R1e) + "  \tI3=" + std::to_string(res_om.I13) + "\n"
                         "\nВторой Этап:\n"
                         "R1=" + std::to_string(res_om.R101) + "  \tI2=" + std::to_string(res_om.I22) + "\n"
                         "R3=" + std::to_string(res_om.R303) + "  \tU=" + std::to_string(res_om.U2) + "\n"
                         "R13=" + std::to_string(res_om.R2o) + "  \tI1=" + std::to_string(res_om.I21) + "\n"
                         "Rэ=" + std::to_string(res_om.R2e) + "  \tI3=" + std::to_string(res_om.I23) + "\n"
                         "\nТретий Этап:\n"
                         "R2=" + std::to_string(res_om.R202) + "  \tI3=" + std::to_string(res_om.I33) + "\n"
                         "R1=" + std::to_string(res_om.R101) + "  \tU=" + std::to_string(res_om.U3) + "\n"
                         "R12=" + std::to_string(res_om.R3o) + "  \tI2=" + std::to_string(res_om.I32) + "\n"
                         "Rэ=" + std::to_string(res_om.R3e) + "  \tI1=" + std::to_string(res_om.I31) + "\n"
                         "\nИтого:\n"
                         "I1=" + std::to_string(res_om.I1) + "\tI2=" + std::to_string(res_om.I2) + "\tI3=" + std::to_string(res_om.I3) + "\n"
                         "sum: " + std::to_string(unfull_round(res_om.I1 + res_om.I2 + res_om.I3, 4));
    output_om->setText(QString::fromStdString(out_om));

    // Метод узлового напряжения
    result_nem res_nem = calculate_nem(input_data);
    std::string out_nem = "g1="+std::to_string(res_nem.g1)+
                        "\tg2="+std::to_string(res_nem.g2)+
                        "\tg3="+std::to_string(res_nem.g3)+
                        "\nU="+std::to_string(res_nem.U)+
                        "\nI1="+std::to_string(res_nem.I1)+
                        "\tI2="+std::to_string(res_nem.I2)+
                        "\tI3"+std::to_string(res_nem.I3)+
                        "\nsum: "+std::to_string(res_nem.I1 + res_nem.I2 + res_nem.I3);
    output_nem->setText(QString::fromStdString(out_nem));

    // Метод Узловых и контурных уравнений
    result_mnce res_mnce = calculate_mnce(input_data);

    std::string out_mnce = "{ I1 + I2 + I3 = 0\n"
                           "{ "+ std::to_string(input_data.E1 - input_data.E2) + " = " + std::to_string(res_mnce.R101) + "·I1 -" + std::to_string(res_mnce.R202) + "·I2\n"
                           "{ " + std::to_string(input_data.E2 - input_data.E3) + " = " + std::to_string(res_mnce.R202) + "·I2 -" + std::to_string(res_mnce.R303) + "·I3\n\n"

                           "{ I1 = - I2 - I3\n"
                           "{ " + std::to_string(input_data.E1 - input_data.E2) + " = -" + std::to_string(res_mnce.R101) + "·I2 -" + std::to_string(res_mnce.R101) + "·I3 -" + std::to_string(res_mnce.R202) + "·I2\n"
                           "{ " + std::to_string(input_data.E2 - input_data.E3) + " = " + std::to_string(res_mnce.R202) + "·I2 -" + std::to_string(res_mnce.R303) + "·I3\n\n"

                           "{ I1 = - I2 - I3\n"
                           "{ " + std::to_string(input_data.E1 - input_data.E2) + " = -" + std::to_string(res_mnce.R101 + res_mnce.R202) + "·I2 -" + std::to_string(res_mnce.R101) + "·I3 | ·" + std::to_string(res_mnce.R303) + "\n"
                           "{ " + std::to_string(input_data.E2 - input_data.E3) + " = " + std::to_string(res_mnce.R202) + "·I2 -" + std::to_string(res_mnce.R303) + "·I3 | ·" + std::to_string(res_mnce.R101) + "\n"

                           "-{ " + std::to_string((input_data.E1 - input_data.E2) * res_mnce.R303) + " = -" + std::to_string((res_mnce.R101 + res_mnce.R202) * res_mnce.R303) + "·I2 -" + std::to_string(res_mnce.R101 * res_mnce.R303) + "·I3\n"
                           " { " + std::to_string((input_data.E2 - input_data.E3) * res_mnce.R101) + " = " + std::to_string(res_mnce.R202 * res_mnce.R101) + "·I2 -" + std::to_string(res_mnce.R303 * res_mnce.R101) + "·I3\n"
                           " ―――――――――――――――――――――\n"
                           "  " + std::to_string(res_mnce.R303 * (input_data.E1 - input_data.E2) - res_mnce.R101 * (input_data.E2 - input_data.E3)) + " = " + std::to_string(-(res_mnce.R101 + res_mnce.R202) * res_mnce.R303 + res_mnce.R202 * res_mnce.R101) + "·I2\n\n"

                           "{ I2 = " + std::to_string(-(res_mnce.R303 * (input_data.E1 - input_data.E2) - res_mnce.R101 * (input_data.E2 - input_data.E3))) + " / " + std::to_string((res_mnce.R101 + res_mnce.R202) * res_mnce.R303 + res_mnce.R202 * res_mnce.R101) + "\n"
                           "{ I3 = " + std::to_string(-(input_data.E2 - input_data.E3 - res_mnce.I2 * res_mnce.R202)) + " / " + std::to_string(res_mnce.R303) + "\n"
                           "{ I1 = " + std::to_string(res_mnce.I2) + " - " + std::to_string(res_mnce.I3) + "\n\n"

                           "I1=" + std::to_string(res_mnce.I1) + "\tI2=" + std::to_string(res_mnce.I2) + "\tI3=" + std::to_string(res_mnce.I3) + "\n"
                           "sum: " + std::to_string(unfull_round(res_mnce.I1 + res_mnce.I2 + res_mnce.I3, 4)) + "\n";

    output_mnce->setText(QString::fromStdString(out_mnce));


    // Метод контурных токов
    result_lcm res_lcm = calculate_lcm(input_data);
    std::string out_lcm = "{ " + std::to_string(res_lcm.E1 + res_lcm.E2) + " = " + std::to_string(res_lcm.R1 + res_lcm.R2) +
                          "·I11 + " + std::to_string(res_lcm.R2) + "·I22\n"
                          "{ " + std::to_string(res_lcm.E2 + res_lcm.E3) +
                          " = " + std::to_string(res_lcm.R2 + res_lcm.R3) + "·I22 + "+ std::to_string(res_lcm.R2) + "·I11\n\n"
                          "{ " + std::to_string(res_lcm.E1 + res_lcm.E2) + " = " + std::to_string(res_lcm.R2) + "·I22 + " +
                          std::to_string(res_lcm.R1 + res_lcm.R2) + "·I11  | ·" + std::to_string(res_lcm.R2 + res_lcm.R3) + "\n"
                          "{ " + std::to_string(res_lcm.E2 + res_lcm.E3) + " = " + std::to_string(res_lcm.R2 + res_lcm.R3) +
                          "·I22 + " + std::to_string(res_lcm.R2) + "·I11  | ·" + std::to_string(res_lcm.R2) + "\n\n"
                          "-{ " + std::to_string((res_lcm.E1 + res_lcm.E2) * (res_lcm.R2 + res_lcm.R3)) +
                          " = " + std::to_string(res_lcm.R2 * (res_lcm.R2 + res_lcm.R3)) +
                          "·I22 + " + std::to_string((res_lcm.R1 + res_lcm.R2) * (res_lcm.R2 + res_lcm.R3)) + "·I11\n"
                          " { " + std::to_string((res_lcm.E2 + res_lcm.E3) * res_lcm.R2) + " = " +
                          std::to_string((res_lcm.R2 + res_lcm.R3) * res_lcm.R2) + "·I22 + " +
                          std::to_string(res_lcm.R2 * res_lcm.R2) + "·I11\n"
                          "―――――――――――――――――――――\n"
                          "  " + std::to_string((res_lcm.E1 + res_lcm.E2) * (res_lcm.R2 + res_lcm.R3) - (res_lcm.E2 + res_lcm.E3) * res_lcm.R2) +
                          " = " + std::to_string((res_lcm.R1 + res_lcm.R2) * (res_lcm.R2 + res_lcm.R3) - res_lcm.R2 * res_lcm.R2) + "·I1\n\n"
                          "I1=" + std::to_string(res_lcm.I1) + "\tI2=" + std::to_string(res_lcm.I2) + "\tI3=" + std::to_string(res_lcm.I3) + "\n"
                          "sum: " + std::to_string(unfull_round(res_lcm.I1 + res_lcm.I2 + res_lcm.I3, 4));
    output_lcm->setText(QString::fromStdString(out_lcm));
}