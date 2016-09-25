#include"CarlsMatrixCalculator.h"
#include<fstream>
#include<string>
using namespace std;
vector < vector < double >>readin_assets(string a){


	ifstream infile;
	if (a == "asset")
	{
		infile.open("pdata.txt");
		double x;
		bool mark = 1;
		vector<double> indatas;
		vector<double>::iterator inda;
		int num;
		cout << "Please input the numbers of assets in the portfolio (default is 4) " << endl;
		cin >> num;

		while (mark)
		{
			infile >> x;
			if (infile)
			{
				indatas.push_back(x);
			}
			else
			{
				mark = 0;
				if (infile.eof())
				{
				}
				else
					cout << "Wrong file!" << endl;
			}
		}

		vector<vector<double>>pricevec;

		vector<double>temp0;
		for (int i = 0; i < indatas.size(); i++)
		{
			temp0.push_back(indatas[i]);
			if ((((i + 1) % (indatas.size() / num)) == 0) && i != 0)
			{
				pricevec.push_back(temp0);
				temp0.clear();
			}
		}

		return pricevec;
	}
	else if (a=="market")
	{
		vector<vector<double>>pricevec;
		infile.open("s&p500.txt");
		double x;
		bool mark = 1;
		vector<double> indatas;
		vector<double>::iterator inda;
		while (mark)
		{
			infile >> x;
			if (infile)
			{
				indatas.push_back(x);
			}
			else
			{
				mark = 0;
				if (infile.eof())
				{
				}
				else
					cout << "Wrong file!" << endl;
			}
		}
		pricevec.push_back(indatas);
		return pricevec;
	}
	else if (a=="rate")
	{
		vector<vector<double>>pricevec;
		infile.open("rf.txt");
		double x;
		bool mark = 1;
		vector<double> indatas;
		vector<double>::iterator inda;
		while (mark)
		{
			infile >> x;
			if (infile)
			{
				indatas.push_back(x);
			}
			else
			{
				mark = 0;
				if (infile.eof())
				{
				}
				else
					cout << "Wrong file!" << endl;
			}
		}
		pricevec.push_back(indatas);
		return pricevec;
	}
	else
	{
		vector<vector<double>>pricevec;
		infile.open("market_cap.txt");
		double x;
		bool mark = 1;
		vector<double> indatas;
		vector<double>::iterator inda;
		while (mark)
		{
			infile >> x;
			if (infile)
			{
				indatas.push_back(x);
			}
			else
			{
				mark = 0;
				if (infile.eof())
				{
				}
				else
					cout << "Wrong file!" << endl;
			}
		}
		pricevec.push_back(indatas);
		return pricevec;
	}

	
}
vector < vector < double >>to_rates(vector < vector < double >>pricevec)
{
	vector<vector<double>>ratevec;
	for (int i = 0; i < pricevec.size(); i++)
	{
		vector<double>temp;
		for (int j = 0; j < pricevec[0].size() - 1; j++)
		{
			temp.push_back((pricevec[i][j + 1] - pricevec[i][j]) / pricevec[i][j]);
		}
		ratevec.push_back(temp);
	}
	return ratevec;

}
double average(vector < vector<double>>x){
	int rows = x.size();
	int columns = x[0].size();
	double sum = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			sum += x[i][j];
		}
	}
	return sum / (rows*columns);

}
int main()
{
	cout << "                      --Black-Litterman Portfolio Optimizing Project--" <<endl<< endl;
	cout << "By Dongdi Jia & Tongda Che" << endl;

	//Get datas!
 vector<vector<double>>pricevec=readin_assets("asset");
 vector<vector<double>>ratevec = to_rates(pricevec);
 vector<vector<double>>marketindexvec = readin_assets("market");
 vector<vector<double>>marketratevec = to_rates(marketindexvec);
 vector<vector<double>>riskfreeratevec = readin_assets("rate");
 vector<vector<double>>marketcap = readin_assets("marketcap");

 // Step #1 Calculating the investors' risk aversion A
 Matrix carl;
 vector<vector<double>>excessreturn = carl.subtraction(marketratevec, riskfreeratevec);
 vector<vector<double>>VarianceofMarketReturn = carl.covariance(marketratevec);
 double num = average(excessreturn);
 double den = VarianceofMarketReturn[0][0];
 double A = num / den;
 cout << "#1#  The parameter of investors' Risk Aversion A is " << A << endl;
 cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;

 // Step #2 Calculating the covariance matrix of assets;
 vector<vector<double>>S = carl.covariance(ratevec);
 cout << "#2#  The Covariance Matrix of Portfolio Assets is " << endl;
 carl.show_matrix(S);
 cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;

 // Step #3 Calculating the market weights
 double sumvalue = average(marketcap)*marketcap.size()*marketcap[0].size();
 marketcap=carl.scale(1 / sumvalue, marketcap);
 marketcap = carl.trans(marketcap);
 cout << "#3#  The Market Weights of the Portfolio is" << endl;
 carl.show_matrix(marketcap);
 cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;

// Step #4 Calculating Implied Equilibrium Excess Return.
 vector<vector<double>>PI;
 PI = carl.multiplication(S, marketcap);
 PI = carl.scale(A, PI);
 cout << "#4#  The Implied Equilibrium Excess Return Matrix of the Portfolio assets " << endl;
 carl.show_matrix(PI);
 cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;

 // Step #5 Incorporating the views and Step #6 Link Matrix

//Here, we have two views: 1. Apple is going to out perform NOKIA by 1.5%.  2. Goldman is going to out perform GM by 2%;
 //Then we have the Views Matrix Q:
 vector<vector<double>>Q;
 vector<double> view1;
 vector<double> view2;
 view1.push_back(0.015);
 view2.push_back(0.017);
 Q.push_back(view1);
 Q.push_back(view2);
 vector<vector<double>>P = carl.ordinary_generator(2, 4);
     P[0][0] = 1;
	 P[0][1] = -1;
	 P[1][2] = 1;
	 P[1][3] = -1;
	 cout << "#5#  Views upon the market: Here we get two views--1. Apple is going to out perform Nokia by 1.5%;  2. Goldman is going to out perform GM by 1.7%." << endl;
	 cout << "*So the matrix of Views is" << endl;
	 carl.show_matrix(Q);
	 cout << "*The matrix of the Link Matrix is" << endl;
	 carl.show_matrix(P);
	 cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;

	
//	Step #7 Calculating the uncertainty about the views
	 double tao = 1.0;
	 vector<vector<double>> Omiga;
	 Omiga = carl.multiplication(P, S);
	 Omiga = carl.multiplication(Omiga, carl.trans(P)); 1,
	 Omiga = carl.scale(tao, Omiga);
	 cout << "#6# The Matrix of Uncertainty of the Views: " << endl;
	 carl.show_matrix(Omiga);
	 cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;


// Step #8 Using the Formula
	 vector<vector<double>>eme;
	 vector<vector<double>>eme1;
	 vector<vector<double>>eme2;
	eme1 = carl.inverse( carl.addition( carl.inverse ( carl.scale(tao, S)), carl.multiplication( carl.multiplication(carl.trans(P), carl.inverse(Omiga)), P) ) );
	eme2 = carl.addition( carl.multiplication( carl.inverse ( carl.scale(tao, S)), PI), carl.multiplication ( carl.multiplication(carl.trans(P), carl.inverse(Omiga)), Q));
	eme = carl.multiplication(eme1, eme2);
	cout << "#7#  With the parameters above, apply the Black-Litterman Formula and acquired	BL Expected Returns :" << endl;
	carl.show_matrix(eme);
	cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;



	 // MVF
	// START!
	//Crucial paras;
	double a;
	double b;
	double c;
	double D;
	double rate = 0.01;
	double onenum = S.size();
	vector<vector<double>> variance;
	vector<vector<double>> e;


//	carl.show_matrix(excessreturn);
	variance = carl.covariance(ratevec);
    e = eme;
	cout << "Expected Return of the portfolio: " << rate << endl;
	vector<vector<double>> v_inverse = carl.inverse(S);
	cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;

	//calculate a
	vector<vector<double>>one_tran = carl.generator(onenum, "r");
	vector<vector<double>>temp = carl.multiplication(one_tran, v_inverse);
	temp = carl.multiplication(temp, e);
	a = temp[0][0];
	
	
	//carlculate B
	
	temp = carl.trans(e);
	temp = carl.multiplication(temp, v_inverse);
	temp = carl.multiplication(temp, e);
	b = temp[0][0];
	
	// calculate C
	temp = carl.multiplication(one_tran, v_inverse);
	temp = carl.multiplication(temp, carl.trans(one_tran));
	c = temp[0][0];
	
	
	
	// calculate D
	D = b*c - a*a;


	//calculating g;
	vector<vector<double>>temp2;
	temp = carl.scale(b, one_tran);
	temp2 = carl.scale(a, carl.trans(e));
	temp = carl.subtraction(temp, temp2);
	temp = carl.multiplication(temp, v_inverse);
	temp = carl.scale(1.0 / D, temp);
	vector<vector<double>>g = temp;

	//calculating h;

	temp = carl.scale(c, carl.trans(e));
	temp2 = carl.scale(a, one_tran);
	temp = carl.subtraction(temp, temp2);
	temp = carl.multiplication(temp, v_inverse);
	temp = carl.scale(1.0 / D, temp);
	vector<vector<double>>h = temp;
	
	//calculating w
	cout << endl;
	vector<vector<double>>wp;
	temp = carl.scale(rate, h);
	temp = carl.addition(g, temp);
	wp = temp;
	cout << "With the Matrix of BL Returns, we then apply the traditional optimizing method, MVF Method and finally acquired the weight of the portfolio:" << endl;
	carl.show_matrix(wp);
	cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;
	cout << "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;
	cout << "~~~~~~END OF THE PROGRAM~~~~~~" << endl;
	return 0;
}
