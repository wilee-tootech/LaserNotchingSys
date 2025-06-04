#pragma once

#include "afxwin.h"
#include "TabPageSSL.h"
#include "afxext.h"
#include "Control\fpspread8.h"
#include "ChartViewer.h"
#include <afxmt.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include "ProjectBaseView.h"
#include "MESFormView.h"
#include "Include\EXTERN\ctlist.h"

// 구조체 정의: 엔코더 위치 + I/O 상태 저장
struct RecordedData {
    int position;  // 엔코더 위치
    bool ioState;  // I/O 상태

    // 출력 편의성을 위한 연산자 오버로딩
    friend std::ostream& operator<<(std::ostream& os, const RecordedData& data) {
        //os << "{ 위치: " << data.position << ", I/O 상태: " << (data.ioState ? "ON" : "OFF") << " }";
        return os;
    }
};

// 노칭 관련 
struct RecordedFirstTabData {
    int position;  // 엔코더 위치
    bool ioState;  // I/O 상태
	 // 출력 편의성을 위한 연산자 오버로딩
    friend std::ostream& operator<<(std::ostream& os, const RecordedFirstTabData& data) {
        //os << "{ 위치: " << data.position << ", I/O 상태: " << (data.ioState ? "ON" : "OFF") << " }";
        return os;
    }
};

class CMainFormView : public CProjectBaseView
{
	DECLARE_DYNCREATE(CMainFormView)

public:
	CMainFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMainFormView();

public:
	enum { IDD = IDD_MAINFORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	

protected:
	CWinThread	  *m_pDrawThread1;
	CWinThread	  *m_pDrawThread2;
	BOOL		  m_DrawThreadAlive1;
	BOOL		  m_DrawThreadAlive2;
	static UINT DrawThreaFunc1(LPVOID pParam);
	static UINT DrawThreaFunc2(LPVOID pParam);


	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnViewPortChanged();
	afx_msg void OnViewPortChanged2();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	//virtual BOOL OnInitDialog();
	virtual void OnInitialUpdate();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonAdd();
	void LogAddData();

//	afx_msg void OnBnClickedButtonInit();
//	afx_msg void OnBnClickedButtonClear();
//	afx_msg void OnBnClickedButtonDelete();
//	afx_msg void OnBnClickedButtonReset();
	void InitEncDisplay(int nHeadNo);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void UpdateEncInfo(int nCardNo);

//	afx_msg void OnBnClickedButtonInit2();
public:
	CMESFormView *m_pMESForm;
	CctList m_LogList;
	BOOL m_bEncCheckedFlag;
	BOOL m_bEncCheckedFlag2;
	BOOL m_bEncCheckedNonFlag;
	BOOL m_bEncCheckedNonFlag2;

	CBrush m_DlgBackgroundBrush;
//	CBeamEditor6View *GetView();
	
	CFpspread8		m_SpreadEncHEAD1;
	CFpspread8		m_SpreadEncHEAD2;
	CChartViewer	m_ScannerHEAD1Vewer;
	CChartViewer	m_ScannerHEAD2Vewer;

	CChartViewer	m_NotchControlVewer1;
	CChartViewer	m_NotchControlVewer2;
	CChartViewer	m_NotchControlVewer3;
	CChartViewer	m_NotchControlVewer4;
	CChartViewer	m_NotchControlVewer5;
	CChartViewer	m_NotchControlVewer6;





