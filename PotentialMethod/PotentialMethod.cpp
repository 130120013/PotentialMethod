#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
	vector<double> X; //�����
	vector<double> params; //��������
	vector<double> H; //������ ����������
	vector<double> Y; //������

	double epsilon; //���������� ������
	int i = 0;

	//erf - 2/sqrt(PI)*integral(0 - x) (e^(-t^2) dt)

	while (erf(1) > epsilon) //���� ������� ������ ������ ��������� ������ epsilon
	{
		
	}
	return 0;
}