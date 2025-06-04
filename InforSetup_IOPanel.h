#ifndef _INFOR_SETUP_IO_PANEL_H_
#define _INFOR_SETUP_IO_PANEL_H_

#pragma once

#include "ProjectBaseView.h"

#include "afxcmn.h"

#include "./Include/EXTERN/fpspread8.h"

#define MAX_IO_BOARD						2
#define MAX_IO_INPUT						16
#define MAX_IO_OUTPUT						16

#define MAX_IO_CH							16


// CInforSetup_IOPanel 폼 뷰입니다.
//X00~X07
#define X_EMO									Digital->m_bfInput[0].Bit.B00	// X00      
#define X_MC_ON									Digital->m_bfInput[0].Bit.B01	// X01
#define X_AIR_PUSHER_1							Digital->m_bfInput[0].Bit.B02	// X02
#define X_AIR_PUSHER_2							Digital->m_bfInput[0].Bit.B03	// X03
#define X_04									Digital->m_bfInput[0].Bit.B04	// X04
#define X_05									Digital->m_bfInput[0].Bit.B05	// X05
#define X_06									Digital->m_bfInput[0].Bit.B06	// X06
#define X_07									Digital->m_bfInput[0].Bit.B07	// X07
//X08~X15
#define X_08									Digital->m_bfInput[0].Bit.B08   // X08
#define X_09									Digital->m_bfInput[0].Bit.B09   // X09
#define X_LASER_ON								Digital->m_bfInput[0].Bit.B10   // X10
#define X_11									Digital->m_bfInput[0].Bit.B11	// X11 
#define X_12									Digital->m_bfInput[0].Bit.B12	// X12 
#define X_13									Digital->m_bfInput[0].Bit.B13	// X13 
#define X_14	 								Digital->m_bfInput[0].Bit.B14	// X14 
#define X_15									Digital->m_bfInput[0].Bit.B15   // X15 

//Y00~Y07
#define Y_00									Digital->m_bfOutput[0].Bit.B00	//Y_00 
#define Y_MC_ON									Digital->m_bfOutput[0].Bit.B01	//Y_01 
#define Y_AIR_PUSHER							Digital->m_bfOutput[0].Bit.B02	//Y_02 
#define Y_03									Digital->m_bfOutput[0].Bit.B03	//Y_03 
#define Y_04									Digital->m_bfOutput[0].Bit.B04	//Y_04 
#define Y_05									Digital->m_bfOutput[0].Bit.B05	//Y_05 
#define Y_06									Digital->m_bfOutput[0].Bit.B06	//Y_06 
#define Y_07									Digital->m_bfOutput[0].Bit.B07	//Y_07 
//Y08~Y15
#define Y_08									Digital->m_bfOutput[0].Bit.B08	//Y_08 
#define Y_09									Digital->m_bfOutput[0].Bit.B09	//Y_09 
#define Y_LASER_ON								Digital->m_bfOutput[0].Bit.B10	//Y_10 
#define Y_11									Digital->m_bfOutput[0].Bit.B11	//Y_11 
#define Y_12									Digital->m_bfOutput[0].Bit.B12	//Y_12 
#define Y_13									Digital->m_bfOutput[0].Bit.B13	//Y_13 
#define Y_14									Digital->m_bfOutput[0].Bit.B14	//Y_14 
#define Y_15									Digital->m_bfOutput[0].Bit.B15	//Y_15 


typedef union DEF_IO_DATA
{
	unsigned long Data;
	struct Bit
	{
		unsigned long B00 : 1;
		unsigned long B01 : 1;
		unsigned long B02 : 1;
		unsigned long B03 : 1;
		unsigned long B04 : 1;
		unsigned long B05 : 1;
		unsigned long B06 : 1;
		unsigned long B07 : 1;
		unsigned long B08 : 1;
		unsigned long B09 : 1;
		unsigned long B10 : 1;
		unsigned long B11 : 1;
		unsigned long B12 : 1;
		unsigned long B13 : 1;
		unsigned long B14 : 1;
		unsigned long B15 : 1;

		unsigned long B16 : 1;
		unsigned long B17 : 1;
		unsigned long B18 : 1;
		unsigned long B19 : 1;
		unsigned long B20 : 1;
		unsigned long B21 : 1;
		unsigned long B22 : 1;
		unsigned long B23 : 1;
		unsigned long B24 : 1;
		unsigned long B25 : 1;
		unsigned long B26 : 1;
		unsigned long B27 : 1;
		unsigned long B28 : 1;
		unsigned long B29 : 1;
		unsigned long B30 : 1;
		unsigned long B31 : 1;
	}Bit;
}IO_DATA;

class CInforSetup_IOPanel : public CDialogEx
{
	DECLARE_DYNCREATE(CInforSetup_IOPanel)

public:
	//CInforSetup_IOPanel();           // 동적 만들기에 사용되는 protected 생성자입니다.
	CInforSetup_IOPanel(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInforSetup_IOPanel();

	IO_DATA m_bfInput[MAX_IO_BOARD];
	IO_DATA m_bfOutput[MAX_IO_BOARD];

public:
	enum { IDD = IDD_INFORSETUP_IOPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	//
	UINT m_nTimerID;
	int  m_nTimerDelay;
	CBitmap m_background;
	CFpspread8 m_spreadInput;
	CFpspread8 m_spreadOutput;

private:
	void Init_Input(void);
	void Open_Input(void);
	void Save_Input(void);

	void Init_Output(void);
	void Open_Output(void);
	void Save_Output(void);

	void Display_Input(void);
	void Display_Output(void);

public:
	void Display(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//virtual void OnInitialUpdate();
	DECLARE_EVENTSINK_MAP()
	void ClickFpspreadInput(long Col, long Row);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void ClickBtnInfoInputOpen();
	void ClickBtnInfoInputSave();
	void ClickFpspreadOutput(long Col, long Row);
	void ClickBtnInfoOutputOpen();
	void ClickBtnInfoOutputSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRadioHead1();
	afx_msg void OnBnClickedRadioHead2();
};
#endif

