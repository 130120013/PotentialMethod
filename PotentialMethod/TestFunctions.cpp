#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct subject;

int a(vector<int>);
//double w(double, double, double);
double K(double);
double evcl(subject, subject);
double H(vector<subject>, subject);

int h;
const int epsilon = 18;

//classes
enum soybeanClass {
	diaporthe_stem_canker, charcoal_rot, rhizoctonia_root_rot,
	brown_stem_rot, powdery_mildew, downy_mildew, bacterial_blight,
	bacterial_pustule, purple_seed_stain, anthracnose, phyllosticta_leaf_spot,
	diaporthe_pod_stem_blight, cyst_nematode, type_2_4_d_injury, herbicide_injury
};

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

//struct params
//{
//	subject x;
//	double p;
//	soybeanClass classVal;
//	params() = default;
//	params(subject X, double P, soybeanClass cV)
//	{
//		x = X; p = P; classVal = cV;
//	}
//};

int a(vector<int> W)
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

double H(vector<subject> X, int ex, int& index) //Parsen's window with variable width
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
	index = distances.front().second;
	return result;
}
//Л И Ш Н Е Е
//pair<subject, double> p(subject u, const vector<subject> X) //берем sqrt((xi - xj)^2 + (yi - yj)^2 + ...) 
//{
//	pair<subject, double> res;
//	res.second = 0;
//	for (auto it = X.begin(); it != X.end(); it++)
//	{
//		if (res.second > evcl(u, (*it)))
//		{
//			res.second = evcl(u, (*it));
//			res.first = (*it);
//		}
//	}
//	return res;
//}

//double w(double x, double param)
//{
//	return param * K(h);
//}

double K(double r)
{
	return 1 / (r + 1);
}


vector<int> learnParams(vector<subject> X, const vector<soybeanClass> Y)
{
	int errorCount = 0;
	vector<int> q; //gamma

	for (int n = 0; n < X.size(); n++)
	{
		q.push_back(0);
	}

	vector<int> weights;

	double maxW = 0;
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

			//			maxPotIndex = a(weights, weights[k]); //find max W (its index)
			maxPotIndex = a(weights); //find max W (its index)

			if (Y[maxPotIndex] != Y[k]) //different classes? +1 error, +1 for q
			{
				errorCount += 1;
				q[k] += 1;
			}

			weights.clear();
		}
	} while (errorCount > epsilon); //while errors more than limit (epsilon)

	cout << "\n\n\n";
	for (auto it = q.begin(); it != q.end(); it++)
	{
		cout << *it << " - ";
	}
	
	ofstream outQ;
		outQ.open("124234.txt", ios::out | ios::trunc);
		for (int item = 0; item < q.size(); item++)
		{
			outQ << q[item] << "\n";
		}
	
	return q;
}

void makeReportEducation()
{
	//âûãðóçêà äàííûõ â áëîêíîò
}

void makeReportResult(const vector<subject> X, const vector<int> q, const vector<subject> XLearned, const vector<soybeanClass> Y)
{
	ofstream outQ;
	outQ.open("ReportResult.txt", ios::app);
	
	outQ << "\n_____RESULTS_____\n";
	vector<int> weights;
	int errorCount, maxPotIndex = 0;
		errorCount = 0;
		for (int k = 0; k < X.size(); k++)
		{
			for (int i = 0; i < X.size(); i++)
			{
				double w = K(H(X, k, maxPotIndex));
				w = w * q[maxPotIndex];
				weights.push_back(w); //find all W
			}

			maxPotIndex = a(q); //find max W (its index)

			outQ << "Subject: x - " << X[k].x << ", y - " << X[k].y << ", z - " << X[k].z <<";";
			outQ << " Result: class " << Y[maxPotIndex] << " - ";
			if ((soybeanClass)Y[maxPotIndex] != Y[k]) //different classes? +1 error, +1 for q
			{
				errorCount += 1;
				outQ << "WRONG CLASS! RIGHT - " << Y[k] << ".\n";
			}
			else
			{
				cout<< Y[k]<< "\n";
				outQ << "OK\n";
			}
		}

		outQ << "Error count = " << errorCount << "\n_____END REPORT_____\n";
}

