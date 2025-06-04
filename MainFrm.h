// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__E7197DF8_7E74_46FC_A626_302D3C5DD8EA__INCLUDED_)
#define AFX_MAINFRM_H__E7197DF8_7E74_46FC_A626_302D3C5DD8EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BCMenu.h" /* Loading 24Bit Image */
#include "DlgSpectron.h" /* Laser Control */
#include "DlgFiber.h"	// 2007.02.13  
//#include "ConcreteIterator.h"
#include "TipToolBar.h"
#include "QuntronixDlg.h"
#include "Communicate.h"

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
#endif

#if _RTCSCANALONE_
#include ".\Include\RtcScanAlone\SCANalone4impl.h"
//#include ".\Include\RtcScanAlone\SCANalone4expl.h"
#endif


#if	_RTC6_
#include ".\Include\Rtc5\RTC5impl.h"
#endif
*/

#include "define.h"
#include "DlgProgressBar.h"
#include "DlgMsgDC.h"

#include "FieldParameter.h"
#include "DlgSPIDualLaser.h"
#include "DlgIPGDualLaser.h"
#include "IniUtil.h"


#include "DFVFrameWnd.h"
#include "UsefulSplitterWnd.h"
#include "DlgMES.h"
#include "DustTrap.h"
#include "DlgDualScannerParameter.h"

#define AUTO_MARK_VIEW		984
#define AUTO_MARK_START		985

#define TM_UPDATEINFO		300
#define TM_CHECK_HARDSPACE  320



#define TOOLBAR_DRAW_BUTTON_WIDTH 60

#define WM_LOGIN_SUCCESS WM_USER + 1


////////// RunMgr 용 TImerID //////////
#define TM_INTER_LOCK_CHECK  1001
#define TM_START_PROGRAM	1111
#define TM_LASER_START		1112
#define TM_LASER_CHECK		1113

//class CBeamEditor6View;
//class CDlgProgressBar;

//class CDlgDspTest;

class CBeamEditor6Doc;

class CMainFrame : public CDFVFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	HMENU LoadingMenu(); /* Loading 24Bit Image */
	afx_msg LRESULT OnLoginSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSockReceive(WPARAM wParam, LPARAM lParam);

	CStatusBar *GetStatusBar();
// Attributes
public:
	CFileMgr FileMgr;
	static void __stdcall ThreadRun(void); 
	static void __stdcall ThreadStop(void); 
	static void __stdcall ThreadStart(void); 

	void ChangeView( int nFormID );
	void HideView( int nFormID );
	void UpdateWindowButtons(bool enable);
//	CItemList<CParameter*>	*m_pItemList;
	void DisableFunctions();
    void EnableFunctions();

	bool m_bFunctionsDisabled;

	BOOL m_OrgScaleFlag;
	_NOTCH_PATTERN_DATA m_stNotchPatternData;

	CString m_strUserID;
	CString m_strUserPW;

	bool mesLoginCheck;

	CDlgMES *GetDlgMES() const { return pDlgMES; }
	//CDlgDualScannerParameter *GetDlgDualScannerParameter() const { return pDlgDualScannerParameter; }

	IniUtil _iniUtil;

	BOOL bHead1LockA;
	BOOL bHead1LockB; 
	BOOL bHead2LockA;
	BOOL bHead2LockB; 
	

// Operations
public:
//	CItemList<CParameter*> *GetItemList();
	BOOL OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult );

