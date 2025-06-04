#pragma once
#include "Communicate.h"
#include "RS232.h"
#include "TabPageSSL.h"
#include "PYH_Comm.h"
#include "DlgMES.h"
#include "../DIALOGEX/UserDialogEx.h"
// CDustCollector 대화 상자입니다.

class CDustCollector : public CUserDialogEx
{
	DECLARE_DYNAMIC(CDustCollector)

public:
	CPYH_Comm* m_Comm;
	CDustCollector(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDustCollector();
	CRS232 *m_pSockComm;
	LRESULT ReceiveData(WPARAM wParam, LPARAM lParam);
	void SendData(LPCTSTR buf, int size);
	//static CDustCollector* GetInstance();
	void StrParsing(CString adress, CString str);
	void OpenPort();
	BOOL m_bToggleBtn;
	CDlgMES* m_pDlgMES;


	BYTE m_buf[100];
	char m_data[1024];

	BYTE m_ReadData[4];
	BYTE m_Converter[2];
	
	static int nCountLaserMonitoring; // 200ms마다 호출되는 카운터
    static double dHead1Total;        // HEAD1 파워 총합
    static double dHead2Total;		  // HEAD2 파워 총합
	 
// 대화 상자 데이터입니다.
	enum { IDD = IDD_TAP_DUSTTRAP };

private:
	//static CDustCollector* m_pDustColl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void OnTimer(UINT_PTR nIDEvent);
	unsigned short CRC16(char *data, int dataSize);
	void intToByteArray16(int intData, BYTE* byteArr);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonToggle();
	void SetDelayTime(unsigned int iSecond);
	float byteArrayToFloat32(const BYTE* byteArr);
	void floatToByteArray32(float floatData, BYTE* byteArr);
	int convertBufferToInt(char* buffer);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
