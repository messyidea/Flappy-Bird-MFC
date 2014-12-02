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

typedef struct Bird{		//鸟的结构体
	CImage*	img;
	CRect	rect;
	double	movedis;
	double upmovedis;
	double allup;
}mBird;

typedef struct Pipe{		//水管的结构体
	CImage	imgup;
	CRect	rectup;
	CImage imgdown;
	CRect rectdown;
	//int high;
}mPipe;

typedef struct Pic{			//图片
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
	CDC m_BufferDC;	//缓冲DC
	CBitmap m_BufferBmp;	//缓冲BMP
	int m_State;		//当前状态
	CSize m_Client;		//客户区大小
	struct bg{
		CImage	img1;//第一张背景
		CImage	img2;//第二张背景
		CRect rec1;
		CRect rec2;
	}m_Bg;

	struct sbg{
		CImage bg;		//背景图片
		CRect  rect;
		bool   isStart;
	}m_Sbg;
	struct rbg1{
		CImage bg;
		CRect  rect;
		bool   isStart;
	}m_Rbg1;
	bool m_Isdie;		//小鸟是否死亡
	bool m_Isup;		//小鸟是够已经在上升状态
	mPic m_Medel0;		//奖牌
	mPic m_Medel1;
	mPic m_Medel2;
	mPic m_Res;			//显示结果的牌子
	mPic m_Gameover;	//gameover牌子
	mBird m_Bird;		//小鸟
	mPipe	m_Pipe[3];	//水管，只需3根
	int m_Score;		//分数
	CString m_St;		//分数
	CString m_Stmax;	//历史最高分
	bool m_Candraw;		//是否能够画图了
	mPic m_Start;		//开始图片
	CImage m_BIRD[3];	//小鸟的图片
	int m_Birdnum;		//小鸟的编号
public:
	afx_msg void OnDestroy();	//结束并释放资源
private:
	void StartUI(void);			//开始游戏界面
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);		//左键点击的监听器
private:
	void RunningUI(void);		//正在运行的界面
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);	//定时器的回调函数
private:
	inline void Movebird(void);		//小鸟下降
	void Replaygame(void);			//重新游戏
	void Startgame();	//开始游戏
	inline void Upbird(void);		//小鸟上升
	void ReplayUI(void);			//重新游戏界面
	inline void Movepipe(void);		//移动水管
	void Rotatebg(void);			//移动背景
	void Drawscore(CDC& cdc);		//画分数
	void Upgameover(void);			//上升gameover图片
	void Drawscoreend(CDC& cdc);		//绘制最终分数
	bool LoadImageFromResource(IN CImage* pImage,IN UINT nResID,IN LPCWSTR lpTyp);		//从资源中获取图片
private:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);		//双击监听器
	void Changebird(void);		//变换小鸟
};

#ifndef _DEBUG  // debug version in Flappy_birdView.cpp
inline CFlappy_birdDoc* CFlappy_birdView::GetDocument() const
   { return reinterpret_cast<CFlappy_birdDoc*>(m_pDocument); }
#endif

