#include "phase.h"

void astroshell::phase(Eigen::Array<double, -1, 4> &phot, std::vector<unsigned long> &indices, double frequency)
{
    phot.col(0) = phot.col(1) * frequency;
    phot.col(0) -= phot.col(0).floor();
    std::sort(indices.begin(), indices.end(),
              [&phot](long a, long b){return phot(a, 0) < phot(b, 0);});
}