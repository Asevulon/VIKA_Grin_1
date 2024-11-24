// GraphDlg.cpp: файл реализации
//

#include "pch.h"
#include "VIKA_Grin_1.h"
#include "afxdialogex.h"
#include "GraphDlg.h"


// Диалоговое окно GraphDlg

IMPLEMENT_DYNAMIC(GraphDlg, CDialogEx)

GraphDlg::GraphDlg(CWnd* pParent /*=nullptr*/)
	//: CDialogEx(IDD_GRAPG_DIALOG, pParent)
{
	Create(IDD_GRAPG_DIALOG);
}

GraphDlg::~GraphDlg()
{
}

void GraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Graph1, EDrw);
	DDX_Control(pDX, IDC_Graph2, EkDrw);
	DDX_Control(pDX, IDC_Graph3, EpDrw);
	DDX_Control(pDX, IDC_Graph4, BallDrw);
}


BEGIN_MESSAGE_MAP(GraphDlg, CDialogEx)
END_MESSAGE_MAP()


// Обработчики сообщений GraphDlg


BOOL GraphDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	EDrw.SetPadding(22, 22, 10, 10);
	EDrw.SetTitle(L"E");
	EkDrw.SetPadding(22, 22, 10, 10);
	EkDrw.SetTitle(L"Ek");
	EpDrw.SetPadding(22, 22, 10, 10);
	EpDrw.SetTitle(L"Ep");
	BallDrw.SetPadding(22, 22, 10, 10);
	BallDrw.SetTitle(L"Путь шара");
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
