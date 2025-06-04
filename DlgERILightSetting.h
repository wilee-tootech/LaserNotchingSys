#pragma once
#include "NX_COMM\CommDefine.h"
#include <NX_LIGHT/LightMgr.h>
#include "PointerContainer.h"
#include "BtnST.h"
#include <string>

// CDlgERILightSetting ��ȭ �����Դϴ�.

#define TIMER_CHECK_IS_RECIVE_MESSAGE_CHANGED 123


class CDlgERILightSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgERILightSetting)

public:
	CDlgERILightSetting(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgERILightSetting();

	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;


// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_ERI_LIGHT_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	
	DECLARE_MESSAGE_MAP()

	

//	CLightMgr* m_gLightMgr;



private:
	std::string checkstring;
	std::string sumString;

	int m_nLightIntensity; //Percentage�� �����Դϴ�.
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

