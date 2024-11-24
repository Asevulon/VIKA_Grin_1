#pragma once
#include<vector>
#include<thread>
#include<mutex>
using namespace std;

class Model
{
private:
	int N = 0;
	double k = 0;
	double dt = 0;
	double t = 0;
	double l0 = 0;
	double mu = 0;
	double m = 0;
	double g = 9.8;
	double betta = 0;
	double x0;
	double tE = 0;
	double tEk = 0;
	double tEp = 0;
	int Delay = 0;
	double kalpha = 0;
	double kbetta = 0;

	vector<double>x;
	vector<double>v;
	vector<double>Ek;
	vector<double>Ep;
	vector<double>E;
	vector<vector<double>>path;
	bool Continue = false;

	mutex xmutex;
	mutex smutex;
	mutex emutex;
protected:
	void DoStep(int id);
	double f(double xl, double xr, double cx, double cy);
	void threadFunc();
	void CalcEnergy();
public:
	void main();

	void SetN(int val);
	void SetK(double val);
	void SetDt(double val);
	void SetL0(double val);
	void SetMu(double val);
	void SetM(double val);
	void SetBetta(double val);
	void SetX0(double val);
	void SetDelay(int val);
	void SetKAlpha(double val);
	void SetKBetta(double val);
	vector<double> GetX();
	vector<double> GetE();
	vector<double> GetEk();
	vector<double> GetEp();
	vector<double> GetPath(int id);
	void Stop();
	bool InProc();

};

