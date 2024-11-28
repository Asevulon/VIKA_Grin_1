// ModelDrawer.cpp: файл реализации
//

#include "pch.h"
#include "ModelDrawer.h"


// ModelDrawer

IMPLEMENT_DYNAMIC(ModelDrawer, CStatic)

ModelDrawer::ModelDrawer()
{
	GdiplusStartupInput si;
	GdiplusStartup(&token, &si, NULL);
}

ModelDrawer::~ModelDrawer()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(ModelDrawer, CStatic)
END_MESSAGE_MAP()



// Обработчики сообщений ModelDrawer




void ModelDrawer::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics ToWindow(lpDrawItemStruct->hDC);
	int width = lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left;
	int height = lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;
	Bitmap bmp(width, height);
	Graphics gr(&bmp);
	gr.Clear(Color::White);

	if (data.empty())
	{
		ToWindow.DrawImage(&bmp, 0, 0);
		return;
	}

	gr.SetSmoothingMode(SmoothingModeAntiAlias);
	double actWidth(right - left);
	double actHeight(top - bot);
	double actLP = actWidth * lPadding / 100.;
	double actRP = actWidth * rPadding / 100.;
	double actTP = actHeight * tPadding / 100.;
	double actBP = actHeight * bPadding / 100.;

	double actTop = top + actTP;
	double actBot = bot - actBP;
	double actLeft = left - actLP;
	double actRight = right + actRP;

	actWidth = actRight - actLeft;
	actHeight = actTop - actBot;


	double xScale = width / actWidth;
	double yScale = -height / actHeight;

	Pen BackGroundPen(Color(200, 200, 200));

	Matrix matr;
	matr.Scale(xScale, yScale);
	matr.Translate(actLP - left, -actTop);


	float steplenY = (top - bot) / 10.;
	float steplenX = (right - left) / 10.;

	FontFamily FF(L"Arial");
	Gdiplus::Font font(&FF, 12, FontStyle::FontStyleRegular, UnitPixel);
	SolidBrush brush(Color::Black);

	Pen pen(Color::Black, 1.1F);
	PointF p1(left, top), p2(left, bot);

	if (!title.IsEmpty())
	{

		p1.X = actLeft + actWidth / 2 - CalcStringLen(lpDrawItemStruct->hDC, title) / 2 / xScale;
		p1.Y = (actTop + top) / 2 - 6 / yScale;
		matr.TransformPoints(&p1);
		gr.DrawString(title, title.GetLength() + 1, &font, p1, &brush);
	}

	double ycenter = (top - bot) / 2.;
	p1 = PointF(data[0], ycenter);
	matr.TransformPoints(&p1);

	Pen DataPen(Color(200, 100, 0));

 	for (int i = 1; i < data.size(); i++)
	{
		p2 = PointF(data[i], ycenter);
		matr.TransformPoints(&p2);
		gr.DrawLine(&DataPen, p1, p2);
		p1 = p2;
	}
	
	SolidBrush OrangeBrush(Color(200, 100, 0));
	for (int i = 0; i < data.size(); i++)
	{
		p2 = PointF(data[i], ycenter);
		matr.TransformPoints(&p2);
		gr.FillEllipse(&OrangeBrush, INT(p1.X - radius), INT(p1.Y - radius), 2 * radius, 2 * radius);
		p1 = p2;
	}

	ToWindow.DrawImage(&bmp, 0, 0);
}


void ModelDrawer::SetData(vector<double>& y)
{
	data = y;
	if (data.empty())return;
	left = 0;
	right = (y.size() - 1) * nodelength;
}

void ModelDrawer::SetL(double val)
{
	nodelength = val;
}

void ModelDrawer::SetPadding(double lP, double rP, double tP, double bP)
{
	lPadding = lP;
	rPadding = rP;
	tPadding = tP;
	bPadding = bP;
}
void ModelDrawer::SetMarksLen(int len)
{
	MarksLen = len;
}
void ModelDrawer::SetTitle(CString str)
{
	title = str;
}

void ModelDrawer::SetRadius(int val)
{
	radius = val;
}


double ModelDrawer::CalcStringLen(HDC hDC, CString str)
{
	double numlen = 0;
	int size = str.GetLength() + 1;
	for (int i = 0; i < size; i++)
	{
		ABCFLOAT abc;
		GetCharABCWidthsFloatW(hDC, str[i], str[i], &abc);
		numlen += abc.abcfA + abc.abcfB + abc.abcfC;
	}
	return numlen;
}

