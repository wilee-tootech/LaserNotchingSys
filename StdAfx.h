// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DC004EC8_6131_4882_92F8_D9A0EC4A970E__INCLUDED_)
#define AFX_STDAFX_H__DC004EC8_6131_4882_92F8_D9A0EC4A970E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers


#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
 #include <SDKDDKVer.h>

#include "MCDefine.h"

#endif // _AFX_NO_AFXCMN_SUPPORT

/*

#if	_RTC3_
#include ".\Include\Rtc3\RTC3impl.h"
#endif

#if	_RTC4_
#include ".\Include\Rtc4\RTC4impl.h"
#endif

#if	_RTC4eth_
#include ".\Include\Rtc4eth\RTC4ethexpl.h"
#include ".\Include\Rtc4eth\stdint.h"
#pragma comment( lib, "RTC4ethDLL.lib") 
#endif

#if _RTCSCANALONE_
#include ".\Include\RtcScanAlone\SCANalone4impl.h"
//#include ".\Include\RtcScanAlone\SCANalone4expl.h"
#pragma comment(lib, "SCANalone4.lib")	
#endif


#if	_RTC6_
#include ".\Include\Rtc5\RTC5impl.h"
#endif


*/



#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// 2003.11.07 다이얼로그마다 사용
#include "LoadString.h"
#include "DRect.h"
#include "DPoint.h"
#include "DSize.h"
#include "DebugConsole.h"   //콘솔창으로 디버깅 정보 뿌리기 위한
#include <afxcontrolbars.h>

	typedef struct  {   
          double f_param;
          double s_param;
		  CString strTxt;
}FieldParam;


	extern "C" {
		FILE* _iob = NULL;
	}


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_STDAFX_H__DC004EC8_6131_4882_92F8_D9A0EC4A970E__INCLUDED_)
