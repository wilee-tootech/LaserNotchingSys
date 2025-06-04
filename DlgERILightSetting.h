#pragma once
#include "NX_COMM\CommDefine.h"
#include <NX_LIGHT/LightMgr.h>
#include "PointerContainer.h"
#include "BtnST.h"
#include <string>

// CDlgERILightSetting 대화 상자입니다.

#define TIMER_CHECK_IS_RECIVE_MESSAGE_CHANGED 123


class CDlgERILightSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgERILightSetting)

public:
	CDlgERILightSetting(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgERILightSetting();

	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;


// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_ERI_LIGHT_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()

	

//	CLightMgr* m_gLightMgr;



private:
	std::string checkstring;
	std::string sumString;

	int m_nLightIntensity; //Percentage가 단위입니다.
public:

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedLight0Apply();
	afx_msg void OnBnClickedLight1Apply();
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushLoadLightinfo();
	void ClickCtpushSaveLightinfo();
	void ClickCtpushGetdataTest();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	void ClickCttextLightIntensity();
	void SetDlgLightCttextBackcolor(int redIntensity);
	bool ParseReciveData(std::string str);
	afx_msg void OnBnClickedCancel();
	void ClickCtpushLoadLightiOn();
	void ClickCtpushLoadLightiOff();
	void SetDelayTime(unsigned int iSecond);
};

