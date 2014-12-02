// Flappy_birdView.cpp : implementation of the CFlappy_birdView class
//

#include "stdafx.h"
#include "Flappy_bird.h"

#include "Flappy_birdDoc.h"
#include "Flappy_birdView.h"
#include "fstream"
#include "sstream"
#include "iostream"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFlappy_birdView

IMPLEMENT_DYNCREATE(CFlappy_birdView, CView)

BEGIN_MESSAGE_MAP(CFlappy_birdView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CFlappy_birdView construction/destruction

CFlappy_birdView::CFlappy_birdView()
: m_State(0)
{
	// TODO: add construction code here
	srand((unsigned int)time(0));		//���������
	m_Birdnum = 0;						//С��ı��
	//����Ϊ���ظ���ͼƬ����Դ
	m_Medel0.img.LoadFromResource(AfxGetInstanceHandle(),IDB_MEDEL0);
	m_Medel1.img.LoadFromResource(AfxGetInstanceHandle(),IDB_MEDEL1);
	m_Medel2.img.LoadFromResource(AfxGetInstanceHandle(),IDB_MEDEL2);
	m_Res.img.LoadFromResource(AfxGetInstanceHandle(),IDB_PAIZI);
	m_Start.img.LoadFromResource(AfxGetInstanceHandle(),IDB_START);
	m_Medel0.rect.left = 80;
	m_Medel0.rect.right = 130;
	m_Medel0.rect.top = 220;
	m_Medel0.rect.bottom = 270;
	m_Medel1.rect.left = 80;
	m_Medel1.rect.right = 130;
	m_Medel1.rect.top = 220;
	m_Medel1.rect.bottom = 270;
	m_Medel2.rect.left = 80;
	m_Medel2.rect.right = 130;
	m_Medel2.rect.top = 220;
	m_Medel2.rect.bottom = 270;
	m_Client.SetSize(360, 640);
	m_BIRD[0].LoadFromResource(AfxGetInstanceHandle(),IDB_BIRD);
	m_BIRD[1].LoadFromResource(AfxGetInstanceHandle(),IDB_BIRD2);
	m_BIRD[2].LoadFromResource(AfxGetInstanceHandle(),IDB_BIRD3);
	m_Bird.img = &m_BIRD[0];
	LoadImageFromResource(&m_Gameover.img,IDB_GAMEOVER,_T("PNG"));
	m_Gameover.rect.left = 50;
	m_Gameover.rect.right = m_Gameover.rect.left+m_Gameover.img.GetWidth()*0.7;
	m_Gameover.rect.top = 640;
	m_Gameover.rect.bottom = 640+m_Gameover.img.GetHeight()*0.7;
	m_Res.rect.left=50;
	m_Res.rect.right = 50+m_Res.img.GetWidth()*0.7;
	m_Res.rect.top = m_Gameover.rect.bottom + 20;
	m_Res.rect.bottom = m_Res.rect.top + m_Res.img.GetHeight()*0.7;
	m_Start.rect.left = 60;
	m_Start.rect.right = 180;
	m_Start.rect.top = m_Res.rect.bottom+20;
	m_Start.rect.bottom = m_Start.rect.top+60;
	//����͸��ͼƬ
	for(int i = 0; i < m_Gameover.img.GetWidth(); i++)
	{
    for(int j = 0; j < m_Gameover.img.GetHeight(); j++)
    {
        unsigned char* pucColor = reinterpret_cast<unsigned char *>(m_Gameover.img.GetPixelAddress(i , j));
        pucColor[0] = pucColor[0] * pucColor[3] / 255;
        pucColor[1] = pucColor[1] * pucColor[3] / 255;
        pucColor[2] = pucColor[2] * pucColor[3] / 255;
    }
	}

	m_Bird.rect.left = 50;
	m_Bird.rect.top = 250;
	m_Bird.rect.right = 100;
	m_Bird.rect.bottom =300;
	m_Bird.movedis = 1;
	LoadImageFromResource(&m_Sbg.bg,IDB_STARTBG,_T("PNG"));
	m_Sbg.isStart = false;
	m_Sbg.rect.SetRect(0,0,360,640);
	LoadImageFromResource(&m_Rbg1.bg,IDB_RUNNINGBG,_T("PNG"));
	m_Rbg1.rect.SetRect(0,0,360,640);
	for(int i=0;i<3;++i){
		LoadImageFromResource(&m_Pipe[i].imgup,IDB_UPPIC,_T("PNG"));
		LoadImageFromResource(&m_Pipe[i].imgdown,IDB_DOWNPIC,_T("PNG"));
	}
	LoadImageFromResource(&m_Bg.img1,IDB_BGPIC1,_T("PNG"));
	LoadImageFromResource(&m_Bg.img2,IDB_BGPIC2,_T("PNG"));
	m_Bg.rec1.left = 0;
	m_Bg.rec1.right = m_Bg.img1.GetWidth();
	m_Bg.rec2.left = m_Bg.rec1.right;
	m_Bg.rec2.right = m_Bg.rec1.right+m_Bg.img1.GetWidth();
	m_Bg.rec1.top = 492;
	m_Bg.rec2.top = 492;
	m_Bg.rec1.bottom = m_Bg.rec1.top + m_Bg.img1.GetHeight();
	m_Bg.rec2.bottom = m_Bg.rec2.top +m_Bg.img1.GetHeight();

}

CFlappy_birdView::~CFlappy_birdView()
{
}

BOOL CFlappy_birdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CFlappy_birdView drawing

void CFlappy_birdView::OnDraw(CDC* pDC)
{
	CFlappy_birdDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	m_BufferDC.CreateCompatibleDC(NULL);		//��ȡdc
	m_BufferBmp.CreateCompatibleBitmap(pDC,		//����������
		m_Sbg.bg.GetWidth() * 2, m_Sbg.bg.GetHeight());
	m_BufferDC.SelectObject(m_BufferBmp);	//ѡ�񻺳�������
	switch(m_State)
	{
	//��Ϸ��ʼ����
	case 0:
		StartUI();
		break;

	//������Ϸ����
	case 1:
		RunningUI();
		Drawscore(m_BufferDC);
		break;

	//��Ϸ��������
	case 2:
		ReplayUI();
		if(m_Candraw)			//�ܻ����ٻ�����
			Drawscoreend(m_BufferDC);
		break;
	}


	pDC->BitBlt(0, 0, m_Client.cx, m_Client.cy, &m_BufferDC, 0, 0, SRCCOPY);		//����
	m_BufferBmp.DeleteObject();		//�ͷ���Դ
	m_BufferDC.DeleteDC();

}


// CFlappy_birdView printing

BOOL CFlappy_birdView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFlappy_birdView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFlappy_birdView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CFlappy_birdView diagnostics

#ifdef _DEBUG
void CFlappy_birdView::AssertValid() const
{
	CView::AssertValid();
}

void CFlappy_birdView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFlappy_birdDoc* CFlappy_birdView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlappy_birdDoc)));
	return (CFlappy_birdDoc*)m_pDocument;
}
#endif //_DEBUG


