#pragma once

#include "Control\fpspread8.h"
#include "Include\EXTERN\ctlist.h"
#include "Communicate.h"
#include "DualScannerParameter.h"
#include "Control\ControlHeader.h"
#include "Dsp.h"
#include "DlgWaitForMES.h"
#include "./Include/EXTERN/FileMgr.h"
#include "../DIALOGEX/UserDialogEx.h"
#include "IniUtil.h"


#define WM_LOGIN_SUCCESS WM_USER + 1
#define MAX_LOG_CNT     500

typedef unsigned char BYTE;
// CDlgMES 대화 상자입니다.
// 클라이언트
// 병목 현상 : 동기소켓을 사용했을때 기다리는 현상
// 멀티스레딩 - 비동기소켓 사용
class CDlgUserLogIn;

typedef struct 
{
	CString strTotalXMLLength;
	CString strMESDate;
	CString strSysByte;

} LinkTestMessage;

#pragma pack(push, 1)
typedef struct
{
    BYTE bySTX;

    // General Parameters
    double P9011_TOTAL_WIDTH;
    double P9012_TAB_COUNT;
    double P9013_TOTAL_HEIGHT;

    double P9021_CUTTING_WIDTH;
    double P9022_CUTTING_HEIGHT;
    double P9023_CUTTING_HEIGHT_OFFSET;

    double P9031_ARC_IN_X;
    double P9032_ARC_IN_Y;
    double P9033_ARC_OUT_X;
    double P9034_ARC_OUT_Y;
    double P9035_ARC_DEG;

    double P9051_CUTTING_SPEED;
    double P9052_CUTTING_EXT_SPEED;
    double P9053_CUTTING_LINE_SPEED;
    double P9054_NOTCHING_LINE_SPEED;
    double P9055_JUMP_SPEED;
    double P9056_CUTTING_LASER_POWER;
    double P9057_NOTCHING_LASER_POWER;
    double P9058_CUTTING_LASER_FREQ;
    double P9059_NOTCHING_LASER_FREQ;
    double P9060_LASER_ARC_OFFSET;
    double P9061_NG_SENSOR_LENGTH;
    double P9062_ARC_MARK_SPEED;

    double P9063_LASER_ON_DELAY;
    double P9064_LASER_OFF_DELAY;
    double P9065_END_SCALE;
    double P9066_ARC_SCALE;
    double P9067_CORNER_SCALE;
    double P9068_FLAG_LINE_EXT;
    double P9069_TAB_OFFSET;
    double P9070_LINE_END_OFFSET;
    double P9071_FIRST_CUTTING_EXT;
    double P9072_LASER_PULSE_WIDTH;
    double P9073_FIRST_NOTCH_OFFSET;
    double P9074_SENSOR_OFFSET;

    // LASER 기준값
    double P9101_NotchingWidth1;
    double P9102_NotchingWidth2;
    double P9103_NotchingWidth3;
    double P9104_NotchingWidth4;
    double P9105_NotchingWidth5;
    double P9106_NotchingWidth6;
    double P9107_NotchingWidth7;
    double P9108_NotchingWidth8;
    double P9109_NotchingWidth9;
    double P9110_NotchingWidth10;
    double P9111_NotchingWidth11;
    double P9112_NotchingWidth12;
    double P9113_NotchingWidth13;
    double P9114_NotchingWidth14;
    double P9115_NotchingWidth15;
    double P9116_NotchingWidth16;
    double P9117_NotchingWidth17;
    double P9118_NotchingWidth18;
    double P9119_NotchingWidth19;
    double P9120_NotchingWidth20;
    double P9121_NotchingWidth21;
    double P9122_NotchingWidth22;
    double P9123_NotchingWidth23;
    double P9124_NotchingWidth24;
    double P9125_NotchingWidth25;

    // LASER 옵셋값
    double P9201_NotchingOffset1;
    double P9202_NotchingOffset2;
    double P9203_NotchingOffset3;
    double P9204_NotchingOffset4;
    double P9205_NotchingOffset5;
    double P9206_NotchingOffset6;
    double P9207_NotchingOffset7;
    double P9208_NotchingOffset8;
    double P9209_NotchingOffset9;
    double P9210_NotchingOffset10;
    double P9211_NotchingOffset11;
    double P9212_NotchingOffset12;
    double P9213_NotchingOffset13;
    double P9214_NotchingOffset14;
    double P9215_NotchingOffset15;
    double P9216_NotchingOffset16;
    double P9217_NotchingOffset17;
    double P9218_NotchingOffset18;
    double P9219_NotchingOffset19;
    double P9220_NotchingOffset20;
    double P9221_NotchingOffset21;
    double P9222_NotchingOffset22;
    double P9223_NotchingOffset23;
    double P9224_NotchingOffset24;
    double P9225_NotchingOffset25;

    // LASER 적용값
    double P9301_NotchingRealWidth1;
    double P9302_NotchingRealWidth2;
    double P9303_NotchingRealWidth3;
    double P9304_NotchingRealWidth4;
    double P9305_NotchingRealWidth5;
    double P9306_NotchingRealWidth6;
    double P9307_NotchingRealWidth7;
    double P9308_NotchingRealWidth8;
    double P9309_NotchingRealWidth9;
    double P9310_NotchingRealWidth10;
    double P9311_NotchingRealWidth11;
    double P9312_NotchingRealWidth12;
    double P9313_NotchingRealWidth13;
    double P9314_NotchingRealWidth14;
    double P9315_NotchingRealWidth15;
    double P9316_NotchingRealWidth16;
    double P9317_NotchingRealWidth17;
    double P9318_NotchingRealWidth18;
    double P9319_NotchingRealWidth19;
    double P9320_NotchingRealWidth20;
    double P9321_NotchingRealWidth21;
    double P9322_NotchingRealWidth22;
    double P9323_NotchingRealWidth23;
    double P9324_NotchingRealWidth24;
    double P9325_NotchingRealWidth25;

	BYTE byETX;


	void clear()
	{
		bySTX = 0x02;
		P9011_TOTAL_WIDTH = 0.00;
		P9012_TAB_COUNT = 0.00;
		P9013_TOTAL_HEIGHT = 0.00;
		P9021_CUTTING_WIDTH = 0.00;
		P9022_CUTTING_HEIGHT = 0.00;
		P9023_CUTTING_HEIGHT_OFFSET = 0.00;
		P9031_ARC_IN_X = 0.00;
		P9032_ARC_IN_Y = 0.00;
		P9033_ARC_OUT_X = 0.00;
		P9034_ARC_OUT_Y = 0.00;
		P9035_ARC_DEG = 0.00;
		P9051_CUTTING_SPEED = 0.00;
		P9052_CUTTING_EXT_SPEED = 0.00;
		P9053_CUTTING_LINE_SPEED = 0.00;
		P9054_NOTCHING_LINE_SPEED = 0.00;
		P9055_JUMP_SPEED = 0.00;
		P9056_CUTTING_LASER_POWER = 0.00;
		P9057_NOTCHING_LASER_POWER = 0.00;
		P9058_CUTTING_LASER_FREQ = 0.00;
		P9059_NOTCHING_LASER_FREQ = 0.00;
		P9060_LASER_ARC_OFFSET = 0.00;
		P9061_NG_SENSOR_LENGTH = 0.00;
		P9062_ARC_MARK_SPEED = 0.00;
		P9063_LASER_ON_DELAY = 0.00;
		P9064_LASER_OFF_DELAY = 0.00;
		P9065_END_SCALE = 0.00;
		P9066_ARC_SCALE = 0.00;
		P9067_CORNER_SCALE = 0.00;
		P9068_FLAG_LINE_EXT = 0.00;
		P9069_TAB_OFFSET = 0.00;
		P9070_LINE_END_OFFSET = 0.00;
		P9071_FIRST_CUTTING_EXT = 0.00;
		P9072_LASER_PULSE_WIDTH = 0.00;
		P9073_FIRST_NOTCH_OFFSET = 0.00;
		P9074_SENSOR_OFFSET = 0.00;

		byETX = 0x03;

		for (int i = 1; i <= 25; ++i)
		{
			((&P9101_NotchingWidth1)[i - 1]) = 0.00;
			((&P9201_NotchingOffset1)[i - 1]) = 0.00;
			((&P9301_NotchingRealWidth1)[i - 1]) = 0.00;
		}
	}

} _stPLC_PouchData;
#pragma pack(pop)
class CDlgMES : public CUserDialogEx
{
	DECLARE_DYNAMIC(CDlgMES)

public:
	CDlgMES* pDlgMES;

