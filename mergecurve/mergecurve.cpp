#include "mergecurve.h"

Eigen::Array<double, -1, 3> astroshell::merge(const Eigen::Array<double, -1, 3>& phot1, const Eigen::Array<double, -1, 3>& phot2)
{
    std::vector<double> vals;
    vals.reserve(phot2.rows());
    int j = 0;
    for(int i = 0; i < phot1.rows(); ++i)
    {
        for(; j < phot2.rows(); ++j)
        {
            if(std::abs(phot1(i, 0) - phot2(j, 0)) < 0.000005)
            {
                vals.emplace_back(phot1(i, 1) - phot2(j, 1));
                break;
            }
        }
    }
    if((long)vals.size() != phot1.rows())
    {
        std::cerr << "Points missing in the second curve!\n";
        exit(3);
    }
    for(unsigned long i = 1; i < vals.size(); ++i)
    {
        if(std::abs(vals[i] - vals[i - 1]) > 0.0005)
        {
            std::cerr << "Calibration error!\n";
            exit(4);
        }
    }
    Eigen::Array<double, -1, 3> result(phot1.rows() + (phot2.rows() - j - 1), 3);
    result << phot1, phot2(Eigen::seq(j + 1, Eigen::last), Eigen::all);
    result(Eigen::seq(phot1.rows(), Eigen::last), 1) += 1000;
    return result;
}

