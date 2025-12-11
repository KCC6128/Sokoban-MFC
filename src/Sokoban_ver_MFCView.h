
// Sokoban_ver_MFCView.h : interface of the CSokobanverMFCView class
//

#pragma once


class CSokobanverMFCView : public CView
{
protected: // create from serialization only
	CSokobanverMFCView() noexcept;
	DECLARE_DYNCREATE(CSokobanverMFCView)

// Attributes
public:
	CSokobanverMFCDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSokobanverMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CBitmap CBMPArrival;
	CBitmap CBMPBlank;
	CBitmap CBMPBox;
	CBitmap CBMPDest;
	CBitmap CBMPWall;
	CBitmap CBMPWorker;
	bool CComplete;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Sokoban_ver_MFCView.cpp
inline CSokobanverMFCDoc* CSokobanverMFCView::GetDocument() const
   { return reinterpret_cast<CSokobanverMFCDoc*>(m_pDocument); }
#endif

