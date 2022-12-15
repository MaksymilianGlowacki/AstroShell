#include <iostream>
#include <iomanip>
#include <tools/InputParser.h>
#include "getperiod.h"


int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    tools::InputParser app(argc, argv, true);
    app.add_option("max-input", "Maximal number of data points. Default: 100000", 'M');
    app.add_flag("forward", "Forwards the photometry data to the next program", 'f');
    auto params = app.parse();
    unsigned long MAX_SIZE = 100000;
    if(params.find("max-input") != params.end())
    {
        MAX_SIZE = std::strtol(params["max-input"].c_str(), nullptr, 10);
    }
    bool forward = false;
    if(params.find("forward") != params.end())
    {
        forward = true;
    }

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

    std::cout << std::setprecision(8) << astroshell::getPeriod(phot, indices) << '\n';
    if(forward)
    {
        std::cout << phot(Eigen::all, {1, 2, 3});
    }
    return 0;
}
