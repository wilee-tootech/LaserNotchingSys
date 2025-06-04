#pragma once
#include "_Picture.h"
#include "_Font.h"

// 컴퓨터에서 Microsoft Visual C++를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// 참고: 이 파일의 내용을 수정하지 마십시오. Microsoft Visual C++에서
//  이 클래스를 다시 생성할 때 수정한 내용을 덮어씁니다.

/////////////////////////////////////////////////////////////////////////////
// CtCombobox 래퍼 클래스입니다.

class CtCombobox : public CWnd
{
protected:
	DECLARE_DYNCREATE(CtCombobox)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xA8003B66, 0xC093, 0x11D4, { 0xA8, 0x5D, 0x0, 0x80, 0xC8, 0xDF, 0xC8, 0x81 } };
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
    btRegular = 0,
    btNone = 1,
    btRaised = 2,
    btLowered = 3,
    btRaisedThin = 4,
    btLoweredThin = 5
}enumHeaderBorder;
enum
{
    ArrowSmall = 0,
    ArrowLarge = 1
}enumArrowSize;
enum
{
    StyleCombo = 0,
    StyleList = 1
}enumStyle;
enum
{
    DisplayRegular = 0,
    DisplayFlat = 1
}enumDisplay;
enum
{
    lbRegular = 0,
    lbBeveled = 1
}enumListBorder;
enum
{
    AlignLeft = 0,
    AlignRight = 1
}enumAlign;
enum
{
    AutoNone = 0,
    AutoAppend = 1,
    AutoSuggest = 2,
    AutoBoth = 3
}enumAuto;
enum
{
    ScrollRegular = 0,
    ScrollThin = 1
}enumScrollStyle;


// 작업입니다.
public:

// _DctCombo

