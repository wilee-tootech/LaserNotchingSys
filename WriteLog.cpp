// WriteLog.cpp: implementation of the CWriteLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "WriteLog.h"
#include "InitialTable.h"
#include "PointerManager.h"
#include "PointerContainer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWriteLog::CWriteLog(CString strpath)
{
	path = strpath;
	stSeconds_Buff = 0;
	stMilliseconds_Buff = 0;
}

CWriteLog::~CWriteLog()
{

}

CString CWriteLog::GetStringDate(SYSTEMTIME time)
{
	CString str;

	// GMT 시간대에 맞추어
	time.wHour += 9;
	if (time.wHour > 23)
	{
		time.wDay++;
	}
	time.wHour = time.wHour % 24;

	str.Format(_T("%4d-%2d-%2d"), time.wYear, time.wMonth, time.wDay);

	return SpaceToZero(str);
}

CString CWriteLog::GetStringTime(SYSTEMTIME time)
{
	CString str;

	// GMT 시간대에 맞추어
	time.wHour += 9;
	if (time.wHour > 23)
	{
		time.wDay++;
	}
	time.wHour = time.wHour % 24;

	str.Format(_T("%2d:%2d:%2d.%3d"), time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	return SpaceToZero(str);
}

CString CWriteLog::SpaceToZero(CString str)
{
	for (int i = 0; i < str.GetLength(); i++)
	{
		if (str.GetAt(i) == ' ')
			str.SetAt(i, '0');
	}

	return str;
}

CString CWriteLog::AsciiToHex(TCHAR tc)
{
	CString str;

	if ((BYTE)tc < 0x0F)
		str.Format(_T("0x0%1X"), (BYTE)tc);
	else
		str.Format(_T("0x%2X"), (BYTE)tc);	

	return str;
}

CString CWriteLog::AsciiToHex(CString str)
{
	CString hex = "";

	for (int i = 0; i < str.GetLength(); i++)
	{
		if (i > 0) 
			hex += ",";

		hex += AsciiToHex(str.GetAt(i));
	}

	return hex;
}

LPSTR CWriteLog::StringToLPSTR(CString str)
{
	return (LPSTR)(LPCTSTR)str;
}

void CWriteLog::WriteString(CString str)
{
	return;
	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();

	FILE *fp;
	CString filename;
	CString strTime;
	CString strDate;
	SYSTEMTIME stime;
	::GetSystemTime(&stime);

	CString SaveFile;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	//SaveFile = pInitialTable->GetSpecImgFolder();
	SaveFile = pApp->m_strCwd;  // 2021.11.22 김준혁 상대경로로 변환
	//AfxGetApp



	stime.wHour += 9;
	if (stime.wHour > 23)
	{
		stime.wDay++;
	}
	stime.wHour = stime.wHour % 24;

	
	strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
	strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);

	
	for (int i = 0; i < strDate.GetLength(); i++)
	{
		if (strDate.GetAt(i) == ' ')
			strDate.SetAt(i, '0');
	}

	for (int j = 0; j < strTime.GetLength(); j++)
	{
		if (strTime.GetAt(j) == ' ')
			strTime.SetAt(j, '0');
	}

	

	//filename = "c:\\CommLog_" + strDate + ".txt";
	filename = SaveFile + _T("\\Log\\CommLog_") + strDate + _T(".txt");

	fp = fopen((char*)(LPCTSTR)filename, (char*)(LPCTSTR)(_T("at")));
	if (fp == NULL)
	{
		return;
	}

	if (str == _T(""))
	{
		fprintf(fp, (char*)(LPCTSTR)(_T("\n")));
	}
	else
	{
		fprintf(fp, (char*)(LPCTSTR)(_T("[%s] %s\n")), (char*)(LPCTSTR)strTime, (char*)(LPCTSTR)str);
	}
	
	fclose(fp);
}

