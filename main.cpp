#include <iostream>
#include <cmath>
#include <iomanip>

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

//Function and its derrivative for task 1

double fun1(double x)
{
    return cos(x) - x;
}

double derrivative_fun1(double x)
{
    return -sin(x) - 1;
}

//Function and its derrivative for task 2

double fun2(double x)
{
    double ans = (6435. * power(x, 8) - 12012. * power(x, 6)
    + 6930. * power(x, 4) - 1260. * power(x, 2) + 35.)/128.;
    return ans;
}

double derrivative_fun2(double x)
{
    double ans = (6435. * 8. * power(x, 7) - 12012. * 6. * power(x, 5)
    + 6930. * 4 * power(x, 3) - 1260. * 2. * x)/128.;
    return ans;
}

//Function and its derrivative for task 3

double fun3(double x)
{
    return power(x,3) - 169.;
}

double derrivative_fun3(double x)
{
    return 3.*power(x,2);
}

//main algorythm 

double count_root(double(*fun)(double), double(*derr)(double),
 double x0, double tolerance = 1e-8)
{
    double x_i, x_i1, error;
    int counter = 0;

    x_i = x0;

    while (true)
    {
        x_i1 = x_i - fun(x_i)/derr(x_i);
        error = count_error(x_i, x_i1);
        counter++;
        x_i = x_i1;

        if (error <= tolerance) break;
    }

    return x_i1;
}

//running function
int main()
{
    std::cout << std::setprecision(8);

    /*Task 1:
    cos(x) - x = 0
    tolerance: 1e-8*/


    std::cout << "Task 1: \n";
    std::cout << "x_root: " << count_root(fun1, derrivative_fun1, 0.) << '\n';
    // 5 iterations
    std::cout << "------------------------------\n\n";

    /*
    Task 2
    P(x) = (6435x**8 - 12012x**6 + 6930x**4 -1260x**2 +35)/128
    tolerance: 1e-8
    */

    std::cout << "Task 2: \n";
    std::cout << "x_root 1: " << count_root(fun2, derrivative_fun2, 0.15) << '\n';
    std::cout << "x_root 2: " << count_root(fun2, derrivative_fun2, 0.5) << '\n';
    std::cout << "x_root 3: " << count_root(fun2, derrivative_fun2, 0.75) << '\n';
    std::cout << "x_root 4: " << count_root(fun2, derrivative_fun2, 0.9) << '\n';
    std::cout << "------------------------------\n\n";

    /*
    Task 3
    x = 13**(2/3)
    tolerance: 1e-8
    */

    std::cout << "Task 3: \n";
    std::cout << std::setprecision(9) <<"x_root: " << count_root(fun3, derrivative_fun3, 4.) << '\n'; //idk why 9 lol
    // 5 iterations
    std::cout << "------------------------------\n\n";

    return 0;
}