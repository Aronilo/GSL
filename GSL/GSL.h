
// GSL.h: основной файл заголовка для приложения GSL
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CGSLApp:
// Сведения о реализации этого класса: GSL.cpp
//

class CGSLApp : public CWinApp
{
public:
	CGSLApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGSLApp theApp;
