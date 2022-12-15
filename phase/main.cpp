#include <iostream>
#include <tools/InputParser.h>
#include "phase.h"

int main(int argc, char *argv[])
{
    std::ios::sync_with_stdio(false);
    tools::InputParser app(argc, argv);
    app.add_argument("period", "Period to phase the light curve", 'p');
    auto params = app.parse();
    double period = std::strtod(params["period"].c_str(), nullptr);

    const unsigned long MAX_SIZE = 1000000;

    auto *time = new double[MAX_SIZE], *mag = new double[MAX_SIZE], *mag_err = new double[MAX_SIZE];
    int counter = 0;

    while(std::cin >> time[counter] >> mag[counter] >> mag_err[counter]) ++counter;
    Eigen::Array<double, -1, 4> phot(counter, 4);
    phot.col(0) << Eigen::Map<Eigen::ArrayXd>(time, counter);
    phot.col(1) << Eigen::Map<Eigen::ArrayXd>(time, counter);
    phot.col(2) << Eigen::Map<Eigen::ArrayXd>(mag, counter);
    phot.col(3) << Eigen::Map<Eigen::ArrayXd>(mag_err, counter);
    delete[] time; delete[] mag; delete[] mag_err;
    std::vector<unsigned long> indices(counter); std::iota(indices.begin(), indices.end(), 0);

    astroshell::phase(phot, indices, 1.0 / period);

    std::cout << phot(indices, Eigen::all) << '\n';
}