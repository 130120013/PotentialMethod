#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double a(double, double);
double w(double, double, double);
double K(double);
const int h = 5;
int epsilon;

struct params
{
	double x;
	double p;
};

double a(double u, double w)
{
	double res;
	return res;
}

pair<double, double> p(double u, const vector<double> X)
{
	pair<double, double> res;
	res.second = res.first = X.front();
	for (auto it = X.begin(); it != X.end(); it++)
	{
		if (res.second > *it - u)
		{
			res.second = *it - u;
			res.first = *it;
		}
	}
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



vector<params> learnParams()
{
	vector<double> X; //входы 
	vector<double> Y; //выходы
	int errorCount = 0;
	vector<params> par;

	for (int j = 0; j < X.size(); j++)
	{
		params v;
		v.x = X[j];
		v.p = 0;
		par.emplace_back(v);
	}
	do
	{
		errorCount = 0;

		for (int i = 0; i < X.size(); i++)
		{
			if (a(X[i], 1) != Y[i])
			{
				errorCount += 1;
				par[i].p += 1;
			}
		}

	} while (errorCount > epsilon); //пока количество ошибок больше допустимого

	return par;
}

void makeReport()
{
	//выгрузка данных в блокнот
}

const double findPotential(double val, const vector<params>& param)
{
	for (auto it = param.begin(); it != param.end(); it++)
	{
		if (it->x == val)
		{
			return it->p;
		}
	}
}
//double h(double)

int main()
{
	vector<double> X; //входы
	vector<params> param; //важность
	vector<double> W; //выходы

	param = learnParams();

	for (auto i = 0; i < X.size(); i++)
	{
		W.emplace_back(K(p(X[i], X).second/h)*findPotential(p(X[i], X).second, param));
	}



	//erf - 2/sqrt(PI)*integral(0 - x) (e^(-t^2) dt)


	return 0;
}