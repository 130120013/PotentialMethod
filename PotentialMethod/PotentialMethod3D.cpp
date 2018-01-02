#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

double a(double, double);
double w(double, double, double);
double K(double);
const int h = 5;
int epsilon;

struct subject
{
	double x;
	double y;
	double z;
};

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

double evcl(subject a, subject b) //или сделать x, y, z
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

pair<subject, double> p(subject u, const vector<pair<subject, double>> X) //берем sqrt((xi - xj)^2 + (yi - yj)^2 + ...)
{
	pair<subject, double> res;
	res.second = X.front().second;
	for (auto it = X.begin(); it != X.end(); it++)
	{
		if (res.second > evcl(u, (*it).first))
		{
			res.second = evcl(u, (*it).first);
			res.first = (*it).first;
		}
	}
	return res;
}

double w(double x, double p, double param)
{
	return param * K(p / h);
}

double K(double r)
{
	return 1 / (r + 1);
}


vector<params> learnParams(const vector<double> X, const vector<double> Y)
{
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

	} while (errorCount > epsilon); //ïîêà êîëè÷åñòâî îøèáîê áîëüøå äîïóñòèìîãî

	return par;
}

void makeReport()
{
	//âûãðóçêà äàííûõ â áëîêíîò
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
	ifstream istrX;
	ifstream istrY("1234.txt");
	ifstream inX("12.txt");
	istrX.open("123.txt");
	string str;
	vector<subject> XLearn; //(read from file input)
	vector<subject> YLearn; //(read from file output)
	vector<subject> X; //âõîäû
	vector<params> param; //âàæíîñòü
	vector<double> W; //âûõîäû
	vector<pair<subject, double>> w;//использовать этот
	double n;

	getline(istrX, str);

	while (istrX >> n)
	{
		YLearn.push_back(n);
	}

	while (istrY >> n)
	{
		XLearn.push_back(n);
	}
	param = learnParams(XLearn, YLearn);

	for (auto i = 0; i < X.size(); i++)
	{
		W.emplace_back(K(p(X[i], XLearn).second / h)*findPotential(p(X[i], XLearn).second, param));
	}



	//erf - 2/sqrt(PI)*integral(0 - x) (e^(-t^2) dt)

	return 0;
}