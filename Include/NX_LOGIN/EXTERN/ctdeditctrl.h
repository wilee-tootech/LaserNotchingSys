#pragma once
#include "_Picture.h"
#include "_Font.h"

// 컴퓨터에서 Microsoft Visual C++를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// 참고: 이 파일의 내용을 수정하지 마십시오. Microsoft Visual C++에서
//  이 클래스를 다시 생성할 때 수정한 내용을 덮어씁니다.

/////////////////////////////////////////////////////////////////////////////
// CCtdeditctrl 래퍼 클래스입니다.

class CCtdeditctrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CCtdeditctrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xE86DC262, 0xFCDB, 0x480E, { 0xB3, 0x2D, 0xA8, 0x57, 0xD2, 0x7D, 0xD8, 0x62 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 특성입니다.
public:
enum
{
    BorderRegular = 0,
    BorderNone = 1,
    BorderRaised = 2,
    BorderLowered = 3
}enumBorder;
enum
{
    Format_MMDDYY = 0,
    Format_DDMMYY = 1,
    Format_YYMMDD = 2,
    Format_HHMMSS = 3
}enumTimeFormat;
enum
{
    ArrowSmall = 0,
    ArrowLarge = 1,
    ArrowLine1 = 2,
    ArrowLine2 = 3
}enumArrowType;
enum
{
    MonthNumeric = 0,
    MonthLong = 1,
    MonthShort = 2
}enumMonthFormat;
enum
{
    AlignLeft = 0,
    AlignRight = 1,
    AlignCenter = 2
}enumAlignment;
enum
{
    DisplayRegular = 0,
    DisplayFlat = 1
}enumDisplay;
enum
{
    FillSolid = 0,
    FillHorizontal = 1,
    FillVertical = 2,
    FillDiagonal = 3,
    FillRevDiag = 4,
    FillHorzBump = 5,
    FillVertBump = 6,
    FillDiamond = 7,
    FillPyramid = 8,
    FillCircle = 9,
    FillEllipse = 10
}enumFillType;
enum
{
    ButtonRegular = 0,
    ButtonModern = 1
}enumButtonStyle;


// 작업입니다.
public:

// _DCtDEdit

// Functions
//

