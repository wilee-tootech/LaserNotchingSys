
#ifndef _RTC5_HEADER_FILE_
	#define _RTC5_HEADER_FILE_
#pragma once

#include "ScannerDefine.h"
#include <vector>
#include <iterator>
#include <algorithm>

#ifdef NX_SCANNER_EXPORTS 
#define NX_DLL_EXPORTS	__declspec( dllexport )
#else 
#define NX_DLL_EXPORTS	__declspec( dllimport )
#endif

class NX_DLL_EXPORTS CRtc5
{
private:
	int  m_nBoardIdx;
	UINT m_unErroNo;
	CHAR m_caCfgPath[MAX_PATH];
	BOOL m_bInit;

	// List Execute status
	UINT m_unListPos;

	// Galvano Status
	// Head Status

	TCHAR m_szRet[MAX_PATH*3];

#ifdef _UNICODE
	std::wstring m_strList;
#else
	std::string m_strList;
#endif

	long m_lEncX;
	long m_lEncY;

	// Version 
	UINT m_unDllVer;
	UINT m_unHexVer;
	UINT m_unRtcVer;
	UINT m_unSerialNum;

	// Scale
	double m_dScaleX;
	double m_dScaleY;

	// Configuration 
	TDefLasPulse m_tDefLasPulse;
	TDefDelay    m_tDefDelay;
	TDefLasDelay m_tDefLasDelay;
	TDefSpeed    m_tDefSpeed;
	UINT         m_unLasMode;

	// List
	UINT m_unAllListSpace;
	UINT m_unExeListSize;
	UINT m_unExeListIdx;
		
public:
	THeadInfo    m_tHeadInfo;
	TListExeStat m_tListExeStat;
	UINT         m_unListExePos;
	UDefErr      m_uErrList;

	std::vector< CPoint > m_vData;
	std::vector< TDefCmdList > m_vCmdList;
	std::vector< TDefCmdList > m_vEtchList;
	std::vector< TDefCmdList > m_vEtchListFly; //BJBD
	UINT		m_uTotalRepeat;			   //BJBD
	BOOL		m_bRotationDone;

public:			//BJBD
	SCANNER_MODE    m_nScannerMode;  
	int				m_nListNumber;
private:
	//
	void SetStrList( int nListNo = 1U );
	void EndList();

	//Board Initialize
	BOOL LoadProgFile();
	BOOL LoadCorrectFile();	
	void SelCorrectTable();

	// Error
	UINT GetErr();
	//
	UINT GetListSpace();
	
	// Get Status & Position
	void GetPos();
	void GetHeadStat();

public:
	CRtc5( int nBoardIdx, double dScaleX, double dScaleY );
	~CRtc5(void);

	// 
	BOOL Init();	
	virtual void Terminate();

	//
	int GetIndex(){ return m_nBoardIdx;}
	
	// Galvo Initializing
	void GalvoInit();

	// Thread
	void __stdcall Execute( void ); //BJBD
	void SetScannerMode(SCANNER_MODE nScanMode); //BJBD
	void SetListNumber(int nListNum);
	void SetTotalRepNum(int nRepeatNum); // BJBD
	UINT GetTotalRepNum();
	void SetRotationDone(BOOL bRotationDone); //BJBD
	// Version 
	UINT GetDllVer();
	UINT GetHexVer();
	UINT GetRtcVer();
	UINT GetSerialNum();

	// Laser Signal
	void SetLasSigOn();
	void SetLasSigOff();

	// Dll Init && Release
	static BOOL LoadDll(  UINT &unBoardNum );
	static BOOL ReleaseDll();

	long GetEncX(){ return m_lEncX; }
	long GetEncY(){ return m_lEncY ;}

	// Galvono Goto
	void GotoXY( long lX, long lY );

	//Execute List
	void ExeList( int nListNo = 1U );
	void StopExeList();
	void PauseExe();
	void ReExeList();
	void StopList();

	// List 
	void AddListCmd( ENUM_LIST_CMD eCmd, long nData, ... );

	// Manual Load Lists
	void ExeCmdList(void);
	//Make Command Lists
	BOOL MakeCmdList( int nListNo = 1);
	BOOL MakeCmdListRot( int nListNo = 1); //BJBD
	BOOL MakeCmdListFly( int nListNo = 1); //BJBD
	   
	void GetListStat();

	// Set & Get Configuration Parameter.
	void OpenParam();
	void SaveParam();

	double GetCfgLasPulsePeriod() { return m_tDefLasPulse.dHalfPeriod; }
	double GetCfgLasPulseLength() { return m_tDefLasPulse.dPulseLen; }
	UINT GetCfgJumpDelay()        { return m_tDefDelay.unJump; }
	UINT GetCfgMarkDelay()        { return m_tDefDelay.unMark; }
	UINT GetCfgPolygonDelay()     { return m_tDefDelay.unPolygon; }
	UINT GetCfgLaserOnDelay()     { return m_tDefLasDelay.unLaserOn; }
	UINT GetCfgLaserOffDelay()    { return m_tDefLasDelay.unLaserOff; }
	UINT GetCfgLaserMode()        { return m_unLasMode; }

	double GetCfgJumpSpeed()      { return m_tDefSpeed.dJump; }
	double GetCfgMarkSpeed()      { return m_tDefSpeed.dMark; }

	void SetCfgLasPulse( double dHalf, double dLen );
	void SetCfgDelay( UINT unJump, UINT unJumpMark, UINT unPolygon );
	void SetCfgLasDelay( UINT unOnDelay, UINT unOffDelay );
	void SetCfgSpeed( double dJump, double dMark );
	void SetCfgLasMode( int nIdx );

	void SetLasPulse( double dHalf, double dLen );
	void SetScanDelay( UINT unJump, UINT unJumpMark, UINT unPolygon );
	void SetLasDelay( UINT unOnDelay, UINT unOffDelay );
	void SetJumpMarkSpeed( double dJump, double dMark );
	void SetFirstPulseKiller( int nlen );
	void SetLasMode( int nIdx );

	void SetLasPulseCtrl( double dHalf, double dLen );
	void SetLasMode();

	BOOL LoadCmdList( TCHAR* szName );
	BOOL SaveCmdList( TCHAR* szName );
	BOOL DelCmdList( TCHAR* szName );
	TCHAR* GetCmdListView();
	// List
	UINT GetAllListSpace();
	UINT GetListExeSize();
	UINT GetListExeIdx( UINT unSelList = 1U );

	void GetStat();

};

#endif


