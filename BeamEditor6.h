// BeamEditor6.h : main header file for the BEAMEDITOR6 application
//

#if !defined(AFX_BEAMEDITOR6_H__06611410_0111_4787_9B22_DE107567D581__INCLUDED_)
#define AFX_BEAMEDITOR6_H__06611410_0111_4787_9B22_DE107567D581__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
// 2003.11.03 Define 모으기
#include "define.h"

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6App:
// See BeamEditor6.cpp for the implementation of this class
//
#define TIMER_MONITOR	100
#define TIMER_INIT		101
#define TIMER_COMMAND	102
#define TIMER_OVERRIDE	103


class CBeamEditor6App : public CWinAppEx
{
public:
	CBeamEditor6App();

	// 2003.11.03
public:
	void InitDefaultObject();
	CString m_strCwd; // 현재 작업 디렉토리 저장
	CString m_strDeviceIndex[255];
	CString m_strDeviceName[255];
	CString m_strLotNo_DisplaceText[255];
	CString m_strLotNo_DisplaceIndex[255];


	
	TCHAR m_szProductName[100];
	TCHAR m_szProductVersion[100];
	TCHAR m_szFileVersion[100];

	CString m_strProductName;
	CString m_strProductVersion;
	CString m_strProductFileVersion;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBeamEditor6App)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBeamEditor6App)
	afx_msg void OnAppAbout();
	afx_msg void OnVersion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL init(void);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEAMEDITOR6_H__06611410_0111_4787_9B22_DE107567D581__INCLUDED_)
