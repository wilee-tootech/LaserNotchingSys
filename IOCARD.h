// IOCARD.h: interface for the CIOCARD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOCARD_H__9D76C9B7_8A14_46DE_8FAB_430473517CF7__INCLUDED_)
#define AFX_IOCARD_H__9D76C9B7_8A14_46DE_8FAB_430473517CF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIOCARD  
{
public:
	BOOL testi;
	int SendDataToIOCard0_7(WORD Setdata);
	int SendDataToIOCard8_15(WORD Setdata);
	int SendDataToIOCard16_23(WORD Setdata);
	int SendDataToIOCard24_31(WORD Setdata);
	WORD GetDataToIOCard0_7(DWORD Setdata);
	WORD GetDataToIOCard8_15(DWORD  AddrBase);
    WORD GetDataToIOCard16_23(DWORD  AddrBase);
    WORD GetDataToIOCard24_31(DWORD  AddrBase);
	int InitCard();
	CIOCARD();
	virtual ~CIOCARD();
	WORD wInitialCode,wTotalBoard;
	DWORD    wGetAddrBase;   
	WORD     wGetIrqNo;      
	WORD     wGetSubVendor,wGetSubDevice,wGetSubAux,wGetSlotBus,wGetSlotDevice;
    WORD     wIndex,wRetVal;
	WORD     wDigitalOut;
			BYTE AAA,BBB;


	static CIOCARD *GetInstance();
private:
	static CIOCARD *m_pIOCARD; // ¿Ø¿œ«— instance
};

#endif // !defined(AFX_IOCARD_H__9D76C9B7_8A14_46DE_8FAB_430473517CF7__INCLUDED_)
