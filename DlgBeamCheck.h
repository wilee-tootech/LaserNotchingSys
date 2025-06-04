#pragma once


// CDlgBeamCheck 대화 상자입니다.

class CDlgBeamCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBeamCheck)

public:
	CDlgBeamCheck(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgBeamCheck();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_BEAM_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrlOn();
	void ClickCtpushctrlOff();
	void SetDelayTime(unsigned int iSecond);
};
