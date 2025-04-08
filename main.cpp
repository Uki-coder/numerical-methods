#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//Helping functions

double power(double number, int powe)
{
    double ans = number;
    for (int i = 0; i < powe - 1; i++)
    {
        ans *= number;
    }

    return ans;
}

//Function for tasks

double fun1(double x)
{
    return exp(x);
}

double fun2(double x)
{
    return 1./(1 + x * x);
}

double derr1(double x)
{
    return exp(x);
}

double derr2(double x)
{
    return - 2 * x / power((x * x + 1), 4);
}
//helping function for false_positon method
double count_l(vector<double>&x_array, unsigned int j, double x)
{
    double result = 1.;

    for (unsigned int i = 0; i < j; i++)
    {
        result *= (x-x_array[i]) / (x_array[j] - x_array[i]);
    }

    for(unsigned int i = j + 1; i < x_array.size(); i ++)
    {
        result *= (x-x_array[i]) / (x_array[j] - x_array[i]);
    }

    return result;
}

double count_l2(vector<double>&x_array, unsigned int j)
{
    double result = 0.;

    for (unsigned int i = 0; i < j; i++)
    {
        result += 1. / (x_array[j] - x_array[i]);
    }

    for(unsigned int i = j + 1; i < x_array.size(); i ++)
    {
        result += 1. / (x_array[j] - x_array[i]);
    }

    return result;
    
}

double count_h(vector<double>&x_array, unsigned int j, double x)
{
    return (1 - 2 * (x - x_array[j]) * count_l2(x_array, j)) * count_l(x_array, j, x);
}

double count_h2(vector<double>&x_array, unsigned int j, double x)
{
    return (x - x_array[j]) * power(count_l(x_array, j, x),2);
}

double lagange_interpolation(vector<double>&x_array, double x, double(*function)(double))
{
    double result = 0.;

    for (unsigned int j = 0; j < x_array.size(); j++)
    {
        result += count_l(x_array, j, x) + function(x_array[j]);
    }

    return result;
}

double hermite_interpolation(vector<double>&x_array, double x, double(*function)(double), double(*derrivative)(double))
{
    double result = 0.;

    for(unsigned int j = 0; j < x_array.size(); j ++)
    {
        result += count_h(x_array, j, x) * function(x_array[j]) + count_h2(x_array, j, x) * derrivative(x_array[j]);
    }

    return result;
}

int main()
{
    vector<double> x;

    for (double i = -5.; i < 5.1; i += 0.1)
    {
        x.push_back(i);
    }

    vector<double> inter1{-1., 0.5, 1.5, 2.};
    vector<double> inter2;

    for(int i = 0; i < 6.; i++)
    {
        inter2.push_back(i);
    }

    vector<double>result1l;
    vector<double>result1h;
    vector<double>result2l;
    vector<double>result2h;

    for (int i = 0; i < x.size(); i++)
    {
        result1l.push_back(lagange_interpolation(inter1, x[i], fun1));
        result2l.push_back(lagange_interpolation(inter2, x[i], fun2));

        result1h.push_back(hermite_interpolation(inter1, x[i], fun1, derr1));
        result2h.push_back(hermite_interpolation(inter2, x[i], fun2, derr2));
    }

    return 0;
}