	void StopTimer()
	{
		InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long CurrentDate()
	{
		long result;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long CurrentTime()
	{
		long result;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	short CaretPosition()
	{
		short result;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short SelEnd()
	{
		short result;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short SelStart()
	{
		short result;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	void SetSel(short nStartChar, short nEndChar, long bNoScroll)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I4 ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nStartChar, nEndChar, bNoScroll);
	}
	long EditHwnd()
	{
		long result;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

unsigned long GetForeColor()
{
	unsigned long result;
	GetProperty(DISPID_FORECOLOR, VT_UI4, (void*)&result);
	return result;
}
void SetForeColor(unsigned long propVal)
{
	SetProperty(DISPID_FORECOLOR, VT_UI4, propVal);
}
BOOL GetEnabled()
{
	BOOL result;
	GetProperty(DISPID_ENABLED, VT_BOOL, (void*)&result);
	return result;
}
void SetEnabled(BOOL propVal)
{
	SetProperty(DISPID_ENABLED, VT_BOOL, propVal);
}
COleFont GetFont()
{
	LPDISPATCH result;
	GetProperty(DISPID_FONT, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetFont(LPDISPATCH propVal)
{
	SetProperty(DISPID_FONT, VT_DISPATCH, propVal);
}
OLE_HANDLE GethWnd()
{
	OLE_HANDLE result;
	GetProperty(DISPID_HWND, VT_I4, (void*)&result);
	return result;
}
void SethWnd(OLE_HANDLE propVal)
{
	SetProperty(DISPID_HWND, VT_I4, propVal);
}
CString GetText()
{
	CString result;
	GetProperty(DISPID_TEXT, VT_BSTR, (void*)&result);
	return result;
}
void SetText(CString propVal)
{
	SetProperty(DISPID_TEXT, VT_BSTR, propVal);
}
long Get_Value()
{
	long result;
	GetProperty(0x0, VT_I4, (void*)&result);
	return result;
}
void Set_Value(long propVal)
{
	SetProperty(0x0, VT_I4, propVal);
}
unsigned long GetBorderColor()
{
	unsigned long result;
	GetProperty(0x1, VT_UI4, (void*)&result);
	return result;
}
void SetBorderColor(unsigned long propVal)
{
	SetProperty(0x1, VT_UI4, propVal);
}
long GetBorderType()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}
void SetBorderType(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}
BOOL GetSpinButton()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}
void SetSpinButton(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}
short GetSpinWidth()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}
void SetSpinWidth(short propVal)
{
	SetProperty(0x4, VT_I2, propVal);
}
BOOL GetDropButton()
{
	BOOL result;
	GetProperty(0x5, VT_BOOL, (void*)&result);
	return result;
}
void SetDropButton(BOOL propVal)
{
	SetProperty(0x5, VT_BOOL, propVal);
}
short GetDropWidth()
{
	short result;
	GetProperty(0x6, VT_I2, (void*)&result);
	return result;
}
void SetDropWidth(short propVal)
{
	SetProperty(0x6, VT_I2, propVal);
}
unsigned long GetDropBackColor()
{
	unsigned long result;
	GetProperty(0x7, VT_UI4, (void*)&result);
	return result;
}
void SetDropBackColor(unsigned long propVal)
{
	SetProperty(0x7, VT_UI4, propVal);
}
unsigned long GetDropForeColor()
{
	unsigned long result;
	GetProperty(0x8, VT_UI4, (void*)&result);
	return result;
}
void SetDropForeColor(unsigned long propVal)
{
	SetProperty(0x8, VT_UI4, propVal);
}
short GetButtonBevel()
{
	short result;
	GetProperty(0x9, VT_I2, (void*)&result);
	return result;
}
void SetButtonBevel(short propVal)
{
	SetProperty(0x9, VT_I2, propVal);
}
unsigned long GetDisabledColor()
{
	unsigned long result;
	GetProperty(0xa, VT_UI4, (void*)&result);
	return result;
}
void SetDisabledColor(unsigned long propVal)
{
	SetProperty(0xa, VT_UI4, propVal);
}
short GetArrowSize()
{
	short result;
	GetProperty(0xb, VT_I2, (void*)&result);
	return result;
}
void SetArrowSize(short propVal)
{
	SetProperty(0xb, VT_I2, propVal);
}
unsigned long GetSpinBackColor()
{
	unsigned long result;
	GetProperty(0xc, VT_UI4, (void*)&result);
	return result;
}
void SetSpinBackColor(unsigned long propVal)
{
	SetProperty(0xc, VT_UI4, propVal);
}
unsigned long GetSpinForeColor()
{
	unsigned long result;
	GetProperty(0xd, VT_UI4, (void*)&result);
	return result;
}
void SetSpinForeColor(unsigned long propVal)
{
	SetProperty(0xd, VT_UI4, propVal);
}
long GetFormatType()
{
	long result;
	GetProperty(0xe, VT_I4, (void*)&result);
	return result;
}
void SetFormatType(long propVal)
{
	SetProperty(0xe, VT_I4, propVal);
}
long GetValue()
{
	long result;
	GetProperty(0xf, VT_I4, (void*)&result);
	return result;
}
void SetValue(long propVal)
{
	SetProperty(0xf, VT_I4, propVal);
}
BOOL GetLongYear()
{
	BOOL result;
	GetProperty(0x10, VT_BOOL, (void*)&result);
	return result;
}
void SetLongYear(BOOL propVal)
{
	SetProperty(0x10, VT_BOOL, propVal);
}
BOOL GetIncludeAmPm()
{
	BOOL result;
	GetProperty(0x11, VT_BOOL, (void*)&result);
	return result;
}
void SetIncludeAmPm(BOOL propVal)
{
	SetProperty(0x11, VT_BOOL, propVal);
}
short GetCrossYear()
{
	short result;
	GetProperty(0x12, VT_I2, (void*)&result);
	return result;
}
void SetCrossYear(short propVal)
{
	SetProperty(0x12, VT_I2, propVal);
}
BOOL GetEditOnError()
{
	BOOL result;
	GetProperty(0x13, VT_BOOL, (void*)&result);
	return result;
}
void SetEditOnError(BOOL propVal)
{
	SetProperty(0x13, VT_BOOL, propVal);
}
short GetInitialDelay()
{
	short result;
	GetProperty(0x14, VT_I2, (void*)&result);
	return result;
}
void SetInitialDelay(short propVal)
{
	SetProperty(0x14, VT_I2, propVal);
}
short GetRepeatRate()
{
	short result;
	GetProperty(0x15, VT_I2, (void*)&result);
	return result;
}
void SetRepeatRate(short propVal)
{
	SetProperty(0x15, VT_I2, propVal);
}
_CPicture GetDropPicture()
{
	LPDISPATCH result;
	GetProperty(0x16, VT_DISPATCH, (void*)&result);
	return _CPicture(result);
}
void SetDropPicture(LPDISPATCH propVal)
{
	SetProperty(0x16, VT_DISPATCH, propVal);
}
short GetPicXOffset()
{
	short result;
	GetProperty(0x17, VT_I2, (void*)&result);
	return result;
}
void SetPicXOffset(short propVal)
{
	SetProperty(0x17, VT_I2, propVal);
}
short GetPicYOffset()
{
	short result;
	GetProperty(0x18, VT_I2, (void*)&result);
	return result;
}
void SetPicYOffset(short propVal)
{
	SetProperty(0x18, VT_I2, propVal);
}
BOOL GetIncludeSeconds()
{
	BOOL result;
	GetProperty(0x19, VT_BOOL, (void*)&result);
	return result;
}
void SetIncludeSeconds(BOOL propVal)
{
	SetProperty(0x19, VT_BOOL, propVal);
}
BOOL GetMilitaryTime()
{
	BOOL result;
	GetProperty(0x1a, VT_BOOL, (void*)&result);
	return result;
}
void SetMilitaryTime(BOOL propVal)
{
	SetProperty(0x1a, VT_BOOL, propVal);
}
CString GetDateSepChar()
{
	CString result;
	GetProperty(0x1b, VT_BSTR, (void*)&result);
	return result;
}
void SetDateSepChar(CString propVal)
{
	SetProperty(0x1b, VT_BSTR, propVal);
}
CString GetTimeSepChar()
{
	CString result;
	GetProperty(0x1c, VT_BSTR, (void*)&result);
	return result;
}
void SetTimeSepChar(CString propVal)
{
	SetProperty(0x1c, VT_BSTR, propVal);
}
short GetMinutes()
{
	short result;
	GetProperty(0x1d, VT_I2, (void*)&result);
	return result;
}
void SetMinutes(short propVal)
{
	SetProperty(0x1d, VT_I2, propVal);
}
long GetMinValue()
{
	long result;
	GetProperty(0x1e, VT_I4, (void*)&result);
	return result;
}
void SetMinValue(long propVal)
{
	SetProperty(0x1e, VT_I4, propVal);
}
long GetMaxValue()
{
	long result;
	GetProperty(0x1f, VT_I4, (void*)&result);
	return result;
}
void SetMaxValue(long propVal)
{
	SetProperty(0x1f, VT_I4, propVal);
}
long GetDate()
{
	long result;
	GetProperty(0x20, VT_I4, (void*)&result);
	return result;
}
void SetDate(long propVal)
{
	SetProperty(0x20, VT_I4, propVal);
}
long GetTime()
{
	long result;
	GetProperty(0x21, VT_I4, (void*)&result);
	return result;
}
void SetTime(long propVal)
{
	SetProperty(0x21, VT_I4, propVal);
}
CString GetMonthNames()
{
	CString result;
	GetProperty(0x22, VT_BSTR, (void*)&result);
	return result;
}
void SetMonthNames(CString propVal)
{
	SetProperty(0x22, VT_BSTR, propVal);
}
long GetMonthFormat()
{
	long result;
	GetProperty(0x23, VT_I4, (void*)&result);
	return result;
}
void SetMonthFormat(long propVal)
{
	SetProperty(0x23, VT_I4, propVal);
}
short GetDateOffset()
{
	short result;
	GetProperty(0x24, VT_I2, (void*)&result);
	return result;
}
void SetDateOffset(short propVal)
{
	SetProperty(0x24, VT_I2, propVal);
}
BOOL GetSelectOnFocus()
{
	BOOL result;
	GetProperty(0x25, VT_BOOL, (void*)&result);
	return result;
}
void SetSelectOnFocus(BOOL propVal)
{
	SetProperty(0x25, VT_BOOL, propVal);
}
long GetAlignment()
{
	long result;
	GetProperty(0x26, VT_I4, (void*)&result);
	return result;
}
void SetAlignment(long propVal)
{
	SetProperty(0x26, VT_I4, propVal);
}
BOOL GetNegativeDates()
{
	BOOL result;
	GetProperty(0x27, VT_BOOL, (void*)&result);
	return result;
}
void SetNegativeDates(BOOL propVal)
{
	SetProperty(0x27, VT_BOOL, propVal);
}
long GetDisplayStyle()
{
	long result;
	GetProperty(0x28, VT_I4, (void*)&result);
	return result;
}
void SetDisplayStyle(long propVal)
{
	SetProperty(0x28, VT_I4, propVal);
}
BOOL GetMaskBitmap()
{
	BOOL result;
	GetProperty(0x29, VT_BOOL, (void*)&result);
	return result;
}
void SetMaskBitmap(BOOL propVal)
{
	SetProperty(0x29, VT_BOOL, propVal);
}
unsigned long GetMaskColor()
{
	unsigned long result;
	GetProperty(0x2a, VT_UI4, (void*)&result);
	return result;
}
void SetMaskColor(unsigned long propVal)
{
	SetProperty(0x2a, VT_UI4, propVal);
}
BOOL GetEmbossBitmap()
{
	BOOL result;
	GetProperty(0x2b, VT_BOOL, (void*)&result);
	return result;
}
void SetEmbossBitmap(BOOL propVal)
{
	SetProperty(0x2b, VT_BOOL, propVal);
}
long GetButtonFillType()
{
	long result;
	GetProperty(0x2c, VT_I4, (void*)&result);
	return result;
}
void SetButtonFillType(long propVal)
{
	SetProperty(0x2c, VT_I4, propVal);
}
unsigned long GetDropBackColorTo()
{
	unsigned long result;
	GetProperty(0x2d, VT_UI4, (void*)&result);
	return result;
}
void SetDropBackColorTo(unsigned long propVal)
{
	SetProperty(0x2d, VT_UI4, propVal);
}
unsigned long GetSpinBackColorTo()
{
	unsigned long result;
	GetProperty(0x2e, VT_UI4, (void*)&result);
	return result;
}
void SetSpinBackColorTo(unsigned long propVal)
{
	SetProperty(0x2e, VT_UI4, propVal);
}
long GetButtonStyle()
{
	long result;
	GetProperty(0x2f, VT_I4, (void*)&result);
	return result;
}
void SetButtonStyle(long propVal)
{
	SetProperty(0x2f, VT_I4, propVal);
}
long GetArrowType()
{
	long result;
	GetProperty(0x30, VT_I4, (void*)&result);
	return result;
}
void SetArrowType(long propVal)
{
	SetProperty(0x30, VT_I4, propVal);
}
BOOL GetReverseBorder()
{
	BOOL result;
	GetProperty(0x31, VT_BOOL, (void*)&result);
	return result;
}
void SetReverseBorder(BOOL propVal)
{
	SetProperty(0x31, VT_BOOL, propVal);
}
unsigned long GetBackColor()
{
	unsigned long result;
	GetProperty(0x32, VT_UI4, (void*)&result);
	return result;
}
void SetBackColor(unsigned long propVal)
{
	SetProperty(0x32, VT_UI4, propVal);
}


};
