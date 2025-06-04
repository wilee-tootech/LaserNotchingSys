// OptionTable.h: interface for the COptionTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONTABLE_H__0141E07C_F79B_46BE_8D0F_55E0384A596C__INCLUDED_)
#define AFX_OPTIONTABLE_H__0141E07C_F79B_46BE_8D0F_55E0384A596C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define OPT   COptionTable::Instance()

class COptionTable  
{
public:
	enum OptionID
	{
		ID_FONT_FILE_SAVE = 900,
		ID_MASTER_X_OFFSET = 901,
		ID_MASTER_Y_OFFSET = 902,
		ID_SLAVE_X_OFFSET = 903,
		ID_SLAVE_Y_OFFSET = 904,
		ID_UNIT = 905,
		ID_MAX_FIELD = 906,
		ID_MAX_MM =907,
		ID_SET_POWER = 908,
	};
public:
	COptionTable();
	virtual ~COptionTable();
	static COptionTable &Instance();
	char *Serialize(DWORD &dwLength);
	void Unserialize(char *pstrSerial);
	
public:
	void SetFontFileSave(BOOL bFlag);
	BOOL GetFontFileSave();

private:
	BOOL m_bFontFileSave;
	double m_dBaseMasterX;
	double m_dBaseMasterY;
	double m_dBaseSlaveX;
	double m_dBaseSlaveY;
	double m_dMMSize;
	double m_dFieldSize;
	double m_dSetedPower;
	double m_dMeasuredPower;
		
	
};

#endif // !defined(AFX_OPTIONTABLE_H__0141E07C_F79B_46BE_8D0F_55E0384A596C__INCLUDED_)
