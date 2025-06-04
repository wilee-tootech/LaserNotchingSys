// OptionsDlg.h : header file
//

#if !defined(AFX_OPTIONSDLG_H__310471FE_A8D3_4D0F_8219_4E7A7B7452F1__INCLUDED_)
#define AFX_OPTIONSDLG_H__310471FE_A8D3_4D0F_8219_4E7A7B7452F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog
#include "DlgView.h"
#define PARA_NUM 20

class COptionsDlg : public CDialog
{
// Construction
public:
	enum OptionsID {
		ID_OPTIONS = 100,
		ID_DEFAULT_MARK_FILE = 101,
		ID_LOAD_HK_IMAGE = 102,
		ID_HANDLER_NETWORK = 103,
		ID_USE_LOADING_IMAGE = 104,
		ID_USE_TWO_PART = 105,
		ID_USE_CHIP_SELECT = 106,
		ID_USE_SHUTTER = 107,
		ID_FIELD_SCALE = 108,
		ID_FIELD_ANGLE = 109,
		ID_MAX_FIELD = 110,
		ID_MAX_MM = 111,
		ID_MASTER_X_OFFSET = 112,
		ID_MASTER_Y_OFFSET = 113,
		ID_SLAVE_X_OFFSET = 114,
		ID_SLAVE_Y_OFFSET = 115,
		ID_UNIT = 116,
		ID_LASER_SOURCE = 117,
		ID_KINDOF_LASER = 118,
		ID_HEAD = 119,
		ID_LOW_POWER = 120,
		ID_NORMAL_POWER = 121,
		ID_MAX_POWER = 122,
		
		ID_SELBOX_SIZE = 123,
		ID_RULER_SIZE = 124,
		ID_RULER_FONTSIZE = 125,
		ID_RULER_SCALESIZE = 126,
		ID_COL_DEVINNER = 127,
		ID_COL_DEVOUTER = 128,
		ID_COL_DEVLINE = 129,
		ID_COL_GRIDLINE = 130,
		ID_COL_GRIDSCALE = 131,
		ID_COL_SELBOX = 132,
		ID_COL_RULER = 133,
		ID_CHK_AUTO_START = 134,
		ID_CHK_AUTO_END = 135,
		ID_CHK_AUTO_END_EVENT = 136,
		ID_CHK_MANUAL_START = 137,
		ID_CHK_MANUAL_END = 138,
		ID_CHK_WAIT_START = 139,
		ID_CHK_WAIT_END = 140,
		ID_CHK_LASER_ERROR = 141,
		ID_CODE_AUTO_START = 142,
		ID_CODE_AUTO_END = 143,
		ID_CODE_AUTO_END_EVENT = 144,
		ID_CODE_MANUAL_START = 145,
		ID_CODE_MANUAL_END = 146,
		ID_CODE_WAIT_START = 147,
		ID_CODE_WAIT_END = 148,
		ID_CODE_LASER_ERROR = 149,
		ID_LOG_SAVE_DIR = 150,
		ID_LOG_SAVE_PERIOD = 151,
		ID_USE_PARA_COL = 152,
		ID_PARA_COL = 153,
		ID_USE_OBJECT_RATIO = 154,

		ID_KINDOF_USER = 155,
		//--------- Amkor Dir -------------
		ID_USE_AMKOR_EDIT_DIR = 156,
		ID_USE_AMKOR_RSC_DIR = 157,
		ID_USE_AMKOR_PRJ_DIR = 158,
		ID_USE_AMKOR_HPGL_DIR = 159,
		ID_USE_AMKOR_FONT_DIR = 160,
		ID_USE_AMKOR_TMP_DIR = 161,
		ID_USE_AMKOR_FIELD   = 162,
		ID_USE_COMPANY_CODE   = 163,
		ID_USE_AMKOR_PEN_FILE  = 164,
		ID_HEAD1_NAME   = 165,
		ID_USE_SPECIMG_VIEW = 166,
		ID_USE_SPECIMG_FOLDER = 167,

