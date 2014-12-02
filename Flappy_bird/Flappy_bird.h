// Flappy_bird.h : main header file for the Flappy_bird application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CFlappy_birdApp:
// See Flappy_bird.cpp for the implementation of this class
//

class CFlappy_birdApp : public CWinApp
{
public:
	CFlappy_birdApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFlappy_birdApp theApp;