// CFlappy_birdView message handlers


void CFlappy_birdView::Startgame()
{
	//��ʼ����������
	m_Isdie = false;
	m_Isup = false;
	m_State = 1;
	m_Score = 0;
	m_Candraw = false;
	m_Bird.rect.left = 50;
	m_Bird.rect.top = 250;
	m_Bird.rect.right = 80;
	m_Bird.rect.bottom = 280;
	m_Bird.movedis = 0;
	m_Gameover.rect.left = 50;
	m_Gameover.rect.right = m_Gameover.rect.left+m_Gameover.img.GetWidth()*0.7;
	m_Gameover.rect.top = 640;
	m_Gameover.rect.bottom = 640+m_Gameover.img.GetHeight()*0.7;
	m_Res.rect.left=50;
	m_Res.rect.right = 50+m_Res.img.GetWidth()*0.7;
	m_Res.rect.top = m_Gameover.rect.bottom + 40;
	m_Res.rect.bottom = m_Res.rect.top + m_Res.img.GetHeight()*0.7;
	m_Start.rect.left = 110;
	m_Start.rect.right = 230;
	m_Start.rect.top = m_Res.rect.bottom+20;
	m_Start.rect.bottom = m_Start.rect.top+60;
	for(int i=0;i<3;++i){
		m_Pipe[i].rectup.left = 400+240*i;
		m_Pipe[i].rectup.right = 450+240*i;
		m_Pipe[i].rectup.top =460 - rand()%300;
		m_Pipe[i].rectup.bottom = 490;
		m_Pipe[i].rectdown.left = m_Pipe[i].rectup.left;
		m_Pipe[i].rectdown.right = m_Pipe[i].rectup.right;
		m_Pipe[i].rectdown.top = 0;
		m_Pipe[i].rectdown.bottom = m_Pipe[i].rectup.top-160;
	}
	//��ʼ�ĸ���ʱ��
	SetTimer(ID_PIPE,40, NULL);
	SetTimer(ID_ROTATEBG,40, NULL);
	SetTimer(ID_BIRD,20, NULL);
	SetTimer(ID_CHANGEBIRD,40,NULL);
	//m_Bird.rect.SetRect(0,200,m_Bird.img.GetWidth(),m_Bird.img.GetHeight()+200);

}
void CFlappy_birdView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	m_Sbg.bg.ReleaseGDIPlus();
	m_Rbg1.bg.ReleaseGDIPlus();
	m_BIRD[0].ReleaseGDIPlus();
	m_BIRD[1].ReleaseGDIPlus();
	m_BIRD[2].ReleaseGDIPlus();
	m_Pipe[0].imgdown.ReleaseGDIPlus();
	m_Pipe[0].imgup.ReleaseGDIPlus();
	m_Pipe[1].imgdown.ReleaseGDIPlus();
	m_Pipe[1].imgup.ReleaseGDIPlus();
	m_Pipe[2].imgdown.ReleaseGDIPlus();
	m_Pipe[2].imgup.ReleaseGDIPlus();
	m_Gameover.img.ReleaseGDIPlus();
	m_Res.img.ReleaseGDIPlus();
	m_Start.img.ReleaseGDIPlus();
	m_Medel0.img.ReleaseGDIPlus();
	m_Medel1.img.ReleaseGDIPlus();
	m_Medel2.img.ReleaseGDIPlus();


}