	CString SerializePLCData(const _stPLC_PouchData& data);
	void RecipeViewInIt();

	BYTE m_sendData[30000];

	BOOL m_bConnectCheck;
	BOOL m_bConnectCheck_Pouch;

	CString FormatDustData(double value);
	CString LoadXMLFile(CString filePath);

	CDlgWaitForMES* m_pDlgWFM;
	CFileMgr FileMgr;
	CString m_strEQCode;
	CString m_strTmpTitle;
	CString m_ChangeRecipeName;

	BOOL m_bLoginCheck;


	// 집진기 통신 PV값 송신을 위한 멤버변수
	double m_dDustCollectorInverter;	// 인버터
	double m_dDustCollectorTemp;		// 온도
	double m_dDustCollector;			// 풍속
	double m_dDustCollectorSlack;		// 소석회
	double m_dDustCollectorAttach;		// 차압
	int m_nRecipeSendCount; //레시피 메세지 전송 카운트

	BOOL m_bRecipeCheck;

	BOOL m_bRecipeInserting;

	BOOL m_bLoginReplyCheck;

	BOOL m_bRecipeChangeOK;

	BOOL m_QMSReceiveCheck;

	BOOL m_RecipeNameChange;

	LinkTestMessage m_LinkTestMessage;

	CString m_strQMSXmlData;

