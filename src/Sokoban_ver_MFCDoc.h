
// Sokoban_ver_MFCDoc.h : interface of the CSokobanverMFCDoc class
//


#pragma once


class CSokobanverMFCDoc : public CDocument
{
protected: // create from serialization only
	CSokobanverMFCDoc() noexcept;
	DECLARE_DYNCREATE(CSokobanverMFCDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSokobanverMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int CROW, CCOLUMN;
	int CStep;
	int Corder;
	int CMapNumber = 1;
	string CMapNo;
	vector <Coordinate>CWall;
	vector <Coordinate>CBox;
	vector <Coordinate>CDest;
	vector <Coordinate>CArrival;
	vector <Coordinate>CWorker;
	vector <Coordinate>CBlank;
	bool Contral(char c);
	bool MoveWorker();
	bool NextToWorker(Direction d);
	bool NextNextToWorker(Direction d);
	bool Arrive();
	bool LoadMap(int n);
};
