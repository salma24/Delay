#ifndef NEWTON_RAPHSON_H
#define NEWTON_RAPHSON_H

#include <stdio.h>
#include <math.h>
#include <conio.h>

#define EPSILON 1.0E-10
#define INITIAL_VAL 10
#define MAX_VALUES_NUM 20
#define MAX_ITERATIONS 200
#define TOL 0.00000001

double func(double x, double a1, double a2, double a3, double a4,double a5)
{
    double value = 1 + a1*x + a2*pow(x,2) + a3*pow(x,3) + a4*pow(x,4) + a5*pow(x,5);
    return value;
}

double derivative(double x, double a1, double a2, double a3, double a4, double a5)
{
    double value = a1 + 2*a2*pow(x,1) + 3*a3*pow(x,2) + 4*a4*pow(x,3) + 5*a5*pow(x,4);
    return value;
}

void newton(double a1,double a2,double a3,double a4,double a5)
{ 
    double x0 = INITIAL_VAL, x1; 
    double *values = new double[MAX_VALUES_NUM]; 
    //Newton-Raphson formula
    for(int i = 0;i <= MAX_ITERATIONS;i++) {
        x1 = x0 - func(x0,a1,a2,a3,a4,a5) / derivative(x0,a1,a2,a3,a4,a5);
        printf("%d\t\t %.8f\t %.8f\t %.8f\t %.8f\n", i, x0, x1, func(x0,a1,a2,a3,a4,a5), derivative(x0,a1,a2,a3,a4,a5));
        if(fabs(derivative(x0,a1,a2,a3,a4,a5)) < EPSILON) {
            //exit
            return;
        } else {
            x0 = x1;
            values[i] = x0; 
        }
    }

    if(fabs(values[MAX_ITERATIONS] - values[MAX_ITERATIONS-1]) <= TOL) { 

        printf("The solution after %d th iteration is %.10f.\n",MAX_ITERATIONS,x1);
        printf("%d th value is %.8f\n",MAX_ITERATIONS,values[MAX_ITERATIONS]);
        printf("%d th value is %.8f\n",MAX_ITERATIONS-1,values[MAX_ITERATIONS-1]);
        printf("The possible error in estimation is %.8f\n",fabs(values[MAX_ITERATIONS]-values[MAX_ITERATIONS-1]));
        printf("where as our tolerance is %.8f",TOL);

    } else {
        printf("Failed to meet tolerance after given iterations. So the roots cannot be found!\nMaybe try more iterations?\n");
        printf("%d th value is %.8f\n",MAX_ITERATIONS,values[MAX_ITERATIONS]);
        printf("%d th value is %.8f\n",MAX_ITERATIONS-1,values[MAX_ITERATIONS-1]);
        printf("The possible error in estimation is %.8f\n",fabs(values[MAX_ITERATIONS]-values[MAX_ITERATIONS-1]));
        printf("where as our tolerance is %.8f",TOL);
    }

    delete[] values; 
}
#endif //NEWTON_RAPHSON_H
