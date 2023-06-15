#include <Eigen/Eigen>
#include <algorithm>

#ifndef ASTROSHELL_GETCOLOR_H
#define ASTROSHELL_GETCOLOR_H

namespace astroshell
{
    double getColor(const Eigen::Array<double, -1, 3>& phot1, const Eigen::Array<double, -1, 3>& phot2);
}

#endif //ASTROSHELL_GETCOLOR_H
