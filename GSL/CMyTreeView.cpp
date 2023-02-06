// CMyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "GSL.h"
#include "CMyTreeView.h"
#include "GSLDoc.h"
#include <iostream>

// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений CMyTreeView



int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS
		| TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания
	
	FillTree();
	return 0;
}

void CMyTreeView::FillTree() {
	
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();
	
	linearInterpolation = tree.InsertItem(L"Кусочно-линейная интерполяция", -1, -1, NULL, TVI_FIRST);

	lagrange = tree.InsertItem(L"Многочлен Лагранжа", -1, -1, NULL, TVI_FIRST);

	cubicSplines = tree.InsertItem(L"Кубические сплайны", -1, -1, NULL, TVI_FIRST);

}


void CMyTreeView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeView::OnLButtonDblClk(nFlags, point);
	
	CTreeCtrl& tree = GetTreeCtrl();
	CRect rc;

	
	tree.GetItemRect(linearInterpolation, &rc, false);

	if (rc.PtInRect(point)) {
		m_pDoc->SetMethod(1);
	}

	tree.GetItemRect(lagrange, &rc, false);

	if (rc.PtInRect(point)) {
		m_pDoc->SetMethod(2);
	}
	
	tree.GetItemRect(cubicSplines, &rc, false);

	if (rc.PtInRect(point)) {
		m_pDoc->SetMethod(3);
	}
}
