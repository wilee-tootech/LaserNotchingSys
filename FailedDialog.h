#pragma once

class CFailedDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CFailedDialog)

public:
    CFailedDialog(CWnd* pParent = nullptr);   // 표준 생성자입니다.
    virtual ~CFailedDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DLG_FAIL_LOGIN };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

    DECLARE_MESSAGE_MAP()

public:
    CString m_strMessage; // 표시할 메시지 변수
};
