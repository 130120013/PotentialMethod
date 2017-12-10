#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double a(double, double);
double w(double, double, double);
double K(double);
const int h = 3;

double a(double u, double w)
{
	double res;
	return res;
}

double w(double x, double p, double param)
{
	return param*K(p / h);
}

double K(double r)
{
	return 1 / (r + 1);
}

//double h(double)

int main()
{
	vector<double> X; //входы
	vector<double> params; //важность
	vector<double> H; //ширина потенциала
	vector<double> Y; //выходы

	double epsilon; //допустимая ошибка
	int i = 0;

	//erf - 2/sqrt(PI)*integral(0 - x) (e^(-t^2) dt)

	while (erf(1) > epsilon) //пока функция ошибки выдает результат больше epsilon
	{
		
	}
	return 0;
}