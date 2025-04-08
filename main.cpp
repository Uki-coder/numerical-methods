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

vector<double> gauss_elimination(vector<vector<double>> &koeffs, vector<double> &values)
{
    vector<double> beta, rho, ans;
    beta.push_back(koeffs[0][0]);
    rho.push_back(values[0]);

    const int SIZE = values.size();

    for (unsigned int i = 1; i < SIZE; i++)
    {
        beta.push_back(koeffs[i][i] - (koeffs[i][i - 1] / beta[i - 1]) * koeffs[i - 1][i]);

        rho.push_back(values[i] - (koeffs[i][i-1] / beta[i - 1]) * rho[i - 1]);
    }

    ans.push_back(rho[SIZE - 1] /  beta[SIZE - 1]);
    int hi = SIZE - 2;
     

    for (int i = SIZE - 2; i > -1; i--)
    {
        double value1 = ((rho[i] - koeffs[i][i + 1] * ans[0]) / beta[i]);
        ans.insert(ans.begin(), value1);
    }
    
    return ans;
}


int main()
{
    vector<double> values;
    for (int i = 0; i < 5; i++)
    {
        values.push_back(i);
    }
    
    vector<vector<double>> koeffs(5, vector<double>(5,0));

    for (int i = 0; i < 5; i++)
    {
        koeffs[i][i] = 2.;
    }

    for (int i = 0; i < 4; i++)
    {
        koeffs[i + 1][i] = -1.;
    }

    for (int i = 0; i < 4; i++)
    {
        koeffs[i][i + 1] = -1.;
    }
    
    vector<double> ans(gauss_elimination(koeffs, values));

    return 0;
}