#pragma once
#include "afxdialogex.h"


// Диалоговое окно ParamsDialog

class ParamsDialog : public CDialogEx
{
	DECLARE_DYNAMIC(ParamsDialog)

public:
	ParamsDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ParamsDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARAMS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int N;
	double k;
	double dt;
	double l0;
	double m;
	double mu;
	double betta;
	double x0;
	int Delay;
	int Radius;
	double kalpha;
	double kbetta;
	int ballid;
};
