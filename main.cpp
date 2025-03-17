#include <iomanip>
#include <iostream>
#include <cmath>

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

double count_error(double x_left, double x_right)
{
    double ans = (x_right - x_left)/x_right;

    if (ans < 0.) return -1.*ans;
    else return ans;
}

double middle(double left, double right)
{
    return (left + right)/2.;
}

//Function and its derrivative for task 1

double fun1(double x)
{
    double ans = (6435. * power(x, 8) - 12012. * power(x, 6)
    + 6930. * power(x, 4) - 1260. * power(x, 2) + 35.)/128.;
    return ans;
}

double derrivative_fun1(double x)
{
    double ans = (6435. * 8. * power(x, 7) - 12012. * 6. * power(x, 5)
    + 6930. * 4 * power(x, 3) - 1260. * 2. * x)/128.;
    return ans;
}

//Function and its derrivative for task 2

double fun2(double x)
{
    return x*x - 2*x -2;
}

double derrivative_fun2(double x)
{
    return 2*x - 2.;
}

//functions for Newton-Raphson step and bisectional step
double newton_raphson_step(double(*function)(double), double(*derrivative)(double), double x)
{
    return x - function(x)/derrivative(x);
}

//main algorythm
double hybryd_bisec_nr(double x_left, double x0, double x_right,
     double(*function)(double), double(*derrivative)(double),
     double tolerance = 1e-8)
{
    unsigned int nr_steps, bis_steps;
    nr_steps = 0;
    bis_steps = 0;
    double error = count_error(x_left, x_right);
    double x_old = x0;

    while(tolerance < error)
    {
        double derr = derrivative(x0);
        double check_value = ((x0-x_left)*derrivative(x0) - function(x0))*((x0-x_right)*derrivative(x0) - function(x0)); 

        if(check_value < 0) //NR step
        {
            x0 = newton_raphson_step(function, derrivative, x0);
            nr_steps++;
        }

        else //bisection step
        {
            x0 = middle(x_left, x_right);
            bis_steps++;
        }

        if (function(x_left) * function(x0) < 0)
        {
            x_right = x0;
        }

        else
        {
            x_left = x0;
        }

        error = count_error(x0, x_old);
        x_old = x0;
    }

    std::cout << "Newton-Raphson steps: " << nr_steps << '\n';
    std::cout << "Bisectional steps: " << bis_steps << "\n\n";

    return x0;
}


int main()
{
    std::cout << "Task 1" << "\n\n";
    double root_task1 = hybryd_bisec_nr(0.4, 0.4, 0.7, fun1, derrivative_fun1);
    std::cout << std::setprecision(8);
    std::cout << root_task1 << '\n';
    std::cout << "------------------------------------\n\n";

    std::cout << "Task 2" << "\n\n";
    double root_task2 = hybryd_bisec_nr(0., 0., 3., fun2, derrivative_fun2);
    std::cout << std::setprecision(9);
    std::cout << root_task2 << '\n';
    std::cout << "------------------------------------\n\n";

    return 0;
}