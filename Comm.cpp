// Comm.cpp: implementation of the CComm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Comm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComm::CComm()
{
	m_strOwner = _T(""); // Owner가 index의 역할을 한다.
	m_strMethod = _T("");
	m_strPort = _T("");
	m_strBaud = _T("");
	m_strData = _T("");
	m_strParity = _T("");
	m_strStopBit = _T("");
	m_StrLocalDevice = _T("");
	m_StrNetworkPath = _T("");
}

CComm::~CComm()
{

}

CComm::CComm(CString owner, CString method, CString port, CString baud, CString data, CString parity, CString stopBit, CWnd *wnd)
{
	m_strOwner = owner; // Owner가 index의 역할을 한다.
	m_strMethod = method;
	m_strPort = port;
	m_strBaud = baud;
	m_strData = data;
	m_strParity = parity;
	m_strStopBit = stopBit;
	m_pOwner = wnd;
}

CComm::CComm(CString owner, CString method, CString localDevice, CString networkPath, CWnd *wnd)
{
	m_strOwner = owner; // Owner가 index의 역할을 한다.
	m_strMethod = method;
	m_StrLocalDevice = localDevice;
	m_StrNetworkPath = networkPath;
	m_pOwner = wnd;
}

CComm::CComm(CString owner, CString method, CString sockType, CString ipAddress, CString portNumber, CWnd *wnd)
{
	m_strOwner = owner;	// Owner가 index의 역할을 한다.
	m_strMethod = method;
	m_strSocketType = sockType;
	m_strIPAddress = ipAddress;
	m_strPortNum = portNumber;
	m_pOwner = wnd;
}

CString CComm::GetOwner()
{
	return m_strOwner;
}

CString CComm::GetMethod()
{
	return m_strMethod;
}

CString CComm::GetPort()
{
	return m_strPort;
}

CString CComm::GetBaud()
{
	return m_strBaud;
}

CString CComm::GetData()
{
	return m_strData;
}

CString CComm::GetParity()
{
	return m_strParity;
}

CString CComm::GetStopBit()
{
	return m_strStopBit;
}

CString CComm::GetLocalDevice()
{
	return m_StrLocalDevice;
}

CString CComm::GetNetworkPath()
{
	return m_StrNetworkPath;
}

CWnd* CComm::GetOwnerPointer()
{
	return m_pOwner;
}

CString CComm::GetIPAddress()
{
	return m_strIPAddress;
}

CString CComm::GetPortNumber()
{
	return m_strPortNum;
}

CString CComm::GetSocketType()
{
	return m_strSocketType;
}
