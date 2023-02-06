
// GSLDoc.cpp: реализация класса CGSLDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "GSL.h"
#endif

#include <sstream>
#include <fstream>

#include "GSLDoc.h"

#include <propkey.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGSLDoc

IMPLEMENT_DYNCREATE(CGSLDoc, CDocument)

BEGIN_MESSAGE_MAP(CGSLDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CGSLDoc

CGSLDoc::CGSLDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CGSLDoc::~CGSLDoc()
{
}

BOOL CGSLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CGSLDoc

void CGSLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		file_x.clear();
		file_y.clear();
		std::ifstream file(ar.m_strFileName);
		double x, y;
		while (!file.eof())
		{
			n++;
			file_x.resize(n + 1);
			file_y.resize(n + 1);

			
			char buf[100];
			file.getline(buf, 100);
			
			std::stringstream s(buf);

			std::string value;
			s >> value;
			sscanf_s(value.c_str(), "%lf", &file_x[n]);

			s >> value;
			sscanf_s(value.c_str(), "%lf", &file_y[n]);
		}
		file.close();
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CGSLDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CGSLDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CGSLDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CGSLDoc

#ifdef _DEBUG
void CGSLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGSLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CGSLDoc::SetMethod(int method) {
	
	double a, a0;

	double xi, yi;
	double dx = 0.01;
	

	switch (method) {
	case 1:
		m_vX.clear();
		m_vY.clear();
		for (int i = 1; i < n; i++) {
			a = (file_y[i] - file_y[i - 1]) / (file_x[i] - file_x[i - 1]);
			a0 = file_y[i - 1] - a * file_x[i - 1];
			for (double xx = file_x[i - 1]; xx < file_x[i]; xx += dx) {
				double yy = a0 + a * xx;

				m_vX.push_back(xx);
				m_vY.push_back(yy);
			}
		}
		break;
	case 2:
		m_vX.clear();
		m_vY.clear();
		for (double xx = file_x[0]; xx < file_x[n - 1]; xx += dx) {
			double yy = 0;
			for (int i = 0; i < n; i++) {
				double p = 1;
				for (int j = 0; j < n; j++) {
					if (i != j) {
						p *= (xx - file_x[j]) / (file_x[i] - file_x[j]);
					}
				}
				yy += file_y[i] * p;

			}
			m_vX.push_back(xx);
			m_vY.push_back(yy);
		}
		break;
	case 3:
		m_vX.clear();
		m_vY.clear();

		gsl_interp_accel* acc = gsl_interp_accel_alloc();
		gsl_spline* spline = gsl_spline_alloc(gsl_interp_cspline, n);
		gsl_spline_init(spline, file_x.data(), file_y.data(), n);
		
		for (int i = 0; i <= 100; ++i)
		{
			double xi = (1 - i / 100.0) * file_x[0] + (i / 100.0) * file_x[n - 1];
			double yi = gsl_spline_eval(spline, xi, acc);
			m_vX.push_back(xi);
			m_vY.push_back(yi);
			
		}

		gsl_spline_free(spline);
		gsl_interp_accel_free(acc); 
		break;
	}
}

// Команды CGSLDoc
