﻿#include <iostream>
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

struct soybean
{
	int month;
	int hail;
	int severity;
	int leaves;
	int leafspots_halo;
	int lodfing;
	int canker_lesion;
	int fruiting_bodies;
	int mycelium;
	int int_discolor;
	int sclerotia;
	int fruit_pods;
};

/*
classes

1. diaporthe-stem-canker: 10
2. charcoal-rot: 10
3. rhizoctonia-root-rot: 10
5. brown-stem-rot: 20
6. powdery-mildew: 10
7. downy-mildew: 10
9. bacterial-blight: 10
10. bacterial-pustule: 10
11. purple-seed-stain: 10
12. anthracnose: 20
13. phyllosticta-leaf-spot: 10
16. diaporthe-pod-&-stem-blight: 6
17. cyst-nematode: 6
18. 2-4-d-injury: 1
19. herbicide-injury: 4
*/
struct params
{
	soybean x;
	double p;
};

double a(double u, double w)
{
	double res;
	return res;
}

double evcl(soybean a, soybean b) //или сделать x, y, z
{
	int month;
	int hail;
	int severity;
	int leaves;
	int leafspots_halo;
	int lodfing;
	int canker_lesion;
	int fruiting_bodies;
	int mycelium;
	int int_discolor;
	int sclerotia;
	int fruit_pods;
}

pair<double, double> p(soybean u, const vector<pair<soybean, double>> X) //берем sqrt((xi - xj)^2 + (yi - yj)^2 + ...)
{
	pair<soybean, double> res;
	res.second = X.front().second;
	for (auto it = X.begin(); it != X.end(); it++)
	{
		if (res.second > evcl())
		{
			res.second = *it - u;
			res.first = *it;
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


vector<params> learnParams(const vector<soybean> X, const vector<soybean> Y)
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
	ifstream istrX("123.txt");
	ifstream istrY("1234.txt");
	ifstream inX("12.txt");
	vector<double> XLearn; //(read from file input)
	vector<double> YLearn; //(read from file output)
	vector<double> X; //âõîäû
	vector<params> param; //âàæíîñòü
	vector<double> W; //âûõîäû
	vector<pair<soybean, double>> w;//использовать этот
	double n;

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