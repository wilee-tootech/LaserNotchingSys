// PointerContainer.h: interface for the CPointerContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTERCONTAINER_H__F6DB6B2F_588D_4115_8C7F_7B15423E9043__INCLUDED_)
#define AFX_POINTERCONTAINER_H__F6DB6B2F_588D_4115_8C7F_7B15423E9043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//class CDisplay;
//class CMKObjectApproacher;
//class CMKFile;
//
//#include "MKObjectApproacher.h"
//#include "MKFile.h"
//#include "CommandManager.h"

#include "ProjectBaseView.h"

class CMKObjectApproacher;
class CBeamEditor6View;
class CommandManager;
class CMKFile;
class CInformationView;
//class CPatternEditVeiw;
class CMainFormView;
class CGraphView;



class CPointerContainer
{
public:
	CPointerContainer();
	virtual ~CPointerContainer();


	

	static CMKObjectApproacher *GetApproacher();
	static void SetApproacher(CMKObjectApproacher *pApproacher);
	
	static CMKFile *GetMKFile();
	static void SetMKFile(CMKFile *pMKFile);
	
	
	static CBeamEditor6View *GetView();
	static void SetView(CBeamEditor6View *pView);

	static CMainFormView *GetCMainFormView(); 
	static void SetCMainFormView(CMainFormView *pView);
	
	
	static CInformationView *GetInformationView(); 
	static void SetInformationView(CInformationView *pView);

	static CGraphView *GetGraphView(); 
	static void SetGraphView(CGraphView *pView);

	
	static CommandManager *m_pCmdMng;

	static CMKObjectApproacher *m_pApproacher;
	static CMKFile *m_pFile;
	static CBeamEditor6View *m_pView;
	static CInformationView *m_pInfoView;
	static CGraphView *m_pGraphView;
	static CMainFormView *m_pMainFormView;
	
private:







};

#endif // !defined(AFX_POINTERCONTAINER_H__F6DB6B2F_588D_4115_8C7F_7B15423E9043__INCLUDED_)
