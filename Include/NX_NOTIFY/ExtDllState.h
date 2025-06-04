#pragma once
class CExtDllState
{
public:
	CExtDllState();
	~CExtDllState(void);
public:
	HINSTANCE GetCurrentMouduleHandle();
protected:
	HINSTANCE m_hInsOld;
	CString   m_strDllName;
};