	void Display(void);
	void UpdateInfo(void);
	void StopMarkThread();
	void UpdateLog(CString strData);

//---------------- 2025.03.07 I/O 엔코더 모니터링 추가 --------------------------------------------------------
	 // I/O 상태 업데이트 (외부 입력값 받아옴)
	// void updateFirstTabIoState(bool newState);
    void updateIoState(bool newState);
	//void updateFirstTabIoStateHEAD2(bool newState);
    void updateIoStateHEAD2(bool newState);
	// 기록된 위치 및 I/O 상태 출력
    void printRecordedPositions();
//--------------------------------------------------------------------------------------------------------------
private:
//---------------- 2025.03.07 I/O 엔코더 모니터링 추가 HEAD1 --------------------------------------------------------
	int  m_encoderPosition;                  // 현재 엔코더 위치
    bool m_ioState;                          // 현재 I/O 상태
    bool m_previousIoState;                  // 이전 I/O 상태
	bool m_FirstTabioState;                          // 현재 I/O 상태
    bool m_previousFirstTabIoState;                  // 이전 I/O 상태
    std::vector<RecordedData> m_recordedPositions; // 변화 감지 시 저장되는 데이터
	std::vector<RecordedFirstTabData> m_recordedFirstTabPositions; // 변화 감지 시 저장되는 데이터
	 // m_recordedPositions를 추가할 리스트 (벡터의 벡터)
    std::vector<std::vector<RecordedData>> m_listOfPositions;
	std::vector<std::vector<RecordedFirstTabData>> m_listOfFirstTabPositions;
//--------------------------------------------------------------------------------------------------------------
	//---------------- 2025.03.07 I/O 엔코더 모니터링 추가 HEAD2 --------------------------------------------------------
	int  m_encoderPositionHEAD2;                  // 현재 엔코더 위치
	bool m_ioStateHEAD2;                          // 현재 I/O 상태
	bool m_previousIoStateHEAD2;                  // 이전 I/O 상태
	bool m_FirstTabioStateHEAD2;                          // 현재 I/O 상태
	bool m_previousFirstTabIoStateHEAD2;                  // 이전 I/O 상태
	std::vector<RecordedData> m_recordedPositionsHEAD2; // 변화 감지 시 저장되는 데이터
	std::vector<RecordedFirstTabData> m_recordedFirstTabPositionsHEAD2; // 변화 감지 시 저장되는 데이터
	// // m_recordedPositions를 추가할 리스트 (벡터의 벡터)
	std::vector<std::vector<RecordedData>> m_listOfPositionsHEAD2;
	std::vector<std::vector<RecordedFirstTabData>> m_listOfFirstTabPositionsHEAD2;
//--------------------------------------------------------------------------------------------------------------
	CString m_strHEAD1Name;

	CBitmap m_background;

	double m_minX;		// The minimum overall x scale
	double m_maxX;		// The maximum overall x scale
	double m_minY;		// The minimum overall y scale
	double m_maxY;		// The maximum overall y scale

	double m_dEncLaserOnPos;

	std::vector<CRect> m_originalRects; // 컨트롤 원래 위치 저장
	CRect m_originalDlgRect; 

	float m_fScaleX; 
	float m_fScaleY;


	void DrawScannerHead1(CChartViewer *viewer);
	void DrawScannerHead2(CChartViewer *viewer);

	void DrawControlViewer1(CChartViewer *viewer);
	void DrawControlViewer2(CChartViewer *viewer);
	void DrawControlViewer3(CChartViewer *viewer);
	void DrawControlViewer4(CChartViewer *viewer);
	void DrawControlViewer5(CChartViewer *viewer);
	void DrawControlViewer6(CChartViewer *viewer);

	void CalculateScaleFactor();
	void ResizeControls();
	int GetControlCount();

	

public:
	
	afx_msg void OnStnClickedMarkImage();
	afx_msg void OnStnClickedScannerViewer2();
	afx_msg void OnStnClickedMarkImage2();
	afx_msg void OnStnClickedScannerViewer1();
	afx_msg void OnBnClickedButtonAdd4();
//	afx_msg void OnBnClickedButtonInit4();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStnClickedScannerViewer3();
	afx_msg void OnStnClickedScannerViewer4();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg void OnStnClickedControlViewer1();

	
//	afx_msg void OnBnClickedButtonIoTest();
//	afx_msg void OnEnChangeSetedEncPos();
	void RefreshIOViewer(void);
	void RefreshIOViewerHEAD2(void);
	afx_msg void OnBnClickedButtonInit();
	DECLARE_EVENTSINK_MAP()
//	void ClickCthead1Xoffset();
//	void ClickCthead1Yoffset();
//	void ClickCthead2Xoffset();
//	void ClickCthead2Yoffset();
};


