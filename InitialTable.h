 // InitialTable.h: interface for the CInitialTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INITIALTABLE_H__E7E8EA5D_E52E_411D_82D0_D1DB0D393FAD__INCLUDED_)
#define AFX_INITIALTABLE_H__E7E8EA5D_E52E_411D_82D0_D1DB0D393FAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CInitialTable은 전체적으로 공통적인 요소들, MARK File과는 관계 없을 때
// COptionTable을 추가했습니다. (마크화일하곤 상관있고 마땅한 저장 공간이 없을때)
class CInitialTable  
{
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
		ID_HEAD1_NAME    = 165,
		ID_USE_SPECIMG_VIEW = 166,
		ID_USE_SPECIMG_FOLDER = 167,

		ID_VIEW_GRID = 200,
		ID_VIEW_RULER = 201,
		ID_VIEW_ONLYMARK = 202,

		ID_USE_COUNT     = 203,

		ID_RTC_BOARD	= 204,
		// syhun START - List mode
		ID_MODE_LIST = 210,

		ID_ENCODER_KX = 211,
		ID_ENCODER_KY = 212,
		ID_ENCODER_SIMUL_MODE = 213,
		ID_REVERSE_KXY = 214,
		ID_MAX_CUTTING_SIZE = 215,
		ID_ROLL_SPEED = 216,
		ID_FIRST_CUT_SIZE = 217,
		ID_SECOND_CUT_SIZE = 218,
		ID_LAST_CUT_SIZE = 219,
		ID_SAMPLE_SIZE = 220,
		ID_REAL_SIZE = 221,
		ID_REAL_FIELD_SIZE = 222,
		ID_MARKING_FIELD = 223,
		ID_CYCLE_OFFSET = 224,
		ID_SCANNER_SX_POS = 225,
		ID_SCANNER_SY_POS = 226,
		ID_RUNMODE = 227,
		ID_PATTERNMODE = 228,

		ID_ENCODER_KX2 = 229,
		ID_ENCODER_KY2 = 230,

		ID_ENCODER_KX_NOTCHING = 232,
		ID_ENCODER_KY_NOTCHING = 233,
		ID_ENCODER_KX2_NOTCHING = 234,
		ID_ENCODER_KY2_NOTCHING = 235,

		ID_CYCLE_OFFSET2 = 231,


	};

public:
	double GetFieldScale();
	int GetKindOfRtcBoard();
	int GetListMode();
	BOOL GetUseSpecImg();
	CString GetSpecImgFolder();
	CString GetHead1Name();
	COLORREF GetSelBoxColor();
	COLORREF GetGridLineColor();
	COLORREF GetDeviceLineColor();
	COLORREF GetDeviceOuterColor();
	COLORREF GetDeviceInnerColor();
	BOOL GetUseMarkCount();
	CString GetDefaultPenFile();
	double GetMaxLimitPower();
	double GetNormalLimitPower();
	double GetLowLimitPower();
	void SetDefaultLaserPower(double m_dPower);
	double GetDefaultLaserPower();
	CString GetAmkorHpglDir();
	CString GetAmkorFontDir();
	CString GetAmkorTmpDir();
	CString GetAmkorRscDir();
	CString GetAmkorPrjDir();
	CString GetAmkorEditDir();
	int     GetAmkorField();
	CString GetCompanyCode();
	int GetKindOfUser();
	CInitialTable();
	virtual ~CInitialTable();

	// Setting된 값들을 return
	int GetHead();
	BOOL GetLoadingImage();
	BOOL GetHKImage();
	BOOL GetNetwork();
	BOOL GetDefaultFile();
	BOOL GetNumberOfPart();
	int GetLanguage();
	int GetUnit();
	int GetLaser();
	int GetFieldSize();
	double GetMMSize();
	double GetFieldAngle();
	void SetFieldAngle(double dFieldAngle);
	void SetNetwork(BOOL bNetwork);
	void SetUseChipSelect(BOOL bUseChipSelect);
	BOOL GetUseChipSelect();
	void SetUseShutter(BOOL bUseShutter);
	BOOL GetUseShutter();
	CString GetDspFile();
	int GetBaseMasterX();
	int GetBaseMasterY();
	int GetBaseSlaveX();
	int GetBaseSlaveY();
	BOOL GetViewGrid();
	BOOL GetViewRuler();
	BOOL GetViewOnlyMark();
	void SetViewGrid(BOOL bFlag);
	void SetViewRuler(BOOL bFlag);
	void SetViewOnlyMark(BOOL bFlag);
	BOOL GetUseParaColor();
	BOOL GetObjectRatio();
	int GetRulerSize();
	int GetRulerScale();
	int GetRulerFontSize();
	int GetKindOfLaser();

	COLORREF *GetParaCol();

	// 초기화 파일을 Loading
	UINT LoadInitialFile(CString FileName);
	UINT SaveInitialFile(CString FileName);
	char *Serialize(DWORD &dwLength);
	void Unserialize(char *pstrSerial);
	// 유일한 instance 반환
	static CInitialTable *GetInstance();

