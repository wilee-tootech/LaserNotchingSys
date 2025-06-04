#pragma once

class CDBVariantEx : public CDBVariant
{
public:
	void GetStringValue(LPSTR lpsz);
	void GetStringValue(CString& rstrValue);
};