void CFlappy_birdView::StartUI(void)
{
	m_Sbg.bg.BitBlt(m_BufferDC, 0, 0, SRCCOPY); //���ƿ�ʼͼƬ
}

void CFlappy_birdView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	switch(m_State){
		case 0:
		{
			//m_State = 1;
			Startgame();
			break;
		}
		case 1:
		{
			if(m_Isup == true){				//���С���Ѿ�����������Ҫ�ظ�����ʱ����
				PlaySound ( MAKEINTRESOURCE(IDR_WING), GetModuleHandle(NULL),SND_RESOURCE |SND_ASYNC);
				m_Bird.upmovedis = 50;
				m_Bird.allup += 50;
				return ;
			}
			m_Bird.upmovedis = 50;		//��ʼ��С��������ʱ����ִ��
			m_Bird.allup = 50;
			PlaySound ( MAKEINTRESOURCE(IDR_WING), GetModuleHandle(NULL),SND_RESOURCE |SND_ASYNC);
			SetTimer(ID_UPBIRD,1, NULL);
			m_Isup = true;
			break;
		}
		case 2:
		{
			if(m_Start.rect.PtInRect(point)){
				Startgame();
			}
			break;
		}
		
	}
	InvalidateRect(NULL, FALSE);
	CView::OnLButtonDown(nFlags, point);
}

