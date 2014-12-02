// Flappy_birdDoc.h : interface of the CFlappy_birdDoc class
//


#pragma once


class CFlappy_birdDoc : public CDocument
{
protected: // create from serialization only
	CFlappy_birdDoc();
	DECLARE_DYNCREATE(CFlappy_birdDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CFlappy_birdDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


