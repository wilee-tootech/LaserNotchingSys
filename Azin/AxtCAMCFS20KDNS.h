#ifndef __AXT_CAMC_FS20_KDNS_H__
#define __AXT_CAMC_FS20_KDNS_H__

#include "AxtLIBDef.h"
#include "CAMCFSDef.h"

/*------------------------------------------------------------------------------------------------*
	AXTCAMCFS Library - CAMC-FS 2.0이상 Motion module => KDNS전용 PLD에 적용됨
	적용제품
		SMC-1V02 - CAMC-FS Ver2.0 이상 1축
		SMC-2V02 - CAMC-FS Ver2.0 이상 2축
 *------------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus
	//<+> 2002/12/10 gun5, 외부 limit 처리(PLD) CAMCFS 2.0에서 +,-각각의 limit를 enable/disable 할수 없어 PLD에서 처리한다.
	BOOL	PASCAL EXPORT CFS20set_ext_nelm_level(INT16 axis, INT16 level);
	UINT8	PASCAL EXPORT CFS20get_ext_nelm_level(INT16 axis);
	BOOL	PASCAL EXPORT CFS20set_ext_nelm_enable(INT16 axis, INT16 enable);
	UINT8	PASCAL EXPORT CFS20get_ext_pelm_enable(INT16 axis);
	BOOL	PASCAL EXPORT CFS20set_ext_pelm_level(INT16 axis, INT16 level);
	UINT8	PASCAL EXPORT CFS20get_ext_pelm_level(INT16 axis);
	BOOL	PASCAL EXPORT CFS20set_ext_pelm_enable(INT16 axis, INT16 enable);
	UINT8	PASCAL EXPORT CFS20get_ext_pelm_enable(INT16 axis);
	UINT8	PASCAL EXPORT CFS20get_ext_pelm_switch(INT16 axis);
	UINT8	PASCAL EXPORT CFS20get_ext_nelm_switch(INT16 axis);

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//__AXT_CAMC_FS20_KDNS_H__
