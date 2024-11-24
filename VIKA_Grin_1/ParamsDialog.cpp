// ParamsDialog.cpp: файл реализации
//

#include "pch.h"
#include "VIKA_Grin_1.h"
#include "afxdialogex.h"
#include "ParamsDialog.h"


// Диалоговое окно ParamsDialog

IMPLEMENT_DYNAMIC(ParamsDialog, CDialogEx)

ParamsDialog::ParamsDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PARAMS_DIALOG, pParent)
	, N(10)
	, k(100)
	, dt(0.001)
	, l0(1)
	, m(1)
	, mu(0)
	, betta(0)
	, x0(0.5)
	, Delay(100)
	, Radius(5)
	, kalpha(0)
	, kbetta(0)
{

}

ParamsDialog::~ParamsDialog()
{
}

void ParamsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, N);
	DDX_Text(pDX, IDC_EDIT2, k);
	DDX_Text(pDX, IDC_EDIT3, dt);
	DDX_Text(pDX, IDC_EDIT4, l0);
	DDX_Text(pDX, IDC_EDIT5, m);
	DDX_Text(pDX, IDC_EDIT6, mu);
	DDX_Text(pDX, IDC_EDIT7, betta);
	DDX_Text(pDX, IDC_EDIT8, x0);
	DDX_Text(pDX, IDC_EDIT9, Delay);
	DDX_Text(pDX, IDC_EDIT10, Radius);
	DDX_Text(pDX, IDC_EDIT11, kalpha);
	DDX_Text(pDX, IDC_EDIT12, kbetta);
}


BEGIN_MESSAGE_MAP(ParamsDialog, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений ParamsDialog
