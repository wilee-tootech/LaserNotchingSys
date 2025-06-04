#ifndef __AXT_CNT_H__
#define __AXT_CNT_H__

#include "AxtLIBDef.h"
#include "CNTDef.h"

/*------------------------------------------------------------------------------------------------*
	AXTCNT Library - Digital Input/Ouput module
	적용제품
		SIO-CN2CH - 고속 카운터 2채널
 *------------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

	/// 초기화 함수군 ----------------------------------------------------------------------------*/
	// CNT모듈을 초기화한다. 열려있는 모든베이스보드에서 CNT모듈을 검색하여 초기화한다
	BOOL	PASCAL EXPORT InitializeCNT();
	// CNT모듈을 사용할 수 있도록 라이브러리가 초기화되었는가?
	BOOL	PASCAL EXPORT CNTIsInitialized();

	// 인터럽트 메세지 및 핸들러를 설정한다.
	void PASCAL EXPORT CNTSetWindowMessage(HANDLE hWnd, UINT16 wMsg, AXT_CNT_INTERRUPT_PROC proc);
	BOOL PASCAL EXPORT CNTSetInterruptEvent(INT16 nModuleNo, INT16 nEventNum, HANDLE *hEvent);

	/// 보드 및 모듈 정보 함수군 -----------------------------------------------------------------*/
	// 지정한 베이스보드가 열려있는지(오픈되었는지)를 확인한다
	BOOL	PASCAL EXPORT CNTIsOpenBoard(INT16 nBoardNo);
	// 지정한 CNT모듈이 열려있는지(오픈되었는지)를 확인한다
	BOOL	PASCAL EXPORT CNTIsOpenModule(INT16 nModuleNo);
	// 유효한 모듈번호인지를 확인한다
	BOOL	PASCAL EXPORT CNTIsValidModuleNo(INT16 nModuleNo);
	// CNT모듈이 장착된 베이스보드의 갯수를 리턴한다
	UINT16	PASCAL EXPORT CNTget_board_count();
	// CNT 모듈의 갯수를 리턴한다.
	UINT16	PASCAL EXPORT CNTget_module_count();
	// CNT 모듈의 전체 체널 갯수를 리턴한다.
	UINT16  PASCAL EXPORT CNTget_total_numof_channel();
	// 지정한 번지를 사용하는 베이스보드 번호를 리턴한다
	INT16 	PASCAL EXPORT CNTget_boardno(UINT32 address);
		/*	address : 절대번지
			리턴값
				0..베이스보드-1
				-1	= 유효하지 않는 번지			*/
	// 지정한 모듈의 모델번호를 리턴한다
	UINT16	PASCAL EXPORT CNTget_module_id(INT16 nModuleNo);
		/*	리턴값
				A8h(AXT_SIO_CN2CH)	= SIO-CN2CH
				00h	= 유효하지 않는 모듈번호		*/
	// 지정한 모듈의 베이스보드내 모듈 위치를 리턴한다.(0:SUB1, 1:SUB2, 2:SUB3, 3:SUB4)
	INT16 	PASCAL EXPORT CNTget_module_pos(INT16 nModuleNo);
	// 지정한 모듈의 유효채널 수를 리턴한다.
	UINT16	PASCAL EXPORT CNTget_channel_number(INT16 nModuleNo);
	// 지정한 베이스보드의 모듈위치에 있는 CNT모듈의 모듈번호를 리턴한다.
	UINT16	PASCAL EXPORT CNTget_module_number(INT16 nBoardNo, INT16 nModulePos);
	// 지정한 모듈번호의 베이스보드 번호와 모듈위치를 리턴한다
	BOOL	PASCAL EXPORT CNTget_module_info(INT16 nModuleNo, INT16 *pBoardNo, INT16 *nModulePos);

	/// 카운트 보드의 상태읽기 함수군 -----------------------------------------------------------*/
	// Mechanical 신호를 읽는다
	UINT16	PASCAL EXPORT CNTget_mechanical_signal(INT16 channel);
		/*	리턴값
				Bit0: Phase A Input Status
				Bit1: Phase B Input Status
				Bit2: Phase Z Input Status
				Bit4~7: UIN0~UIN3					*/
	// RAM 데이타 읽기 대기상태를 확인한다.
	BOOL	PASCAL EXPORT CNTget_read_wait_status(INT16 channel);
	// RAM 데이타 쓰기 대기상태를 확인한다.
	BOOL	PASCAL EXPORT CNTget_write_wait_status(INT16 channel);
	// 현재 카운트 값이 하한값과 상한값 범위 안에 있는 확인함
	UINT8	PASCAL EXPORT CNTchk_trigger_inbound(INT16 channel);

	/// 카운트 보드의 설정관련 함수군 -----------------------------------------------------------*/
	// Encoder입력 방식을 설정한다.
	BOOL	PASCAL EXPORT CNTset_enc_input_method(INT16 channel, UINT8 method);
	UINT8	PASCAL EXPORT CNTget_enc_input_method(INT16 channel);
		/*	리턴값
				0: Up/Down Mode
				1: 2Phase. 1채배
				2: 2Phase. 2채배
				3: 2Phase. 4채배					*/
	// Encoder 입력 반전여부를 설정한다.
	BOOL	PASCAL EXPORT CNTset_enc_reverse(INT16 channel, UINT8 reverse);
	BOOL	PASCAL EXPORT CNTget_enc_reverse(INT16 channel);
	// Encoder 입력 신호형태를 설정한다.
	BOOL	PASCAL EXPORT CNTset_enc_source_sel(INT16 channel, UINT8 phase);
	BOOL	PASCAL EXPORT CNTget_enc_source_sel(INT16 channel);
		/*	리턴값
				0: AB Phase
				1:  Z Phase							*/
	// 트리거 영역의 하한값을 설정함.
	BOOL	PASCAL EXPORT CNTset_trigger_lower(INT16 channel, double dLower);
	double	PASCAL EXPORT CNTget_trigger_lower(INT16 channel);
	// 트리거 영역의 상한값을 설정함.
	BOOL	PASCAL EXPORT CNTset_trigger_upper(INT16 channel, double dLower);
	double	PASCAL EXPORT CNTget_trigger_upper(INT16 channel);
	// 트리거 출력신호의 펄스폭을 설정함 [usec], ex) pulse_width = 10, 10usec
	BOOL	PASCAL EXPORT CNTset_trigger_pulse_width(INT16 channel, double pulse_width);
	double	PASCAL EXPORT CNTget_trigger_pulse_width(INT16 channel);
	// 트리거 출력신호의 Active Level을 설정함 (0: Active Low, 1: Active High)
	BOOL	PASCAL EXPORT CNTset_trigger_active_level(INT16 channel, UINT8 level);
	UINT8	PASCAL EXPORT CNTget_trigger_active_level(INT16 channel);
	// 펄스 카운트 값을 설정합니다.
	BOOL	PASCAL EXPORT CNTset_pulse_counter(INT16 channel, double count);
	double	PASCAL EXPORT CNTget_pulse_counter(INT16 channel);
	// 트리거를 ENABLE한다.
	BOOL	PASCAL EXPORT CNTset_trigger_enable(INT16 channel);
	BOOL	PASCAL EXPORT CNTset_trigger_disable(INT16 channel);
	// 트리거 출력 모드를 설정함.(0: ABSOLUTE POSITION EDGE, 1: PERIODIC TIME TRIGGER, 2: ABSOLUTE POSITION LEVEL)
	BOOL	PASCAL EXPORT CNTset_trigger_mode(INT16 channel, UINT8 mode);
	UINT8	PASCAL EXPORT CNTget_trigger_mode(INT16 channel);
	// 트리거 모드가 PERIODIC TIME모드일 경우 발생시킬 주파수. ( 1Hz ~ 500KHz)
	BOOL	PASCAL EXPORT CNTset_time_trigger_frequency(INT16 channel, UINT32 trig_freq);
	UINT32	PASCAL EXPORT CNTget_time_trigger_frequency(INT16 channel);

	/// 카운트 보드의 비교기 관련 함수군 -----------------------------------------------------*/
	// 펄스 카운터 비교기 값을 설정합니다.
	BOOL	PASCAL EXPORT CNTset_pulse_comparator(INT16 channel, double count);
	double	PASCAL EXPORT CNTget_pulse_comparator(INT16 channel);
	// 펄스 카운터 비교기 인터럽트 발생 조건을 설정한다.
	BOOL	PASCAL EXPORT CNTset_pulse_comparator_condition(INT16 channel, UINT8 condition);
	UINT8	PASCAL EXPORT CNTget_pulse_comparator_condition(INT16 channel);
		/*	리턴값
				0: 비교기 > 카운터 조건
				1: 비교기 = 카운터 조건
				2: 비교기 < 카운터 조건
				3: 비교기 = 카운터 조건(카운터 증가 중)
				4: 비교기 = 카운터 조건(카운터 감소 중)	
				그외 : 조건 발생하지 않음.		*/
	// 펄스 카운터 비교기 상태 읽기.
	UINT8	PASCAL EXPORT CNTget_pulse_comparator_status(INT16 channel);
		/*	리턴값
				0 bit : 비교기 > 카운터 상황
				1 bit : 비교기 = 카운터 상황
				2 bit : 비교기 < 카운터 상황
				그외 bit: 정보 없음.		*/

	/// 카운트 보드의 트리거 정보관련 함수군 -----------------------------------------------------*/
	// 메모리에 데이타를 설정할 때 Write Busy Timeout을 설정(단위[msc] 설정범위[100mSec~10000mSec])
	BOOL	PASCAL EXPORT CNTset_trigger_timeout(DWORD dwTimeout);
	DWORD	PASCAL EXPORT CNTget_trigger_timeout();

	// 메모리에(H/W RAM) 트리거정보를 읽고 쓴다.
	INT32	PASCAL EXPORT CNTread_trigger_ram_data(INT16 channel, UINT32 ulAdder);
	BOOL	PASCAL EXPORT CNTwrite_trigger_ram_data(INT16 channel, UINT32 ulAdder, UINT32 ulData);
	// 트리거 정보를 한꺼번에 설정한다.(direction : 0(카운터 증가 방향 쓰기), 1(카운터 감소 방향 쓰기))
	int		PASCAL EXPORT CNTset_trigger_absolute(INT16 channel, UINT32 trig_num, UINT32 *trig_pos, UINT8 direction);
	// 메모리의(H/W RAM) 트리거 정보를 특정 데이타로 모두 설정한다.
	BOOL	PASCAL EXPORT CNTreset_ram_data_all(INT16 nModuleNo, UINT32 data);

	/// 범용 입출력 제어함수군 -------------------------------------------------------------------*/
	// 범용 출력(Universal output)핀에 워드(4비트)값 쓰기/읽기
	BOOL	PASCAL EXPORT CNTset_output(INT16 channel, UINT8 value);
	UINT8	PASCAL EXPORT CNTget_output(INT16 channel);
	// 범용 입력(Universal input)핀에서 워드(4비트)값 읽기
	UINT8	PASCAL EXPORT CNTget_input(INT16 channel);
	// 범용 출력(Universal output)핀에서 1비트값 읽기
	BOOL	PASCAL EXPORT CNToutput_bit_on(INT16 channel, UINT8 bitNo);
	// 범용 입력(Universal input)핀에서 1비트값 읽기
	BOOL	PASCAL EXPORT CNTinput_bit_on(INT16 channel, UINT8 bitNo);
	// 범용 출력(Universal output)핀에 1비트 SET/RESET
	BOOL	PASCAL EXPORT CNTset_output_bit(INT16 channel, UINT8 bitNo);
	BOOL	PASCAL EXPORT CNTreset_output_bit(INT16 channel, UINT8 bitNo);
	// 범용 출력(Universal output)핀에 1비트값 쓰기
	BOOL	PASCAL EXPORT CNTchange_output_bit(INT16 channel, UINT8 bitNo, UINT8 state);

	/// Interrupt 관련 함수군
	// 지정한 모듈의 인터럽트를 허용한다.
	void PASCAL EXPORT CNTEnableInterrupt(INT16 nModuleNo);
	// 지정한 모듈의 인터럽트를 금지한다.
	void PASCAL EXPORT CNTDisableInterrupt(INT16 nModuleNo);
	// 모듈이 인터럽트 허용상태인지를 확인한다.
	BOOL PASCAL EXPORT CNTIsInterruptEnabled(INT16 nModuleNo);

	/// Interrupt 위치 비교기 설정 함수군
	// 펄스 카운터 비교기와 펄스 카운터 사이 설정된 조건이 일치할 때 인터럽트를 발생 사용.
	BOOL	PASCAL EXPORT CNTset_compare_interrupt(INT16 channel);
	// 펄스 카운터 비교기와 펄스 카운터 사이 설정된 조건이 일치할 때 인터럽트를 발생 사용하지 않음.
	BOOL	PASCAL EXPORT CNTreset_compare_interrupt(INT16 channel);
	// 펄스 카운터 비교기와 펄스 카운터 사이 설정된 조건이 일치할 때 인터럽트를 발생 사용 유무.
	BOOL	PASCAL EXPORT CNTis_compare_interrupt_enabled(INT16 channel);

	/// Interrupt 범용 입력 Up-edge port(Register) 함수군
	// 상승에지(Upedge) 인터럽트 ENABLE 포트로에 1비트의 데이터를 써넣는다. 지정한 모듈의 점수 단위
	BOOL	PASCAL EXPORT CNTwrite_upedge_bit(INT16 nModuleNo, UINT16 offset, BOOL bValue);
	// 상승에지(Upedge) 인터럽트 ENABLE 포트로에 1바이트의 데이터를 써넣는다. 지정한 모듈의 바이트 단위
	BOOL	PASCAL EXPORT CNTwrite_upedge_byte(INT16 nModuleNo, UINT16 offset, UINT8 byValue);
	// 상승에지(Upedge) 인터럽트 ENABLE 포트로부터 1비트의 데이터를 읽어들인다. 지정한 모듈의 점수 단위
	BOOL	PASCAL EXPORT CNTread_upedge_bit(INT16 nModuleNo, UINT16 offset);
	// 상승에지(Upedge) 인터럽트 ENABLE 포트로부터 1바이트의 데이터를 읽어들인다, 지정한 모듈의 바이트 단위
	UINT8	PASCAL EXPORT CNTread_upedge_byte(INT16 nModuleNo, UINT16 offset);

	/// Interrupt 범용입력 Down-edge port(Register) 함수군
	// 하강에지(Downedge) 인터럽트 ENABLE 포트로에 1비트의 데이터를 써넣는다. 지정한 모듈의 점수 단위
	BOOL	PASCAL EXPORT CNTwrite_downedge_bit(INT16 nModuleNo, UINT16 offset, BOOL bValue);
	// 하강에지(Downedge) 인터럽트 ENABLE  포트로에 1바이트의 데이터를 써넣는다. 지정한 모듈의 바이트 단위
	BOOL	PASCAL EXPORT CNTwrite_downedge_byte(INT16 nModuleNo, UINT16 offset, UINT8 byValue);
	// 하강에지(Downedge) 인터럽트 ENABLE  포트로부터 1비트의 데이터를 읽어들인다. 지정한 모듈의 점수 단위
	BOOL	PASCAL EXPORT CNTread_downedge_bit(INT16 nModuleNo, UINT16 offset);
	// 하강에지(Downedge) 인터럽트 ENABLE  포트로부터 1바이트의 데이터를 읽어들인다, 지정한 모듈의 바이트 단위
	UINT8	PASCAL EXPORT CNTread_downedge_byte(INT16 nModuleNo, UINT16 offset);

/*----------------------- 공통적으로 사용하는 인자(Parameter) ------------------------------------*
	nBoardNo	: 베이스보드번호, 검출된 순서대로 0부터 할당된다
	nModuleNo	: CNT모듈 번호, CNT모듈의 종류에 관계없이 검출된 순서대로 0부터 할당된다
 *------------------------------------------------------------------------------------------------*/
	// 마지막 발생한 에러코드를 반환함
	INT16  PASCAL EXPORT CNTget_error_code();
	// 입력한 에러코드에 대한 에러 메세지를 반환
	char * PASCAL EXPORT CNTget_error_msg(INT16 ErrorCode);

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//__AXT_CNT_H__