//Л И Ш Н Е Е
//const double findPotential(subject val, const vector<params>& param)
//{
//	for (auto it = param.begin(); it != param.end(); it++)
//	{
//		if (it->x.x == val.x && it->x.y == val.y && it->x.z == val.z)
//		{
//			return it->p;
//		}
//	}
//}
//double h(double)

int main()
{

	
	//ifstream istrX;
	//ifstream istrY("1234.txt");
	//ifstream inX("12.txt");
	//istrX.open("123.txt", ios::in);
	//string str;
	/*vector<subject> XLearn; //(read from file input)
	vector<soybeanClass> YLearn; //(read from file output)
	vector<subject> X; //âõîäû
	vector<int> param; //âàæíîñòü
	vector<double> W; //âûõîäû

	XLearn.push_back(subject(1, 2, 3));
	XLearn.push_back(subject(2, 1, 1));
	XLearn.push_back(subject(1, 1, 2));
	XLearn.push_back(subject(2, 1, 2));
	//XLearn.push_back(subject(1, 1, 0));
	//XLearn.push_back(subject(1, 3, 0));
	XLearn.push_back(subject(1, 1, 2));
	XLearn.push_back(subject(2, 2, 1));
	XLearn.push_back(subject(1, 1, 2));
	//XLearn.push_back(subject(1, 4, 0));
	XLearn.push_back(subject(2, 3, 1));
	XLearn.push_back(subject(1, 3, 1));
	XLearn.push_back(subject(1, 2, 4));
	XLearn.push_back(subject(1, 4, 7));

	YLearn.push_back(soybeanClass(1));
	YLearn.push_back(soybeanClass(3));
	YLearn.push_back(soybeanClass(1));
	YLearn.push_back(soybeanClass(3));
	//YLearn.push_back(soybeanClass(2));
	//YLearn.push_back(soybeanClass(2));
	YLearn.push_back(soybeanClass(1));
	YLearn.push_back(soybeanClass(3));
	YLearn.push_back(soybeanClass(1));
	//YLearn.push_back(soybeanClass(2));
	YLearn.push_back(soybeanClass(3));
	YLearn.push_back(soybeanClass(1));
	YLearn.push_back(soybeanClass(1));
	YLearn.push_back(soybeanClass(1));*/


	//cout << evcl(XLearn[0], XLearn[1])<<"\n";

ifstream istrX;
	ifstream istrParam; //for reading params
	ifstream istrY;
	//ifstream inX("12.txt");
	istrX.open("123.txt", ios::in);
	istrY.open("1234.txt", ios::in);
	istrParam.open("124234.txt", ios::in);
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
/*
	for(auto it : XLearn)
	{
		cout<< it.x <<"\n";
	}*/
	while (getline(istrY, n))
	{
		YLearn.push_back(soybeanClass(stoi(n)));
	}
	
	while (getline(istrParam, n))
	{
		param.push_back(stoi(n));
	}
	param = learnParams(XLearn, YLearn);
	cout<<"\n\n\n";

	makeReportResult(XLearn, param, XLearn, YLearn);

	system("pause");

	//vector<pair<subject, double>> w;//использовать этот
	//string n;
	//vector<string> XL, sx;

	////getline(istrX, str);
	///*
	//string s;
	//while(getline(i, s))
	//{
	//cout<<s;
	//str = split(s, ',');
	//*/

	//while (getline(istrX, n))
	//{
	//	XL = split(n, ',');
	//	subject subj(stod(XL[0]), stod(XL[1]), stod(XL[2]));
	//	XLearn.push_back(subj);
	//}

	//while (getline(istrY, n))
	//{
	//	YLearn.push_back(soybeanClass(stoi(n)));
	//}

	//while (getline(inX, n))
	//{
	//	sx = split(n, ',');
	//	subject subj(stod(sx[0]), stod(sx[1]), stod(sx[2]));
	//	X.push_back(subj);
	//}

	//param = learnParams(XLearn, YLearn);

	///*for (auto i = 0; i < X.size(); i++)
	//{
	//W.emplace_back(K(p(X[i], XLearn).second / h)*findPotential(p(X[i], XLearn).first, param));
	//}*/

	return 0;
}
