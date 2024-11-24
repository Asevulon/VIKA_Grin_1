
// MyDlg.h: файл заголовка
//

#pragma once
#include"ParamsDialog.h"
#include"Model.h"
#include"ModelDrawer.h"
#include"GraphDlg.h"
// Диалоговое окно MyDlg
class MyDlg : public CDialogEx
{
// Создание
public:
	MyDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIKA_GRIN_1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedParamsDialogButton();
	ParamsDialog pdlg;
	Model model;
	bool init = false;

	ModelDrawer MainPic;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton StartButton;
	GraphDlg gdlg;
	UINT_PTR timerid;
	afx_msg void OnEnChangeEdit1();
	int BallId;
};
