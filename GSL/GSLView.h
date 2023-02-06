
// GSLView.h: интерфейс класса CGSLView
//

#pragma once


class CGSLView : public CView
{
protected: // создать только из сериализации
	CGSLView() noexcept;
	DECLARE_DYNCREATE(CGSLView)

// Атрибуты
public:
	CGSLDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CGSLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // версия отладки в GSLView.cpp
inline CGSLDoc* CGSLView::GetDocument() const
   { return reinterpret_cast<CGSLDoc*>(m_pDocument); }
#endif

