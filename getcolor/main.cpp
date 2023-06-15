#include <fstream>
#include <iostream>
#include <iomanip>
#include <tools/InputParser.h>
#include "getcolor.h"


int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    tools::InputParser app(argc, argv, true);
    app.add_option("max-input", "Maximal number of data points. Default: 100000", 'M');
    app.add_argument("curve-1", "File to read the light curve in I band", '1');
    app.add_argument("curve-2", "File to read the light curve in V band", '2');
    auto params = app.parse();
    unsigned long MAX_SIZE = 100000;
    if(params.find("max-input") != params.end())
    {
        MAX_SIZE = std::strtol(params["max-input"].c_str(), nullptr, 10);
    }
    std::ifstream input1(params["curve-1"], std::ios::in), input2(params["curve-2"], std::ios::in);
    if(!input1.good())
    {
        std::cerr << "Can't open file " << params["curve-1"] << "\n";
        return 1;
    }
    if(!input2.good())
    {
        std::cerr << "Can't open file " << params["curve-2"] << "\n";
        return 2;
    }

    auto *time = new double[MAX_SIZE], *mag = new double[MAX_SIZE], *mag_err = new double[MAX_SIZE];
    int counter = 0;

    while(input1 >> time[counter] >> mag[counter] >> mag_err[counter]) ++counter;
    Eigen::Array<double, -1, 3> phot1(counter, 3);
    phot1.col(0) << Eigen::Map<Eigen::ArrayXd>(time, counter);
    phot1.col(1) << Eigen::Map<Eigen::ArrayXd>(mag, counter);
    phot1.col(2) << Eigen::Map<Eigen::ArrayXd>(mag_err, counter);

    counter = 0;
    while(input2 >> time[counter] >> mag[counter] >> mag_err[counter]) ++counter;
    Eigen::Array<double, -1, 3> phot2(counter, 3);
    phot2.col(0) << Eigen::Map<Eigen::ArrayXd>(time, counter);
    phot2.col(1) << Eigen::Map<Eigen::ArrayXd>(mag, counter);
    phot2.col(2) << Eigen::Map<Eigen::ArrayXd>(mag_err, counter);
    delete[] time; delete[] mag; delete[] mag_err;
    input1.close(); input2.close();

    double color = astroshell::getColor(phot1, phot2);
    std::cout << color << '\n';
    return 0;
}