// Functions
//

	short ListCount()
	{
		short result;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short AddItem(LPCTSTR strText)
	{
		short result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strText);
		return result;
	}
	void ClearList()
	{
		InvokeHelper(0x40, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL RemoveItem(short nIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nIndex);
		return result;
	}
	void HideList()
	{
		InvokeHelper(0x42, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL ClearColumns()
	{
		BOOL result;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	short ColumnCount()
	{
		short result;
		InvokeHelper(0x44, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short AddColumn(LPCTSTR strCaption, short nWidth)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x45, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strCaption, nWidth);
		return result;
	}
	BOOL RemoveColumn(short nIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x46, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nIndex);
		return result;
	}
	long EditHwnd()
	{
		long result;
		InvokeHelper(0x47, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	short InsertItem(LPCTSTR strText, short nIndex)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x48, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strText, nIndex);
		return result;
	}
	void SetItemImage(LPDISPATCH picImage, short nIndex)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I2 ;
		InvokeHelper(0x49, DISPATCH_METHOD, VT_EMPTY, NULL, parms, picImage, nIndex);
	}
	CString get_ListText(short nIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x4a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListText(short nIndex, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_BSTR ;
		InvokeHelper(0x4a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	CString get_ListCargo(short nIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListCargo(short nIndex, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_BSTR ;
		InvokeHelper(0x4b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	long get_ListData(short nIndex)
	{
		long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListData(short nIndex, long newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I4 ;
		InvokeHelper(0x4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	short get_ColumnWidth(short nColumn)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nColumn);
		return result;
	}
	void put_ColumnWidth(short nColumn, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x4d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nColumn, newValue);
	}
	short get_ColumnAlign(short nColumn)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nColumn);
		return result;
	}
	void put_ColumnAlign(short nColumn, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x4e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nColumn, newValue);
	}
	CString get_ColumnText(short nIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnText(short nIndex, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_BSTR ;
		InvokeHelper(0x4f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	LPDISPATCH get_ListImage(short nIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListImage(short nIndex, LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_DISPATCH ;
		InvokeHelper(0x50, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

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
long GetReadyState()
{
	long result;
	GetProperty(DISPID_READYSTATE, VT_I4, (void*)&result);
	return result;
}
void SetReadyState(long propVal)
{
	SetProperty(DISPID_READYSTATE, VT_I4, propVal);
}
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
CPicture GetPicture()
{
	LPDISPATCH result;
	GetProperty(0x1, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetPicture(LPDISPATCH propVal)
{
	SetProperty(0x1, VT_DISPATCH, propVal);
}
short GetButtonWidth()
{
	short result;
	GetProperty(0x2, VT_I2, (void*)&result);
	return result;
}
void SetButtonWidth(short propVal)
{
	SetProperty(0x2, VT_I2, propVal);
}
long GetBorderType()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}
void SetBorderType(long propVal)
{
	SetProperty(0x3, VT_I4, propVal);
}
unsigned long GetBorderColor()
{
	unsigned long result;
	GetProperty(0x4, VT_UI4, (void*)&result);
	return result;
}
void SetBorderColor(unsigned long propVal)
{
	SetProperty(0x4, VT_UI4, propVal);
}
unsigned long GetButtonBackColor()
{
	unsigned long result;
	GetProperty(0x5, VT_UI4, (void*)&result);
	return result;
}
void SetButtonBackColor(unsigned long propVal)
{
	SetProperty(0x5, VT_UI4, propVal);
}
unsigned long GetButtonForeColor()
{
	unsigned long result;
	GetProperty(0x6, VT_UI4, (void*)&result);
	return result;
}
void SetButtonForeColor(unsigned long propVal)
{
	SetProperty(0x6, VT_UI4, propVal);
}
unsigned long GetDisabledColor()
{
	unsigned long result;
	GetProperty(0x7, VT_UI4, (void*)&result);
	return result;
}
void SetDisabledColor(unsigned long propVal)
{
	SetProperty(0x7, VT_UI4, propVal);
}
long GetArrowSize()
{
	long result;
	GetProperty(0x8, VT_I4, (void*)&result);
	return result;
}
void SetArrowSize(long propVal)
{
	SetProperty(0x8, VT_I4, propVal);
}
short GetPicXOffset()
{
	short result;
	GetProperty(0x9, VT_I2, (void*)&result);
	return result;
}
void SetPicXOffset(short propVal)
{
	SetProperty(0x9, VT_I2, propVal);
}
short GetPicYOffset()
{
	short result;
	GetProperty(0xa, VT_I2, (void*)&result);
	return result;
}
void SetPicYOffset(short propVal)
{
	SetProperty(0xa, VT_I2, propVal);
}
short GetTextXOffset()
{
	short result;
	GetProperty(0xb, VT_I2, (void*)&result);
	return result;
}
void SetTextXOffset(short propVal)
{
	SetProperty(0xb, VT_I2, propVal);
}
short GetTextYOffset()
{
	short result;
	GetProperty(0xc, VT_I2, (void*)&result);
	return result;
}
void SetTextYOffset(short propVal)
{
	SetProperty(0xc, VT_I2, propVal);
}
short GetListIndex()
{
	short result;
	GetProperty(0xd, VT_I2, (void*)&result);
	return result;
}
void SetListIndex(short propVal)
{
	SetProperty(0xd, VT_I2, propVal);
}
short GetMaxListItems()
{
	short result;
	GetProperty(0xe, VT_I2, (void*)&result);
	return result;
}
void SetMaxListItems(short propVal)
{
	SetProperty(0xe, VT_I2, propVal);
}
long GetStyle()
{
	long result;
	GetProperty(0xf, VT_I4, (void*)&result);
	return result;
}
void SetStyle(long propVal)
{
	SetProperty(0xf, VT_I4, propVal);
}
BOOL GetAutoSave()
{
	BOOL result;
	GetProperty(0x10, VT_BOOL, (void*)&result);
	return result;
}
void SetAutoSave(BOOL propVal)
{
	SetProperty(0x10, VT_BOOL, propVal);
}
short GetAutoFindSize()
{
	short result;
	GetProperty(0x11, VT_I2, (void*)&result);
	return result;
}
void SetAutoFindSize(short propVal)
{
	SetProperty(0x11, VT_I2, propVal);
}
short GetMaxSaveItems()
{
	short result;
	GetProperty(0x12, VT_I2, (void*)&result);
	return result;
}
void SetMaxSaveItems(short propVal)
{
	SetProperty(0x12, VT_I2, propVal);
}
BOOL GetMaskBitmap()
{
	BOOL result;
	GetProperty(0x13, VT_BOOL, (void*)&result);
	return result;
}
void SetMaskBitmap(BOOL propVal)
{
	SetProperty(0x13, VT_BOOL, propVal);
}
unsigned long GetMaskColor()
{
	unsigned long result;
	GetProperty(0x14, VT_UI4, (void*)&result);
	return result;
}
void SetMaskColor(unsigned long propVal)
{
	SetProperty(0x14, VT_UI4, propVal);
}
BOOL GetSelectOnFocus()
{
	BOOL result;
	GetProperty(0x15, VT_BOOL, (void*)&result);
	return result;
}
void SetSelectOnFocus(BOOL propVal)
{
	SetProperty(0x15, VT_BOOL, propVal);
}
BOOL GetMatchCase()
{
	BOOL result;
	GetProperty(0x16, VT_BOOL, (void*)&result);
	return result;
}
void SetMatchCase(BOOL propVal)
{
	SetProperty(0x16, VT_BOOL, propVal);
}
BOOL GetAutoSwap()
{
	BOOL result;
	GetProperty(0x17, VT_BOOL, (void*)&result);
	return result;
}
void SetAutoSwap(BOOL propVal)
{
	SetProperty(0x17, VT_BOOL, propVal);
}
long GetDisplayStyle()
{
	long result;
	GetProperty(0x18, VT_I4, (void*)&result);
	return result;
}
void SetDisplayStyle(long propVal)
{
	SetProperty(0x18, VT_I4, propVal);
}
short GetButtonBevel()
{
	short result;
	GetProperty(0x19, VT_I2, (void*)&result);
	return result;
}
void SetButtonBevel(short propVal)
{
	SetProperty(0x19, VT_I2, propVal);
}
BOOL GetEmbossBitmap()
{
	BOOL result;
	GetProperty(0x1a, VT_BOOL, (void*)&result);
	return result;
}
void SetEmbossBitmap(BOOL propVal)
{
	SetProperty(0x1a, VT_BOOL, propVal);
}
long GetListBorder()
{
	long result;
	GetProperty(0x1b, VT_I4, (void*)&result);
	return result;
}
void SetListBorder(long propVal)
{
	SetProperty(0x1b, VT_I4, propVal);
}
unsigned long GetListBackColor()
{
	unsigned long result;
	GetProperty(0x1c, VT_UI4, (void*)&result);
	return result;
}
void SetListBackColor(unsigned long propVal)
{
	SetProperty(0x1c, VT_UI4, propVal);
}
unsigned long GetListForeColor()
{
	unsigned long result;
	GetProperty(0x1d, VT_UI4, (void*)&result);
	return result;
}
void SetListForeColor(unsigned long propVal)
{
	SetProperty(0x1d, VT_UI4, propVal);
}
CPicture GetDropPicture()
{
	LPDISPATCH result;
	GetProperty(0x1e, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetDropPicture(LPDISPATCH propVal)
{
	SetProperty(0x1e, VT_DISPATCH, propVal);
}
BOOL GetAlternateColor()
{
	BOOL result;
	GetProperty(0x1f, VT_BOOL, (void*)&result);
	return result;
}
void SetAlternateColor(BOOL propVal)
{
	SetProperty(0x1f, VT_BOOL, propVal);
}
short GetAlternateItems()
{
	short result;
	GetProperty(0x20, VT_I2, (void*)&result);
	return result;
}
void SetAlternateItems(short propVal)
{
	SetProperty(0x20, VT_I2, propVal);
}
unsigned long GetAltColorOdd()
{
	unsigned long result;
	GetProperty(0x21, VT_UI4, (void*)&result);
	return result;
}
void SetAltColorOdd(unsigned long propVal)
{
	SetProperty(0x21, VT_UI4, propVal);
}
unsigned long GetAltColorEven()
{
	unsigned long result;
	GetProperty(0x22, VT_UI4, (void*)&result);
	return result;
}
void SetAltColorEven(unsigned long propVal)
{
	SetProperty(0x22, VT_UI4, propVal);
}
BOOL GetDisplayHeader()
{
	BOOL result;
	GetProperty(0x23, VT_BOOL, (void*)&result);
	return result;
}
void SetDisplayHeader(BOOL propVal)
{
	SetProperty(0x23, VT_BOOL, propVal);
}
short GetHeaderOffset()
{
	short result;
	GetProperty(0x24, VT_I2, (void*)&result);
	return result;
}
void SetHeaderOffset(short propVal)
{
	SetProperty(0x24, VT_I2, propVal);
}
long GetHeaderBorder()
{
	long result;
	GetProperty(0x25, VT_I4, (void*)&result);
	return result;
}
void SetHeaderBorder(long propVal)
{
	SetProperty(0x25, VT_I4, propVal);
}
unsigned long GetHeaderBackColor()
{
	unsigned long result;
	GetProperty(0x26, VT_UI4, (void*)&result);
	return result;
}
void SetHeaderBackColor(unsigned long propVal)
{
	SetProperty(0x26, VT_UI4, propVal);
}
unsigned long GetHeaderForeColor()
{
	unsigned long result;
	GetProperty(0x27, VT_UI4, (void*)&result);
	return result;
}
void SetHeaderForeColor(unsigned long propVal)
{
	SetProperty(0x27, VT_UI4, propVal);
}
COleFont GetHeaderFont()
{
	LPDISPATCH result;
	GetProperty(0x28, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetHeaderFont(LPDISPATCH propVal)
{
	SetProperty(0x28, VT_DISPATCH, propVal);
}
short GetDataColumn()
{
	short result;
	GetProperty(0x29, VT_I2, (void*)&result);
	return result;
}
void SetDataColumn(short propVal)
{
	SetProperty(0x29, VT_I2, propVal);
}
long GetAutoComplete()
{
	long result;
	GetProperty(0x2a, VT_I4, (void*)&result);
	return result;
}
void SetAutoComplete(long propVal)
{
	SetProperty(0x2a, VT_I4, propVal);
}
BOOL GetSorted()
{
	BOOL result;
	GetProperty(0x2b, VT_BOOL, (void*)&result);
	return result;
}
void SetSorted(BOOL propVal)
{
	SetProperty(0x2b, VT_BOOL, propVal);
}
BOOL GetVerticalLines()
{
	BOOL result;
	GetProperty(0x2c, VT_BOOL, (void*)&result);
	return result;
}
void SetVerticalLines(BOOL propVal)
{
	SetProperty(0x2c, VT_BOOL, propVal);
}
BOOL GetHorizontalLines()
{
	BOOL result;
	GetProperty(0x2d, VT_BOOL, (void*)&result);
	return result;
}
void SetHorizontalLines(BOOL propVal)
{
	SetProperty(0x2d, VT_BOOL, propVal);
}
long GetControlPointer()
{
	long result;
	GetProperty(0x2e, VT_I4, (void*)&result);
	return result;
}
void SetControlPointer(long propVal)
{
	SetProperty(0x2e, VT_I4, propVal);
}
short GetListOffset()
{
	short result;
	GetProperty(0x2f, VT_I2, (void*)&result);
	return result;
}
void SetListOffset(short propVal)
{
	SetProperty(0x2f, VT_I2, propVal);
}
unsigned long GetVertLineColor()
{
	unsigned long result;
	GetProperty(0x30, VT_UI4, (void*)&result);
	return result;
}
void SetVertLineColor(unsigned long propVal)
{
	SetProperty(0x30, VT_UI4, propVal);
}
unsigned long GetHorzLineColor()
{
	unsigned long result;
	GetProperty(0x31, VT_UI4, (void*)&result);
	return result;
}
void SetHorzLineColor(unsigned long propVal)
{
	SetProperty(0x31, VT_UI4, propVal);
}
long GetListAlign()
{
	long result;
	GetProperty(0x32, VT_I4, (void*)&result);
	return result;
}
void SetListAlign(long propVal)
{
	SetProperty(0x32, VT_I4, propVal);
}
CString GetBreakChar()
{
	CString result;
	GetProperty(0x33, VT_BSTR, (void*)&result);
	return result;
}
void SetBreakChar(CString propVal)
{
	SetProperty(0x33, VT_BSTR, propVal);
}
BOOL GetSmallIcons()
{
	BOOL result;
	GetProperty(0x34, VT_BOOL, (void*)&result);
	return result;
}
void SetSmallIcons(BOOL propVal)
{
	SetProperty(0x34, VT_BOOL, propVal);
}
short GetImageXOffset()
{
	short result;
	GetProperty(0x35, VT_I2, (void*)&result);
	return result;
}
void SetImageXOffset(short propVal)
{
	SetProperty(0x35, VT_I2, propVal);
}
short GetImageYOffset()
{
	short result;
	GetProperty(0x36, VT_I2, (void*)&result);
	return result;
}
void SetImageYOffset(short propVal)
{
	SetProperty(0x36, VT_I2, propVal);
}
BOOL GetShowListPicture()
{
	BOOL result;
	GetProperty(0x37, VT_BOOL, (void*)&result);
	return result;
}
void SetShowListPicture(BOOL propVal)
{
	SetProperty(0x37, VT_BOOL, propVal);
}
long GetScrollStyle()
{
	long result;
	GetProperty(0x38, VT_I4, (void*)&result);
	return result;
}
void SetScrollStyle(long propVal)
{
	SetProperty(0x38, VT_I4, propVal);
}
BOOL GetSelectOnChange()
{
	BOOL result;
	GetProperty(0x39, VT_BOOL, (void*)&result);
	return result;
}
void SetSelectOnChange(BOOL propVal)
{
	SetProperty(0x39, VT_BOOL, propVal);
}
CPicture GetSelectPicture()
{
	LPDISPATCH result;
	GetProperty(0x3a, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetSelectPicture(LPDISPATCH propVal)
{
	SetProperty(0x3a, VT_DISPATCH, propVal);
}
BOOL GetScrollDrop()
{
	BOOL result;
	GetProperty(0x3b, VT_BOOL, (void*)&result);
	return result;
}
void SetScrollDrop(BOOL propVal)
{
	SetProperty(0x3b, VT_BOOL, propVal);
}
short GetScrollSpeed()
{
	short result;
	GetProperty(0x3c, VT_I2, (void*)&result);
	return result;
}
void SetScrollSpeed(short propVal)
{
	SetProperty(0x3c, VT_I2, propVal);
}
unsigned long GetBackColor()
{
	unsigned long result;
	GetProperty(0x3d, VT_UI4, (void*)&result);
	return result;
}
void SetBackColor(unsigned long propVal)
{
	SetProperty(0x3d, VT_UI4, propVal);
}


};
