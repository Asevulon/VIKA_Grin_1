#pragma once
#include "afxdialogex.h"
#include"Drawer.h"

// Диалоговое окно GraphDlg

class GraphDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GraphDlg)

public:
	GraphDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~GraphDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAPG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	Drawer EDrw;
	Drawer EkDrw;
	Drawer EpDrw;
	virtual BOOL OnInitDialog();
	Drawer BallDrw;
};
