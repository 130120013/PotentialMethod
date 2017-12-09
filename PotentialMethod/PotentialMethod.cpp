#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

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