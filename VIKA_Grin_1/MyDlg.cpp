
// MyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "VIKA_Grin_1.h"
#include "MyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно MyDlg



MyDlg::MyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VIKA_GRIN_1_DIALOG, pParent)
	, BallId(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_PICTURE, MainPic);
	DDX_Control(pDX, IDOK, StartButton);
	DDX_Text(pDX, IDC_EDIT1, BallId);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &MyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_PARAMS_DIALOG_BUTTON, &MyDlg::OnBnClickedParamsDialogButton)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT1, &MyDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg

BOOL MyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	MainPic.SetPadding(10, 10, 10, 10);
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void MyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR MyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void MyDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (!init)OnBnClickedParamsDialogButton();
	if (model.InProc())
	{
		model.Stop();
		StartButton.SetWindowTextW(L"Старт");
		KillTimer(timerid);
	}
	else
	{
		model.main();
		timerid = SetTimer(123, 100, NULL);
		StartButton.SetWindowTextW(L"Стоп");
		gdlg.ShowWindow(SW_SHOW);
	}
}


void MyDlg::OnBnClickedParamsDialogButton()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (pdlg.DoModal() != IDOK)return;
	model.SetK(pdlg.k);
	model.SetN(pdlg.N);
	model.SetDt(pdlg.dt);
	model.SetL0(pdlg.l0);
	model.SetMu(pdlg.mu);
	model.SetM(pdlg.m);
	model.SetBetta(pdlg.betta);
	model.SetX0(pdlg.x0);
	model.SetDelay(pdlg.Delay);
	MainPic.SetRadius(pdlg.Radius);
	init = true;
}


void MyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	MainPic.SetData(model.GetX());
	MainPic.Invalidate();

	gdlg.EDrw.SetData(model.GetE());
	gdlg.EDrw.Invalidate();
	gdlg.EkDrw.SetData(model.GetEk());
	gdlg.EkDrw.Invalidate();
	gdlg.EpDrw.SetData(model.GetEp());
	gdlg.EpDrw.Invalidate();
	gdlg.BallDrw.SetData(model.GetPath(BallId));
	gdlg.BallDrw.Invalidate();
	CDialogEx::OnTimer(nIDEvent);
}


void MyDlg::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	UpdateData();
}
