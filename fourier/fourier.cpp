#include "fourier.h"

astroshell::FourierSeriesModel::FourierSeriesModel(unsigned int order, double frequency) : order(order), frequency(frequency)
{}

void astroshell::FourierSeriesModel::getFitYVector(const Eigen::ArrayXd &x, const Eigen::ArrayXd &y) {
    fitYVector = Eigen::ArrayXd::Zero(2 * order);
    for(unsigned int n = 0; n < order; ++n)
    {
        fitYVector[2 * n] = (y * ((n + 1) * x * frequency * 2 * M_PI).sin()).sum();
        fitYVector[2 * n + 1] = (y * ((n + 1) * x * frequency * 2 * M_PI).cos()).sum();
    }
}

void astroshell::FourierSeriesModel::getFitMatrix(const Eigen::ArrayXd &x) {
    fitMatrix = Eigen::MatrixXd::Zero(2 * order, 2 * order);
    for(unsigned int row = 0; row < order; ++row)
    {
        for(unsigned int col = 0; col < order; ++col)
        {
            fitMatrix(2 * row, 2 * col) = (((col + 1) * x * frequency * 2 * M_PI).sin()
                                                    * ((row + 1) * x * frequency * 2 * M_PI).sin()).sum();

            fitMatrix(2 * row, 2 * col + 1) = (((col + 1) * x * frequency * 2 * M_PI).cos()
                                           * ((row + 1) * x * frequency * 2 * M_PI).sin()).sum();
        }
        for(unsigned int col = 0; col < order; ++col)
        {
            fitMatrix(2 * row + 1, 2 * col) = (((col + 1) * x * frequency * 2 * M_PI).sin()
                                           * ((row + 1) * x * frequency * 2 * M_PI).cos()).sum();

            fitMatrix(2 * row + 1, 2 * col + 1) = (((col + 1) * x * frequency * 2 * M_PI).cos()
                                               * ((row + 1) * x * frequency * 2 * M_PI).cos()).sum();
        }
    }
}

void astroshell::FourierSeriesModel::fit(const Eigen::ArrayXd &x, const Eigen::ArrayXd &y) {
    getTrend(y);
    getFitMatrix(x);
    getFitYVector(x, y - b);
    coefficients = fitMatrix.inverse() * fitYVector.matrix();
}

Eigen::ArrayXd astroshell::FourierSeriesModel::getValues(const Eigen::ArrayXd &x) const{
    Eigen::ArrayXd vals = Eigen::ArrayXd::Zero(x.rows(), x.cols());
    for(unsigned int n = 0; n < order; ++n)
    {
        vals += coefficients(2 * n) * ((n + 1) * x * frequency * 2 * M_PI).sin();
        vals += coefficients(2 * n + 1) * ((n + 1) * x * frequency * 2 * M_PI).cos();
    }
    return vals + b;
}

void astroshell::FourierSeriesModel::getTrend(/*const Eigen::ArrayXd &x,*/ const Eigen::ArrayXd &y) {
    /*
    auto S = (double)x.rows();
    double Sx = x.sum();
    double Sy = y.sum();
    double Sxx = x.square().sum();
    double Sxy = (x * y).sum();

    a = ((S * Sxy) - (Sx * Sy)) / (S * Sxx - (Sx * Sx));
    b = ((Sxx * Sy) - (Sx * Sxy)) / (S * Sxx - (Sx * Sx));
    a = 0;
     */
    b = y.mean();
}

void astroshell::FourierSeriesModel::getSigma(const Eigen::ArrayXd &x, const Eigen::ArrayXd &y) {
    sigma = sqrt((y - getValues(x)).square().mean());
}

void astroshell::FourierSeriesModel::iterative_fit(const Eigen::ArrayXd &x, const Eigen::ArrayXd &y) {
    indices = std::vector<unsigned long>(x.rows()); std::iota(indices.begin(), indices.end(), 0);
    std::vector<unsigned long> new_indices;
    new_indices.reserve(x.rows());
    bool if_removed;
    Eigen::ArrayXd diff;
    do {
        if_removed = false;
        fit(x(indices), y(indices));
        getSigma(x(indices), y(indices));
        diff = (y - getValues(x)).abs();
        for(auto index : indices)
        {
            if(diff((long)index) > n_sigma * sigma)
            {
                if_removed = true;
            } else
            {
                new_indices.emplace_back(index);
            }
        }
        indices = new_indices;
        new_indices.clear();
    } while(if_removed);
}

std::ostream& astroshell::FourierSeriesModel::printFitParams(std::ostream& out) const{
    out << b << ' ' << coefficients.transpose();
    return out;
}

const std::vector<unsigned long> &astroshell::FourierSeriesModel::getIndices() const{
    return indices;
}

void astroshell::FourierSeriesModel::setSigma(double s) {
    n_sigma = s;
}