		ID_VIEW_GRID = 200,
		ID_VIEW_RULER = 201,
		ID_VIEW_ONLYMARK = 202,
		ID_USE_COUNT     = 203,

		ID_RTC_BOARD = 204,
		// syhun START - List mode
		ID_MODE_LIST = 210,

	
		
		
		
	};

private:
	int m_iRtcBoard;
	CString m_strLaserSource;
	int m_iLaserSource;
	int m_iHead;
	int m_iKindOfLaser;
	//double m_dLaserPower;
	double m_LowLimitPower;
	double m_NormalLimitPower;
	double m_MaxLimitPower;

	int	m_iSelBoxSize;
	int	m_iRulerSize;
	int	m_iRulerFontSize;
	int	m_iRulerScaleSize;
	COLORREF m_colDevInner;
	COLORREF m_colDevOuter;
	COLORREF m_colDevLine;
	COLORREF m_colGridLine;
	COLORREF m_colGridScale;
	COLORREF m_colSelBox;
	COLORREF m_colRuler;
	BOOL	m_bAutoEnd;
	BOOL	m_bAutoEndEvent;
	BOOL	m_bAutoStart;
	int		m_iAutoEnd;
	int		m_iAutoEndEvent;
	int		m_iAutoStart;
	int		m_iLaserError;
	int		m_iManualEnd;
	int		m_iManualStart;
	int		m_iWaitEnd;
	int		m_iWaitStart;
	BOOL	m_bLaserError;
	BOOL	m_bManualEnd;
	BOOL	m_bManualStart;
	int		m_iSavePeriod;
	BOOL	m_bWaitEnd;
	BOOL	m_bWaitStart;
	CString m_strLogSaveDir;
	COLORREF m_colPara[20];
	int m_KindOfUser;
	int m_SpecImgView;
	CString m_strEditDir,m_strRscDir,m_strFontDir,m_strTmpDir,m_strPrjDir,m_strHpglDir,m_strAmkorField,m_strPenFile; // Amkor Dirsetting 2004.11.03 

	//CString m_strCompanyCode;

public:
	CString SetRtcBoardStatus();
	CString SetHeadStatus();
	CString SetSourceStatus();
	void SetLaserStatus();
	COptionsDlg(CWnd* pParent = NULL);	// standard constructor

	void Save();
	void Load();
	char *Serialize(DWORD &dwLength);
	void Unserialize(char *pchSerial);

// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_OPTIONS_DIALOG };
	CButton	m_AmkorChk;
	BOOL	m_bLoadHKImage;
	BOOL	m_bLoadDefaultFile;
	BOOL	m_bUseHandlerNetwork;
	BOOL	m_bUseLoadingImage;
	BOOL	m_bUseTwoPart;
	BOOL	m_bUseChipSelect;
	BOOL	m_bUseShutter;
	double	m_dFieldAngle;
	int		m_iMaxField;
	int		m_iMaxMm;
	double	m_dBaseMasterY;
	double	m_dBaseMasterX;
	double	m_dBaseSlaveX;
	double	m_dBaseSlaveY;
	int		m_iUnit;
	BOOL	m_bUseParaColor;
	BOOL	m_bUseObjectRatio;
	CString	m_strCompanyCode;
	BOOL	m_bUseCount;
	CString	m_strHead1Name;
	BOOL	m_bUseSpecImg;
	CString	m_strSpecImgFolder;
	int		m_iListMode;	// syhun START - List mode
	
	double	m_dFieldScale;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnLaserSelect();
	afx_msg void OnViewOption();
	afx_msg void OnLogOption();
	afx_msg void OnSelParaColor();
	afx_msg void OnCheckAmkor();
	afx_msg void OnCheckImage();
	afx_msg void OnButtonDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__310471FE_A8D3_4D0F_8219_4E7A7B7452F1__INCLUDED_)