	void SendNowRecipe();
	CFpspread8		m_SpreadRecipeView;
	CFpspread8		m_FileNameView;
	CFpspread8	m_CurrentParameterValue;
	CString m_strTmpChangeRecipe;

	CString strTmpChangeRecipe;
	CCommunicate *m_pSockComm;
	CCommunicate *m_pSockComm_PLC;
	void ShowLoginDialog();
	void SendQMSInterval();
	bool bLoginIsIt;
	BOOL strServerToggle;

	CString strEQTitle;
	bool infoLoginChk;
	void SocketDataSend(BYTE* sendData, int totalLength);
	

	CDlgMES(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgMES();
	CString getCodeNameMES(int code);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_MES };

	void SetParamData(SingleScannerParameter HEAD2, SingleScannerParameter HEAD1);
	SingleScannerParameter GetHEAD2Param();
	SingleScannerParameter GetHEAD1Param();

protected:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	SingleScannerParameter m_HEAD2Parameter;
	SingleScannerParameter m_HEAD1Parameter;
	// IniUtil _iniUtil;

	SingleScannerParameter m_HEAD1ScannerParameter;
	FieldParameter M_FIELD_FARAMETER;
	_POCKET_TMP_DATA_ m_stPocketData;

private:
	BOOL m_bVisible;
	static int tmpN;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	// afx_msg LRESULT OnSockReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceive_Sock(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnReceive(WPARAM wParam,LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
public:
	CString DumpPLCData(const _stPLC_PouchData& data);
	BOOL ParseKeyValue(const std::string& token, std::string& key, std::string& valueStr, double& value);
	BOOL GetPLCValue(const _stPLC_PouchData& stPLCData, const std::string& key, double& outValue);
	BOOL SetPLCValue(_stPLC_PouchData& stPLCData, const std::string& key, double value);
	void HandleReceive(WPARAM wParam, LPARAM lParam);
	BOOL SetParameterValueByKey(const std::string& key, double value);
	void SendParameter();
	void SendOK();
	void ReplaceContentInTag(CString& xmlData, const CString& tagName, const CString& newContent);
	afx_msg void OnBnClickedOk2();
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushResipeView();
	
	void ClickCtpushResipeView(int row, BOOL* handled);
	virtual BOOL OnInitDialog(); 
	void ClickCtpushResipeSave();
	afx_msg void OnBnClickedOk();
	void ClickCtpushResipeUpdate();
	void ProcessCollectedData(const char* xmlContent, const char* folderPath);
	void UpdateTitle(const CString& strEQTitle);


	void OnClickCtpushResipeDelete();
	
    void ShowInfoDialog();
	CString ReplaceAll(CString source, const CString& from, const CString& to);

	bool WaitForServerResponse(int timeout);
    void HandleServerResponse();

	// 로그인 시 세션값 인증
	void bLoginCheck();

	void LanConnectCheck(int nSysByte, CString fileName);
	void DblClickFpspreadRecipeParaList(long Col, long Row);
	void ClickCtpushResipeSelect();
	void ClickCtpushClose();

	void MsgIDCheck(CString csTitle);
	void SetDelayTime(unsigned int iSecond);
	
	// afx_msg void OnBnClickedLogin();
	// afx_msg void OnBnClickedRecipeDownload();
	
	afx_msg void OnBnClickedLogin();

	void CreateLinkTestMessage();
	

	CString m_strLinkTestMessage;

	BOOL bRecipeSucc;

	CString m_strID;
	CString m_strPW;

	CctList m_LogList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton14();
};