#pragma once


// ModelDrawer
#include<gdiplus.h>
#include<vector>
#include<algorithm>
using namespace std;
using namespace Gdiplus;


class ModelDrawer : public CStatic
{
	DECLARE_DYNAMIC(ModelDrawer)
private:
	vector<double>data;

	double lPadding;
	double rPadding;
	double tPadding;
	double bPadding;
	int MarksLen;

	double left;
	double right;
	double bot = 0;
	double top = 100;


	ULONG_PTR token;
	
	CString title;
	int radius = 20;

public:
	ModelDrawer();
	virtual ~ModelDrawer();

protected:
	double CalcStringLen(HDC hDC, CString string);
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	void SetData(vector<double>&y);

	//Отступ задается в процентах (диапазон значений от 0 до 100)
	void SetPadding(double lPadding, double rPadding, double tPadding, double bPadding);
	void SetMarksLen(int len);
	void SetTitle(CString str);
	void SetRadius(int val);
};


