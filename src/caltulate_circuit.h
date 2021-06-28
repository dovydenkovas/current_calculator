#ifndef CALCULATOR_CIRCUIT_CALTULATE_CIRCUIT_H
#define CALCULATOR_CIRCUIT_CALTULATE_CIRCUIT_H
#include <iostream>


/*
 *  Функции расчета токов электрической цепи.
 */
double unfull_round(double a, int n);

struct input_data {
    double E1;
    double R01;
    double R1;
    double E2;
    double R02;
    double R2;
    double E3;
    double R03;
    double R3;
};

struct result_nem {
    double g1;
    double g2;
    double g3;
    double U;
    double I1;
    double I2;
    double I3;
};

result_nem calculate_nem(input_data in);

struct result_om {
    double R101;
    double R202;
    double R303;
    double R1o;
    double R1e;
    double U1;
    double I11;
    double I12;
    double I13;
    double R2o;
    double R2e;
    double I22;
    double U2;
    double I21;
    double I23;
    double R3o;
    double R3e;
    double I33;
    double U3;
    double I32;
    double I31;
    double I1;
    double I2;
    double I3;
};

result_om calculate_om(input_data in);

struct result_mnce {
    double R101;
    double R202;
    double R303;
    double I1;
    double I2;
    double I3;
};

result_mnce calculate_mnce(input_data in);

struct result_lcm {
    double E1;
    double E2;
    double E3;
    double R1;
    double R2;
    double R3;
    double I1;
    double I2;
    double I3;
};

result_lcm calculate_lcm(input_data in);


#endif //CALCULATOR_CIRCUIT_CALTULATE_CIRCUIT_H
