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
    output_om->setHtml("Чтобы появилось решение, введите входные данные и нажмите \"Найти токи\" ");

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

    std::string head =  "<html><head>\n"
                        "<script type=\"text/javascript\" src=\"https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-AMS-MML_HTMLorMML\">\n"
                        "</script></head>\n"
                        "<body>\n"
                        "<p><mathjax style=\"font-size:20px; float:left; width=0;\">";

    std::string end = "</mathjax></p>\n"
                      "</body></html>";

    // Метод наложения
    result_om res_om = calculate_om(input_data);
    std::stringstream stream_om;
    stream_om << std::fixed << std::setprecision(2) << head
        << "$$ Первый Этап: $$"
        << "$$ R_2=" << res_om.R202 << " $$"
        << "$$ R_3=" << res_om.R303 << " $$"
        << "$$ R_{23}=" << res_om.R1o << " $$"
        << "$$ R_э=" << res_om.R1e << " $$"
        << "$$ I_1=" << res_om.I11 << " $$"
        << "$$ U=" << res_om.U1 << " $$"
        << "$$ I_2=" << res_om.I12 << " $$"
        << "$$ I_3=" << res_om.I13 << " $$<br>"
        << "$$ Второй Этап: $$"
        << "$$ R_1=" << res_om.R101 << " $$"
        << "$$ R_3=" << res_om.R303 << " $$"
        << "$$ R_{13}=" << res_om.R2o << " $$"
        << "$$ R_э=" << res_om.R2e << " $$"
        << "$$ I_2=" << res_om.I22 << " $$"
        << "$$ U=" << res_om.U2 << " $$"
        << "$$ I_1=" << res_om.I21 << " $$"
        << "$$ I_3=" << res_om.I23 << " $$<br>"
        << "$$ Третий Этап: $$"
        << "$$ R_1=" << res_om.R101 << " $$"
        << "$$ R_2=" << res_om.R202 << " $$"
        << "$$ R_{12}=" << res_om.R3o << " $$"
        << "$$ R_э= " << res_om.R3e << " $$"
        << "$$ I_3= " << res_om.I33 << " $$"
        << "$$ U= " << res_om.U3 << " $$"
        << "$$ I_1= " << res_om.I31 << " $$"
        << "$$ I_2= " << res_om.I32 << " $$<br>"
        << "$$ Итого: $$"
        << "$$ I_1= " << res_om.I1 << " $$"
        << "$$ I_2= " << res_om.I2 << " $$"
        << "$$ I_3= " << res_om.I3 << " $$"
        << "$$ sum: " << unfull_round(res_om.I1 + res_om.I2 + res_om.I3, 4) << " $$" << end;
    std::string out_om = stream_om.str();
    output_om->setHtml(QString::fromStdString(out_om));

    // Метод узлового напряжения
    result_nem res_nem = calculate_nem(input_data);
    std::stringstream stream_nem;
    stream_nem << std::fixed << std::setprecision(3) << head
               << "$$ g_1= " << res_nem.g1 << " $$"
               << "$$ g_2= " << res_nem.g2 << " $$"
               << "$$ g_3= " << res_nem.g3 << " $$<br>"
               << "$$ U= "  << res_nem.U << " $$<br>"
               << "$$ I_1= " << res_nem.I1 << " $$"
               << "$$ I_2= " << res_nem.I2 << " $$"
               << "$$ I_3= " << res_nem.I3 << " $$"
               << "$$ sum: " << res_nem.I1 + res_nem.I2 + res_nem.I3 << " $$" << end;

    std::string out_nem = stream_nem.str();
    output_nem->setHtml(QString::fromStdString(out_nem));

    // Метод Узловых и контурных уравнений
    result_mnce res_mnce = calculate_mnce(input_data);
    std::stringstream stream_mnce;
    stream_mnce << std::fixed << std::setprecision(3) << head
                << "\\begin{cases}"
                << "I_1 + I_2 + I_3 = 0\\\\"
                << input_data.E1 - input_data.E2 << " = " << res_mnce.R101 << "·I_1 -"  << res_mnce.R202 << "·I_2\\\\"
                << input_data.E2 - input_data.E3 << " = " << res_mnce.R202 << "·I_2 -" << res_mnce.R303 << "·I_3\\\\"
                << "\\end{cases}"

                << "\\begin{cases}"
                << "I_1 = - I_2 - I_3\\\\"
                << input_data.E1 - input_data.E2 << " = -" << res_mnce.R101 << "·I_2 -" << res_mnce.R101 << "·I_3 -" << res_mnce.R202 << "·I_2\\\\"
                << input_data.E2 - input_data.E3 << " = " << res_mnce.R202 << "·I_2 -" << res_mnce.R303 << "·I_3"
                << "\\end{cases}"

                << "\\begin{cases}"
                << "I_1 = - I_2 - I_3\\\\"
                << input_data.E1 - input_data.E2 << " = -" << res_mnce.R101 + res_mnce.R202 << "·I_2 -" << res_mnce.R101 << "·I_3 | ·" << res_mnce.R303 << "\\\\"
                << input_data.E2 - input_data.E3 << " = " << res_mnce.R202 << "·I_2 -" << res_mnce.R303 << "·I_3 | ·" << res_mnce.R101
                << "\\end{cases}"

                << "\\begin{cases}"
                << (input_data.E1 - input_data.E2) * res_mnce.R303 << " = -" << (res_mnce.R101 + res_mnce.R202) * res_mnce.R303 << "·I_2 -" << res_mnce.R101 * res_mnce.R303 << "·I_3\\\\"
                << (input_data.E2 - input_data.E3) * res_mnce.R101 << " = " << res_mnce.R202 * res_mnce.R101 << "·I_2 -" << res_mnce.R303 * res_mnce.R101 << "·I_3\\\\"
                << "\\end{cases}"
                << "$$  ――――――――――――――― $$"
                << "$$" << res_mnce.R303 * (input_data.E1 - input_data.E2) - res_mnce.R101 * (input_data.E2 - input_data.E3) << " = " << -(res_mnce.R101 + res_mnce.R202) * res_mnce.R303 + res_mnce.R202 * res_mnce.R101 << "·I_2 $$"

                << "\\begin{cases}"
                << "I_3 = " << "\\frac{" << -(res_mnce.R303 * (input_data.E1 - input_data.E2) - res_mnce.R101 * (input_data.E2 - input_data.E3)) << "}{" << (res_mnce.R101 + res_mnce.R202) * res_mnce.R303 + res_mnce.R202 * res_mnce.R101 << "}\\\\"
                << "I_2 = " << "\\frac{" << -(input_data.E2 - input_data.E3 - res_mnce.I2 * res_mnce.R202) << "}{" << res_mnce.R303 << "}\\\\"
                << "I_1 = " <<  res_mnce.I2 << " - " << res_mnce.I3
                << "\\end{cases}"

                << "\\begin{cases}"
                << "I_1 =" << res_mnce.I1 << "\\\\"
                << "I_2 =" << res_mnce.I2 << "\\\\"
                << "I_3 =" << res_mnce.I3
                << "\\end{cases}"
                << "$$ sum: " << unfull_round(res_mnce.I1 + res_mnce.I2 + res_mnce.I3, 4) << " $$"
                << end;

    std::string out_mnce = stream_mnce.str();
    output_mnce->setHtml(QString::fromStdString(out_mnce));


    // Метод контурных токов
    result_lcm res_lcm = calculate_lcm(input_data);
    std::stringstream stream_lcm;
    stream_lcm  << std::fixed << std::setprecision(3) << head

        << "\\begin{cases}"
        << res_lcm.E1 + res_lcm.E2 << " = " <<res_lcm.R1 + res_lcm.R2 << "·I_{11} + " << res_lcm.R2 << "·I_{22}\\\\"
        << res_lcm.E2 + res_lcm.E3 << " = " <<res_lcm.R2 + res_lcm.R3 << "·I_{22} + " << res_lcm.R2 << "·I_{11}"
        << "\\end{cases}"

        << "\\begin{cases}"
        << res_lcm.E1 + res_lcm.E2 << " = " << res_lcm.R2 << "·I_{22} + " << res_lcm.R1 + res_lcm.R2 << "·I_{11}  | ·" <<res_lcm.R2 + res_lcm.R3 << "\\\\"
        << res_lcm.E2 + res_lcm.E3 << " = " <<res_lcm.R2 + res_lcm.R3 << "·I_{22} + " << res_lcm.R2 << "·I_{11}  | ·" << res_lcm.R2
        << "\\end{cases}"

        << "\\begin{cases}"
        << (res_lcm.E1 + res_lcm.E2) * (res_lcm.R2 + res_lcm.R3) << " = " <<res_lcm.R2 * (res_lcm.R2 + res_lcm.R3) <<
            "·I_{22} + " << (res_lcm.R1 + res_lcm.R2) * (res_lcm.R2 + res_lcm.R3) << "·I_{11}\\\\"
        << (res_lcm.E2 + res_lcm.E3) * res_lcm.R2 << " = " << (res_lcm.R2 + res_lcm.R3) * res_lcm.R2 << "·I_{22} + " << res_lcm.R2 * res_lcm.R2 << "·I_{11}"
        << "\\end{cases}"
        << "$$ ――――――――――――――――――――― $$"
        << "$$ " << (res_lcm.E1 + res_lcm.E2) * (res_lcm.R2 + res_lcm.R3) - (res_lcm.E2 + res_lcm.E3) * res_lcm.R2 <<
            " = " << (res_lcm.R1 + res_lcm.R2) * (res_lcm.R2 + res_lcm.R3) - res_lcm.R2 * res_lcm.R2 << "·I_{11} $$"

        << "\\begin{cases}"
        << "I_1 = " << res_lcm.I1 << "\\\\"
        << "I_2 = " << res_lcm.I2 << "\\\\"
        << "I_3=" << res_lcm.I3
        << "\\end{cases}"
        << "sum: " + std::to_string(unfull_round(res_lcm.I1 + res_lcm.I2 + res_lcm.I3, 4))
        << end;
    std::string out_lcm = stream_lcm.str();
    output_lcm->setHtml(QString::fromStdString(out_lcm));
}
