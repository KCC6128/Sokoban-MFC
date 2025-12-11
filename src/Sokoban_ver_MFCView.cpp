
// Sokoban_ver_MFCView.cpp : implementation of the CSokobanverMFCView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sokoban_ver_MFC.h"
#endif

#include "Sokoban_ver_MFCDoc.h"
#include "Sokoban_ver_MFCView.h"



// CSokobanverMFCView

IMPLEMENT_DYNCREATE(CSokobanverMFCView, CView)

BEGIN_MESSAGE_MAP(CSokobanverMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CSokobanverMFCView construction/destruction

CSokobanverMFCView::CSokobanverMFCView() noexcept
{
	//initialize
	CComplete = false;

	//load BMP
	CBMPArrival.LoadBitmap(IDB_BITMAP_Arrival);
	CBMPBlank.LoadBitmap(IDB_BITMAP_Blank);
	CBMPBox.LoadBitmap(IDB_BITMAP_Box);
	CBMPDest.LoadBitmap(IDB_BITMAP_Dest);
	CBMPWall.LoadBitmap(IDB_BITMAP_Wall);
	CBMPWorker.LoadBitmap(IDB_BITMAP_Worker);
}

CSokobanverMFCView::~CSokobanverMFCView()
{
}

BOOL CSokobanverMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSokobanverMFCView drawing

void CSokobanverMFCView::OnDraw(CDC* pDC)
{
	CSokobanverMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC aDC(this);
	CDC memDC;
	memDC.CreateCompatibleDC(&aDC);
	int xMax = 0;

	//blank
	for (size_t i = 0; i < pDoc->CBlank.size(); i++)
	{
		memDC.SelectObject(&CBMPBlank);
		aDC.BitBlt(pDoc->CBlank[i].Cx * 32 + 32, pDoc->CBlank[i].Cy * 32 + 32,
			pDoc->CBlank[i].Cx * 32 + 64, pDoc->CBlank[i].Cy * 32 + 64, &memDC, 0, 0, SRCCOPY);
	}

	//wall
	for (size_t i = 0; i < pDoc->CWall.size(); i++)
	{
		memDC.SelectObject(&CBMPWall);
		aDC.BitBlt(pDoc->CWall[i].Cx * 32 + 32, pDoc->CWall[i].Cy * 32 + 32,
			pDoc->CWall[i].Cx * 32 + 64, pDoc->CWall[i].Cy * 32 + 64, &memDC, 0, 0, SRCCOPY);
	}

	//dest
	for (size_t i = 0; i < pDoc->CDest.size(); i++)
	{
		memDC.SelectObject(&CBMPDest);
		aDC.BitBlt(pDoc->CDest[i].Cx * 32 + 32, pDoc->CDest[i].Cy * 32 + 32,
			pDoc->CDest[i].Cx * 32 + 64, pDoc->CDest[i].Cy * 32 + 64, &memDC, 0, 0, SRCCOPY);
	}

	//box
	for (size_t i = 0; i < pDoc->CBox.size(); i++)
	{
		memDC.SelectObject(&CBMPBox);
		aDC.BitBlt(pDoc->CBox[i].Cx * 32 + 32, pDoc->CBox[i].Cy * 32 + 32,
			pDoc->CBox[i].Cx * 32 + 64, pDoc->CBox[i].Cy * 32 + 64, &memDC, 0, 0, SRCCOPY);
	}

	//arrival
	for (size_t i = 0; i < pDoc->CArrival.size(); i++)
	{
		memDC.SelectObject(&CBMPArrival);
		aDC.BitBlt(pDoc->CArrival[i].Cx * 32 + 32, pDoc->CArrival[i].Cy * 32 + 32,
			pDoc->CArrival[i].Cx * 32 + 64, pDoc->CArrival[i].Cy * 32 + 64, &memDC, 0, 0, SRCCOPY);
	}

	//worker
	for (size_t i = 0; i < pDoc->CWorker.size(); i++)
	{
		memDC.SelectObject(&CBMPWorker);
		aDC.BitBlt(pDoc->CWorker[i].Cx * 32 + 32, pDoc->CWorker[i].Cy * 32 + 32,
			pDoc->CWorker[i].Cx * 32 + 64, pDoc->CWorker[i].Cy * 32 + 64, &memDC, 0, 0, SRCCOPY);
	}

	//level
	CString level;
	level.Format(L"Level : %d", pDoc->CMapNumber);
	pDC->TextOut((pDoc->CCOLUMN * 32 + 64 < 1000 ? 1000 : pDoc->CCOLUMN * 32 + 164), 32, level);

	//dest
	CString dest;
	dest.Format(L"Destination : %d", pDoc->CDest.size());
	pDC->TextOut((pDoc->CCOLUMN * 32 + 64 < 1000 ? 1000 : pDoc->CCOLUMN * 32 + 164), 62, dest);

	//arrival
	CString arrival;
	arrival.Format(L"Arrival : %d", pDoc->CArrival.size());
	pDC->TextOut((pDoc->CCOLUMN * 32 + 64 < 1000 ? 1000 : pDoc->CCOLUMN * 32 + 164), 92, arrival);

	//step
	CString step;
	step.Format(L"Step : %d", pDoc->CStep);
	pDC->TextOut((pDoc->CCOLUMN * 32 + 64 < 1000 ? 1000 : pDoc->CCOLUMN * 32 + 164), 122, step);

	//end game
	if (CComplete)
	{
		CComplete = false;
		AfxMessageBox(L"Pass!\nPress SPACE to the next level.", MB_OK);
		pDoc->LoadMap(pDoc->CMapNumber + 1);
		pDoc->UpdateAllViews(NULL);
	}
}


// CSokobanverMFCView printing

BOOL CSokobanverMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSokobanverMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSokobanverMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSokobanverMFCView diagnostics

#ifdef _DEBUG
void CSokobanverMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CSokobanverMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSokobanverMFCDoc* CSokobanverMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSokobanverMFCDoc)));
	return (CSokobanverMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CSokobanverMFCView message handlers


void CSokobanverMFCView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CSokobanverMFCDoc* pDoc = GetDocument();

	if (pDoc->Contral(nChar))
	{
		if (!pDoc->Arrive())
			pDoc->UpdateAllViews(NULL);

		else
		{
			CComplete = true;
			pDoc->UpdateAllViews(NULL);
		}
	}

	else
	{
		CClientDC aDC(this);
		aDC.TextOut(1000, 200, L"You cannot go there!");
	}

	pDoc->SetModifiedFlag();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