private:
	int		m_iRtcBoard;
	int     m_iHead;
	int     m_iKindOfLaser;
	int		m_iLanguage;
	int		m_iUnit;
	int		m_iLaser; // Laser Source 구분
	double	m_dFieldSize;
	double	m_dMMSize;
	BOOL	m_bLoadDefaultFile;
	BOOL	m_bLoadHKImage;
	BOOL	m_bUseLoadingImage;
	BOOL	m_bUseTwoPart; // 싱글 or Co2 용으로 듀얼인것 처럼 사용하는 것
	BOOL	m_bUseHandlerNetwork;
	BOOL	m_bUseChipSelect; // Device 창에서 클릭 선택 사용할 지 여부 저장
	BOOL    m_bUseShutter; // Shutter 사용할 것이면 TRUE, Data No Down을 사용할 것이면 FALSE
	BOOL    m_bReverseKXY; // Encoder Reverse
	double	m_dFieldScale;
	double	m_dFieldAngle;
	double  m_dBaseMasterX;
	double  m_dBaseMasterY;
	double  m_dBaseSlaveX;
	double  m_dBaseSlaveY;
	double  m_dLaserPower;
	double m_LowLimitPower;
	double m_NormalLimitPower;
	double m_MaxLimitPower;
	double m_dKx;
	double m_dKy;
	double m_dKx2;
	double m_dKy2;

	double m_dKx_Notch;
	double m_dKy_Notch;
	double m_dKx2_Notch;
	double m_dKy2_Notch;

	double m_dMaxCuttingSize;
	double m_dRollSpeed;
	double m_dSampleSize;
	double m_dRealSize;
	double m_dRFieldSize;
	double m_dMarkingField;
	double m_dCycleOffset;
	double m_dCycleOffset2;
	double m_dScannerStartPosX;
	double m_dScannerStartPosY;
	int m_nRunMode;
	int m_nPatternMode;


	CString m_strDspFile;
	static CInitialTable *m_pInitialTable; // 유일한 instance
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
	BOOL	m_bLaserError;
	BOOL	m_bManualEnd;
	BOOL	m_bManualStart;
	BOOL	m_bWaitEnd;
	BOOL	m_bWaitStart;
	int		m_iAutoEnd;
	int		m_iAutoEndEvent;
	int		m_iAutoStart;
	int		m_iLaserError;
	int		m_iManualEnd;
	int		m_iManualStart;
	int		m_iWaitEnd;
	int		m_iWaitStart;
	int		m_iSavePeriod;
	CString m_strLogSaveDir;
	COLORREF m_colPara[21];
	BOOL	m_bUseParaColor;
	BOOL	m_bUseObjectRatio;
	BOOL    m_bUseMarkCount;
	BOOL    m_bUseSpecImgView;
	
	BOOL m_bViewGrid;
	BOOL m_bViewRuler;
	BOOL m_bViewOnlyMark;

	int	 m_iListMode;	// syhun START - List mode
	int  m_iSimulationMode; 



	//------------------ EO Dir var--------------------------
	int m_KindOfUser;
	
	CString m_strEditDir,m_strRscDir,m_strFontDir,m_strTmpDir,m_strPrjDir,m_strHpglDir,m_strAmkorField,m_strCompanyCode,m_strPenFile,m_strHead1Name,m_strSpecImgFolder; // Amkor Dirsetting 2004.11.03 

	//----------------------------------------------------------

	void SetVariable(CString Index, CString Variable);
};

#endif // !defined(AFX_INITIALTABLE_H__E7E8EA5D_E52E_411D_82D0_D1DB0D393FAD__INCLUDED_)
