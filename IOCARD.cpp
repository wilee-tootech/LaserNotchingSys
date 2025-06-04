// IOCARD.cpp: implementation of the CIOCARD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "mk.h"
#include "IOCARD.h"
#include "Pisodio.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define NOIOCARD

CIOCARD::CIOCARD()
{
#ifndef NOIOCARD
	CString tempstr,str;
   wInitialCode=PISODIO_DriverInit();
       if( wInitialCode!=PISODIO_NoError )
      {
          AfxMessageBox("No PIO or PISO card in this system !!!",/*"PIO Card Error",*/MB_OK);
       }
	 
       if( wTotalBoard==0 )
       {
            Beep(100,100);
            AfxMessageBox("No PIO or PISO card in this system !!!",/*"PIO Card Error",*/MB_OK);
         //   PostQuitMessage(0);
       }
	   
	     PISODIO_SearchCard(&wTotalBoard,PISO_P32C32);
		wRetVal=PISODIO_GetConfigAddressSpace(0, &wGetAddrBase, &wGetIrqNo,
                        &wGetSubVendor,&wGetSubDevice,&wGetSubAux,&wGetSlotBus,&wGetSlotDevice);

		 if( wRetVal!=PISODIO_NoError )
        {
			// sprintf(str,"%04x",wGetAddrBase);
			 tempstr = str;
		//	 sprintf(str,"%x",wGetIrqNo);
			 tempstr += str;
        AfxMessageBox("No PIO or PISO card in this system !!!",/*"PIO Card Error",*/MB_OK);
		return;
 
        }

	     wRetVal=PISODIO_GetConfigAddressSpace(wTotalBoard, &wGetAddrBase, &wGetIrqNo,
                        &wGetSubVendor,&wGetSubDevice,&wGetSubAux,&wGetSlotBus,&wGetSlotDevice);
         //pWnd->RedrawWindow();
	  PISODIO_OutputByte(wGetAddrBase,1); 
#endif
}

CIOCARD::~CIOCARD()
{
#ifndef NOIOCARD
PISODIO_DriverClose();     
#endif
}

CIOCARD* CIOCARD::m_pIOCARD = 0;
CIOCARD* CIOCARD::GetInstance() 
{
	if (m_pIOCARD == 0) {
		m_pIOCARD = new CIOCARD;
	}
	return m_pIOCARD;
}

int CIOCARD::InitCard()
{
	#ifndef NOIOCARD
	CString tempstr,str;
	wInitialCode=PISODIO_DriverInit();
   if( wInitialCode!=PISODIO_NoError )
       {
        AfxMessageBox("No PIO or PISO card in this system !!!",/*"PIO Card Error",*/MB_OK);
		return wInitialCode;		
       }
	  
       if( wTotalBoard==0 )
       {
            Beep(100,100);
            AfxMessageBox("No PIO or PISO card in this system !!!",/*"PIO Card Error",*/MB_OK);
			return wInitialCode;
			//   PostQuitMessage(0);
       }
	    PISODIO_SearchCard(&wTotalBoard,PISO_P32C32);
		wRetVal=PISODIO_GetConfigAddressSpace(0, &wGetAddrBase, &wGetIrqNo,
                       &wGetSubVendor,&wGetSubDevice,&wGetSubAux,&wGetSlotBus,&wGetSlotDevice);
		 if( wRetVal!=PISODIO_NoError )
         {
     //			 sprintf(str,"%04x",wGetAddrBase);
			 tempstr = str;
       //			 sprintf(str,"%x",wGetIrqNo);
			 tempstr += str;
			 AfxMessageBox("No PIO or PISO card in this system !!!",/*"PIO Card Error",*/MB_OK);
         }
	     wRetVal=PISODIO_GetConfigAddressSpace(wTotalBoard, &wGetAddrBase, &wGetIrqNo,
                        &wGetSubVendor,&wGetSubDevice,&wGetSubAux,&wGetSlotBus,&wGetSlotDevice);
     //pWnd->RedrawWindow();
	  PISODIO_OutputByte(wGetAddrBase,1); 
	  PISODIO_OutputByte(wGetAddrBase+0xc0,0x00);
	  PISODIO_OutputByte(wGetAddrBase+0xc4,0x00);
	  PISODIO_OutputByte(wGetAddrBase+0xc8,0x00);
	  PISODIO_OutputByte(wGetAddrBase+0xcc,0x00);
//

	  #endif
	  return 0;
}

int CIOCARD::SendDataToIOCard0_7(WORD Setdata)
{
	#ifndef NOIOCARD
if( wInitialCode==PISODIO_NoError )
      {
        PISODIO_OutputByte(wGetAddrBase+0xc0,(BYTE)Setdata);
		  return 1;
	}
 else 
	 #endif
return 0;
}
int CIOCARD::SendDataToIOCard8_15(WORD Setdata)
{
	#ifndef NOIOCARD
	if( wInitialCode==PISODIO_NoError )
      {
       PISODIO_OutputByte(wGetAddrBase+0xc4,(BYTE)Setdata);
	  return 1;
	}
   else 
	   #endif
return 0;
}
int CIOCARD::SendDataToIOCard16_23(WORD Setdata)
{
#ifndef NOIOCARD
	if( wInitialCode==PISODIO_NoError )
      {
       PISODIO_OutputByte(wGetAddrBase+0xc8,(BYTE)Setdata);
		  return 1;
	}
    else 
		#endif
return 0;
}
int CIOCARD::SendDataToIOCard24_31(WORD Setdata)
{
	#ifndef NOIOCARD
	if( wInitialCode==PISODIO_NoError )
      {
       PISODIO_OutputByte(wGetAddrBase+0xcc,(BYTE)Setdata);
			  return 1;
	}
  else

	  #endif
		 return 0;
}
WORD CIOCARD::GetDataToIOCard0_7(DWORD  AddrBase)// AddrBase)
{
	#ifndef NOIOCARD
	if( wInitialCode==PISODIO_NoError )
{

		AAA=(BYTE)PISODIO_InputByte(wGetAddrBase+0xc0);
         return AAA;
		
			
 //      return AAA = (BYTE)PISODIO_InputByte(wGetAddrBase+0xc0);
	   }else
	#endif
   return 0;
}
WORD CIOCARD::GetDataToIOCard8_15(DWORD  AddrBase)
{
		#ifndef NOIOCARD
	if( wInitialCode==PISODIO_NoError )
{

		BBB=(BYTE)PISODIO_InputByte(wGetAddrBase+0xc4);
         return 1;
		
			
 //      return AAA = (BYTE)PISODIO_InputByte(wGetAddrBase+0xc0);
	   }else
	#endif
   return 0;
/*	#ifndef NOIOCARD
	if( wInitialCode==PISODIO_NoError )
	{
      return (BYTE)~PISODIO_InputByte(wGetAddrBase+0xc4);
	  
}
	#endif
     return 0;*/
}
WORD CIOCARD::GetDataToIOCard16_23(DWORD  AddrBase)
{
	#ifndef NOIOCARD
	if( wInitialCode==PISODIO_NoError )
{
      //return (BYTE)~PISODIO_InputByte(wGetAddrBase+0xc8);
		return (BYTE)PISODIO_InputByte(wGetAddrBase+0xc8);
	  
}
	#endif
     return 0;
}
WORD CIOCARD::GetDataToIOCard24_31(DWORD  AddrBase)
{
	#ifndef NOIOCARD
	if( wInitialCode==PISODIO_NoError )
	{
        return (BYTE)~PISODIO_InputByte(wGetAddrBase+0xcc);
		
	}
	#endif
     return 0;
}