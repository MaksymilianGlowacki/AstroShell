#include <iostream>
#include <tools/InputParser.h>
#include "fourier.h"
#include <astroshell/phase/phase.h>


int main(int argc, char *argv[]) {
    std::ios::sync_with_stdio(false);
    tools::InputParser app(argc, argv);
    app.add_option("period", "Period of fourier function (in days). Default: 1", 'p');
    app.add_option("order", "Order of Fourier series to fit. Default: 4", 'n');
    app.add_option("max-input", "Maximal number of data points. Default: 100000", 'M');
    app.add_option("sigma", "Sigma range for iterative fit. Default: 3", 'S');
    app.add_flag("read-p", "Read period from stdin", 'r');
    app.add_flag("iterative", "Iterative fit excluding points outside S sigma range", 'i');
    app.add_flag("no-params", "Do not print parameters of the fitted function", 'd');
    app.add_flag("values", "Print values of the fitted function for phased light curve", 'v');
    auto params = app.parse();
    unsigned long MAX_SIZE = 100000;
    if(params.find("max-input") != params.end())
    {
        MAX_SIZE = std::strtol(params["max-input"].c_str(), nullptr, 10);
    }
    unsigned int order = 4;
    if(params.find("order") != params.end())
    {
        order = std::strtol(params["order"].c_str(), nullptr, 10);
    }
    double period = 1;
    if(params.find("period") != params.end())
    {
        period = std::strtod(params["period"].c_str(), nullptr);
    }
    if(params.find("read-p") != params.end())
    {
        std::cin >> period;
    }
    bool iterative = false;
    if(params.find("iterative") != params.end())
    {
        iterative = true;
    }
    bool fit_params = true, values = false;
    if(params.find("no-params") != params.end())
    {
        fit_params = false;
    }
    if(params.find("values") != params.end())
    {
        values = true;
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
    astroshell::phase(phot, indices, 1.0 / period);
    astroshell::FourierSeriesModel model(order, 1.0 / period);
    if(params.find("sigma") != params.end())
    {
        model.setSigma(std::strtod(params["sigma"].c_str(), nullptr));
    }
    if(iterative)
    {
        model.iterative_fit(phot(indices, 0) * period, phot(indices, 2));
        if(fit_params) model.printFitParams() << '\n';
        if(values)
        {
            Eigen::MatrixXd toPrint(phot(model.getIndices(), Eigen::all).rows(), 5);
            toPrint <<  phot(indices, 0)(model.getIndices()),
                    phot(indices, 1)(model.getIndices()),
                    phot(indices, 2)(model.getIndices()),
                    phot(indices, 3)(model.getIndices()),
                    model.getValues(phot(indices, 0)(model.getIndices()) * period);
            std::cout << toPrint;
        }

    }
    else
    {
        model.fit(phot(indices, 0) * period, phot(indices, 2));
        if(fit_params) model.printFitParams() << '\n';
        if(values)
        {
            Eigen::MatrixXd toPrint(phot.rows(), 5);
            toPrint <<  phot(indices, 0),
                    phot(indices, 1),
                    phot(indices, 2),
                    phot(indices, 3),
                    model.getValues(phot(indices, 0) * period);
            std::cout << toPrint;
        }
    }

    return 0;
}