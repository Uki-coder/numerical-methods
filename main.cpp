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

//Function for tasks

double fun1(double x)
{
    return cos(x) - x;
}


//helping function for false_positon method

void fp_step(double &x_left, double &x0, double &x_right,
double(*function)(double))
{
    x0 = (x_left * function(x_right) - x_right * function(x_left)) / (function(x_right) - function(x_left));
    if (function(x_left) * function(x0) < 0)
    {
        x_right = x0;
    }

    else
    {
        x_left = x0;
    }
}

double false_positions(double(*function)(double),
    double x_left, double x_right,
    double tolerance = 1e-8)
{
    unsigned int steps = 1;
    double error, x0, x_old;

    fp_step(x_left, x0, x_right, function);
    x_old = x0;

    error = count_error(x_left, x_right);

    while(tolerance < error)
    {   
        fp_step(x_left, x0, x_right, function);

        error = count_error(x0, x_old);
        x_old = x0;
        steps++;
    }

    std::cout << "Iterations: " << steps << '\n';
    return x0;

}


//secant method

double secant(double(*function)(double),
    double x0, double x1, double tolerance = 1e-8)
{
    double x_old = x0;
    double x = x1;
    double x_next, error;

    unsigned int steps = 0;

    do
    {
        x_next = (x_old * function(x) - x * function(x_old)) / (function(x) - function(x_old));
        steps++;

        error = count_error(x, x_next);
        
        x_old = x;
        x = x_next;
        
    } while (error > tolerance);

    std::cout << "Iterations: " << steps << '\n';
    return x;
}


int main()
{
    std::cout << "False positions method:" << "\n";
    std::cout << "------------------------------------\n";
    double root_task1 = false_positions(fun1, 0.,1.);
    std::cout << std::setprecision(8);
    std::cout << root_task1 << '\n';
    std::cout << "------------------------------------\n\n";

    std::cout << "Secant method:" << "\n";
    std::cout << "------------------------------------\n";
    double root_task2 = secant(fun1, 0., 0.2);
    std::cout << std::setprecision(8);
    std::cout << root_task1 << '\n';
    std::cout << "------------------------------------\n\n";

    return 0;
}