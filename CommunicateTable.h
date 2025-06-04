// CommunicateTable.h: interface for the CCommunicateTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMUNICATETABLE_H__66F5C8A2_2E0A_4E4E_B210_2E177A107BB4__INCLUDED_)
#define AFX_COMMUNICATETABLE_H__66F5C8A2_2E0A_4E4E_B210_2E177A107BB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommunicateTable  
{
public:
	CCommunicateTable();
	virtual ~CCommunicateTable();

	// 초기화 파일을 Loading
	UINT LoadCommunicateFile(CString FileName, CString WorkingDirectory);
	UINT SaveCommunicateFile(CString FileName, CString WorkingDirectory);
	void SetVariable(CString Index, CString Variable);

	static CCommunicateTable *GetInstance();

private:
	static CCommunicateTable *m_pCommunicateTable; // 유일한 instance

	CString  m_strOwner; // Owner가 index의 역할을 한다.
	CString  m_strMethod;
	CString  m_strPort;
	CString  m_strBaud;
	CString  m_strData;
	CString  m_strParity;
	CString  m_strStopBit;
	CString  m_strLocalDevice;
	CString  m_strNetworkPath;
	CString m_strIPAddress;
	CString m_strPortNum;
	CString m_strSocketType;
};

#endif // !defined(AFX_COMMUNICATETABLE_H__66F5C8A2_2E0A_4E4E_B210_2E177A107BB4__INCLUDED_)