public:
	void SetNoClose(BOOL bFlag)
	{
		m_bNoClose = bFlag;
	}
	BOOL GetNoClose()
	{
		return m_bNoClose;
	}
	
	//CDlgDspTest *m_pDlgTest;//   ׽ Ʈ 


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	CBeamEditor6Doc* m_pDoc;
	CSize			m_sizeDrawWindow;
	CQuntronixDlg m_pDlg;
	//CBeamEditor6View * GetView();
	void CreateLaserControl();
	void OnNewSem();
	void OnSelectAll();
	void OnUnselectAllFrame();
	afx_msg void OnScreenZoomOrg();
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
	afx_msg void OnEditParameter();
	afx_msg void OnNewHpgl();
	afx_msg void OnSetFieldSize();
	afx_msg void OnLaserCtr();
	//void OnAlignHcenter();
	//void OnAlignVcenter();
	//void OnUnselectAllFrame();
	afx_msg void OnFileNew();
	afx_msg void OnViewAlign();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	BOOL        m_bNoClose;


	
	
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNewTtf();
	afx_msg void OnCommSetting();
	afx_msg void OnMarkFrame();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnBinSetting();
	
	
	afx_msg void OnViewEdit();
	afx_msg void OnUpdateViewAlign(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewEdit(CCmdUI* pCmdUI);
	afx_msg void OnViewHelp();
	afx_msg void OnUpdateViewHelp(CCmdUI* pCmdUI);
	afx_msg void OnViewMarkorder();
	afx_msg void OnUpdateViewMarkorder(CCmdUI* pCmdUI);
	afx_msg void OnViewStandard();
	afx_msg void OnUpdateViewStandard(CCmdUI* pCmdUI);
	afx_msg void OnChangeUserLevel();
	afx_msg void OnChangePassword();
	afx_msg void OnSetAuthority();
	
	afx_msg void OnEditDevice();
	afx_msg void OnNewText();
	afx_msg void OnNewArc();
	afx_msg void OnNewLine();
	afx_msg void OnUpdateDrawArc(CCmdUI* pCmdUI);
	afx_msg void OnEditObjFrame();
	afx_msg void OnUndo();
	afx_msg void OnRedo();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnObjCopyFrame();
	afx_msg void OnAlignBottom();
	afx_msg void OnAlignTop();
	afx_msg void OnAlignRight();
	afx_msg void OnAlignLeft();
	afx_msg void OnObjEraseFrame();
	afx_msg void OnOrderUp();
	afx_msg void OnOrderDown();
	afx_msg void OnAlignHcenter();
	afx_msg void OnAlignVcenter();
	afx_msg void OnAlignObjLeft();
	afx_msg void OnAlighObjTop();
	afx_msg void OnAlignObjBottom();
	afx_msg void OnAlignObjRight();
	afx_msg void OnSameWidth();
	afx_msg void OnSameHeight();
	afx_msg void OnSameBoth();
	afx_msg void OnOrderFirst();
	afx_msg void OnOrderLast();
	afx_msg void OnNewImg();
	afx_msg void OnNewBar();
	afx_msg void OnObjectFix();
	afx_msg void OnMainZoomIn2();
	afx_msg void OnMainZoomOut();
	afx_msg void OnSelectZoom();
	afx_msg void OnScreenZoomOrgFrame();
	afx_msg void OnUpdateEditParameter(CCmdUI* pCmdUI);
	afx_msg void On2dbarcode();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnUpdateObjectFix(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignObjBottom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignObjLeft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignObjRight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignObjTop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSameBoth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSameHeight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSameWidth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignBottom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignHcenter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignRight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignLeft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignTop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignVcenter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOrderUp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOrderLast(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOrderFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOrderDown(CCmdUI* pCmdUI);
	afx_msg void OnViewGrid();
	afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
	afx_msg void OnViewRuler();
	afx_msg void OnUpdateViewRuler(CCmdUI* pCmdUI);
	afx_msg void OnViewOnlymark();
	afx_msg void OnUpdateViewOnlymark(CCmdUI* pCmdUI);
	afx_msg void OnViewFigure();
	afx_msg void OnUpdateViewFigure(CCmdUI* pCmdUI);
	afx_msg void OnChangeMarkorder();
	afx_msg void OnMenuAmkor();
	afx_msg void OnSampledbMenu();
	afx_msg void OnReLogin();
	afx_msg void OnSemfileSave();
	afx_msg void OnRscfileSave();
	afx_msg void OnShutterDelay();
	afx_msg void OnCustomerCode();	
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOperatorMode();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNewText(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLaserCtr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNewHpgl(CCmdUI* pCmdUI);

	//afx_msg void OnUpdateParameter(CCmdUI* pCmdUI);
		
		
	afx_msg void OnUpdateMarkFileSave(CCmdUI* pCmdUI);
	afx_msg void OnLotCompTime();
	afx_msg void OnUpdateObjCopyFrame(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjEraseFrame(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUnselectAllFrame(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMainZoomIn2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMainZoomOut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateScreenZoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateScreenZoomOrg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNewImg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNewBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdate2dbarcode(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNewTtf(CCmdUI* pCmdUI);
	afx_msg void OnNewDxf();
	afx_msg void OnPaint();
	afx_msg void OnUpdateNewDxf(CCmdUI* pCmdUI);
	afx_msg void OnHardwareTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	//CBeamEditor6Doc* m_pDoc;
	UINT m_nTimerID;
	int m_nTimerDelay;

	/* Separated Toolbar */
	CToolBar m_Tool[MAXTOOLBARS];
	//CTipToolBar m_ToolBar;

	BOOL	 m_bToolCheck[MAXTOOLBARS];
	BOOL	 m_bToolBar;
	BOOL	 m_bShowStandard;
	BOOL	 m_bShowEdit;
	BOOL	 m_bShowAlign;
	BOOL	 m_bShowMarkOrder;
	BOOL	 m_bShowHelp;
	BOOL     m_bShowFigure;

	/* Loading 24Bit Image */
	BCMenu m_menu, m_menuPop;

	/* Split Window*/
//	CSplitterWnd	m_wndSplitter;
	//CSize			m_sizeDrawWindow;
	CSize			m_sizeDialogWindow;
	CSize			m_sizeDrawGraph;
	CCreateContext  m_Context;
	
	/* Laser Control Dialog */
	CDialog		   *m_pDlgLaserControl;

	CDialog		   *m_pDlgManualCutting;



	// Progress bar
	CToolTipCtrl    m_Tip; //    

	UINT			m_nMenuID; //  ˾   ޴     ̵ 


	void InitItemList();
	void LoadToolbar();
	void InitDefaultObject();
	CCommunicate *m_pCommunicate;


	void SetContextMenu(UINT nID);
public:
	BOOL m_bExitFlag;
	void ExitApp();
	CDlgMsgDC *dlgMsg;
	CDlgMES   *pDlgMES;
	CDustTrap *pDlgDustTrap;
	CDlgDualScannerParameter* pDlgDualScannerParameter;
	void OnHatch();
	void ExixProcessName(CString strProcessName);
	void OnMenuFontcad();
	void InitPsc();
	void CreateProgressBar();
	BOOL m_bTempFileNew;	
	void GetOperatorTime();
	int m_nOperatorTime;
	void Load_DeviceIndex();
	void Load_TapPosition();
	void AlignHCenter();
	void AlignVCenter();
	void SetDelayTime(unsigned int iSecond);
	void DeleteObj();
	void CopyObj();
	void OnZoomOrg();
	void UnGroup();
	void GrouopObj();
	void OnShowLaserControl();
	void ResourceSaveProc();
	void EO_OffsetSave();

	void AutoAlignment(BOOL m_flag);
	void SellectAllObj();
	void UnSellectAllFrame();
	void UnSellectInit();
	void OnGroupAll();
	void EnablePopMenu();

	bool FirstLogFlag;

	//    ߰ ...
	//
	BOOL InitRTC(); 
	//CSplitterWnd	m_wndSplitterHor;
	//CSplitterWnd	m_wndSplitterVer;
	CUsefulSplitterWnd	m_wndSplitterHor;
	CUsefulSplitterWnd	m_wndSplitterVer;

	int m_nView1;
	int m_nView2;

	BOOL ProcessKill(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNewData();
	afx_msg void OnUpdateNewData(CCmdUI *pCmdUI);
	void UpdateSplitterWindow(void);
	void UpdateScannerPos();
	void SavePatternCycleImageLog();
	void DisplayMessage(CString strMessage);
	void HideMessage(void);
	
	afx_msg void OnMenuIo();
	
	afx_msg void OnUpdateSetFieldSize(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSetAuthority(CCmdUI *pCmdUI);
	void CheckHardDiskSpace(void);
	void AddLogData(CString strLogData);
	void UpdateInfomationView(void);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
//	afx_msg void OnMenuTest();
//	afx_msg void OnMenuTestcut();
//	afx_msg void OnUpdateMenuTestcut(CCmdUI *pCmdUI);

	afx_msg void OnLightSetting();
	afx_msg void OnUpdateLightSetting(CCmdUI *pCmdUI);
//	afx_msg void OnMenuTestcut();
	
	afx_msg void OnSettingMannual();
	afx_msg void OnMES();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	void RecentFileopen(void);
	int RecipeOpen(CString strFilename);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__E7197DF8_7E74_46FC_A626_302D3C5DD8EA__INCLUDED_)
