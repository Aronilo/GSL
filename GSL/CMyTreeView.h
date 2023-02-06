#pragma once
#include "afxcview.h"


// Просмотр CMyTreeView
class CGSLDoc;

class CMyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CMyTreeView);

protected:
	CMyTreeView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CMyTreeView();

public:
	
	CGSLDoc* m_pDoc;
	void FillTree();

	HTREEITEM linearInterpolation, lagrange, cubicSplines;


	
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


