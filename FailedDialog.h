#pragma once

class CFailedDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CFailedDialog)

public:
    CFailedDialog(CWnd* pParent = nullptr);   // ǥ�� �������Դϴ�.
    virtual ~CFailedDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DLG_FAIL_LOGIN };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

    DECLARE_MESSAGE_MAP()

public:
    CString m_strMessage; // ǥ���� �޽��� ����
};
