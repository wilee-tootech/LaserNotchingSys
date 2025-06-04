// Comm.h: interface for the CComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMM_H__730D686A_9910_4D3D_81FA_315F40FF9D20__INCLUDED_)
#define AFX_COMM_H__730D686A_9910_4D3D_81FA_315F40FF9D20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComm  
{
public:
	CString GetSocketType();
	CString GetPortNumber();
	CString GetIPAddress();
	CComm();
	virtual ~CComm();
	// RS232일 경우 호출되는 생성자
	CComm(CString owner, CString method, CString port, CString baud, CString data, CString parity, CString stopBit, CWnd *wnd);
	// Lan일 경우 호출되는 생성자
	CComm(CString owner, CString method, CString localDevice, CString networkPath, CWnd *wnd);
	// LanSocket일 경우 호출되는 생성자
	CComm(CString owner, CString method, CString sockType, CString ipAddress, CString portNumber, CWnd *wnd);
	CString GetOwner();
	CString GetMethod();
	CString GetPort();
	CString GetBaud();
	CString GetData();
	CString GetParity();
	CString GetStopBit();
	CString GetLocalDevice();
	CString GetNetworkPath();
	CWnd	*GetOwnerPointer();

private:
	CWnd	*m_pOwner;
	CString  m_strOwner; // Owner가 index의 역할을 한다.
	CString  m_strMethod;
	CString  m_strPort;
	CString  m_strBaud;
	CString  m_strData;
	CString  m_strParity;
	CString  m_strStopBit;
	CString  m_StrLocalDevice;
	CString  m_StrNetworkPath;
	CString	m_strIPAddress;
	CString m_strPortNum;
	CString m_strSocketType;
};

#endif // !defined(AFX_COMM_H__730D686A_9910_4D3D_81FA_315F40FF9D20__INCLUDED_)
