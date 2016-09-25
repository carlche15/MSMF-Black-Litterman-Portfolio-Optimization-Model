#ifndef CMC_H
#define CMC_H

#include <iostream>
#include<math.h>
#include<vector>
#include<string>
using namespace std;
class Matrix
{
public:
	Matrix();
	vector<vector<double>> inverse(vector<vector<double>> a);
	void show_matrix(vector<vector<double>> x);
	vector<vector<double>>multiplication(vector<vector<double>> x, vector<vector<double>> y);
	vector<vector<double>>addition(vector<vector<double>> x, vector<vector<double>> y);
	vector<vector<double>>subtraction(vector<vector<double>> x, vector<vector<double>> y);
	vector<vector<double>> generator(int num, string type);
	vector<vector<double>> ordinary_generator(int rows, int columns);
	vector<vector<double>> trans(vector<vector<double>>x);
	vector<vector<double>> scale(double x, vector<vector<double>>);
	vector<vector<double>>covariance(vector<vector<double>>x);
	vector<vector<double>>average;

private:
	double data[30][60];
	int size;
	static int times;
};







#endif