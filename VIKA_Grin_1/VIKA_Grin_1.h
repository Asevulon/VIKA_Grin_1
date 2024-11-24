
// VIKA_Grin_1.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CVIKAGrin1App:
// Сведения о реализации этого класса: VIKA_Grin_1.cpp
//

class CVIKAGrin1App : public CWinApp
{
public:
	CVIKAGrin1App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CVIKAGrin1App theApp;
