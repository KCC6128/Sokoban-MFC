
// Sokoban_ver_MFC.h : main header file for the Sokoban_ver_MFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSokobanverMFCApp:
// See Sokoban_ver_MFC.cpp for the implementation of this class
//

class CSokobanverMFCApp : public CWinApp
{
public:
	CSokobanverMFCApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSokobanverMFCApp theApp;
