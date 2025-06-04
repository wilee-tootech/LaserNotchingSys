#ifndef _SCANNER_MANAGER_HEADER_
#define _SCANNER_MANAGER_HEADER_

#pragma once
#include <vector>
#include <iterator>
#include "Rtc5.h"

#define MAX_SCAN_BUFF                  100000

#ifdef NX_SCANNER_EXPORTS 
#define NX_DLL_EXPORTS	__declspec( dllexport )
#else 
#define NX_DLL_EXPORTS	__declspec( dllimport )
#endif

class NX_DLL_EXPORTS CScannerManager
{
private:
	UINT m_nBoardNum;
	std::vector< CRtc5* > m_vList;
	double m_dScanScaleX;
	double m_dScanScaleY;


public:
	CScannerManager( double fScaleX, double fScaleY );
	~CScannerManager(void);

	void Init();
	void Terminate();

	UINT GetBoardNum() { return m_nBoardNum; }
	CRtc5* GetItem( int nIdx );

};

extern NX_DLL_EXPORTS CScannerManager* g_opScanMgr;

#endif

