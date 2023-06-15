#include <Eigen/Eigen>
#include <cmath>
#include <vector>
#include <iostream>

#ifndef ASTROSHELL_MERGECURVE_H
#define ASTROSHELL_MERGECURVE_H

namespace astroshell
{
    Eigen::Array<double, -1, 3> merge(const Eigen::Array<double, -1, 3>& phot1, const Eigen::Array<double, -1, 3>& phot2);
}
#endif //ASTROSHELL_MERGECURVE_H