void CFlappy_birdView::RunningUI(void)
{
	//����Ҫ���ֵ�ͼƬ
	m_Rbg1.bg.BitBlt(m_BufferDC, 0, 0, SRCCOPY);
	m_Bird.img->TransparentBlt(m_BufferDC, m_Bird.rect, RGB(255, 255, 255));
	for(int i=0;i<3;++i){
		m_Pipe[i].imgup.TransparentBlt(m_BufferDC, m_Pipe[i].rectup, RGB(255, 255, 255));
		m_Pipe[i].imgdown.TransparentBlt(m_BufferDC, m_Pipe[i].rectdown, RGB(255, 255, 255));
	}
	m_Bg.img1.TransparentBlt(m_BufferDC, m_Bg.rec1, RGB(255, 255, 255));
	m_Bg.img2.TransparentBlt(m_BufferDC, m_Bg.rec2, RGB(255, 255, 255));
	//m_Gameover.img.TransparentBlt(m_BufferDC, m_Gameover.rect, RGB(255, 255, 255));

}

void CFlappy_birdView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//��ʱ���Ļص�����
	switch(nIDEvent){
		case ID_BIRD:
			Movebird();
			break;
		case ID_UPBIRD:
			Upbird();
			break;
		case ID_PIPE:
			Movepipe();
			break;
		case ID_ROTATEBG:
			Rotatebg();
			break;
		case ID_GAMEOVER:
			Upgameover();
		case ID_CHANGEBIRD:
			Changebird();
	}

	CView::OnTimer(nIDEvent);
}

void CFlappy_birdView::Movebird(void)
{	//�½�С��
	m_Bird.rect.top +=  m_Bird.movedis;
	m_Bird.rect.bottom += m_Bird.movedis;
	if(m_Bird.rect.bottom>490){
		KillTimer(ID_BIRD);
		if(!m_Isdie)
			Replaygame();
	}
	m_Bird.movedis +=1.5;
	for(int i=0;i<3;++i){		//���ײ�����ӣ�С����������Ϸ����
		if(m_Bird.rect.left<m_Pipe[i].rectdown.right && m_Bird.rect.right > m_Pipe[i].rectdown.left){
			if(m_Bird.rect.top <m_Pipe[i].rectdown.bottom || m_Bird.rect.bottom>m_Pipe[i].rectup.top){
				if(!m_Isdie)
					Replaygame();
			}
		}
	}
	InvalidateRect(NULL, FALSE);
}

void CFlappy_birdView::Replaygame(void)
{
	m_Isdie = true;			//������Ϸ��ʼ��
	m_State = 2;
	KillTimer(ID_ROTATEBG);
	KillTimer(ID_PIPE);
	KillTimer(ID_CHANGEBIRD);
	PlaySound ( MAKEINTRESOURCE(IDR_DIE), GetModuleHandle(NULL),SND_RESOURCE |SND_ASYNC);
	if(m_Bird.rect.bottom<490)
		SetTimer(ID_BIRD,40, NULL);
	SetTimer(ID_GAMEOVER,40, NULL);
}

void CFlappy_birdView::Upbird(void)
{
	//��������С��
	m_Bird.rect.top -=  m_Bird.upmovedis;
	m_Bird.rect.bottom -= m_Bird.upmovedis;
	m_Bird.allup -=	m_Bird.upmovedis;
	if(m_Bird.allup <= 0){
		KillTimer(ID_UPBIRD);
		m_Isup = false;
		m_Bird.movedis=1;
		SetTimer(ID_BIRD,40, NULL);
		return ;
	}
	//С��ײ��������Ϸ����
	for(int i=0;i<3;++i){
		if(m_Bird.rect.left<m_Pipe[i].rectdown.right && m_Bird.rect.right > m_Pipe[i].rectdown.left){
			if(m_Bird.rect.top <m_Pipe[i].rectdown.bottom || m_Bird.rect.bottom>m_Pipe[i].rectup.top){
				if(!m_Isdie)
					Replaygame();
			}
		}
	}
	InvalidateRect(NULL, FALSE);//���¿ͻ���
}

