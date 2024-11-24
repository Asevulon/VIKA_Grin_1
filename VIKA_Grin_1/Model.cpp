#include "pch.h"
#include "Model.h"

void Model::DoStep(int id)
{
	double kk[4] = { 0,0,0,0 };
	unique_lock<mutex>lk(xmutex);
	double cx(x[id]), cv(v[id]);
	double xl = x[id - 1];
	double xr = x[id + 1];
	lk.unlock();

	kk[0] = f(xl, xr, cx, cv) * dt;
	kk[1] = f(xl, xr, cx + cv * dt / 2., cv + kk[0] / 2.) * dt;
	kk[2] = f(xl, xr, cx + cv * dt / 2. + kk[0] * dt / 4., cv + kk[1] / 2.) * dt;
	kk[3] = f(xl, xr, cx + cv * dt + kk[1] * dt / 2., cv + kk[2]) * dt;

	lk.lock();
	x[id] = cx + v[id] * dt + (1. / 6.) * (kk[0] + kk[1] + kk[2]) * dt;
	path[id].push_back(x[id]);
	lk.unlock();
	v[id] = cv + (1. / 6.) * (kk[0] + 2 * kk[1] + 2 * kk[2] + kk[3]);

	t += dt;
}

double Model::f(double xl, double xr, double cx, double cy)
{
	double dll = (l0 - (cx - xl));
	double dlr = (l0 - (xr - cx));
	double kl = k + kalpha * fabs(dll) + kbetta * dll * dll;
	double kr = k + kalpha * fabs(dlr) + kbetta * dlr * dlr;
	double left = kl * dll / m;
	double right = -kr * dlr / m;
	double tr = mu * g;
	if (cy > 0)tr = -tr;
	double trv = -betta * cy / m;
	return left + right + tr + trv;
}

void Model::threadFunc()
{
	unique_lock<mutex>lk(smutex);
	while (Continue)
	{
		for (int i = 1; i < N - 1; i++)
		{
			DoStep(i);
		}
		CalcEnergy();
		Sleep(Delay);
	}
}

void Model::CalcEnergy()
{
	double e = 0;
	double ek = 0;
	double ep = 0;
	double temp = 0;
	double ktemp = 0;
	unique_lock<mutex>lk(xmutex);
	for (auto& item : v)ek += m * item * item / 2.;
	for (int i = 0; i < N - 1; i++)
	{
		temp = l0 - (x[i + 1] - x[i]);
		ktemp = k + kalpha * fabs(temp) + kbetta * temp * temp;
		ep += ktemp * temp * temp / 2.;
	}
	lk.unlock();

	e = ek + ep;

	unique_lock<mutex>lk1(emutex);

	Ek.push_back(ek);
	Ep.push_back(ep);
	E.push_back(e);
}

void Model::main()
{
	Continue = true;
	x.resize(N);
	v.resize(N);
	E.clear();
	Ek.clear();
	Ep.clear();

	path = vector<vector<double>>(N, vector<double>());

	for (int i = 0; i < N; i++)
	{
		x[i] = i * l0;
		v[i] = 0;
		path[i].push_back(x[i]);
	}
	x[1] += l0 * x0;

	thread newthread([&]() {threadFunc(); });
	newthread.detach();
}

void Model::SetN(int val)
{
	N = val;
}

void Model::SetK(double val)
{
	k = val;
}

void Model::SetDt(double val)
{
	dt = val;
}

void Model::SetL0(double val)
{
	l0 = val;
}

void Model::SetMu(double val)
{
	mu = val;
}

void Model::SetM(double val)
{
	m = val;
}

void Model::SetBetta(double val)
{
	betta = val;
}

void Model::SetX0(double val)
{
	x0 = val;
}

void Model::SetDelay(int val)
{
	Delay = val;
}

void Model::SetKAlpha(double val)
{
	kalpha = val;
}

void Model::SetKBetta(double val)
{
	kbetta = val;
}

vector<double> Model::GetX()
{
	unique_lock<mutex>lk(xmutex);
	return x;
}

vector<double> Model::GetE()
{
	unique_lock<mutex>lk1(emutex);
	return E;
}

vector<double> Model::GetEk()
{
	unique_lock<mutex>lk1(emutex);
	return Ek;
}

vector<double> Model::GetEp()
{
	unique_lock<mutex>lk1(emutex);
	return Ep;
}

vector<double> Model::GetPath(int id)
{
	if ((id < 0) || id >= N)return vector<double>();
	unique_lock<mutex>lk(xmutex);
	return path[id];
}

void Model::Stop()
{
	Continue = false;
	unique_lock<mutex>lk(smutex);
}

bool Model::InProc()
{
	return Continue;
}
