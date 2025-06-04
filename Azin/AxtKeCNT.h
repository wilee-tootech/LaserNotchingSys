#ifndef __AXT_KE_CN2CH_H__
#define __AXT_KE_CN2CH_H__

#include "AxtLIBDef.h"
#include "CNTDef.h"

/*------------------------------------------------------------------------------------------------*
	AXTCNT Library - Counter module, 1차 함수군
	적용제품
		SIO-CN2CH - SIO-CN2CH
 *------------------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus
	BOOL	PASCAL EXPORT CNTKeIsEnableChannel(INT16 channel);
	BOOL	PASCAL EXPORT CNTKeSetPortData(INT16 channel, CNTPORT_DATA pdwItem, UINT8 wValue);
	UINT8	PASCAL EXPORT CNTKeGetPortData(INT16 channel, CNTPORT_DATA pdrItem);	
	BOOL	PASCAL EXPORT CNTKeSetCommand(INT16 channel, CNTCOMMAND ccCommand);
	BOOL	PASCAL EXPORT CNTKeSetCommandData32(INT16 channel, CNTCOMMAND ccCommand, UINT32 ulData);
	BOOL	PASCAL EXPORT CNTKeSetCommandData24(INT16 channel, CNTCOMMAND ccCommand, UINT32 ulData);
	BOOL	PASCAL EXPORT CNTKeSetCommandData16(INT16 channel, CNTCOMMAND ccCommand, UINT16 ulData);
	BOOL	PASCAL EXPORT CNTKeSetCommandData08(INT16 channel, CNTCOMMAND ccCommand, UINT8 ulData);

	INT32	PASCAL EXPORT CNTKeGetCommandData32(INT16 channel, CNTCOMMAND ccCommand);
	INT32	PASCAL EXPORT CNTKeGetCommandData24(INT16 channel, CNTCOMMAND ccCommand);
	INT16	PASCAL EXPORT CNTKeGetCommandData16(INT16 channel, CNTCOMMAND ccCommand);	
	INT8	PASCAL EXPORT CNTKeGetCommandData08(INT16 channel, CNTCOMMAND ccCommand);
	
	void	PASCAL EXPORT CNTKeWriteRamDataAddr(INT16 channel, UINT32 ulAddr, UINT32 ulData);
	void	PASCAL EXPORT CNTKeWriteRamDataAddr0(INT16 channel, UINT8 ulAddr, UINT32 ulData);
	void	PASCAL EXPORT CNTKeWriteRamDataAddr1(INT16 channel, UINT8 ulAddr, UINT32 ulData);
	void	PASCAL EXPORT CNTKeWriteRamDataAddr2(INT16 channel, UINT8 ulAddr, UINT32 ulData);

	INT32	PASCAL EXPORT CNTKeReadRamDataAddr(INT16 channel, UINT32 ulAddr);
	INT32	PASCAL EXPORT CNTKeReadRamDataAddr0(INT16 channel, UINT8 ulAddr);
	INT32	PASCAL EXPORT CNTKeReadRamDataAddr1(INT16 channel, UINT8 ulAddr);
	INT32	PASCAL EXPORT CNTKeReadRamDataAddr2(INT16 channel, UINT8 ulAddr);

	BOOL	PASCAL EXPORT CNTKeSetEncInputMethod(INT16 channel, UINT8 method);
	UINT8	PASCAL EXPORT CNTKeGetEncInputMethod(INT16 channel);

	UINT8	PASCAL EXPORT CNTKeGetTriggerStatus(INT16 channel);
	BOOL	PASCAL EXPORT CNTKeReadRamDataPort(INT16 channel);
#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//__AXT_KE_CN2CH_H__
