#pragma once


// CDlgBeamCheck ��ȭ �����Դϴ�.

class CDlgBeamCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBeamCheck)

public:
	CDlgBeamCheck(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgBeamCheck();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_BEAM_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrlOn();
	void ClickCtpushctrlOff();
	void SetDelayTime(unsigned int iSecond);
};
