#include <cmath>
#include "caltulate_circuit.h"


double unfull_round(double a, int n=3) {
    int power = std::pow(10, n);
    double result = std::round(a * power) / power;
    return result;
}


result_nem calculate_nem(input_data in) {
    /* Расчитывает токи методом узлового напряжения */
    result_nem res;
    res.g1 = 1/(in.R01 + in.R1);
    res.g2 = 1/(in.R02 + in.R2);
    res.g3 = 1/(in.R03 + in.R3);
    res.U = unfull_round((in.E1 * res.g1 + in.E2 * res.g2 + in.E3 * res.g3) / (res.g1 + res.g2 + res.g3));
    res.I1 = unfull_round((in.E1 - res.U) * res.g1);
    res.I2 = unfull_round((in.E2 - res.U) * res.g2);
    res.I3 = unfull_round((in.E3 - res.U) * res.g3);
    return res;
}


result_om calculate_om(input_data in) {
    /* Расчитывает токи методом наложения */
    result_om res;

    //int recount(I1,I2,I3):
    //return [I1,abs(I2),abs(I3)] if I1 < 0 else [I1,-abs(I2),-abs(I3)]

    // Первый этап
    res.R101 = in.R1 + in.R01;
    res.R202 = in.R2 + in.R02;
    res.R303 = in.R3 + in.R03;
    res.R1o = unfull_round(res.R202 * res.R303 / (res.R202 + res.R303));
    res.R1e = res.R1o + res.R101;
    res.I11 = unfull_round(in.E1 / res.R1e);
    res.U1 = unfull_round(res.I11 * res.R1o);
    res.I12 = unfull_round(res.U1 / res.R202);
    res.I13 = unfull_round(res.U1 / res.R303);
    res.I12 = res.I11<=0 ? std::abs(res.I12) : -std::abs(res.I12);
    res.I13 = res.I11<=0 ? std::abs(res.I13) : -std::abs(res.I13);

    // Второй этап
    res.R2o = unfull_round(res.R101 * res.R303 / (res.R101 + res.R303));
    res.R2e = res.R2o+res.R202;
    res.I22 = unfull_round(in.E2 / res.R2e);
    res.U2 = unfull_round(res.I22 * res.R2o);
    res.I21 = unfull_round(res.U2 / res.R101);
    res.I23 = unfull_round(res.U2 / res.R303);
    res.I21 = res.I22<=0 ? std::abs(res.I21) : -std::abs(res.I21);
    res.I23 = res.I22<=0 ? std::abs(res.I23) : -std::abs(res.I23);

    // Третий этап
    res.R3o = unfull_round(res.R202 * res.R101 / (res.R202 + res.R101));
    res.R3e = res.R3o + res.R303;
    res.I33 = unfull_round(in.E3 / res.R3e);
    res.U3 = unfull_round(res.I33 * res.R3o);
    res.I32 = unfull_round(res.U3 / res.R202);
    res.I31 = unfull_round(res.U3 / res.R101);
    res.I31 = res.I33<=0 ? std::abs(res.I31) : -std::abs(res.I31);
    res.I32 = res.I33<=0 ? std::abs(res.I32) : -std::abs(res.I32);

    res.I1 = res.I11 + res.I21 + res.I31;
    res.I2 = res.I12 + res.I22 + res.I32;
    res.I3 = res.I13 + res.I23 + res.I33;

    return res;
}



result_mnce calculate_mnce(input_data in) {
    /* Расчитывает токи методом узловых и контурных уравнений */
    result_mnce res;

    res.R101 = in.R1 + in.R01;
    res.R202 = in.R2 + in.R02;
    res.R303 = in.R3 + in.R03;

    res.I2 = - (res.R303*(in.E1-in.E2)-res.R101*(in.E2-in.E3)) / ((res.R101+res.R202)*res.R303+res.R202*res.R101);
    res.I3 = - (in.E2-in.E3-res.I2*res.R202)/res.R303;
    res.I1 = - res.I2-res.I3;

    return res;
};



result_lcm calculate_lcm(input_data in) {
    /* Расчитывает токи методом контурных токов */
    result_lcm res;

    res.R1 = in.R1 + in.R01;
    res.R2 = in.R2 + in.R02;
    res.R3 = in.R3 + in.R03;

    res.E1 = -in.E1;
    res.E2 = in.E2;
    res.E3 = -in.E3;

    double I11 = ((res.E1+res.E2)*(res.R2+res.R3)-(res.E2+res.E3)*res.R2) / ((res.R1+res.R2)*(res.R2+res.R3)-res.R2*res.R2);
    double I22 = (res.E2+res.E3-I11*res.R2) / (res.R2 + res.R3);

    res.I1 = -I11;
    res.I2 = I22 + I11;
    res.I3 = -I22;

    return res;
};
