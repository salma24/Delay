#ifndef UNTITLED_LAPLACE_H
#define UNTITLED_LAPLACE_H

#include <iostream>
#include<math.h>

class Laplace
{
    public:
        double* V;       //  Stehfest coefficients
        double ln2;       //  log of 2
        const int DefaultStehfestN = 14;
        double k1;
        double k2;
        double p1;
        double p2;

     double F(double t){
        return (k1*exp(-1*p1*t))+(k2*exp(-1*p2*t));
     }

    Laplace(double k1, double k2, double p1,double p2) {
        this->ln2 = log(2.0);
        InitStehfest(DefaultStehfestN);
        this->k1=k1;
        this->k2=k2;
        this->p1=p1;
        this->p2=p2;
    }


     double Transform(double s) {
        const int DefaultIntegralN = 5000;
        double du = 0.5 / (double)DefaultIntegralN;
        double y =  - F(0) / 2.0;
        double u = 0;
        double limit = 1.0 - 1e-10;
        while (u < limit)
        {
            u += du;
            y += 2.0 * pow(u, s - 1) * F(-1*log(u));
            u += du;
            y += pow(u, s - 1) * F(-1*log(u));
        }
        return 2.0 * y * du / 3.0;
    }

     double InverseTransform(double t) {
        double ln2t = ln2 / t;
        double x = 0;
        double y = 0;
        for (int i = 0; i < DefaultStehfestN; i++)
        {
            x += ln2t;
            y += V[i] * F(x);
        }
        return ln2t * y;
    }

     double Factorial(int N)
    {
        double x = 1;
        if (N > 1)
        {
            for (int i = 2; i <= N; i++)
                x = i * x;
        }
        return x;
    }
     void InitStehfest()
    {
        InitStehfest(DefaultStehfestN);
    }

     void InitStehfest(int N)
    {

        int N2 = N / 2;
        int NV = 2 * N2;
        V = new double[NV];
        int sign = 1;
        if ((N2 % 2) != 0)
            sign = -1;
        for (int i = 0; i < NV; i++)
        {
            int kmin = (i + 2) / 2;
            int kmax = i + 1;
            if (kmax > N2)
                kmax = N2;
            V[i] = 0;
            sign = -sign;
            for (int k = kmin; k <= kmax; k++) {
                V[i] = V[i] + (pow(k, N2) / Factorial(k)) * (Factorial(2 * k) / Factorial(2 * k - i - 1)) / Factorial(N2 - k) / Factorial(k - 1)/ Factorial(i + 1 - k);
            }
            V[i] = sign * V[i];
        }
    }
};
#endif //UNTITLED_LAPLACE_H