void CWriteLog::WriteStringLot(CString str)
{
	FILE *fp;
	CString filename;
	CString strTime;
	CString strDate;

	SYSTEMTIME stime;
	::GetSystemTime(&stime);

	stime.wHour += 9;
	if (stime.wHour > 23)
	{
		stime.wDay++;
	}
	stime.wHour = stime.wHour % 24;

	strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
	strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);

	for (int i = 0; i < strDate.GetLength(); i++)
	{
		if (strDate.GetAt(i) == ' ')
			strDate.SetAt(i, '0');
	}

	for (int j = 0; j < strTime.GetLength(); j++)
	{
		if (strTime.GetAt(j) == ' ')
			strTime.SetAt(j, '0');
	}

	filename = _T("c:\\CommLot_") + strDate + _T(".txt");

	fp = fopen((char*)(LPCTSTR)filename, (char*)(LPCTSTR)_T("at"));
	if (fp == NULL)
	{
		return;
	}

	if (str == _T(""))
	{
		fprintf(fp, (char*)(LPCTSTR)_T("\n"));
	}
	else
	{
		fprintf(fp, (char*)(LPCTSTR)_T("[%s] %s\n"), (char*)(LPCTSTR)strTime, (char*)(LPCTSTR)str);
	}
	
	fclose(fp);
}
// 2007.06.20  
void CWriteLog::WriteStringMark(int master, int slave, int skip, int object, CString str)
{
	FILE *fp;
	CString filename;
	CString strTime;
	CString strDate;
	CString strMaster;
	CString strSlave;
	CString strSkip;
	CString strObject;

	SYSTEMTIME stime;
	::GetSystemTime(&stime);

	stime.wHour += 9;
	if (stime.wHour > 23)
	{
		stime.wDay++;
	}
	stime.wHour = stime.wHour % 24;

	strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
	strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);

	for (int i = 0; i < strDate.GetLength(); i++)
	{
		if (strDate.GetAt(i) == ' ')
			strDate.SetAt(i, '0');
	}

	for (int j = 0; j < strTime.GetLength(); j++)
	{
		if (strTime.GetAt(j) == ' ')
 			strTime.SetAt(j, '0');
	}

	filename = _T("c:\\CommMarkLog_") + strDate + _T(".txt");

	fp = fopen((char*)(LPCTSTR)filename, (char*)(LPCTSTR)_T("at"));
	if (fp == NULL)
	{
		return;
	}

	strMaster.Format(_T(" M:%d"), master);	
	strSlave.Format(_T(" S:%d"), slave);	
	strSkip.Format(_T(" K:%d"), skip);	
	strObject.Format(_T(" O:%d"), object);	
	fprintf(fp, (char*)(LPCTSTR)_T("%s: %s,%s,%s,%s\n"), (char*)(LPCTSTR)str, (char*)(LPCTSTR)strMaster, (char*)(LPCTSTR)strSlave, (char*)(LPCTSTR)strSkip, (char*)(LPCTSTR)strObject);
	
	fclose(fp);
}

void CWriteLog::WriteTestString(CString fileName, CString str)
{
	CBeamEditor6App *pApp = (CBeamEditor6App*)AfxGetApp();
	FILE *fp;
	CString filename;
	CString strTime;
	CString strDate;
	CString SaveFile;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	SaveFile = pInitialTable->GetSpecImgFolder();

	SYSTEMTIME stime;
	::GetSystemTime(&stime);

	stime.wHour += 9;
	if (stime.wHour > 23)
	{
		stime.wDay++;
	}
	stime.wHour = stime.wHour % 24;

	strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
	strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);

	for (int i = 0; i < strDate.GetLength(); i++)
	{
		if (strDate.GetAt(i) == ' ')
			strDate.SetAt(i, '0');
	}

	for (int j = 0; j < strTime.GetLength(); j++)
	{
		if (strTime.GetAt(j) == ' ')
			strTime.SetAt(j, '0');
	}

	filename = SaveFile + _T("\\Log\\") + fileName + "_" + strDate + _T(".txt");

	fp = fopen((char*)(LPCTSTR)filename, (char*)(LPCTSTR)_T("at"));
	if (fp == NULL)
	{
		return;
	}

	if (str == "")
	{
		fprintf(fp, (char*)(LPCTSTR)_T("\n"));
	}
	else
	{
		fprintf(fp, (char*)(LPCTSTR)_T("[%s] %s\n"), (char*)(LPCTSTR)strTime, (char*)(LPCTSTR)str);
	}
	
	fclose(fp);
}


CString CWriteLog::MakeFormatString(char* strMsg, ...)
// 2021.11.01 김준혁 Log쓸때 코드 2줄이면 된다 
// 가변인자를 사용하므로 갯수에 제한이 없다.
{
	char strBuf[1024] = {0};
	va_list valist;
	va_start(valist, strMsg);
	vsprintf(strBuf,strMsg,valist);
	va_end(valist);

	return CString(strBuf);
}
