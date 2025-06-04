// WriteLog.h: interface for the CWriteLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WRITELOG_H__C324D436_06A1_40D9_B524_7967DFE8548B__INCLUDED_)
#define AFX_WRITELOG_H__C324D436_06A1_40D9_B524_7967DFE8548B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWriteLog  
{
public:
	void WriteTestString(CString fileName, CString str);
	void WriteString(CString str);
	void WriteStringLot(CString str);
	void WriteStringMark(int master, int slave, int skip, int object, CString str);
	CWriteLog(CString strpath);
	virtual ~CWriteLog();

	CString GetStringDate(SYSTEMTIME time);
	CString GetStringTime(SYSTEMTIME time);
	CString SpaceToZero(CString str);
	CString AsciiToHex(TCHAR tc);
	CString AsciiToHex(CString str);
	LPSTR   StringToLPSTR(CString str);

	static CString MakeFormatString(char* strMsg, ...);

	CString path;
	int stSeconds_Buff;
	int stMilliseconds_Buff;
};

#endif // !defined(AFX_WRITELOG_H__C324D436_06A1_40D9_B524_7967DFE8548B__INCLUDED_)
