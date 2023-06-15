#include <vector>
#include <numeric>
#include <Eigen/Eigen>
#include <iostream>
#include <cmath>

#ifndef ASTROSHELL_FOURIER_H
#define ASTROSHELL_FOURIER_H

namespace astroshell
{
    class FourierSeriesModel
    {
    public:
        FourierSeriesModel(unsigned int order, double frequency);
        void fit(const Eigen::ArrayXd &x, const Eigen::ArrayXd &y);
        void iterative_fit(const Eigen::ArrayXd &x, const Eigen::ArrayXd &y);
        std::ostream& printFitParams(std::ostream& out = std::cout) const;
        [[nodiscard]] const std::vector<unsigned long>& getIndices() const;
        [[nodiscard]] Eigen::ArrayXd getValues(const Eigen::ArrayXd &x) const;
        void setSigma(double s);
    private:
        std::vector<unsigned long> indices;
        void getFitYVector(const Eigen::ArrayXd &x, const Eigen::ArrayXd &y);
        void getFitMatrix(const Eigen::ArrayXd &x);
        void getTrend(/*const Eigen::ArrayXd &x,*/ const Eigen::ArrayXd &y);
        void getSigma(const Eigen::ArrayXd &x, const Eigen::ArrayXd &y);

        unsigned int order;
        double frequency, /*a{},*/ b{}, sigma{}, n_sigma = 3;
        Eigen::ArrayXd fitYVector, coefficients;
        Eigen::MatrixXd fitMatrix;
    };

}

#endif //ASTROSHELL_FOURIER_H
