#include "getcolor.h"

double astroshell::getColor(const Eigen::Array<double, -1, 3>& phot1, const Eigen::Array<double, -1, 3>& phot2)
{
    double diff = 100000;
    long long t1_index = 0, t2_index = 0;
    auto upper = phot1.col(0).begin();
    for(long index = 0; index < phot2.rows(); ++index)
    {
        upper = std::lower_bound(phot1.col(0).begin(), phot1.col(0).end(), phot2(index, 0));
        if(upper != phot1.col(0).begin() && (std::abs(phot2(index, 0) - (*(upper - 1))) < diff))
        {
                diff = std::abs(phot2(index, 0) - (*(upper - 1)));
                t2_index = index;
                t1_index = upper - 1 - phot1.col(0).begin();
        }
        if(upper != phot1.col(0).end() && std::abs(phot2(index, 0) - (*upper)) < diff)
        {
            diff = std::abs(phot2(index, 0) - (*upper));
            t2_index = index;
            t1_index = upper - phot1.col(0).begin();
        }
    }

    return phot2(t2_index, 1) - phot1(t1_index, 1);
}