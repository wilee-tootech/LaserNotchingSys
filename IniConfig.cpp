// IniConfig.cpp: implementation of the CIniConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CONFIG_FILENAME "mk.ini"
#define CONFIG_BUF		1024

CIniConfig::CIniConfig()
{
	//  - �ٸ� ��η� ������ �ɶ��� �ֱ�. ���� ��η� �Է������״�!
	TCHAR tcPath[4096];

	// ���� ��θ� ��´�
	GetModuleFileName(NULL, tcPath, 4096);

	// ������ ���ϸ��� �����ϰ� �ҷ��� ���ϸ��� ���δ�
	*strrchr(tcPath, '\\') = '\0';
	strcat(tcPath, "\\");
  	strcat(tcPath, (LPCTSTR)CONFIG_FILENAME);
	
	path = tcPath;
	//AfxMessageBox(path);
}

CIniConfig::CIniConfig(CString cwdPath)
{
	path = cwdPath;
}

CIniConfig::~CIniConfig()
{

}

CString CIniConfig::GetConfigString(CString root, CString sub, CString def)
{
	TCHAR buf[CONFIG_BUF];
	GetPrivateProfileString(root, sub, def, buf, sizeof(buf), path);	

	return (CString)buf;
}

float CIniConfig::GetConfigFloat(CString root, CString sub, float def)
{
	TCHAR buf[CONFIG_BUF];
	CString str;

	str.Format("%f", def);
	GetPrivateProfileString(root, sub, str, buf, sizeof(buf), path);	

	return atof((CString)buf);
}

int CIniConfig::GetConfigInt(CString root, CString sub, int def)
{
	return GetPrivateProfileInt(root, sub, def, path);
}

void CIniConfig::SetConfigString(CString root, CString sub, CString result)
{
	WritePrivateProfileString(root, sub, result, path);
}

void CIniConfig::SetConfigFloat(CString root, CString sub, float result)
{
	CString str;

	str.Format("%f", result);
	WritePrivateProfileString(root, sub, str, path);
}

void CIniConfig::SetConfigInt(CString root, CString sub, int result)
{
	CString str;

	str.Format("%d", result);
	WritePrivateProfileString(root, sub, str, path);
}

void CIniConfig::SetDeviceString(CString name, CString path)
{
	//WritePrivateProfileString(CONFIG_PACKAGE, CONFIG_DEVICE_NAME, name, path);

	FILE *fp;

	fp = fopen(path, "wt");
	if (fp == NULL) return;

	// 2007.06.02   - Device Change �޼����� �� �Ʒ��� ���ƾ� �Ѵ�. ����, ���� ����
	fprintf(fp, "[DEVICE]\nNAME = %s\n", name);

	fclose(fp);


	fp = fopen("c:\\package.ini", "wt");
	if (fp == NULL) return;

	// 2007.06.02   - Device Change �޼����� �� �Ʒ��� ���ƾ� �Ѵ�. ����, ���� ����
	fprintf(fp, "[DEVICE]\nNAME = %s\n", name);

	fclose(fp);

}

int CIniConfig::GetConfigSection(CString section)
{
	TCHAR tmp[5000] = {0,};
	int ret = GetPrivateProfileSection(section, tmp, 5000, path);
	return ret;
}
