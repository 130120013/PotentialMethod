﻿#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct subject;

int a(vector<double>);
double K(double);
double evcl(subject, subject);
double H(vector<subject>, subject);

int h;
const int epsilon = 6;

//classes
enum soybeanClass { diaporthe_stem_canker, charcoal_rot, rhizoctonia_root_rot,
	brown_stem_rot, powdery_mildew, downy_mildew, bacterial_blight,
	bacterial_pustule, purple_seed_stain, anthracnose, phyllosticta_leaf_spot,
	diaporthe_pod_stem_blight, cyst_nematode, type_2_4_d_injury, herbicide_injury };

//for dividing to strings
vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

struct subject
{
	double x;
	double y;
	double z;
	subject() = default;
	subject(double X, double Y, double Z)
	{
		x = X; y = Y; z = Z;
	}
};


int a(vector<double> W) //find maximum W
{
	int res = 0;
	double start = W.front();

	for (int i = 1; i < W.size(); i++)
	{
		if (W[i] > start)
		{
			start = W[i];
			res = i;
		}
	}
	return res;
}

double evcl(subject a, subject b) //distance
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

double H(vector<subject> X, int ex) //Parsen's window with variable width
{
	vector<pair<double, int>> distances;

	for (int i = 0; i < X.size(); i++)
	{
		if (i != ex) //no repeats like evcl(X[2], X[2])
		{
			double dist = evcl(X[ex], X[i]);
			distances.push_back({ dist, i });
		}
	}

	for (auto it : distances)
	{
		std::sort(distances.begin(), distances.end());
	}

	double result = distances.front().first / distances[1].first;
	return result;
}

double K(double r)
{
	return 1 / (r + 1);
}

/////////////////////////////////////////////////////////////////////////////

vector<int> learnParams(vector<subject> X, const vector<soybeanClass> Y)
{
	int errorCount = 0;
	vector<int> q; //gamma

	for (int n = 0; n < X.size(); n++)
	{
		q.push_back(0);
	}

	vector<double> weights;

	int maxPotIndex = 0;
	do
	{
		errorCount = 0;
		for (int k = 0; k < X.size(); k++)
		{
			for (int i = 0; i < X.size(); i++)
			{
				double w = K(H(X, k))* q[i];
				weights.push_back(w); //find all W
			}

			maxPotIndex = a(weights); //find max W (its index)

			if (Y[maxPotIndex] != Y[k]) //different classes? +1 error, +1 for q
			{
				errorCount += 1;
				q[k] += 1;
			}

			weights.clear();
		}
	} while (errorCount > epsilon); //while errors more than limit (epsilon)

	ofstream outQ("124234.txt");
	if (!outQ.good())
	{
		outQ.open("124234.txt", ios::app);
		for (auto item : q)
		{
			outQ << item << "\n";
		}
	}
	return q;
}

void makeReportEducation()
{
}

void makeReportResult()
{
}

int main()
{
	ifstream istrX;
	ifstream istrParam; //for reading params
	ifstream istrY("1234.txt");
	ifstream inX("12.txt");
	istrX.open("123.txt", ios::in);
	string str;
	vector<subject> XLearn; //(read from file input)
	vector<soybeanClass> YLearn; //(read from file output)
	vector<subject> X; //âõîäû
	vector<int> param; //âàæíîñòü
	vector<double> W; //âûõîäû
	vector<pair<subject, double>> w;//использовать этот
	string n;
	vector<string> XL, sx;

	//getline(istrX, str);
	/*
		string s;
		while(getline(i, s))
		{
		cout<<s;
		str = split(s, ',');
	*/

	while (getline(istrX, n))
	{
		XL = split(n, ',');
		subject subj(stod(XL[0]), stod(XL[1]), stod(XL[2]));
		XLearn.push_back(subj);
	}

	while (getline(istrY, n))
	{
		YLearn.push_back(soybeanClass(stoi(n)));
	}

	while (getline(inX, n))
	{
		sx = split(n, ',');
		subject subj(stod(sx[0]), stod(sx[1]), stod(sx[2]));
		X.push_back(subj);
	}

	param = learnParams(XLearn, YLearn);

	return 0;
}
