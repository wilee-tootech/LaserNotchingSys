#ifndef __AXT_CNT_H__
#define __AXT_CNT_H__

#include "AxtLIBDef.h"
#include "CNTDef.h"

/*------------------------------------------------------------------------------------------------*
	AXTCNT Library - Digital Input/Ouput module
	������ǰ
		SIO-CN2CH - ��� ī���� 2ä��
 *------------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

	/// �ʱ�ȭ �Լ��� ----------------------------------------------------------------------------*/
	// CNT����� �ʱ�ȭ�Ѵ�. �����ִ� ��纣�̽����忡�� CNT����� �˻��Ͽ� �ʱ�ȭ�Ѵ�
	BOOL	PASCAL EXPORT InitializeCNT();
	// CNT����� ����� �� �ֵ��� ���̺귯���� �ʱ�ȭ�Ǿ��°�?
	BOOL	PASCAL EXPORT CNTIsInitialized();

	// ���ͷ�Ʈ �޼��� �� �ڵ鷯�� �����Ѵ�.
	void PASCAL EXPORT CNTSetWindowMessage(HANDLE hWnd, UINT16 wMsg, AXT_CNT_INTERRUPT_PROC proc);
	BOOL PASCAL EXPORT CNTSetInterruptEvent(INT16 nModuleNo, INT16 nEventNum, HANDLE *hEvent);

	/// ���� �� ��� ���� �Լ��� -----------------------------------------------------------------*/
	// ������ ���̽����尡 �����ִ���(���µǾ�����)�� Ȯ���Ѵ�
	BOOL	PASCAL EXPORT CNTIsOpenBoard(INT16 nBoardNo);
	// ������ CNT����� �����ִ���(���µǾ�����)�� Ȯ���Ѵ�
	BOOL	PASCAL EXPORT CNTIsOpenModule(INT16 nModuleNo);
	// ��ȿ�� ����ȣ������ Ȯ���Ѵ�
	BOOL	PASCAL EXPORT CNTIsValidModuleNo(INT16 nModuleNo);
	// CNT����� ������ ���̽������� ������ �����Ѵ�
	UINT16	PASCAL EXPORT CNTget_board_count();
	// CNT ����� ������ �����Ѵ�.
	UINT16	PASCAL EXPORT CNTget_module_count();
	// CNT ����� ��ü ü�� ������ �����Ѵ�.
	UINT16  PASCAL EXPORT CNTget_total_numof_channel();
	// ������ ������ ����ϴ� ���̽����� ��ȣ�� �����Ѵ�
	INT16 	PASCAL EXPORT CNTget_boardno(UINT32 address);
		/*	address : �������
			���ϰ�
				0..���̽�����-1
				-1	= ��ȿ���� �ʴ� ����			*/
	// ������ ����� �𵨹�ȣ�� �����Ѵ�
	UINT16	PASCAL EXPORT CNTget_module_id(INT16 nModuleNo);
		/*	���ϰ�
				A8h(AXT_SIO_CN2CH)	= SIO-CN2CH
				00h	= ��ȿ���� �ʴ� ����ȣ		*/
	// ������ ����� ���̽����峻 ��� ��ġ�� �����Ѵ�.(0:SUB1, 1:SUB2, 2:SUB3, 3:SUB4)
	INT16 	PASCAL EXPORT CNTget_module_pos(INT16 nModuleNo);
	// ������ ����� ��ȿä�� ���� �����Ѵ�.
	UINT16	PASCAL EXPORT CNTget_channel_number(INT16 nModuleNo);
	// ������ ���̽������� �����ġ�� �ִ� CNT����� ����ȣ�� �����Ѵ�.
	UINT16	PASCAL EXPORT CNTget_module_number(INT16 nBoardNo, INT16 nModulePos);
	// ������ ����ȣ�� ���̽����� ��ȣ�� �����ġ�� �����Ѵ�
	BOOL	PASCAL EXPORT CNTget_module_info(INT16 nModuleNo, INT16 *pBoardNo, INT16 *nModulePos);

	/// ī��Ʈ ������ �����б� �Լ��� -----------------------------------------------------------*/
	// Mechanical ��ȣ�� �д´�
	UINT16	PASCAL EXPORT CNTget_mechanical_signal(INT16 channel);
		/*	���ϰ�
				Bit0: Phase A Input Status
				Bit1: Phase B Input Status
				Bit2: Phase Z Input Status
				Bit4~7: UIN0~UIN3					*/
	// RAM ����Ÿ �б� �����¸� Ȯ���Ѵ�.
	BOOL	PASCAL EXPORT CNTget_read_wait_status(INT16 channel);
	// RAM ����Ÿ ���� �����¸� Ȯ���Ѵ�.
	BOOL	PASCAL EXPORT CNTget_write_wait_status(INT16 channel);
	// ���� ī��Ʈ ���� ���Ѱ��� ���Ѱ� ���� �ȿ� �ִ� Ȯ����
	UINT8	PASCAL EXPORT CNTchk_trigger_inbound(INT16 channel);

	/// ī��Ʈ ������ �������� �Լ��� -----------------------------------------------------------*/
	// Encoder�Է� ����� �����Ѵ�.
	BOOL	PASCAL EXPORT CNTset_enc_input_method(INT16 channel, UINT8 method);
	UINT8	PASCAL EXPORT CNTget_enc_input_method(INT16 channel);
		/*	���ϰ�
				0: Up/Down Mode
				1: 2Phase. 1ä��
				2: 2Phase. 2ä��
				3: 2Phase. 4ä��					*/
	// Encoder �Է� �������θ� �����Ѵ�.
	BOOL	PASCAL EXPORT CNTset_enc_reverse(INT16 channel, UINT8 reverse);
	BOOL	PASCAL EXPORT CNTget_enc_reverse(INT16 channel);
	// Encoder �Է� ��ȣ���¸� �����Ѵ�.
	BOOL	PASCAL EXPORT CNTset_enc_source_sel(INT16 channel, UINT8 phase);
	BOOL	PASCAL EXPORT CNTget_enc_source_sel(INT16 channel);
		/*	���ϰ�
				0: AB Phase
				1:  Z Phase							*/
	// Ʈ���� ������ ���Ѱ��� ������.
	BOOL	PASCAL EXPORT CNTset_trigger_lower(INT16 channel, double dLower);
	double	PASCAL EXPORT CNTget_trigger_lower(INT16 channel);
	// Ʈ���� ������ ���Ѱ��� ������.
	BOOL	PASCAL EXPORT CNTset_trigger_upper(INT16 channel, double dLower);
	double	PASCAL EXPORT CNTget_trigger_upper(INT16 channel);
	// Ʈ���� ��½�ȣ�� �޽����� ������ [usec], ex) pulse_width = 10, 10usec
	BOOL	PASCAL EXPORT CNTset_trigger_pulse_width(INT16 channel, double pulse_width);
	double	PASCAL EXPORT CNTget_trigger_pulse_width(INT16 channel);
	// Ʈ���� ��½�ȣ�� Active Level�� ������ (0: Active Low, 1: Active High)
	BOOL	PASCAL EXPORT CNTset_trigger_active_level(INT16 channel, UINT8 level);
	UINT8	PASCAL EXPORT CNTget_trigger_active_level(INT16 channel);
	// �޽� ī��Ʈ ���� �����մϴ�.
	BOOL	PASCAL EXPORT CNTset_pulse_counter(INT16 channel, double count);
	double	PASCAL EXPORT CNTget_pulse_counter(INT16 channel);
	// Ʈ���Ÿ� ENABLE�Ѵ�.
	BOOL	PASCAL EXPORT CNTset_trigger_enable(INT16 channel);
	BOOL	PASCAL EXPORT CNTset_trigger_disable(INT16 channel);
	// Ʈ���� ��� ��带 ������.(0: ABSOLUTE POSITION EDGE, 1: PERIODIC TIME TRIGGER, 2: ABSOLUTE POSITION LEVEL)
	BOOL	PASCAL EXPORT CNTset_trigger_mode(INT16 channel, UINT8 mode);
	UINT8	PASCAL EXPORT CNTget_trigger_mode(INT16 channel);
	// Ʈ���� ��尡 PERIODIC TIME����� ��� �߻���ų ���ļ�. ( 1Hz ~ 500KHz)
	BOOL	PASCAL EXPORT CNTset_time_trigger_frequency(INT16 channel, UINT32 trig_freq);
	UINT32	PASCAL EXPORT CNTget_time_trigger_frequency(INT16 channel);

	/// ī��Ʈ ������ �񱳱� ���� �Լ��� -----------------------------------------------------*/
	// �޽� ī���� �񱳱� ���� �����մϴ�.
	BOOL	PASCAL EXPORT CNTset_pulse_comparator(INT16 channel, double count);
	double	PASCAL EXPORT CNTget_pulse_comparator(INT16 channel);
	// �޽� ī���� �񱳱� ���ͷ�Ʈ �߻� ������ �����Ѵ�.
	BOOL	PASCAL EXPORT CNTset_pulse_comparator_condition(INT16 channel, UINT8 condition);
	UINT8	PASCAL EXPORT CNTget_pulse_comparator_condition(INT16 channel);
		/*	���ϰ�
				0: �񱳱� > ī���� ����
				1: �񱳱� = ī���� ����
				2: �񱳱� < ī���� ����
				3: �񱳱� = ī���� ����(ī���� ���� ��)
				4: �񱳱� = ī���� ����(ī���� ���� ��)	
				�׿� : ���� �߻����� ����.		*/
	// �޽� ī���� �񱳱� ���� �б�.
	UINT8	PASCAL EXPORT CNTget_pulse_comparator_status(INT16 channel);
		/*	���ϰ�
				0 bit : �񱳱� > ī���� ��Ȳ
				1 bit : �񱳱� = ī���� ��Ȳ
				2 bit : �񱳱� < ī���� ��Ȳ
				�׿� bit: ���� ����.		*/

	/// ī��Ʈ ������ Ʈ���� �������� �Լ��� -----------------------------------------------------*/
	// �޸𸮿� ����Ÿ�� ������ �� Write Busy Timeout�� ����(����[msc] ��������[100mSec~10000mSec])
	BOOL	PASCAL EXPORT CNTset_trigger_timeout(DWORD dwTimeout);
	DWORD	PASCAL EXPORT CNTget_trigger_timeout();

	// �޸𸮿�(H/W RAM) Ʈ���������� �а� ����.
	INT32	PASCAL EXPORT CNTread_trigger_ram_data(INT16 channel, UINT32 ulAdder);
	BOOL	PASCAL EXPORT CNTwrite_trigger_ram_data(INT16 channel, UINT32 ulAdder, UINT32 ulData);
	// Ʈ���� ������ �Ѳ����� �����Ѵ�.(direction : 0(ī���� ���� ���� ����), 1(ī���� ���� ���� ����))
	int		PASCAL EXPORT CNTset_trigger_absolute(INT16 channel, UINT32 trig_num, UINT32 *trig_pos, UINT8 direction);
	// �޸���(H/W RAM) Ʈ���� ������ Ư�� ����Ÿ�� ��� �����Ѵ�.
	BOOL	PASCAL EXPORT CNTreset_ram_data_all(INT16 nModuleNo, UINT32 data);

	/// ���� ����� �����Լ��� -------------------------------------------------------------------*/
	// ���� ���(Universal output)�ɿ� ����(4��Ʈ)�� ����/�б�
	BOOL	PASCAL EXPORT CNTset_output(INT16 channel, UINT8 value);
	UINT8	PASCAL EXPORT CNTget_output(INT16 channel);
	// ���� �Է�(Universal input)�ɿ��� ����(4��Ʈ)�� �б�
	UINT8	PASCAL EXPORT CNTget_input(INT16 channel);
	// ���� ���(Universal output)�ɿ��� 1��Ʈ�� �б�
	BOOL	PASCAL EXPORT CNToutput_bit_on(INT16 channel, UINT8 bitNo);
	// ���� �Է�(Universal input)�ɿ��� 1��Ʈ�� �б�
	BOOL	PASCAL EXPORT CNTinput_bit_on(INT16 channel, UINT8 bitNo);
	// ���� ���(Universal output)�ɿ� 1��Ʈ SET/RESET
	BOOL	PASCAL EXPORT CNTset_output_bit(INT16 channel, UINT8 bitNo);
	BOOL	PASCAL EXPORT CNTreset_output_bit(INT16 channel, UINT8 bitNo);
	// ���� ���(Universal output)�ɿ� 1��Ʈ�� ����
	BOOL	PASCAL EXPORT CNTchange_output_bit(INT16 channel, UINT8 bitNo, UINT8 state);

	/// Interrupt ���� �Լ���
	// ������ ����� ���ͷ�Ʈ�� ����Ѵ�.
	void PASCAL EXPORT CNTEnableInterrupt(INT16 nModuleNo);
	// ������ ����� ���ͷ�Ʈ�� �����Ѵ�.
	void PASCAL EXPORT CNTDisableInterrupt(INT16 nModuleNo);
	// ����� ���ͷ�Ʈ ������������ Ȯ���Ѵ�.
	BOOL PASCAL EXPORT CNTIsInterruptEnabled(INT16 nModuleNo);

	/// Interrupt ��ġ �񱳱� ���� �Լ���
	// �޽� ī���� �񱳱�� �޽� ī���� ���� ������ ������ ��ġ�� �� ���ͷ�Ʈ�� �߻� ���.
	BOOL	PASCAL EXPORT CNTset_compare_interrupt(INT16 channel);
	// �޽� ī���� �񱳱�� �޽� ī���� ���� ������ ������ ��ġ�� �� ���ͷ�Ʈ�� �߻� ������� ����.
	BOOL	PASCAL EXPORT CNTreset_compare_interrupt(INT16 channel);
	// �޽� ī���� �񱳱�� �޽� ī���� ���� ������ ������ ��ġ�� �� ���ͷ�Ʈ�� �߻� ��� ����.
	BOOL	PASCAL EXPORT CNTis_compare_interrupt_enabled(INT16 channel);

	/// Interrupt ���� �Է� Up-edge port(Register) �Լ���
	// ��¿���(Upedge) ���ͷ�Ʈ ENABLE ��Ʈ�ο� 1��Ʈ�� �����͸� ��ִ´�. ������ ����� ���� ����
	BOOL	PASCAL EXPORT CNTwrite_upedge_bit(INT16 nModuleNo, UINT16 offset, BOOL bValue);
	// ��¿���(Upedge) ���ͷ�Ʈ ENABLE ��Ʈ�ο� 1����Ʈ�� �����͸� ��ִ´�. ������ ����� ����Ʈ ����
	BOOL	PASCAL EXPORT CNTwrite_upedge_byte(INT16 nModuleNo, UINT16 offset, UINT8 byValue);
	// ��¿���(Upedge) ���ͷ�Ʈ ENABLE ��Ʈ�κ��� 1��Ʈ�� �����͸� �о���δ�. ������ ����� ���� ����
	BOOL	PASCAL EXPORT CNTread_upedge_bit(INT16 nModuleNo, UINT16 offset);
	// ��¿���(Upedge) ���ͷ�Ʈ ENABLE ��Ʈ�κ��� 1����Ʈ�� �����͸� �о���δ�, ������ ����� ����Ʈ ����
	UINT8	PASCAL EXPORT CNTread_upedge_byte(INT16 nModuleNo, UINT16 offset);

	/// Interrupt �����Է� Down-edge port(Register) �Լ���
	// �ϰ�����(Downedge) ���ͷ�Ʈ ENABLE ��Ʈ�ο� 1��Ʈ�� �����͸� ��ִ´�. ������ ����� ���� ����
	BOOL	PASCAL EXPORT CNTwrite_downedge_bit(INT16 nModuleNo, UINT16 offset, BOOL bValue);
	// �ϰ�����(Downedge) ���ͷ�Ʈ ENABLE  ��Ʈ�ο� 1����Ʈ�� �����͸� ��ִ´�. ������ ����� ����Ʈ ����
	BOOL	PASCAL EXPORT CNTwrite_downedge_byte(INT16 nModuleNo, UINT16 offset, UINT8 byValue);
	// �ϰ�����(Downedge) ���ͷ�Ʈ ENABLE  ��Ʈ�κ��� 1��Ʈ�� �����͸� �о���δ�. ������ ����� ���� ����
	BOOL	PASCAL EXPORT CNTread_downedge_bit(INT16 nModuleNo, UINT16 offset);
	// �ϰ�����(Downedge) ���ͷ�Ʈ ENABLE  ��Ʈ�κ��� 1����Ʈ�� �����͸� �о���δ�, ������ ����� ����Ʈ ����
	UINT8	PASCAL EXPORT CNTread_downedge_byte(INT16 nModuleNo, UINT16 offset);

/*----------------------- ���������� ����ϴ� ����(Parameter) ------------------------------------*
	nBoardNo	: ���̽������ȣ, ����� ������� 0���� �Ҵ�ȴ�
	nModuleNo	: CNT��� ��ȣ, CNT����� ������ ������� ����� ������� 0���� �Ҵ�ȴ�
 *------------------------------------------------------------------------------------------------*/
	// ������ �߻��� �����ڵ带 ��ȯ��
	INT16  PASCAL EXPORT CNTget_error_code();
	// �Է��� �����ڵ忡 ���� ���� �޼����� ��ȯ
	char * PASCAL EXPORT CNTget_error_msg(INT16 ErrorCode);

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//__AXT_CNT_H__