void CFlappy_birdView::ReplayUI(void)
{
	m_Rbg1.bg.BitBlt(m_BufferDC, 0, 0, SRCCOPY);
	for(int i=0;i<3;++i){
		m_Pipe[i].imgup.TransparentBlt(m_BufferDC, m_Pipe[i].rectup, RGB(255, 255, 255));
		m_Pipe[i].imgdown.TransparentBlt(m_BufferDC, m_Pipe[i].rectdown, RGB(255, 255, 255));
	}
	m_Bg.img1.TransparentBlt(m_BufferDC, m_Bg.rec1, RGB(255, 255, 255));
	m_Bg.img2.TransparentBlt(m_BufferDC, m_Bg.rec2, RGB(255, 255, 255));
	m_Bird.img->TransparentBlt(m_BufferDC, m_Bird.rect, RGB(255, 255, 255));
	m_Gameover.img.AlphaBlend(m_BufferDC,-10,m_Gameover.rect.top);
	m_Res.img.TransparentBlt(m_BufferDC, m_Res.rect, RGB(255, 255, 255));
	m_Start.img.TransparentBlt(m_BufferDC, m_Start.rect, RGB(255, 255, 255));
	if(m_Candraw ){
		if(m_Score >= 30)
			m_Medel2.img.TransparentBlt(m_BufferDC, m_Medel2.rect, RGB(255, 255, 255));
		else if(m_Score >= 20)
			m_Medel1.img.TransparentBlt(m_BufferDC, m_Medel1.rect, RGB(255, 255, 255));
		else if(m_Score >= 10)
			m_Medel0.img.TransparentBlt(m_BufferDC, m_Medel0.rect, RGB(255, 255, 255));
	}
	
}

void CFlappy_birdView::Movepipe(void)
{
	//�ƶ�ˮ��
	for(int i=0;i<3;++i){
		m_Pipe[i].rectup.left -= 10;
		m_Pipe[i].rectup.right -= 10;
		m_Pipe[i].rectdown.left -= 10;
		m_Pipe[i].rectdown.right -= 10;
		if(m_Pipe[i].rectup.right<=0){
			//�����µ�ˮ��
			PlaySound ( MAKEINTRESOURCE(IDR_POINT), GetModuleHandle(NULL),SND_RESOURCE |SND_ASYNC);
			m_Score++;
			m_Pipe[i].rectdown.left = m_Pipe[(i+2)%3].rectdown.left+240;
			m_Pipe[i].rectdown.right = m_Pipe[(i+2)%3].rectdown.right+240;
			m_Pipe[i].rectup.left = m_Pipe[i].rectdown.left;
			m_Pipe[i].rectup.right = m_Pipe[i].rectdown.right;
			m_Pipe[i].rectup.top = 460 - rand()%260;
			m_Pipe[i].rectdown.bottom = m_Pipe[i].rectup.top-160+m_Score*3;
		}
	}
	InvalidateRect(NULL, FALSE);//���¿ͻ���
}

void CFlappy_birdView::Rotatebg(void)
{
	//�ƶ�����
	m_Bg.rec1.left -= 10;
	m_Bg.rec1.right -= 10;
	m_Bg.rec2.left -= 10;
	m_Bg.rec2.right -= 10;
	if(m_Bg.rec1.right<=0){
		m_Bg.rec1.left = m_Bg.rec2.right;
		m_Bg.rec1.right = m_Bg.rec1.left + 360;

	}
	if(m_Bg.rec2.right<=0){
		m_Bg.rec2.left = m_Bg.rec1.right;
		m_Bg.rec2.right = m_Bg.rec2.left + 360;
	}
	InvalidateRect(NULL, FALSE);
	
}

void CFlappy_birdView::Drawscore(CDC& cdc)//������
{
	CFont font;
	font.CreatePointFont(200, L"΢���ź�");
	cdc.SelectObject(font);
	cdc.SetBkMode(TRANSPARENT);
	m_St.Format(_T("%d"),m_Score); 
	cdc.SetTextColor(RGB(255, 255, 255));
	cdc.TextOutW(160,
		200,
		m_St);
}

