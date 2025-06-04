// IniConfig.h: interface for the CIniConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INICONFIG_H__FF93B723_E4E5_4CC5_AEDA_341AB63B8FD8__INCLUDED_)
#define AFX_INICONFIG_H__FF93B723_E4E5_4CC5_AEDA_341AB63B8FD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniConfig  
{
public:
	int GetConfigSection(CString section);
	CIniConfig();
	CIniConfig(CString cwdPath);
	virtual ~CIniConfig();
	CString path;

	CString	GetConfigString	(CString root, CString sub, CString result);
	float	GetConfigFloat	(CString root, CString sub, float result);
	int		GetConfigInt	(CString root, CString sub, int result);
	void	SetConfigString	(CString root, CString sub, CString result);
	void	SetConfigFloat	(CString root, CString sub, float result);
	void	SetConfigInt	(CString root, CString sub, int result);
	void	SetDeviceString (CString name, CString path);
};

#endif // !defined(AFX_INICONFIG_H__FF93B723_E4E5_4CC5_AEDA_341AB63B8FD8__INCLUDED_)
