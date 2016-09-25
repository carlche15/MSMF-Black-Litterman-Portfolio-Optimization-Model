#include"CarlsMatrixCalculator.h"

int Matrix::times = 1;
Matrix::Matrix(){
}
vector<vector<double>> Matrix::inverse(vector<vector<double>>vec)
{
	vector<vector<double>> raw;
	vector<vector<double>> result;
	raw = vec;
	size = vec.size();
	
	int i, j;
	data[30][60] = { 0 };
	for (i = 0; i<size; i++)
	{
		vector<double> temp = raw[i];
		for (j = 0; j<2 * size; j++)
		{
			if (j<size)
			{
				data[i][j] = temp[j];
			}
			else if (j == i + size)
				data[i][j] = 1.0;
			else
				data[i][j] = 0.0;
		}
	}
	int ii, jj, kk;
	int maxI = 0;
	for (ii = 1; ii<size; ii++)
	{
		if (fabs(data[maxI][0])<fabs(data[ii][0]))
			maxI = ii;
	}
	if (maxI != 0)
	{
		double temp;
		for (jj = 0; jj<2 * size; jj++)
		{
			temp = data[0][jj];
			data[0][jj] = data[maxI][jj];
			data[maxI][jj] = temp;
		}
	}
	double temp2;
	for (ii = 0; ii<size; ii++)
	{
		if (data[ii][ii] != 0)
			temp2 = 1.0 / data[ii][ii];
		else
		{
			cout << "this matrix has no inverse !" << endl;

		}
		for (jj = 0; jj<2 * size; jj++)
			data[ii][jj] *= temp2;
		for (jj = 0; jj<size; jj++)
		{
			if (jj != ii)
			{
				double temp3 = data[jj][ii];
				for (kk = 0; kk<2 * size; kk++)
					data[jj][kk] -= temp3*data[ii][kk];
			}
		}
	}
	int m, n;
	for (m = 0; m < size; m++)
	{
		vector<double> temp;
		for (n = size; n<2 * size; n++)
		{
			temp.push_back(data[m][n]);
		}
		result.push_back(temp);
	}
	return result;
}
vector<vector<double>> Matrix::multiplication(vector<vector<double>> x, vector<vector<double>> y){
	vector<vector<double>> multi1 = x;
	vector<vector<double>> multi2 = y;
	vector<vector<double>> multi_result;
	int rowsof1 = multi1.size();
	int columnsof2 = multi2[0].size();
	int columnsof1 = multi1[0].size();
	for (int i = 0; i < rowsof1; i++)
	{
		vector<double> temprow;
		for (int j = 0; j < columnsof2; j++)
		{
			double sum = 0;
			for (int k = 0; k < columnsof1; k++)
			{
				sum += multi1[i][k] * multi2[k][j];
				//cout << sum<<"~";
			}
			temprow.push_back(sum);
		}
		multi_result.push_back(temprow);
	}

	return multi_result;
}
vector<vector<double>> Matrix::addition(vector<vector<double>> x, vector<vector<double>> y){
	vector<vector<double>> add1;
	vector<vector<double>> add2;
	vector<vector<double>> add_result;
	add1 = x;
	add2 = y;
	int rows = add1.size();
	int columns = add1[0].size();
	for (int i = 0; i < rows; i++)
	{
		vector<double>temp;
		for (int j = 0; j < columns; j++)
		{
			temp.push_back(add1[i][j] + add2[i][j]);
		}
		add_result.push_back(temp);

	}

	return add_result;
}
vector<vector<double>> Matrix::subtraction(vector<vector<double>> x, vector<vector<double>> y){
	vector<vector<double>> add1;
	vector<vector<double>> add2;
	vector<vector<double>> add_result;
	add1 = x;
	add2 = y;
	int rows = add1.size();
	int columns = add1[0].size();
	for (int i = 0; i < rows; i++)
	{
		vector<double>temp;
		for (int j = 0; j < columns; j++)
		{
			temp.push_back(add1[i][j] - add2[i][j]);
		}
		add_result.push_back(temp);

	}

	return add_result;
}
vector<vector<double>> Matrix::generator(int num, string type)
{
	vector<vector<double>> single;
	if (type == "r")
	{
		vector<double> temp;
		for (int i = 0; i < num; i++)
		{
			temp.push_back(1);
		}
		single.push_back(temp);

	}
	else
	{
		for (int i = 0; i < num; i++)
		{
			vector<double> temp;
			temp.push_back(1);
			single.push_back(temp);
		}
	}
	return single;

}
vector<vector<double>> Matrix::ordinary_generator(int rows, int columns){
	vector<vector<double>>result;
	for (int i = 0; i < rows; i++)
	{
		vector<double>temp;
		for (int j = 0; j < columns; j++)
		{
			temp.push_back(0);
		}
		result.push_back(temp);
	}
	return result;
}
void Matrix::show_matrix(vector<vector<double>> x){
	vector<vector<double>>::iterator iter = x.begin();

	for (; iter != x.end(); iter++)
	{
		vector<double>::iterator iter2 = (*iter).begin();
		for (; iter2 != ((*iter).end()); iter2++)
			cout << (*iter2) << " ";
		cout << endl;
	}

}
vector<vector<double>> Matrix::trans(vector<vector<double>>x){
	vector<vector<double>>y;
	int oldrows = x.size();
	int oldcolumns = x[0].size();
	for (int j = 0; j < oldcolumns; j++)
	{
		vector<double> temp;
		for (int i = 0; i < oldrows; i++)
		{
			temp.push_back(x[i][j]);
		}
		y.push_back(temp);
	}
	return y;

}
vector<vector<double>>Matrix::scale(double x, vector<vector<double>>xx){
	vector<vector<double>>y = xx;
	vector<vector<double>>::iterator iter = y.begin();

	for (; iter != y.end(); iter++)
	{
		vector<double>::iterator iter2 = (*iter).begin();
		for (; iter2 != ((*iter).end()); iter2++)
			(*iter2) = (*iter2)*x;
	}
	return y;
}
vector<vector<double>>Matrix::covariance(vector<vector<double>>x){
	vector<vector<double>>ratevec = x;
	for (int m = 0; m < ratevec.size(); m++)
	{
		double sum = 0;
		for (int i = 0; i < ratevec[0].size(); i++)
		{
			sum += ratevec[m][i];
		}
		sum /= ratevec[0].size();
		vector<double>temp;
		temp.push_back(sum);
		average.push_back(temp);
	}

	vector<vector<double>> covmatrix;
	for (int i = 0; i < ratevec.size(); i++)
	{
		vector<double>temp;
		for (int j = 0; j < ratevec.size(); j++)
		{
			double sum = 0;
			for (int k = 0; k < ratevec[0].size(); k++)
			{
				sum += (ratevec[i][k] - average[i][0])*(ratevec[j][k] - average[j][0]);
			}
			temp.push_back(sum / ratevec[0].size());
		}
		covmatrix.push_back(temp);
	}
	return covmatrix;

}