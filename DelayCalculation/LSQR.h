#ifndef UNTITLED_LSQR_H
#define UNTITLED_LSQR_H

#include <iostream>
#include "eigen-eigen-323c052e1731\Eigen\Dense"
#include "eigen-eigen-323c052e1731\Eigen\Sparse"

class LSQR
{
public:
    Eigen::VectorXd x;
    LSQR(const Eigen::SparseMatrix<double> &A, const Eigen::VectorXd &b, const Eigen::VectorXd &x_ini, const double &gamma);
    Eigen::VectorXd SolutionX();
};



#endif //UNTITLED_LSQR_H
