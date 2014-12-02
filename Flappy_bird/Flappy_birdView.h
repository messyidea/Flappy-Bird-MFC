// Flappy_birdView.h : interface of the CFlappy_birdView class
//


#pragma once
#include "afxwin.h"

#define ID_BIRD	100
#define ID_UPBIRD 101
#define ID_PIPE	102
#define ID_ROTATEBG 103
#define ID_GAMEOVER 104
#define ID_CHANGEBIRD 105

typedef struct Bird{		//��Ľṹ��
	CImage*	img;
	CRect	rect;
	double	movedis;
	double upmovedis;
	double allup;
}mBird;

typedef struct Pipe{		//ˮ�ܵĽṹ��
	CImage	imgup;
	CRect	rectup;
	CImage imgdown;
	CRect rectdown;
	//int high;
}mPipe;

typedef struct Pic{			//ͼƬ
	CImage img;
	CRect rect;
}mPic;

class CFlappy_birdView : public CView
{
protected: // create from serialization only
	CFlappy_birdView();
	DECLARE_DYNCREATE(CFlappy_birdView)

// Attributes
public:
	CFlappy_birdDoc* GetDocument() const;

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
	virtual ~CFlappy_birdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	CDC m_BufferDC;	//����DC
	CBitmap m_BufferBmp;	//����BMP
	int m_State;		//��ǰ״̬
	CSize m_Client;		//�ͻ�����С
	struct bg{
		CImage	img1;//��һ�ű���
		CImage	img2;//�ڶ��ű���
		CRect rec1;
		CRect rec2;
	}m_Bg;

	struct sbg{
		CImage bg;		//����ͼƬ
		CRect  rect;
		bool   isStart;
	}m_Sbg;
	struct rbg1{
		CImage bg;
		CRect  rect;
		bool   isStart;
	}m_Rbg1;
	bool m_Isdie;		//С���Ƿ�����
	bool m_Isup;		//С���ǹ��Ѿ�������״̬
	mPic m_Medel0;		//����
	mPic m_Medel1;
	mPic m_Medel2;
	mPic m_Res;			//��ʾ���������
	mPic m_Gameover;	//gameover����
	mBird m_Bird;		//С��
	mPipe	m_Pipe[3];	//ˮ�ܣ�ֻ��3��
	int m_Score;		//����
	CString m_St;		//����
	CString m_Stmax;	//��ʷ��߷�
	bool m_Candraw;		//�Ƿ��ܹ���ͼ��
	mPic m_Start;		//��ʼͼƬ
	CImage m_BIRD[3];	//С���ͼƬ
	int m_Birdnum;		//С��ı��
public:
	afx_msg void OnDestroy();	//�������ͷ���Դ
private:
	void StartUI(void);			//��ʼ��Ϸ����
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);		//�������ļ�����
private:
	void RunningUI(void);		//�������еĽ���
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);	//��ʱ���Ļص�����
private:
	inline void Movebird(void);		//С���½�
	void Replaygame(void);			//������Ϸ
	void Startgame();	//��ʼ��Ϸ
	inline void Upbird(void);		//С������
	void ReplayUI(void);			//������Ϸ����
	inline void Movepipe(void);		//�ƶ�ˮ��
	void Rotatebg(void);			//�ƶ�����
	void Drawscore(CDC& cdc);		//������
	void Upgameover(void);			//����gameoverͼƬ
	void Drawscoreend(CDC& cdc);		//�������շ���
	bool LoadImageFromResource(IN CImage* pImage,IN UINT nResID,IN LPCWSTR lpTyp);		//����Դ�л�ȡͼƬ
private:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);		//˫��������
	void Changebird(void);		//�任С��
};

#ifndef _DEBUG  // debug version in Flappy_birdView.cpp
inline CFlappy_birdDoc* CFlappy_birdView::GetDocument() const
   { return reinterpret_cast<CFlappy_birdDoc*>(m_pDocument); }
#endif

