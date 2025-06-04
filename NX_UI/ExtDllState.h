#pragma once
class CExtDllState
{
public:
	CExtDllState();
	~CExtDllState(void);
protected:
	HINSTANCE	m_hInsOld;
	CString		m_strDllName;
};

