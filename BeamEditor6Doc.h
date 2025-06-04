// BeamEditor6Doc.h : interface of the CBeamEditor6Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEAMEDITOR6DOC_H__153146E4_8C5F_4F7F_8541_C7FEF84DFCBE__INCLUDED_)
#define AFX_BEAMEDITOR6DOC_H__153146E4_8C5F_4F7F_8541_C7FEF84DFCBE__INCLUDED_

//#include "AxtLIBDef.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TITLE_SIZE 16
#define TITLE_STR  "BeamEditor  "   //space 2개 

#define TITLE_SCR_SIZE 20
#define TITLE_SCR_STR "BeamEditorSCR   " //space 3개

#define TITLE_DEV_SIZE 20
#define TITLE_DEV_STR "BeamEditorDEV   " //space 3개


#define LIFE_HOT	1
#define LIFE_OLD	0
#include "./GUI/GuiManager.h"
#include "DFVDocument.h"


class CTitlePanel;
class CNavigationPanel;
class CCmdOperationPanel;
class CCmdLogPanel;
class CMainFormView;
class CGraphview;
class CMESFormView;
class CInfoMESPanel;
class CInforParaPanel;
class CInforMCStatusPanel;
class CInfor_LogPanel;
class CInfo_JamPanel;
class CInforSetupPanel;
// class CInformationView;
class CInforRecipeConfigPanel;


class CBeamEditor6Doc : public CDocument//CDFVDocument
{
protected: // create from serialization only
	CBeamEditor6Doc();
	DECLARE_DYNCREATE(CBeamEditor6Doc)

// Attributes
public:
	enum DataType
	{
		ID_OBJECT = 1,
		ID_PARAMETER = 2,
		ID_DEVICE = 3,
		ID_BIN = 4,
		ID_OFFSET = 5,
		ID_SERIALDATA = 6,
		ID_OPTIONTABLE = 7,
		ID_FONTDATA = 8,
		ID_SCRIBE = 9,
	};
	
// Operations
public:
	CTitlePanel*					m_pTitlePanel;
	CNavigationPanel*				m_pNavigationPanel;
	CCmdOperationPanel*				m_pCmdOperationPanel;
	CCmdLogPanel*					m_pCmdLogPanel;

	CMainFormView*					m_pMainFormView;
	CInforRecipeConfigPanel*		m_pInforRecipeConfigPanel;
	CGraphview*						m_pGraphPanel;
	//CMESFormView*					m_pMESPanel;
	CInfoMESPanel*					m_pMESPanel;
	CInforParaPanel*				m_pInforParaPanel;
	CInforSetupPanel*				m_pInforSetupPanel;
	CInforMCStatusPanel*			m_pInforMCStatusPanel;
	
	CInfor_LogPanel*				m_pInforLogPanel;
	CInfo_JamPanel*					m_pInforLogJamPanel;

//	CInformationView*				m_pInformationPanel;
	
	

	CString m_strDeviceFileName;
	BOOL m_CreateFlag;
	BOOL m_bVectorNoView;
	CString m_CurfileName;
	CString m_CurDevFileName;
	CString m_MrkInfoDisp;
	CString m_SemName;
	CString m_strSigFileName;
	CString m_strCurPower;
	BOOL m_AmkorSQL;
	int m_bTopBottomFlag;
	BOOL m_AutoFlag;
	BOOL m_ParaUpdate;
	BOOL m_savedFlag;
	CString m_CurPath;
	BOOL m_AutoDevHanmi;
	BOOL m_SutterOnFlag;
	BOOL m_GroupFlag;
	float m_fLastCurrent;
	float m_fSetPower;
	int m_iLampTimeMin;
	int m_iLampTimeHour;
	int m_iLampWarningTime;
	int m_iLampErrorTime;

	int m_EOLaserCurrent;
	BOOL m_PowerAdjust;
	BOOL m_ScannerPower;
	BOOL m_AutoVerticalAlign;
	BOOL m_AutoHorizontalAlign;

	BOOL m_bHandlerReady;  // Auto Device Change용
	int  m_iSCanningCount;  //바코드스켄 카운터 변수, 
						

	struct _cusData
	{
		int   index;
		TCHAR code[3];
	} structCusData[1024];

	struct _lotData
	{
		CString strLotNo;
		CString strPartNo;
		int nTime;
	} structLotHistory[1024];

	BOOL m_bHotLife;
	CString m_strCWD;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBeamEditor6Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bDrawStop;
	BOOL m_FileName;
	CString m_cwd;
	int m_iSetPower;
//	BYTE m_buff[4096];
	BOOL m_bServerConnect;	
	BOOL m_bDlgMarkFlag;	
	BOOL m_bFileOpen;	
	void EOOffsetSave(CString m_strRscName, double m_x, double m_y, double s_x, double s_y);
	BOOL AutoDevChange(int m_Devindex);

	// 2007.01.22  
	void ResetCusData(void);

	virtual ~CBeamEditor6Doc();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBeamEditor6Doc)
	afx_msg void OnSaveFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEAMEDITOR6DOC_H__153146E4_8C5F_4F7F_8541_C7FEF84DFCBE__INCLUDED_)