void CFlappy_birdView::Upgameover(void)
{
	//����gameoverͼƬ����
	m_Gameover.rect.top -= 20;		
	m_Gameover.rect.bottom -= 20;
	m_Res.rect.top-=20;
	m_Res.rect.bottom -= 20;
	m_Start.rect.top -=20;
	m_Start.rect.bottom -=20;
	if(m_Gameover.rect.top<100) {
		KillTimer(ID_GAMEOVER);
		m_Candraw = true;
	}
	InvalidateRect(NULL, FALSE);
}

void CFlappy_birdView::Drawscoreend(CDC& cdc)
{
	//�������ķ���
	CFont font;
	font.CreatePointFont(150, L"΢���ź�");
	cdc.SelectObject(font);
	cdc.SetBkMode(TRANSPARENT);
	m_St.Format(_T("%d"),m_Score); 
	cdc.SetTextColor(RGB(255, 255, 255));
	cdc.TextOutW(250,
		210,
		m_St);
	int data_score = 0,score_max;
	ifstream iofile("score.data",ios::in);
	while(iofile.peek()!=EOF){
		iofile>>data_score;
	}
	iofile.close();
	if(data_score > m_Score){
		score_max = data_score;
	}
	else score_max = m_Score;
	m_Stmax.Format(_T("%d"),score_max);
	cdc.SetTextColor(RGB(255, 255, 255));
	cdc.TextOutW(250,
		255,
		m_Stmax);
	ofstream iofileout("score.data",ios::out);
	iofileout<<score_max;
	iofileout.close();
	

}


bool CFlappy_birdView::LoadImageFromResource(IN CImage* pImage,
                           IN UINT nResID, 
                           IN LPCWSTR lpTyp)
{
    if ( pImage == NULL) return false;

    pImage->Destroy();

    // ������Դ
    HRSRC hRsrc = ::FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(nResID), lpTyp);
    if (hRsrc == NULL) return false;

    // ������Դ
    HGLOBAL hImgData = ::LoadResource(AfxGetResourceHandle(), hRsrc);
    if (hImgData == NULL)
    {
        ::FreeResource(hImgData);
        return false;
    }

    // �����ڴ��е�ָ����Դ
    LPVOID lpVoid    = ::LockResource(hImgData);

    LPSTREAM pStream = NULL;
    DWORD dwSize    = ::SizeofResource(AfxGetResourceHandle(), hRsrc);
    HGLOBAL hNew    = ::GlobalAlloc(GHND, dwSize);
    LPBYTE lpByte    = (LPBYTE)::GlobalLock(hNew);
    ::memcpy(lpByte, lpVoid, dwSize);

    // ����ڴ��е�ָ����Դ
    ::GlobalUnlock(hNew);

    // ��ָ���ڴ洴��������
    HRESULT ht = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);
    if ( ht != S_OK )
    {
        GlobalFree(hNew);
    }
    else
    {
        // ����ͼƬ
        pImage->Load(pStream);

        GlobalFree(hNew);
    }

    // �ͷ���Դ
    ::FreeResource(hImgData);

    return true;
}

void CFlappy_birdView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_State == 1)
	{
		if(m_Isup == true){
				PlaySound ( MAKEINTRESOURCE(IDR_WING), GetModuleHandle(NULL),SND_RESOURCE |SND_ASYNC);
				m_Bird.upmovedis = 50;
				m_Bird.allup += 50;
				return ;
			}
			m_Bird.upmovedis = 50;
			m_Bird.allup = 50;
			PlaySound ( MAKEINTRESOURCE(IDR_WING), GetModuleHandle(NULL),SND_RESOURCE |SND_ASYNC);
			SetTimer(ID_UPBIRD,1, NULL);
			m_Isup = true;
	}

	CView::OnLButtonDblClk(nFlags, point);

}

void CFlappy_birdView::Changebird(void)		//����С���ͼƬ
{
	m_Bird.img = &m_BIRD[(m_Birdnum++)%3];
	InvalidateRect(NULL, FALSE);
}
