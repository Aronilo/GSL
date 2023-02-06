
// GSLView.cpp: реализация класса CGSLView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "GSL.h"
#endif

#include "GSLDoc.h"
#include "GSLView.h"
#include <algorithm>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGSLView

IMPLEMENT_DYNCREATE(CGSLView, CView)

BEGIN_MESSAGE_MAP(CGSLView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// Создание или уничтожение CGSLView

CGSLView::CGSLView() noexcept
{
	// TODO: добавьте код создания

}

CGSLView::~CGSLView()
{
}

BOOL CGSLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CGSLView

void CGSLView::OnDraw(CDC* pDC)
{
	CGSLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect(rect);
	GetClientRect(&rect);
	
	/*for (int i = 1; i < 5; i++) {
		pDC->MoveTo(a[i - 1], b[i - 1]);
		pDC->LineTo(a[i], b[i]);
	}*/

	pDC->MoveTo(0, rect.Height() / 2);
	pDC->LineTo(rect.Width(), rect.Height() / 2);
	
	double maxWidth = 0, maxHeight = 0;
	
	for (int i = 0; i < pDoc->m_vX.size(); i++) {
		if (abs(pDoc->m_vX[i]) > maxWidth) {
			maxWidth = abs(pDoc->m_vX[i]);
		}
	}
	
	for (int i = 0; i < pDoc->m_vY.size(); i++) {
		if (abs(pDoc->m_vY[i]) > maxHeight) {
			maxHeight = abs(pDoc->m_vY[i]);
		}
	}
	CString str;

	
	for (int i = 1; i < pDoc->m_vX.size(); i++) {
		pDC->MoveTo(pDoc->m_vX[i - 1] * rect.Width() / ceil(maxWidth), rect.Height() / 2.f - pDoc->m_vY[i - 1] * rect.Height() / ceil(2 * maxHeight));
		pDC->LineTo(pDoc->m_vX[i] * rect.Width() / ceil(maxWidth), rect.Height() / 2.f - pDoc->m_vY[i] * rect.Height() / ceil(2 * maxHeight));
	}
	
	
	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CGSLView

BOOL CGSLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CGSLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CGSLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CGSLView

#ifdef _DEBUG
void CGSLView::AssertValid() const
{
	CView::AssertValid();
}

void CGSLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGSLDoc* CGSLView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGSLDoc)));
	return (CGSLDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CGSLView


void CGSLView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CGSLDoc* pDoc = GetDocument();

	CRect rect;
	GetClientRect(&rect);
	

	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CGSLView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: добавьте специализированный код или вызов базового класса
	SetTimer(0, 100, NULL);
	CGSLDoc* pDoc = GetDocument();
}
