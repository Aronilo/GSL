
// GSLDoc.h: интерфейс класса CGSLDoc 
//

#pragma once
#include "CMyTreeView.h"
#include <vector>

using namespace std;


class CGSLDoc : public CDocument
{
protected: // создать только из сериализации
	CGSLDoc() noexcept;
	DECLARE_DYNCREATE(CGSLDoc);

// Атрибуты
public:
	CGSLDoc* m_pDoc;

	CMyTreeView* m_pTreeView;

	void SetMethod(int);

	vector<double> m_vX, file_x;
	vector<double> m_vY, file_y;
	int n = -1;

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CGSLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
