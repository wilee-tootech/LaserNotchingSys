#ifndef __AXT_MOTION_CAMC_H__
#define __AXT_MOTION_CAMC_H__

/*------------------------------------------------------------------------------------------------*
	CAMC-5M �� CAMC-FS ���̺귯���� ������ ����
	������ǰ
		SMC-1V01 - CAMC-5M 1��
		SMC-2V01 - CAMC-5M 2��
		SMC-1V02 - CAMC-FS Ver1.0 1��
		SMC-2V02 - CAMC-FS Ver1.0 2��
		SMC-1V02 - CAMC-FS Ver2.0 �̻� 1��
		SMC-2V02 - CAMC-FS Ver2.0 �̻� 2��
	CAMC-5M�� �Լ��� ���ξ C5M�̰�, (��, C5Mget_actual_position(...))
	CAMC-FS Ver1.0�� �Լ��� ���ξ CAMC�̰�, (��, CFSget_actual_position(...))
	CAMC-FS Ver2.0�̻��� �Լ��� ���ξ CAMC��, (��, CFS20get_actual_position(...))
	�� �Լ��� CAMC��� ǥ��Ǿ� �ִ� �κ��� ���ξ��
 *------------------------------------------------------------------------------------------------*/


/// �ʱ�ȭ �Լ���

	/// Save/Load parameter
	BOOL	PASCAL EXPORT CAMCload_parameter(INT16 axis, char *nfilename);
	BOOL    PASCAL EXPORT CAMCsave_parameter(INT16 axis, char *nfilename); 
	BOOL    PASCAL EXPORT CAMCload_parameter_all(char *nfilename);
	BOOL    PASCAL EXPORT CAMCsave_parameter_all(char *nfilename); 
		//	nfilename	: �ʱⰪ�� ����/�б⸦ ������ ���ϸ��� ����

	/// ���� �� ��� ���� �Լ���
	INT16	PASCAL EXPORT CAMCget_boardno(UINT32 address);
	INT16	PASCAL EXPORT CAMCget_numof_boards();
	INT16	PASCAL EXPORT CAMCget_numof_axes(INT16 board_id);
	INT16	PASCAL EXPORT CAMCget_total_numof_axis();
	INT16	PASCAL EXPORT CAMCget_axisno(INT16 nBoardNo, INT16 nModuleNo);
	BOOL    PASCAL EXPORT CAMCget_axis_info(INT16 nAxisNo, INT16 *nBoardNo, INT16 *nModuleNo, UINT8   *bModuleID, INT16 *nAxisPos);

	// ���� Ŭ�� ���� - �⺻���� 16.384 MHz
	void	PASCAL EXPORT CAMCKeSetMainClk(INT32 nMainClk);
		//	clk		: CAMC-FS�� ���޵Ǵ� Ŭ��, 16.384 MHz
		//				16384000L(F_16_384M_CLK)	= 16.384 MHz
		//				32768000L(F_32_768M_CLK)	= 32.768 MHz

	/// Drive mode 1, 2
	void	PASCAL EXPORT CAMCset_drive_mode1(INT16 axis, 
				UINT8 decelstartpoint,
				UINT8 pulseoutmethod,
				UINT8 detectsignal);
		// decelstartpoint	:
		//		0(AutoDetect)	= �ڵ�����
		//		1(RestPulse)	= �ܷ��޽�
		// pulseoutmethod	: �޽� ��� ���
		//		0(OneHighLowHigh)		= 1�޽� ���, PULSE(Active High), ������(DIR=Low)  / ������(DIR=High)
		//		1(OneHighHighLow(0x1)	= 1�޽� ���, PULSE(Active High), ������(DIR=High) / ������(DIR=Low)
		//		2(OneLowLowHigh(0x2)	= 1�޽� ���, PULSE(Active Low),  ������(DIR=Low)  / ������(DIR=High)
		//		3(OneLowHighLow(0x3)	= 1�޽� ���, PULSE(Active Low),  ������(DIR=High) / ������(DIR=Low)
		//		4(TwoCcwCwHigh(0x4)		= 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active High	 
		//		5(TwoCcwCwLow(0x5)		= 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active Low	 
		//		6(TwoCwCcwHigh(0x6)		= 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active High
		//		7(TwoCwCcwLow(0x7)		= 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active Low
		// detectsignal)	: Signal search 1/2���� ����ϴ� �����ȣ
		//		0h(PElmNegativeEdge    = +Elm(End limit) �ϰ� edge
		//		1h(NElmNegativeEdge    = -Elm(End limit) �ϰ� edge
		//		2h(PSlmNegativeEdge    = +Slm(Slowdown limit) �ϰ� edge
		//		3h(NSlmNegativeEdge    = -Slm(Slowdown limit) �ϰ� edge
		//		4h(In0DownEdge         = IN0(ORG) �ϰ� edge
		//		5h(In1DownEdge         = IN1(Z��) �ϰ� edge
		//		6h(In2DownEdge         = IN2(����) �ϰ� edge
		//		7h(In3DownEdge         = IN3(����) �ϰ� edge
		//		8h(PElmPositiveEdge    = +Elm(End limit) ��� edge
		//		9h(NElmPositiveEdge    = -Elm(End limit) ��� edge
		//		Ah(PSlmPositiveEdge    = +Slm(Slowdown limit) ��� edge
		//		Bh(NSlmPositiveEdge    = -Slm(Slowdown limit) ��� edge
		//		Ch(In0UpEdge           = IN0(ORG) ��� edge
		//		Dh(In1UpEdge           = IN1(Z��) ��� edge
		//		Eh(In2UpEdge           = IN2(����) ��� edge
		//		Fh(In3UpEdge           = IN3(����) ��� edge
	UINT8	PASCAL EXPORT CAMCget_drive_mode1(INT16 axis);
	void	PASCAL EXPORT CAMCset_drive_mode2(INT16 axis, 
				UINT8 encmethod,
				UINT8 inpactivelevel,
				UINT8 alarmactivelevel,
				UINT8 nslmactivelevel,
				UINT8 pslmactivelevel,
				UINT8 nelmactivelevel,
				UINT8 pelmactivelevel);
		// encmethod		: ���ڴ� �Է� ���
		//		0(UpDownMode)		= Up/Down
		//		1(Sqr1Mode)			= 1ü��
		//		2(Sqr2Mode)			= 2ü��
		//		3(Sqr4Mode)			= 4ü��
 		// inpactivelevel	: INP��ȣ ��Ƽ�극��
 		//		0(InpActiveLow)		= Active low
		//		1(InpActiveHigh)	= Active high
		// alarmactivelevel	: ALARM��ȣ ��Ƽ�극��
		//		0(AlmActiveLow)		= Active low
		//		1(AlmActiveHigh)	= Active high
		// nslmactivelevel	: -SLM(Slowdown limit)��ȣ ��Ƽ�극��
		//		0(NSlmActiveLow)	= Active low
		//		1(NSlmActiveHigh)	= Active high
		// pslmactivelevel	: +SLM(Slowdown limit)��ȣ ��Ƽ�극��
		//		0(PSlmActiveLow)	= Active low
		//		1(PSlmActiveHigh)	= Active high
		// nelmactivelevel	: -ELM(End limit)��ȣ ��Ƽ�극��
		//		0(NElmActiveLow)	= Active low
		//		1(NElmActiveHigh)	= Active high
		// pelmactivelevel	: +ELM(End limit)��ȣ ��Ƽ�극��
		//		0(PElmActiveLow)	= Active low
		//		1(PElmActiveHigh)	= Active high
	UINT8	PASCAL EXPORT CAMCget_drive_mode2(INT16 axis);

	/// ���� �Լ���
	UINT8	PASCAL EXPORT CAMCget_drive_status(INT16 axis);
	UINT16	PASCAL EXPORT CAMCget_end_status(INT16 axis);
	INT32	PASCAL EXPORT CAMCget_drive_pulse_counts(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_mechanical_signal(INT16 axis);
	double	PASCAL EXPORT CAMCget_velocity(INT16 axis);
	double	PASCAL EXPORT CAMCget_error(INT16 axis);
/*
/// ���� �Լ���
	// ��� ���� ���¸� �д´�
	UINT8	PASCAL EXPORT CAMCget_drive_status(INT16 axis);
		//	���ϰ�	: ����̺� ����
		//		Bit 0 : Busy, 1=��� ���� ��
		//		Bit 1 : Down, 1=���� ��
		//		Bit 2 : Const, 1=���� ��
		//		Bit 3 : Up, 1=������
		//		Bit 4 : ICL, 1=���� ��ġ ī���� �񱳰� > ���� ��ġ ī���Ͱ�
		//		Bit 5 : ICG, 1=���� ��ġ ī���� �񱳰� < ���� ��ġ ī���Ͱ�
		//		Bit 6 : ECL, 1=�ܺ� ��ġ ī���� �񱳰� > �ܺ� ��ġ ī���Ͱ�
		//		Bit 7 : ECG, 1=�ܺ� ��ġ ī���� �񱳰� < �ܺ� ��ġ ī���Ͱ�
	
	// ��� �Ϸ� ���¸� �д´�
	UINT16	PASCAL EXPORT CAMCget_end_status(INT16 axis);
		//	���ϰ�	: ����̺� ����
		//		Bit 0 : 1=���� ����Ʈ ��ȣ �Է¿� ���� ����
		//		Bit 1 : 1=����Ʈ ��ȣ �Է¿� ���� ����
		//		Bit 2 : 1=���� ���� ��ȣ �Է¿� ���� ����
		//		Bit 3 : 1=������ ��ȣ �Է¿� ���� ����
		//		Bit 4 : 1=���� ���� ��ɿ� ���� ����
		//		Bit 5 : 1=������ ��ɿ� ���� ����
		//		Bit 6 : 1=Alarm ��ȣ �Է¿� ���� ����
		//		Bit 7 : 1=������ ���� ������ ���� ����
		//		Bit 8 : 1=Ż�� ������ ���� ����
		//		Bit 9 : 1=Reserved
		//		Bit 10: 1=��ȣ ���⿡ ���� ����
		//		����Ʈ�� 0�̸� ���� ����
*/

	// �ִ� �ӵ� ����/�˻�
	BOOL    PASCAL EXPORT CAMCset_max_speed(INT16 axis, double max_velocity);
	double	PASCAL EXPORT CAMCget_max_speed(INT16 axis);

	// �� ���� �Լ�
	BOOL    PASCAL EXPORT CAMCset_axis_sync(INT16 nLen, INT16 *aAxis);
	BOOL    PASCAL EXPORT CAMCreset_axis_sync(INT16 nLen, INT16 *aAxis);

	/// ���࿡ ���� ��ٸ��� �����Լ���
	BOOL    PASCAL EXPORT CAMCstart_move(INT16 axis, double position, double velocity, double acceleration);
	BOOL    PASCAL EXPORT CAMCstart_move_ex(INT16 axis, double position, double velocity, double acceltime);
	UINT8	PASCAL EXPORT CAMCmove(INT16 axis, double position, double velocity, double acceleration);
	UINT8	PASCAL EXPORT CAMCmove_ex(INT16 axis, double position, double velocity, double acceltime);
	BOOL    PASCAL EXPORT CAMCstart_r_move(INT16 axis, double distance, double velocity, double acceleration);
	BOOL    PASCAL EXPORT CAMCstart_r_move_ex(INT16 axis, double distance, double velocity, double acceltime);
	UINT8	PASCAL EXPORT CAMCr_move(INT16 axis, double distance, double velocity, double acceleration);
	UINT8	PASCAL EXPORT CAMCr_move_ex(INT16 axis, double distance, double velocity, double acceltime);
	BOOL    PASCAL EXPORT CAMCstart_signal_search1(INT16 axis, double velocity, double acceleration, UINT8 detect_signal);
	BOOL    PASCAL EXPORT CAMCstart_signal_search1_ex(INT16 axis, double velocity, double acceltime, UINT8 detect_signal);
	BOOL    PASCAL EXPORT CAMCstart_signal_search2(INT16 axis, double velocity, UINT8   detect_signal);

	/// ���࿡ ���� S���� �����Լ���
	BOOL    PASCAL EXPORT CAMCstart_s_move(INT16 axis, double position, double velocity, double acceleration);
	BOOL    PASCAL EXPORT CAMCstart_s_move_ex(INT16 axis, double position, double velocity, double acceltime);
	UINT8	PASCAL EXPORT CAMCs_move(INT16 axis, double position, double velocity, double acceleration);
	UINT8	PASCAL EXPORT CAMCs_move_ex(INT16 axis, double position, double velocity, double acceltime);
	BOOL    PASCAL EXPORT CAMCstart_rs_move(INT16 axis, double distance, double velocity, double acceleration);
	BOOL    PASCAL EXPORT CAMCstart_rs_move_ex(INT16 axis, double distance, double velocity, double acceltime);
	UINT8	PASCAL EXPORT CAMCrs_move(INT16 axis, double distance, double velocity, double acceleration);
	UINT8	PASCAL EXPORT CAMCrs_move_ex(INT16 axis, double distance, double velocity, double acceltime);
	BOOL    PASCAL EXPORT CAMCstart_s_signal_search1(INT16 axis, double velocity, double acceleration, UINT8 detect_signal);
	BOOL    PASCAL EXPORT CAMCstart_s_signal_search1_ex(INT16 axis, double velocity, double acceltime, UINT8 detect_signal);

	/// ���࿡ ���� ��Ÿ�Լ���
	void	PASCAL EXPORT CAMCset_startstop_speed(INT16 axis, double velocity);
	double	PASCAL EXPORT CAMCget_startstop_speed(INT16 axis);
	void	PASCAL EXPORT CAMCset_moveunit_perpulse(INT16 axis, double unitperpulse);
	double	PASCAL EXPORT CAMCget_moveunit_perpulse(INT16 axis);
	void	PASCAL EXPORT CAMCset_movepulse_perunit(INT16 axis, INT32 pulseperunit);
	INT32	PASCAL EXPORT CAMCget_movepulse_perunit(INT16 axis);
	void	PASCAL EXPORT CAMCset_s_rate(INT16 axis, double a_percent, double b_percent);
	void	PASCAL EXPORT CAMCget_s_rate(INT16 axis, double *a_percent, double *b_percent);
	UINT8	PASCAL EXPORT CAMCwait_for_done(INT16 axis);

	/// �����࿡ ���� ��ٸ����� �����Լ���
	BOOL    PASCAL EXPORT CAMCstart_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
	BOOL    PASCAL EXPORT CAMCstart_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
	UINT8	PASCAL EXPORT CAMCmove_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
	UINT8	PASCAL EXPORT CAMCmove_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
	BOOL    PASCAL EXPORT CAMCstart_r_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
	BOOL    PASCAL EXPORT CAMCstart_r_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
	UINT8	PASCAL EXPORT CAMCr_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
	UINT8	PASCAL EXPORT CAMCr_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);

	/// �����࿡ ���� S���� �����Լ���
	BOOL    PASCAL EXPORT CAMCstart_s_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
	BOOL    PASCAL EXPORT CAMCstart_s_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
	UINT8	PASCAL EXPORT CAMCs_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
	UINT8	PASCAL EXPORT CAMCs_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
	BOOL    PASCAL EXPORT CAMCstart_rs_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
	BOOL    PASCAL EXPORT CAMCstart_rs_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
	UINT8	PASCAL EXPORT CAMCrs_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
	UINT8	PASCAL EXPORT CAMCrs_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);

	/// �����࿡ ���� ��Ÿ �Լ���
	UINT8	PASCAL EXPORT CAMCwait_for_all(INT16 number, INT16 *axes);
	void	PASCAL EXPORT CAMCset_s_rate_all(INT16 number, INT16 *axes, double *a_percent, double *b_percent);
	void	PASCAL EXPORT CAMCget_s_rate_all(INT16 number, INT16 *axes, double *a_percent, double *b_percent);

	/// ���ӵ� ���� �Լ���
	BOOL    PASCAL EXPORT CAMCv_move(INT16 axis, double velocity, double acceleration);
	BOOL    PASCAL EXPORT CAMCv_move_ex(INT16 axis, double velocity, double acceltime);
	BOOL    PASCAL EXPORT CAMCv_s_move(INT16 axis, double velocity, double acceleration);
	BOOL    PASCAL EXPORT CAMCv_s_move_ex(INT16 axis, double velocity, double acceltime);
        
	/// Ư�� ��ǥ�迡 ���� �����Լ���
	BOOL    PASCAL EXPORT CAMCmap_axes(INT16 coordinate, INT16 n_axes, INT16 *map_array);
	BOOL    PASCAL EXPORT CAMCget_mapped_axes(INT16 coordinate, INT16 n_axes, INT16 *map_array);
	void	PASCAL EXPORT CAMCset_move_velocity(INT16 coordinate, double velocity);
	double	PASCAL EXPORT CAMCget_move_velocity(INT16 coordinate);
	void	PASCAL EXPORT CAMCset_move_acceleration(INT16 coordinate, double acceleration);
	double	PASCAL EXPORT CAMCget_move_acceleration(INT16 coordinate);
	void	PASCAL EXPORT CAMCset_move_acceltime(INT16 coordinate, double acceltime);
	double	PASCAL EXPORT CAMCget_move_acceltime(INT16 coordinate);
	void	PASCAL EXPORT CAMCset_move_startstop_velocity(INT16 coordinate, double velocity);
	double	PASCAL EXPORT CAMCget_move_startstop_velocity(INT16 coordinate);
	void	PASCAL EXPORT CAMCset_move_profile(INT16 coordinate, INT16 mode);
	INT16	PASCAL EXPORT CAMCget_move_profile(INT16 coordinate);
	void	PASCAL EXPORT CAMCset_coordinate_mode(INT16 coordinate, INT16 mode);
	INT16	PASCAL EXPORT CAMCget_coordinate_mode(INT16 coordinate);

	/// Ư�� ��ǥ�迡 ���� �����Լ���
	BOOL    PASCAL EXPORT CAMCstart_move_2(INT16 coordinate, double x, double y);
	BOOL    PASCAL EXPORT CAMCstart_move_3(INT16 coordinate, double x, double y, double z);
	BOOL    PASCAL EXPORT CAMCstart_move_4(INT16 coordinate, double x, double y, double z, double w);
	BOOL    PASCAL EXPORT CAMCmove_2(INT16 coordinate, double x, double y);
	BOOL    PASCAL EXPORT CAMCmove_3(INT16 coordinate, double x, double y, double z);
	BOOL    PASCAL EXPORT CAMCmove_4(INT16 coordinate, double x, double y, double z, double w);

	/// Ư�� ��ǥ�迡 ���� ��Ÿ�Լ���
	double	PASCAL EXPORT CAMCco_get_velocity(INT16 coordinate);
	BOOL    PASCAL EXPORT CAMCco_motion_done(INT16 coordinate);
	BOOL    PASCAL EXPORT CAMCco_wait_for_done(INT16 coordinate);

	/// ��ġ ����Ÿ �Լ���
	void	PASCAL EXPORT CAMCset_command_position(INT16 axis, double position);
	double	PASCAL EXPORT CAMCget_command_position(INT16 axis);
	void	PASCAL EXPORT CAMCset_actual_position(INT16 axis, double position);
	double	PASCAL EXPORT CAMCget_actual_position(INT16 axis);

	/// ���� ���� �Լ���
	BOOL    PASCAL EXPORT CAMCin_motion(INT16 axis);
	BOOL    PASCAL EXPORT CAMCmotion_done(INT16 axis);
	BOOL    PASCAL EXPORT CAMCin_position(INT16 axis);

	/// ���� �Լ���
	BOOL    PASCAL EXPORT CAMCset_stop(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_stop_decel(INT16 axis, double deceleration);
	BOOL    PASCAL EXPORT CAMCset_stop_deceltime(INT16 axis, double deceltime);
	BOOL    PASCAL EXPORT CAMCset_e_stop(INT16 axis);
	BOOL    PASCAL EXPORT CAMCemergency_stop();

	/// ���� ����� �����Լ���
	BOOL    PASCAL EXPORT CAMCset_output(INT16 axis, UINT8 value);
	UINT8	PASCAL EXPORT CAMCget_output(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_input(INT16 axis);
	BOOL    PASCAL EXPORT CAMCoutput_bit_on(INT16 axis, UINT8 bitNo);
	BOOL    PASCAL EXPORT CAMCinput_bit_on(INT16 axis, UINT8 bitNo);
	BOOL    PASCAL EXPORT CAMCset_output_bit(INT16 axis, UINT8 bitNo);
	BOOL    PASCAL EXPORT CAMCreset_output_bit(INT16 axis, UINT8 bitNo);
	BOOL    PASCAL EXPORT CAMCchange_output_bit(INT16 axis, UINT8 bitNo, UINT8 state);

	/// ������/�����̺� �����Լ���
	BOOL    PASCAL EXPORT CAMClink(INT16 master, INT16 slave, double ratio);
	BOOL    PASCAL EXPORT CAMCendlink(INT16 slave);

	/// ����Ʈ �Լ���
	// End limit
	BOOL    PASCAL EXPORT CAMCset_end_limit_enable(INT16 axis, UINT8 use);
	UINT8	PASCAL EXPORT CAMCget_end_limit_enable(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_pend_limit_level(INT16 axis, UINT8 level);
	UINT8	PASCAL EXPORT CAMCget_pend_limit_level(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_nend_limit_level(INT16 axis, UINT8 level);
	UINT8	PASCAL EXPORT CAMCget_nend_limit_level(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_pend_limit_switch(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_nend_limit_switch(INT16 axis);
	// Slow down limit
	BOOL    PASCAL EXPORT CAMCset_slow_limit_enable(INT16 axis, UINT8 use);
	UINT8	PASCAL EXPORT CAMCget_slow_limit_enable(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_pslow_limit_level(INT16 axis, UINT8 level);
	UINT8	PASCAL EXPORT CAMCget_pslow_limit_level(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_nslow_limit_level(INT16 axis, UINT8 level);
	UINT8	PASCAL EXPORT CAMCget_nslow_limit_level(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_pslow_limit_switch(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_nslow_limit_switch(INT16 axis);

	/// Emergency signal
	BOOL    PASCAL EXPORT CAMCset_emg_signal_enable(INT16 axis, UINT8 use);
	UINT8	PASCAL EXPORT CAMCget_emg_signal_enable(INT16 axis);

	/// ��������(Inposition) �Լ���
	BOOL    PASCAL EXPORT CAMCset_inposition_enable(INT16 axis, UINT8 use);
	UINT8	PASCAL EXPORT CAMCget_inposition_enable(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_inposition_level(INT16 axis, UINT8 level);
	UINT8	PASCAL EXPORT CAMCget_inposition_level(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_inposition_switch(INT16 axis);

	/// ����(SERVO-ON) �Լ���
	BOOL    PASCAL EXPORT CAMCset_servo_enable(INT16 axis, UINT8   state);
	UINT8	PASCAL EXPORT CAMCget_servo_enable(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_servo_level(INT16 axis, UINT8 level);
	UINT8	PASCAL EXPORT CAMCget_servo_level(INT16 axis);

	/// ���� ��� ���� �Լ���
	BOOL    PASCAL EXPORT CAMCset_decel_point(INT16 axis, UINT8 method);
	UINT8	PASCAL EXPORT CAMCget_decel_point(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_pulse_out_method(INT16 axis, UINT8 method);
	UINT8	PASCAL EXPORT CAMCget_pulse_out_method(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_enc_input_method(INT16 axis, UINT8 method);
	UINT8	PASCAL EXPORT CAMCget_enc_input_method(INT16 axis);

	/// �˶�(Alarm) �Լ���
	BOOL    PASCAL EXPORT CAMCset_alarm_enable(INT16 axis, UINT8 use);
	UINT8	PASCAL EXPORT CAMCget_alarm_enable(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_alarm_level(INT16 axis, UINT8 level);
	UINT8	PASCAL EXPORT CAMCget_alarm_level(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_alarm_switch(INT16 axis);

	/// ���� �˻� �Լ���
	BOOL    PASCAL EXPORT CAMCset_home_offset(INT16 axis, INT16 nstep, double *offset);
	BOOL    PASCAL EXPORT CAMCget_home_offset(INT16 axis, INT16 nstep, double *offset);
	BOOL    PASCAL EXPORT CAMCset_zphase_search_range(INT16 axis, INT16 pulses);
	INT16	PASCAL EXPORT CAMCget_zphase_search_range(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_home_method(INT16 axis, INT16 nstep, UINT8 *method);
	BOOL    PASCAL EXPORT CAMCget_home_method(INT16 axis, INT16 nstep, UINT8 *method);
	BOOL    PASCAL EXPORT CAMCset_home_velocity(INT16 axis, INT16 nstep, double *velocity);
	BOOL    PASCAL EXPORT CAMCget_home_velocity(INT16 axis, INT16 nstep, double *velocity);
	BOOL    PASCAL EXPORT CAMCset_home_acceleration(INT16 axis, INT16 nstep, double *acceleration);
	BOOL    PASCAL EXPORT CAMCget_home_acceleration(INT16 axis, INT16 nstep, double *acceleration);
	BOOL    PASCAL EXPORT CAMCset_home_acceltime(INT16 axis, INT16 nstep, double *acceltime);
	BOOL    PASCAL EXPORT CAMCget_home_acceltime(INT16 axis, INT16 nstep, double *acceltime);
	BOOL    PASCAL EXPORT CAMChome_search(INT16 axis);
	BOOL    PASCAL EXPORT CAMChome_zero(INT16 axis);
	BOOL    PASCAL EXPORT CAMCabort_home_search(INT16 axis, UINT8 bStop);
	BOOL    PASCAL EXPORT CAMChome_search_all(INT16 number, INT16 *axes);
	BOOL    PASCAL EXPORT CAMChome_zero_all(INT16 number, INT16 *axes);
	BOOL    PASCAL EXPORT CAMCget_home_done(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_home_end_status(INT16 axis);
	BOOL    PASCAL EXPORT CAMCget_home_done_all(INT16 number, INT16 *axes);
	BOOL    PASCAL EXPORT CAMCget_home_end_status_all(INT16 number, INT16 *axes, UINT8 *endstatus);

	/// �������̵� ���� �Լ���
	BOOL    PASCAL EXPORT CAMCposition_override(INT16 axis, double overrideposition);
	BOOL    PASCAL EXPORT CAMCposition_r_override(INT16 axis, double overridedistance);
	double	PASCAL EXPORT CAMCget_drivedistance(INT16 axis);

	/// Ʈ���� ���� �Լ���
	BOOL    PASCAL EXPORT CAMCset_trigger_enable(INT16 axis, UINT8 ena_status);
	UINT8	PASCAL EXPORT CAMCis_trigger_enabled(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_trigger_sel(INT16 axis, UINT8 trigger_sel);
	UINT8	PASCAL EXPORT CAMCget_trigger_sel(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_trigger_level(INT16 axis, UINT8 trigger_level);
	UINT8	PASCAL EXPORT CAMCget_trigger_level(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_trigger_interrupt_enable(INT16 axis, UINT8 ena_int);
	UINT8	PASCAL EXPORT CAMCis_trigger_interrupt_enabled(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_trigger_time(INT16 axis, UINT8 time);
	UINT8	PASCAL EXPORT CAMCget_trigger_time(INT16 axis);

	/// Internal/External comparator ���� �Լ���
	void	PASCAL EXPORT CAMCset_internal_comparator_position(INT16 axis, double position);
	double	PASCAL EXPORT CAMCget_internal_comparator_position(INT16 axis);
	void	PASCAL EXPORT CAMCset_external_comparator_position(INT16 axis, double position);
	double	PASCAL EXPORT CAMCget_external_comparator_position(INT16 axis);

	/// crc ���� �Լ���
	BOOL    PASCAL EXPORT CAMCset_crc_nelm_mask(INT16 axis, INT16 mask);
	UINT8	PASCAL EXPORT CAMCget_crc_nelm_mask(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_crc_nelm_level(INT16 axis, INT16 level);
	UINT8	PASCAL EXPORT CAMCget_crc_nelm_level(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_crc_pelm_mask(INT16 axis, INT16 mask);
	UINT8	PASCAL EXPORT CAMCget_crc_pelm_mask(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_crc_pelm_level(INT16 axis, INT16 level);
	UINT8	PASCAL EXPORT CAMCget_crc_pelm_level(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_crc_mask(INT16 axis, INT16 mask);
	UINT8	PASCAL EXPORT CAMCget_crc_mask(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_crc_level(INT16 axis, INT16 level);
	UINT8	PASCAL EXPORT CAMCget_crc_level(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_programmed_crc(INT16 axis, INT16 data);
	UINT8	PASCAL EXPORT CAMCget_programmed_crc(INT16 axis);

	/// Interrupt
	BOOL    PASCAL EXPORT CAMCset_motiondone_interrupt_enable(INT16 axis, UINT8 ena_int);
	UINT8	PASCAL EXPORT CAMCis_motiondone_interrupt_enabled(INT16 axis);

	/// Etc.
	void	PASCAL EXPORT CAMCset_slowdown_rear_pulse(INT16 axis, UINT32 ulData);
	UINT32	PASCAL EXPORT CAMCget_slowdown_rear_pulse(INT16 axis);
	BOOL    PASCAL EXPORT CAMCvelocity_override(INT16 axis, double velocity);





























#if 0

	////////////////////////////////////////////////////////////////////////////////////////////////
	
	// �ʱ� ���� �ӵ� ����
	void    CAMCset_startstop_speed(INT16 axis, INT32 velocity);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				velocity: Start/Stop speed, [PPS]
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
				* Object(����) �ӵ��� �����ϸ� ��� ������ �ϰ� �ȴ�
			----------------------------------------------------------------- */

	// �޽� ��� ���(1/2�޽� ��) ���� 
	BOOL    CAMCset_pulse_out_method(INT16 axis, UINT8 method);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				method	: ���
					0(OneHighLowHigh)	= 1�޽� ���, PULSE(Active High), ������(DIR=Low)  / ������(DIR=High)
					1(OneHighHighLow)   = 1�޽� ���, PULSE(Active High), ������(DIR=High) / ������(DIR=Low)
					2(OneLowLowHigh)    = 1�޽� ���, PULSE(Active Low),  ������(DIR=Low)  / ������(DIR=High)
					3(OneLowHighLow)    = 1�޽� ���, PULSE(Active Low),  ������(DIR=High) / ������(DIR=Low)
					4(TwoCcwCwHigh)     = 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active High
					5(TwoCcwCwLow)      = 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active Low
					6(TwoCwCcwHigh)     = 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active High
					7(TwoCwCcwLow)      = 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active Low
				���ϰ�	: ����
			----------------------------------------------------------------- */
	
	// ���ڴ� ��� ����(1/2/4ü�� ��)
	BOOL    CAMCset_enc_input_method(INT16 axis, UINT8 method);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				method	: ���
					1(Sqr1Mode)		= 1ü��
					2(Sqr2Mode)		= 2ü��
					3(Sqr4Mode)		= 4ü��
				���ϰ�	: ����
			----------------------------------------------------------------- */

	// ����Ʈ(End limit) ������ �Է��� ����� �������� ����
	BOOL    CAMCset_end_limit_enable(INT16 axis, UINT8 use);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				use		: ��� ����
					0(ON)	= ������� ����
					1(OFF)	= �����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
			----------------------------------------------------------------- */

	// ���Ӹ���Ʈ(Slow down limit) ������ �Է��� ����� �������� ����
	BOOL    CAMCset_slow_limit_enable(INT16 axis, UINT8 use);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				use		: ��� ����
					0(ON)	= ������� ����
					1(OFF)	= �����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
			----------------------------------------------------------------- */
	
	// Inposition �Է��� ����� �������� ���� - ��� �� Inposition �Է��� Active �Ǿ�� Busy �Ϸᰡ �ȴ�
	BOOL    CAMCset_inposition_enable(INT16 axis, UINT8 use);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				use		: ��� ����
					0(ON)	= ������� ����
					1(OFF)	= �����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
			----------------------------------------------------------------- */

	// Alarm �Է��� ����� �������� ���� - ��� �� Alarm �Է��� Active �Ǹ� �޽� ��� ����
	BOOL    CAMCset_alarm_enable(INT16 axis, UINT8 use);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				use		: ��� ����
					0(ON)	= ������� ����
					1(OFF)	= �����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
			----------------------------------------------------------------- */

	// �ִ� �ӵ� ���� ����
	BOOL    CAMCset_max_speed(INT16 axis, INT32 max_velocity);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				max_velocity	: �ִ� �ӵ�, [PPS]
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
				* Range �� ������ ������ �ֹǷ� ����
			----------------------------------------------------------------- */


	////////////////////////////////////////////////////////////////////////////////////////////////
	/// ��ġ ���� �Լ�
	// Command(Internal) ��ġ ���� / �˻�
	void    CAMCset_command_position(INT16 axis, INT32 position);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				position: �����ϰ��� �ϴ� ��ġ, [PULSE]
				���ϰ�	: ����
			----------------------------------------------------------------- */
	INT32  CAMCget_command_position(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				���ϰ�	: ���� ��ġ, [PULSE]
			----------------------------------------------------------------- */
	
	// Actual(External) ��ġ ���� / �˻�
	void    CAMCset_actual_position(INT16 axis, INT32 position);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				position: �����ϰ��� �ϴ� ��ġ, [PULSE]
				���ϰ�	: ����
			----------------------------------------------------------------- */
	INT32  CAMCget_actual_position(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				���ϰ�	: ���� ��ġ, [PULSE]
			----------------------------------------------------------------- */

	// �� ��ġ ����
	void    CAMCset_internal_comparator_position(INT16 axis, INT32 position);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				position: �����ϰ��� �ϴ� �� ��ġ, [PULSE]
				���ϰ�	: ����
			----------------------------------------------------------------- */
	void    CAMCset_external_comparator_position(INT16 axis, INT32 position);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				position: �����ϰ��� �ϴ� �� ��ġ, [PULSE]
				���ϰ�	: ����
			----------------------------------------------------------------- */


	////////////////////////////////////////////////////////////////////////////////////////////////
	/// ���� Ȯ�� �Լ�
	// ��� ������ ?
	BOOL    CAMCin_motion(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				���ϰ�	: 0(FALSE)=��� ������, 1(TRUE)=��� �Ϸ�
			----------------------------------------------------------------- */
	
	// ��� ���� �Ϸ� ?
	BOOL    CAMCmotion_done(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				���ϰ�	: 0(FALSE)=��� �Ϸ�, 1(TRUE)=��� ������
				CAMCin_motion() �Լ��� �ݴ밪�� ����
			----------------------------------------------------------------- */
	
	
	// Get mechanical signal
	UINT8   CAMCget_mechanical_signal(INT16 axis);

	// Get current speed
	UINT32	CAMCget_velocity(INT16 axis);

	////////////////////////////////////////////////////////////////////////////////////////////////
	/// ��� ���� �Լ�
	// ��ٸ��� ������ ���� - ���� ��ǥ
	BOOL    CAMCstart_move(INT16 axis, INT32 position, INT32 velocity, double acceleration);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				position: �̵��� ��ġ, ���� ��ǥ, [PULSE]
				velocity: �̵� �ӵ�, [PPS]
				acceleration	: ������, �Ϲ������� velocity�� 10�� ����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
				* ���� ���� ��� ������ �õ��ϸ� ���� ����
			----------------------------------------------------------------- */

//%	// ��ٸ��� ������ ���� - ��� ��ǥ
//%	BOOL    CAMCstart_r_move(INT16 axis, INT32 distance, INT32 velocity, double acceleration);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				distance: �̵��� �Ÿ�, ��� ��ǥ, [PULSE]
				velocity: �̵� �ӵ�, [PPS]
				acceleration	: ������, �Ϲ������� velocity�� 10�� ����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
				* ���� ���� ��� ������ �õ��ϸ� ���� ����
			----------------------------------------------------------------- */

	// ��Ī ������(S-Curve) ������ ���� - ���� ��ǥ
	BOOL    CAMCstart_s_move(INT16 axis, INT32 position, INT32 velocity, double acceleration);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				position: �̵��� ��ġ, ���� ��ǥ, [PULSE]
				velocity: �̵� �ӵ�, [PPS]
				acceleration	: ������, �Ϲ������� velocity�� 5�� ����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
				* ���� ���� ��� ������ �õ��ϸ� ���� ����
			----------------------------------------------------------------- */

//%	// ��Ī ������(S-Curve) ������ ���� - ��� ��ǥ
//%	BOOL    CAMCstart_rs_move(INT16 axis, INT32 distance, INT32 velocity, double acceleration);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				distance: �̵��� �Ÿ�, ��� ��ǥ, [PULSE]
				velocity: �̵� �ӵ�, [PPS]
				acceleration	: ������, �Ϲ������� velocity�� 5�� ����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
				* ���� ���� ��� ������ �õ��ϸ� ���� ����
			----------------------------------------------------------------- */

	// ���Ī ������(S-Curve) ������ ���� - ���� ��ǥ
	BOOL    CAMCstart_as_move(INT16 axis, INT32 position, INT32 velocity, double acceleration, double deceleration);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				position: �̵��� ��ġ, ���� ��ǥ, [PULSE]
				velocity: �̵� �ӵ�, [PPS]
				acceleration	: ������, �Ϲ������� velocity�� 5�� ����
				deceleration	: ������, �Ϲ������� velocity�� 5�� ����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
				* ���� ���� ��� ������ �õ��ϸ� ���� ����
			----------------------------------------------------------------- */

//%	// ���Ī ������(S-Curve) ������ ���� - ��� ��ǥ
//%	BOOL    CAMCstart_ras_move(INT16 axis, INT32 distance, INT32 velocity, double acceleration, double deceleration);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				distance: �̵��� �Ÿ�, ��� ��ǥ, [PULSE]
				velocity: �̵� �ӵ�, [PPS]
				acceleration	: ������, �Ϲ������� velocity�� 5�� ����
				deceleration	: ������, �Ϲ������� velocity�� 5�� ����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
				* ���� ���� ��� ������ �õ��ϸ� ���� ����
			----------------------------------------------------------------- */
	
	// ��Ī ������(S-Curve) ������ ���� - ���� ��ǥ, ����(Continuous) ����
	BOOL CAMCv_s_move(INT16 axis, INT32 velocity, double acceleration);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				velocity: �̵� �ӵ�, [PPS]
				acceleration	: ������, �Ϲ������� velocity�� 5�� ����
				���ϰ�	: 0(FALSE)=���� ���� / 1(TRUE)=���� ����
				* ���� ���� ��� ������ �õ��ϸ� ���� ����
			----------------------------------------------------------------- */
	
	// ���� ����
    BOOL    CAMCset_stop(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				���ϰ�	: 0(FALSE)=���� / 1(TRUE)=����
			----------------------------------------------------------------- */

	// ���(��) ����
    BOOL    CAMCset_e_stop(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				���ϰ�	: 0(FALSE)=���� / 1(TRUE)=����
			----------------------------------------------------------------- */

	// Signal search 1 - ���� �ӵ�(���)���� ��ȣ ���� ����(1) ����
	BOOL    CAMCstart_signal_search1(INT16 axis, INT32 velocity, double acceleration, UINT8 detect_signal);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				velocity: �ӵ�, [PPS]
				acceleration	: ������
				detect_signal	: ���� ��ȣ
					(0x0)PElmNegativeEdge	: ������ ����Ʈ�� �ϰ� ��
					(0x1)NElmNegativeEdge	: ������ ����Ʈ�� �ϰ� ��
					(0x2)PSlmNegativeEdge	: ������ ���� ����Ʈ�� �ϰ� ��
					(0x3)NSlmNegativeEdge	: ������ ���� ����Ʈ�� �ϰ� ��
					(0x4)In0DownEdge		: IN0�� �ϰ� ��
					(0x5)In1DownEdge		: IN1�� �ϰ� ��
					(0x6)In2DownEdge		: IN2�� �ϰ� ��
					(0x7)In3DownEdge		: IN3�� �ϰ� ��
					(0x8)PElmPositiveEdge	: ������ ����Ʈ�� ��� ��
					(0x9)NElmPositiveEdge	: ������ ����Ʈ�� ��� ��
					(0xA)PSlmPositiveEdge	: ������ ���� ����Ʈ�� ��� ��
					(0xB)NSlmPositiveEdge	: ������ ���� ����Ʈ�� ��� ��
					(0xC)In0UpEdge			: IN0�� ��� ��
					(0xD)In1UpEdge			: IN1�� ��� ��
					(0xE)In2UpEdge			: IN2�� ��� ��
					(0xF)In3UpEdge			: IN3�� ��� ��
				���ϰ�	: ����
			----------------------------------------------------------------- */

	// Signal search 2 - Start/Stop �ӵ�(����)���� ��ȣ ���� ����(2) ����
	BOOL    CAMCstart_signal_search2(INT16 axis, INT32 velocity, UINT8 detect_signal);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				velocity: �ӵ�, [PPS]
				detect_signal	: ���� ��ȣ
					(0x0)PElmNegativeEdge	: ������ ����Ʈ�� �ϰ� ��
					(0x1)NElmNegativeEdge	: ������ ����Ʈ�� �ϰ� ��
					(0x2)PSlmNegativeEdge	: ������ ���� ����Ʈ�� �ϰ� ��
					(0x3)NSlmNegativeEdge	: ������ ���� ����Ʈ�� �ϰ� ��
					(0x4)In0DownEdge		: IN0�� �ϰ� ��
					(0x5)In1DownEdge		: IN1�� �ϰ� ��
					(0x6)In2DownEdge		: IN2�� �ϰ� ��
					(0x7)In3DownEdge		: IN3�� �ϰ� ��
					(0x8)PElmPositiveEdge	: ������ ����Ʈ�� ��� ��
					(0x9)NElmPositiveEdge	: ������ ����Ʈ�� ��� ��
					(0xA)PSlmPositiveEdge	: ������ ���� ����Ʈ�� ��� ��
					(0xB)NSlmPositiveEdge	: ������ ���� ����Ʈ�� ��� ��
					(0xC)In0UpEdge			: IN0�� ��� ��
					(0xD)In1UpEdge			: IN1�� ��� ��
					(0xE)In2UpEdge			: IN2�� ��� ��
					(0xF)In3UpEdge			: IN3�� ��� ��
				���ϰ�	: ����
			----------------------------------------------------------------- */
			
	// ���� ��� ��Ʈ�� �����͸� ����Ѵ�
	BOOL   CAMCset_output(INT16 axis, UINT8 value);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				value	: �����Ͱ�, 4��Ʈ�� ��ȿ�ϴ�
					Bit0 : OUT0 (SERVO ON)
					Bit1 : OUT1 (Alarm clear)
					Bit2 : OUT2
					Bit3 : OUT3
				���ϰ�	: 0(FALSE)=��� ���� / 1(TRUE)=��� ����
			----------------------------------------------------------------- */

//%	// ���� ��� ��Ʈ�� ����� �����͸� �о� ���δ�			
//%	UINT8  CAMCget_output(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				���ϰ�	: ��� ��Ʈ �����Ͱ�, 4��Ʈ�� ��ȿ�ϴ�
					Bit0 : OUT0 (SERVO ON)
					Bit1 : OUT1 (Alarm clear)
					Bit2 : OUT2
					Bit3 : OUT3
			----------------------------------------------------------------- */

	// ���� �Է� ��Ʈ���� �����͸� �о� ���δ�
	UINT8  CAMCget_input(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				���ϰ�	: �Է� ��Ʈ �����Ͱ�, 4��Ʈ�� ��ȿ�ϴ�
					Bit0 : IN0 (ORG)
					Bit1 : IN1 (Phase-Z)
					Bit2 : IN2
					Bit3 : IN3
			----------------------------------------------------------------- */

//%	// ���� ��� ��Ʈ�� ������ ��Ʈ�� ���¸� �о� ���δ�
//%	BOOL   CAMCoutput_bit_on(INT16 axis, UINT8 bitNo);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				bitNo	: ��Ʈ ��ġ
					0	: OUT0 (SERVO ON)
					1	: OUT1 (Alarm clear)
					2	: OUT2
					3	: OUT3
				���ϰ�	: 
					0(OFF)	= OFF
					1(ON)	= ON
			----------------------------------------------------------------- */

//%	// ���� �Է� ��Ʈ�� ������ ��Ʈ�� ���¸� �о� ���δ�
//%	BOOL   CAMCinput_bit_on(INT16 axis, UINT8 bitNo);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				bitNo	: ��Ʈ ��ġ
					0	: IN0 (ORG)
					1	: IN1 (Phase-Z)
					2	: IN2
					3	: IN3
				���ϰ�	: 
					0(OFF)	= OFF
					1(ON)	= ON
			----------------------------------------------------------------- */

//%	// ���� ��� ��Ʈ�� ������ ��Ʈ�� ON
//%	BOOL   CAMCset_output_bit(INT16 axis, UINT8 bitNo);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				bitNo	: ��Ʈ ��ġ
					0	: OUT0 (SERVO ON)
					1	: OUT1 (Alarm clear)
					2	: OUT2
					3	: OUT3
				���ϰ�	: 0(FALSE)=��� ���� / 1(TRUE)=��� ����
			----------------------------------------------------------------- */

//%	// ���� ��� ��Ʈ�� ������ ��Ʈ�� OFF
//%	BOOL   CAMCreset_output_bit(INT16 axis, UINT8 bitNo);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				bitNo	: ��Ʈ ��ġ
					0	: OUT0 (SERVO ON)
					1	: OUT1 (Alarm clear)
					2	: OUT2
					3	: OUT3
				���ϰ�	: 0(FALSE)=��� ���� / 1(TRUE)=��� ����
			----------------------------------------------------------------- */

//%	// ���� ��� ��Ʈ�� ������ ��Ʈ�� ON �Ǵ� OFF
//%	BOOL   CAMCchange_output_bit(INT16 axis, UINT8 bitNo, UINT8 state);
			/* -----------------------------------------------------------------
				axis    : ���ȣ
				bitNo	: ��Ʈ ��ġ
					0	: OUT0 (SERVO ON)
					1	: OUT1 (Alarm clear)
					2	: OUT2
					3	: OUT3
				state	: ��� ������
					0(OFF)	= OFF
					1(ON)	= ON
				���ϰ�	: 0(FALSE)=��� ���� / 1(TRUE)=��� ����
			----------------------------------------------------------------- */
#endif