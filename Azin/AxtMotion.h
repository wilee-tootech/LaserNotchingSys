#ifndef __AXT_MOTION_CAMC_H__
#define __AXT_MOTION_CAMC_H__

/*------------------------------------------------------------------------------------------------*
	CAMC-5M 및 CAMC-FS 라이브러리의 간단한 설명
	적용제품
		SMC-1V01 - CAMC-5M 1축
		SMC-2V01 - CAMC-5M 2축
		SMC-1V02 - CAMC-FS Ver1.0 1축
		SMC-2V02 - CAMC-FS Ver1.0 2축
		SMC-1V02 - CAMC-FS Ver2.0 이상 1축
		SMC-2V02 - CAMC-FS Ver2.0 이상 2축
	CAMC-5M은 함수의 접두어가 C5M이고, (예, C5Mget_actual_position(...))
	CAMC-FS Ver1.0은 함수의 접두어가 CAMC이고, (예, CFSget_actual_position(...))
	CAMC-FS Ver2.0이상은 함수의 접두어가 CAMC임, (예, CFS20get_actual_position(...))
	각 함수의 CAMC라고 표기되어 있는 부분이 접두어님
 *------------------------------------------------------------------------------------------------*/


/// 초기화 함수군

	/// Save/Load parameter
	BOOL	PASCAL EXPORT CAMCload_parameter(INT16 axis, char *nfilename);
	BOOL    PASCAL EXPORT CAMCsave_parameter(INT16 axis, char *nfilename); 
	BOOL    PASCAL EXPORT CAMCload_parameter_all(char *nfilename);
	BOOL    PASCAL EXPORT CAMCsave_parameter_all(char *nfilename); 
		//	nfilename	: 초기값을 저장/읽기를 수행할 파일명을 지정

	/// 보드 및 모듈 정보 함수군
	INT16	PASCAL EXPORT CAMCget_boardno(UINT32 address);
	INT16	PASCAL EXPORT CAMCget_numof_boards();
	INT16	PASCAL EXPORT CAMCget_numof_axes(INT16 board_id);
	INT16	PASCAL EXPORT CAMCget_total_numof_axis();
	INT16	PASCAL EXPORT CAMCget_axisno(INT16 nBoardNo, INT16 nModuleNo);
	BOOL    PASCAL EXPORT CAMCget_axis_info(INT16 nAxisNo, INT16 *nBoardNo, INT16 *nModuleNo, UINT8   *bModuleID, INT16 *nAxisPos);

	// 메인 클럭 설정 - 기본값은 16.384 MHz
	void	PASCAL EXPORT CAMCKeSetMainClk(INT32 nMainClk);
		//	clk		: CAMC-FS에 공급되는 클럭, 16.384 MHz
		//				16384000L(F_16_384M_CLK)	= 16.384 MHz
		//				32768000L(F_32_768M_CLK)	= 32.768 MHz

	/// Drive mode 1, 2
	void	PASCAL EXPORT CAMCset_drive_mode1(INT16 axis, 
				UINT8 decelstartpoint,
				UINT8 pulseoutmethod,
				UINT8 detectsignal);
		// decelstartpoint	:
		//		0(AutoDetect)	= 자동검출
		//		1(RestPulse)	= 잔량펄스
		// pulseoutmethod	: 펄스 출력 방식
		//		0(OneHighLowHigh)		= 1펄스 방식, PULSE(Active High), 정방향(DIR=Low)  / 역방향(DIR=High)
		//		1(OneHighHighLow(0x1)	= 1펄스 방식, PULSE(Active High), 정방향(DIR=High) / 역방향(DIR=Low)
		//		2(OneLowLowHigh(0x2)	= 1펄스 방식, PULSE(Active Low),  정방향(DIR=Low)  / 역방향(DIR=High)
		//		3(OneLowHighLow(0x3)	= 1펄스 방식, PULSE(Active Low),  정방향(DIR=High) / 역방향(DIR=Low)
		//		4(TwoCcwCwHigh(0x4)		= 2펄스 방식, PULSE(CCW:역방향),  DIR(CW:정방향),  Active High	 
		//		5(TwoCcwCwLow(0x5)		= 2펄스 방식, PULSE(CCW:역방향),  DIR(CW:정방향),  Active Low	 
		//		6(TwoCwCcwHigh(0x6)		= 2펄스 방식, PULSE(CW:정방향),   DIR(CCW:역방향), Active High
		//		7(TwoCwCcwLow(0x7)		= 2펄스 방식, PULSE(CW:정방향),   DIR(CCW:역방향), Active Low
		// detectsignal)	: Signal search 1/2에서 사용하는 검출신호
		//		0h(PElmNegativeEdge    = +Elm(End limit) 하강 edge
		//		1h(NElmNegativeEdge    = -Elm(End limit) 하강 edge
		//		2h(PSlmNegativeEdge    = +Slm(Slowdown limit) 하강 edge
		//		3h(NSlmNegativeEdge    = -Slm(Slowdown limit) 하강 edge
		//		4h(In0DownEdge         = IN0(ORG) 하강 edge
		//		5h(In1DownEdge         = IN1(Z상) 하강 edge
		//		6h(In2DownEdge         = IN2(범용) 하강 edge
		//		7h(In3DownEdge         = IN3(범용) 하강 edge
		//		8h(PElmPositiveEdge    = +Elm(End limit) 상승 edge
		//		9h(NElmPositiveEdge    = -Elm(End limit) 상승 edge
		//		Ah(PSlmPositiveEdge    = +Slm(Slowdown limit) 상승 edge
		//		Bh(NSlmPositiveEdge    = -Slm(Slowdown limit) 상승 edge
		//		Ch(In0UpEdge           = IN0(ORG) 상승 edge
		//		Dh(In1UpEdge           = IN1(Z상) 상승 edge
		//		Eh(In2UpEdge           = IN2(범용) 상승 edge
		//		Fh(In3UpEdge           = IN3(범용) 상승 edge
	UINT8	PASCAL EXPORT CAMCget_drive_mode1(INT16 axis);
	void	PASCAL EXPORT CAMCset_drive_mode2(INT16 axis, 
				UINT8 encmethod,
				UINT8 inpactivelevel,
				UINT8 alarmactivelevel,
				UINT8 nslmactivelevel,
				UINT8 pslmactivelevel,
				UINT8 nelmactivelevel,
				UINT8 pelmactivelevel);
		// encmethod		: 엔코더 입력 방식
		//		0(UpDownMode)		= Up/Down
		//		1(Sqr1Mode)			= 1체배
		//		2(Sqr2Mode)			= 2체배
		//		3(Sqr4Mode)			= 4체배
 		// inpactivelevel	: INP신호 액티브레벨
 		//		0(InpActiveLow)		= Active low
		//		1(InpActiveHigh)	= Active high
		// alarmactivelevel	: ALARM신호 액티브레벨
		//		0(AlmActiveLow)		= Active low
		//		1(AlmActiveHigh)	= Active high
		// nslmactivelevel	: -SLM(Slowdown limit)신호 액티브레벨
		//		0(NSlmActiveLow)	= Active low
		//		1(NSlmActiveHigh)	= Active high
		// pslmactivelevel	: +SLM(Slowdown limit)신호 액티브레벨
		//		0(PSlmActiveLow)	= Active low
		//		1(PSlmActiveHigh)	= Active high
		// nelmactivelevel	: -ELM(End limit)신호 액티브레벨
		//		0(NElmActiveLow)	= Active low
		//		1(NElmActiveHigh)	= Active high
		// pelmactivelevel	: +ELM(End limit)신호 액티브레벨
		//		0(PElmActiveLow)	= Active low
		//		1(PElmActiveHigh)	= Active high
	UINT8	PASCAL EXPORT CAMCget_drive_mode2(INT16 axis);

	/// 상태 함수군
	UINT8	PASCAL EXPORT CAMCget_drive_status(INT16 axis);
	UINT16	PASCAL EXPORT CAMCget_end_status(INT16 axis);
	INT32	PASCAL EXPORT CAMCget_drive_pulse_counts(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_mechanical_signal(INT16 axis);
	double	PASCAL EXPORT CAMCget_velocity(INT16 axis);
	double	PASCAL EXPORT CAMCget_error(INT16 axis);
/*
/// 상태 함수군
	// 모션 구동 상태를 읽는다
	UINT8	PASCAL EXPORT CAMCget_drive_status(INT16 axis);
		//	리턴값	: 드라이브 상태
		//		Bit 0 : Busy, 1=모션 구동 중
		//		Bit 1 : Down, 1=감속 중
		//		Bit 2 : Const, 1=정속 중
		//		Bit 3 : Up, 1=가속중
		//		Bit 4 : ICL, 1=내부 위치 카운터 비교값 > 내부 위치 카운터값
		//		Bit 5 : ICG, 1=내부 위치 카운터 비교값 < 내부 위치 카운터값
		//		Bit 6 : ECL, 1=외부 위치 카운터 비교값 > 외부 위치 카운터값
		//		Bit 7 : ECG, 1=외부 위치 카운터 비교값 < 외부 위치 카운터값
	
	// 모션 완료 상태를 읽는다
	UINT16	PASCAL EXPORT CAMCget_end_status(INT16 axis);
		//	리턴값	: 드라이브 상태
		//		Bit 0 : 1=감속 리미트 신호 입력에 의한 종료
		//		Bit 1 : 1=리미트 신호 입력에 의한 종료
		//		Bit 2 : 1=감속 정지 신호 입력에 의한 종료
		//		Bit 3 : 1=급정지 신호 입력에 의한 종료
		//		Bit 4 : 1=감속 정지 명령에 의한 종료
		//		Bit 5 : 1=급정지 명령에 의한 종료
		//		Bit 6 : 1=Alarm 신호 입력에 의한 종료
		//		Bit 7 : 1=데이터 설정 에러에 의한 종료
		//		Bit 8 : 1=탈조 에러에 의한 종료
		//		Bit 9 : 1=Reserved
		//		Bit 10: 1=신호 검출에 의한 종료
		//		모든비트가 0이면 에러 없음
*/

	// 최대 속도 설정/검색
	BOOL    PASCAL EXPORT CAMCset_max_speed(INT16 axis, double max_velocity);
	double	PASCAL EXPORT CAMCget_max_speed(INT16 axis);

	// 축 동기 함수
	BOOL    PASCAL EXPORT CAMCset_axis_sync(INT16 nLen, INT16 *aAxis);
	BOOL    PASCAL EXPORT CAMCreset_axis_sync(INT16 nLen, INT16 *aAxis);

	/// 한축에 대한 사다리꼴 구동함수군
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

	/// 한축에 대한 S자형 구동함수군
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

	/// 한축에 대한 기타함수군
	void	PASCAL EXPORT CAMCset_startstop_speed(INT16 axis, double velocity);
	double	PASCAL EXPORT CAMCget_startstop_speed(INT16 axis);
	void	PASCAL EXPORT CAMCset_moveunit_perpulse(INT16 axis, double unitperpulse);
	double	PASCAL EXPORT CAMCget_moveunit_perpulse(INT16 axis);
	void	PASCAL EXPORT CAMCset_movepulse_perunit(INT16 axis, INT32 pulseperunit);
	INT32	PASCAL EXPORT CAMCget_movepulse_perunit(INT16 axis);
	void	PASCAL EXPORT CAMCset_s_rate(INT16 axis, double a_percent, double b_percent);
	void	PASCAL EXPORT CAMCget_s_rate(INT16 axis, double *a_percent, double *b_percent);
	UINT8	PASCAL EXPORT CAMCwait_for_done(INT16 axis);

	/// 여러축에 대한 사다리꼴형 구동함수군
	BOOL    PASCAL EXPORT CAMCstart_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
	BOOL    PASCAL EXPORT CAMCstart_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
	UINT8	PASCAL EXPORT CAMCmove_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
	UINT8	PASCAL EXPORT CAMCmove_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
	BOOL    PASCAL EXPORT CAMCstart_r_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
	BOOL    PASCAL EXPORT CAMCstart_r_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
	UINT8	PASCAL EXPORT CAMCr_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
	UINT8	PASCAL EXPORT CAMCr_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);

	/// 여러축에 대한 S자형 구동함수군
	BOOL    PASCAL EXPORT CAMCstart_s_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
	BOOL    PASCAL EXPORT CAMCstart_s_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
	UINT8	PASCAL EXPORT CAMCs_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
	UINT8	PASCAL EXPORT CAMCs_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
	BOOL    PASCAL EXPORT CAMCstart_rs_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
	BOOL    PASCAL EXPORT CAMCstart_rs_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
	UINT8	PASCAL EXPORT CAMCrs_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
	UINT8	PASCAL EXPORT CAMCrs_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);

	/// 여러축에 대한 기타 함수군
	UINT8	PASCAL EXPORT CAMCwait_for_all(INT16 number, INT16 *axes);
	void	PASCAL EXPORT CAMCset_s_rate_all(INT16 number, INT16 *axes, double *a_percent, double *b_percent);
	void	PASCAL EXPORT CAMCget_s_rate_all(INT16 number, INT16 *axes, double *a_percent, double *b_percent);

	/// 정속도 구동 함수군
	BOOL    PASCAL EXPORT CAMCv_move(INT16 axis, double velocity, double acceleration);
	BOOL    PASCAL EXPORT CAMCv_move_ex(INT16 axis, double velocity, double acceltime);
	BOOL    PASCAL EXPORT CAMCv_s_move(INT16 axis, double velocity, double acceleration);
	BOOL    PASCAL EXPORT CAMCv_s_move_ex(INT16 axis, double velocity, double acceltime);
        
	/// 특정 좌표계에 대한 설정함수군
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

	/// 특정 좌표계에 대한 구동함수군
	BOOL    PASCAL EXPORT CAMCstart_move_2(INT16 coordinate, double x, double y);
	BOOL    PASCAL EXPORT CAMCstart_move_3(INT16 coordinate, double x, double y, double z);
	BOOL    PASCAL EXPORT CAMCstart_move_4(INT16 coordinate, double x, double y, double z, double w);
	BOOL    PASCAL EXPORT CAMCmove_2(INT16 coordinate, double x, double y);
	BOOL    PASCAL EXPORT CAMCmove_3(INT16 coordinate, double x, double y, double z);
	BOOL    PASCAL EXPORT CAMCmove_4(INT16 coordinate, double x, double y, double z, double w);

	/// 특정 좌표계에 대한 기타함수군
	double	PASCAL EXPORT CAMCco_get_velocity(INT16 coordinate);
	BOOL    PASCAL EXPORT CAMCco_motion_done(INT16 coordinate);
	BOOL    PASCAL EXPORT CAMCco_wait_for_done(INT16 coordinate);

	/// 위치 데이타 함수군
	void	PASCAL EXPORT CAMCset_command_position(INT16 axis, double position);
	double	PASCAL EXPORT CAMCget_command_position(INT16 axis);
	void	PASCAL EXPORT CAMCset_actual_position(INT16 axis, double position);
	double	PASCAL EXPORT CAMCget_actual_position(INT16 axis);

	/// 구동 상태 함수군
	BOOL    PASCAL EXPORT CAMCin_motion(INT16 axis);
	BOOL    PASCAL EXPORT CAMCmotion_done(INT16 axis);
	BOOL    PASCAL EXPORT CAMCin_position(INT16 axis);

	/// 정지 함수군
	BOOL    PASCAL EXPORT CAMCset_stop(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_stop_decel(INT16 axis, double deceleration);
	BOOL    PASCAL EXPORT CAMCset_stop_deceltime(INT16 axis, double deceltime);
	BOOL    PASCAL EXPORT CAMCset_e_stop(INT16 axis);
	BOOL    PASCAL EXPORT CAMCemergency_stop();

	/// 범용 입출력 제어함수군
	BOOL    PASCAL EXPORT CAMCset_output(INT16 axis, UINT8 value);
	UINT8	PASCAL EXPORT CAMCget_output(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_input(INT16 axis);
	BOOL    PASCAL EXPORT CAMCoutput_bit_on(INT16 axis, UINT8 bitNo);
	BOOL    PASCAL EXPORT CAMCinput_bit_on(INT16 axis, UINT8 bitNo);
	BOOL    PASCAL EXPORT CAMCset_output_bit(INT16 axis, UINT8 bitNo);
	BOOL    PASCAL EXPORT CAMCreset_output_bit(INT16 axis, UINT8 bitNo);
	BOOL    PASCAL EXPORT CAMCchange_output_bit(INT16 axis, UINT8 bitNo, UINT8 state);

	/// 마스터/슬레이브 지정함수군
	BOOL    PASCAL EXPORT CAMClink(INT16 master, INT16 slave, double ratio);
	BOOL    PASCAL EXPORT CAMCendlink(INT16 slave);

	/// 리미트 함수군
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

	/// 인포지션(Inposition) 함수군
	BOOL    PASCAL EXPORT CAMCset_inposition_enable(INT16 axis, UINT8 use);
	UINT8	PASCAL EXPORT CAMCget_inposition_enable(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_inposition_level(INT16 axis, UINT8 level);
	UINT8	PASCAL EXPORT CAMCget_inposition_level(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_inposition_switch(INT16 axis);

	/// 서보(SERVO-ON) 함수군
	BOOL    PASCAL EXPORT CAMCset_servo_enable(INT16 axis, UINT8   state);
	UINT8	PASCAL EXPORT CAMCget_servo_enable(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_servo_level(INT16 axis, UINT8 level);
	UINT8	PASCAL EXPORT CAMCget_servo_level(INT16 axis);

	/// 구동 모드 설정 함수군
	BOOL    PASCAL EXPORT CAMCset_decel_point(INT16 axis, UINT8 method);
	UINT8	PASCAL EXPORT CAMCget_decel_point(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_pulse_out_method(INT16 axis, UINT8 method);
	UINT8	PASCAL EXPORT CAMCget_pulse_out_method(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_enc_input_method(INT16 axis, UINT8 method);
	UINT8	PASCAL EXPORT CAMCget_enc_input_method(INT16 axis);

	/// 알람(Alarm) 함수군
	BOOL    PASCAL EXPORT CAMCset_alarm_enable(INT16 axis, UINT8 use);
	UINT8	PASCAL EXPORT CAMCget_alarm_enable(INT16 axis);
	BOOL    PASCAL EXPORT CAMCset_alarm_level(INT16 axis, UINT8 level);
	UINT8	PASCAL EXPORT CAMCget_alarm_level(INT16 axis);
	UINT8	PASCAL EXPORT CAMCget_alarm_switch(INT16 axis);

	/// 원점 검색 함수군
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

	/// 오버라이드 관련 함수군
	BOOL    PASCAL EXPORT CAMCposition_override(INT16 axis, double overrideposition);
	BOOL    PASCAL EXPORT CAMCposition_r_override(INT16 axis, double overridedistance);
	double	PASCAL EXPORT CAMCget_drivedistance(INT16 axis);

	/// 트리거 관련 함수군
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

	/// Internal/External comparator 관련 함수군
	void	PASCAL EXPORT CAMCset_internal_comparator_position(INT16 axis, double position);
	double	PASCAL EXPORT CAMCget_internal_comparator_position(INT16 axis);
	void	PASCAL EXPORT CAMCset_external_comparator_position(INT16 axis, double position);
	double	PASCAL EXPORT CAMCget_external_comparator_position(INT16 axis);

	/// crc 관련 함수군
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
	
	// 초기 구동 속도 설정
	void    CAMCset_startstop_speed(INT16 axis, INT32 velocity);
			/* -----------------------------------------------------------------
				axis    : 축번호
				velocity: Start/Stop speed, [PPS]
				리턴값	: 0(FALSE)=설정 실패 / 1(TRUE)=설정 성공
				* Object(구동) 속도와 동일하면 등속 구동을 하게 된다
			----------------------------------------------------------------- */

	// 펄스 출력 방식(1/2펄스 등) 설정 
	BOOL    CAMCset_pulse_out_method(INT16 axis, UINT8 method);
			/* -----------------------------------------------------------------
				axis    : 축번호
				method	: 모드
					0(OneHighLowHigh)	= 1펄스 방식, PULSE(Active High), 정방향(DIR=Low)  / 역방향(DIR=High)
					1(OneHighHighLow)   = 1펄스 방식, PULSE(Active High), 정방향(DIR=High) / 역방향(DIR=Low)
					2(OneLowLowHigh)    = 1펄스 방식, PULSE(Active Low),  정방향(DIR=Low)  / 역방향(DIR=High)
					3(OneLowHighLow)    = 1펄스 방식, PULSE(Active Low),  정방향(DIR=High) / 역방향(DIR=Low)
					4(TwoCcwCwHigh)     = 2펄스 방식, PULSE(CCW:역방향),  DIR(CW:정방향),  Active High
					5(TwoCcwCwLow)      = 2펄스 방식, PULSE(CCW:역방향),  DIR(CW:정방향),  Active Low
					6(TwoCwCcwHigh)     = 2펄스 방식, PULSE(CW:정방향),   DIR(CCW:역방향), Active High
					7(TwoCwCcwLow)      = 2펄스 방식, PULSE(CW:정방향),   DIR(CCW:역방향), Active Low
				리턴값	: 없음
			----------------------------------------------------------------- */
	
	// 엔코더 방식 설정(1/2/4체배 등)
	BOOL    CAMCset_enc_input_method(INT16 axis, UINT8 method);
			/* -----------------------------------------------------------------
				axis    : 축번호
				method	: 모드
					1(Sqr1Mode)		= 1체배
					2(Sqr2Mode)		= 2체배
					3(Sqr4Mode)		= 4체배
				리턴값	: 없음
			----------------------------------------------------------------- */

	// 리미트(End limit) 센서의 입력을 허용할 것인지를 설정
	BOOL    CAMCset_end_limit_enable(INT16 axis, UINT8 use);
			/* -----------------------------------------------------------------
				axis    : 축번호
				use		: 사용 유무
					0(ON)	= 사용하지 않음
					1(OFF)	= 사용함
				리턴값	: 0(FALSE)=설정 실패 / 1(TRUE)=설정 성공
			----------------------------------------------------------------- */

	// 감속리미트(Slow down limit) 센서의 입력을 허용할 것인지를 설정
	BOOL    CAMCset_slow_limit_enable(INT16 axis, UINT8 use);
			/* -----------------------------------------------------------------
				axis    : 축번호
				use		: 사용 유무
					0(ON)	= 사용하지 않음
					1(OFF)	= 사용함
				리턴값	: 0(FALSE)=설정 실패 / 1(TRUE)=설정 성공
			----------------------------------------------------------------- */
	
	// Inposition 입력을 허용할 것인지를 설정 - 허용 시 Inposition 입력이 Active 되어야 Busy 완료가 된다
	BOOL    CAMCset_inposition_enable(INT16 axis, UINT8 use);
			/* -----------------------------------------------------------------
				axis    : 축번호
				use		: 사용 유무
					0(ON)	= 사용하지 않음
					1(OFF)	= 사용함
				리턴값	: 0(FALSE)=설정 실패 / 1(TRUE)=설정 성공
			----------------------------------------------------------------- */

	// Alarm 입력을 허용할 것인지를 설정 - 허용 시 Alarm 입력이 Active 되면 펄스 출력 중지
	BOOL    CAMCset_alarm_enable(INT16 axis, UINT8 use);
			/* -----------------------------------------------------------------
				axis    : 축번호
				use		: 사용 유무
					0(ON)	= 사용하지 않음
					1(OFF)	= 사용함
				리턴값	: 0(FALSE)=설정 실패 / 1(TRUE)=설정 성공
			----------------------------------------------------------------- */

	// 최대 속도 제한 설정
	BOOL    CAMCset_max_speed(INT16 axis, INT32 max_velocity);
			/* -----------------------------------------------------------------
				axis    : 축번호
				max_velocity	: 최대 속도, [PPS]
				리턴값	: 0(FALSE)=설정 실패 / 1(TRUE)=설정 성공
				* Range 및 구동에 영향을 주므로 주의
			----------------------------------------------------------------- */


	////////////////////////////////////////////////////////////////////////////////////////////////
	/// 위치 제어 함수
	// Command(Internal) 위치 설정 / 검색
	void    CAMCset_command_position(INT16 axis, INT32 position);
			/* -----------------------------------------------------------------
				axis    : 축번호
				position: 설정하고자 하는 위치, [PULSE]
				리턴값	: 없음
			----------------------------------------------------------------- */
	INT32  CAMCget_command_position(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : 축번호
				리턴값	: 현재 위치, [PULSE]
			----------------------------------------------------------------- */
	
	// Actual(External) 위치 설정 / 검색
	void    CAMCset_actual_position(INT16 axis, INT32 position);
			/* -----------------------------------------------------------------
				axis    : 축번호
				position: 설정하고자 하는 위치, [PULSE]
				리턴값	: 없음
			----------------------------------------------------------------- */
	INT32  CAMCget_actual_position(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : 축번호
				리턴값	: 현재 위치, [PULSE]
			----------------------------------------------------------------- */

	// 비교 위치 설정
	void    CAMCset_internal_comparator_position(INT16 axis, INT32 position);
			/* -----------------------------------------------------------------
				axis    : 축번호
				position: 설정하고자 하는 비교 위치, [PULSE]
				리턴값	: 없음
			----------------------------------------------------------------- */
	void    CAMCset_external_comparator_position(INT16 axis, INT32 position);
			/* -----------------------------------------------------------------
				axis    : 축번호
				position: 설정하고자 하는 비교 위치, [PULSE]
				리턴값	: 없음
			----------------------------------------------------------------- */


	////////////////////////////////////////////////////////////////////////////////////////////////
	/// 상태 확인 함수
	// 모션 구동중 ?
	BOOL    CAMCin_motion(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : 축번호
				리턴값	: 0(FALSE)=모션 구동중, 1(TRUE)=모션 완료
			----------------------------------------------------------------- */
	
	// 모션 구동 완료 ?
	BOOL    CAMCmotion_done(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : 축번호
				리턴값	: 0(FALSE)=모션 완료, 1(TRUE)=모션 구동중
				CAMCin_motion() 함수와 반대값을 리턴
			----------------------------------------------------------------- */
	
	
	// Get mechanical signal
	UINT8   CAMCget_mechanical_signal(INT16 axis);

	// Get current speed
	UINT32	CAMCget_velocity(INT16 axis);

	////////////////////////////////////////////////////////////////////////////////////////////////
	/// 모션 구동 함수
	// 사다리꼴 가감속 구동 - 절대 좌표
	BOOL    CAMCstart_move(INT16 axis, INT32 position, INT32 velocity, double acceleration);
			/* -----------------------------------------------------------------
				axis    : 축번호
				position: 이동할 위치, 절대 좌표, [PULSE]
				velocity: 이동 속도, [PPS]
				acceleration	: 가속율, 일반적으로 velocity의 10배 설정
				리턴값	: 0(FALSE)=구동 실패 / 1(TRUE)=구동 성공
				* 구동 중일 경우 구동을 시도하면 구동 실패
			----------------------------------------------------------------- */

//%	// 사다리꼴 가감속 구동 - 상대 좌표
//%	BOOL    CAMCstart_r_move(INT16 axis, INT32 distance, INT32 velocity, double acceleration);
			/* -----------------------------------------------------------------
				axis    : 축번호
				distance: 이동할 거리, 상대 좌표, [PULSE]
				velocity: 이동 속도, [PPS]
				acceleration	: 가속율, 일반적으로 velocity의 10배 설정
				리턴값	: 0(FALSE)=구동 실패 / 1(TRUE)=구동 성공
				* 구동 중일 경우 구동을 시도하면 구동 실패
			----------------------------------------------------------------- */

	// 대칭 포물선(S-Curve) 가감속 구동 - 절대 좌표
	BOOL    CAMCstart_s_move(INT16 axis, INT32 position, INT32 velocity, double acceleration);
			/* -----------------------------------------------------------------
				axis    : 축번호
				position: 이동할 위치, 절대 좌표, [PULSE]
				velocity: 이동 속도, [PPS]
				acceleration	: 가속율, 일반적으로 velocity의 5배 설정
				리턴값	: 0(FALSE)=구동 실패 / 1(TRUE)=구동 성공
				* 구동 중일 경우 구동을 시도하면 구동 실패
			----------------------------------------------------------------- */

//%	// 대칭 포물선(S-Curve) 가감속 구동 - 상대 좌표
//%	BOOL    CAMCstart_rs_move(INT16 axis, INT32 distance, INT32 velocity, double acceleration);
			/* -----------------------------------------------------------------
				axis    : 축번호
				distance: 이동할 거리, 상대 좌표, [PULSE]
				velocity: 이동 속도, [PPS]
				acceleration	: 가속율, 일반적으로 velocity의 5배 설정
				리턴값	: 0(FALSE)=구동 실패 / 1(TRUE)=구동 성공
				* 구동 중일 경우 구동을 시도하면 구동 실패
			----------------------------------------------------------------- */

	// 비대칭 포물선(S-Curve) 가감속 구동 - 절대 좌표
	BOOL    CAMCstart_as_move(INT16 axis, INT32 position, INT32 velocity, double acceleration, double deceleration);
			/* -----------------------------------------------------------------
				axis    : 축번호
				position: 이동할 위치, 절대 좌표, [PULSE]
				velocity: 이동 속도, [PPS]
				acceleration	: 가속율, 일반적으로 velocity의 5배 설정
				deceleration	: 감속율, 일반적으로 velocity의 5배 설정
				리턴값	: 0(FALSE)=구동 실패 / 1(TRUE)=구동 성공
				* 구동 중일 경우 구동을 시도하면 구동 실패
			----------------------------------------------------------------- */

//%	// 비대칭 포물선(S-Curve) 가감속 구동 - 상대 좌표
//%	BOOL    CAMCstart_ras_move(INT16 axis, INT32 distance, INT32 velocity, double acceleration, double deceleration);
			/* -----------------------------------------------------------------
				axis    : 축번호
				distance: 이동할 거리, 상대 좌표, [PULSE]
				velocity: 이동 속도, [PPS]
				acceleration	: 가속율, 일반적으로 velocity의 5배 설정
				deceleration	: 감속율, 일반적으로 velocity의 5배 설정
				리턴값	: 0(FALSE)=구동 실패 / 1(TRUE)=구동 성공
				* 구동 중일 경우 구동을 시도하면 구동 실패
			----------------------------------------------------------------- */
	
	// 대칭 포물선(S-Curve) 가감속 구동 - 절대 좌표, 연속(Continuous) 구동
	BOOL CAMCv_s_move(INT16 axis, INT32 velocity, double acceleration);
			/* -----------------------------------------------------------------
				axis    : 축번호
				velocity: 이동 속도, [PPS]
				acceleration	: 가속율, 일반적으로 velocity의 5배 설정
				리턴값	: 0(FALSE)=구동 실패 / 1(TRUE)=구동 성공
				* 구동 중일 경우 구동을 시도하면 구동 실패
			----------------------------------------------------------------- */
	
	// 감속 정지
    BOOL    CAMCset_stop(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : 축번호
				리턴값	: 0(FALSE)=실패 / 1(TRUE)=성공
			----------------------------------------------------------------- */

	// 비상(급) 정지
    BOOL    CAMCset_e_stop(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : 축번호
				리턴값	: 0(FALSE)=실패 / 1(TRUE)=성공
			----------------------------------------------------------------- */

	// Signal search 1 - 지정 속도(고속)으로 신호 검출 구동(1) 수행
	BOOL    CAMCstart_signal_search1(INT16 axis, INT32 velocity, double acceleration, UINT8 detect_signal);
			/* -----------------------------------------------------------------
				axis    : 축번호
				velocity: 속도, [PPS]
				acceleration	: 가속율
				detect_signal	: 검출 신호
					(0x0)PElmNegativeEdge	: 정방향 리미트의 하강 시
					(0x1)NElmNegativeEdge	: 역방향 리미트의 하강 시
					(0x2)PSlmNegativeEdge	: 정방향 감속 리미트의 하강 시
					(0x3)NSlmNegativeEdge	: 역방향 감속 리미트의 하강 시
					(0x4)In0DownEdge		: IN0의 하강 시
					(0x5)In1DownEdge		: IN1의 하강 시
					(0x6)In2DownEdge		: IN2의 하강 시
					(0x7)In3DownEdge		: IN3의 하강 시
					(0x8)PElmPositiveEdge	: 정방향 리미트의 상승 시
					(0x9)NElmPositiveEdge	: 역방향 리미트의 상승 시
					(0xA)PSlmPositiveEdge	: 정방향 감속 리미트의 상승 시
					(0xB)NSlmPositiveEdge	: 역방향 감속 리미트의 상승 시
					(0xC)In0UpEdge			: IN0의 상승 시
					(0xD)In1UpEdge			: IN1의 상승 시
					(0xE)In2UpEdge			: IN2의 상승 시
					(0xF)In3UpEdge			: IN3의 상승 시
				리턴값	: 없음
			----------------------------------------------------------------- */

	// Signal search 2 - Start/Stop 속도(저속)으로 신호 검출 구동(2) 수행
	BOOL    CAMCstart_signal_search2(INT16 axis, INT32 velocity, UINT8 detect_signal);
			/* -----------------------------------------------------------------
				axis    : 축번호
				velocity: 속도, [PPS]
				detect_signal	: 검출 신호
					(0x0)PElmNegativeEdge	: 정방향 리미트의 하강 시
					(0x1)NElmNegativeEdge	: 역방향 리미트의 하강 시
					(0x2)PSlmNegativeEdge	: 정방향 감속 리미트의 하강 시
					(0x3)NSlmNegativeEdge	: 역방향 감속 리미트의 하강 시
					(0x4)In0DownEdge		: IN0의 하강 시
					(0x5)In1DownEdge		: IN1의 하강 시
					(0x6)In2DownEdge		: IN2의 하강 시
					(0x7)In3DownEdge		: IN3의 하강 시
					(0x8)PElmPositiveEdge	: 정방향 리미트의 상승 시
					(0x9)NElmPositiveEdge	: 역방향 리미트의 상승 시
					(0xA)PSlmPositiveEdge	: 정방향 감속 리미트의 상승 시
					(0xB)NSlmPositiveEdge	: 역방향 감속 리미트의 상승 시
					(0xC)In0UpEdge			: IN0의 상승 시
					(0xD)In1UpEdge			: IN1의 상승 시
					(0xE)In2UpEdge			: IN2의 상승 시
					(0xF)In3UpEdge			: IN3의 상승 시
				리턴값	: 없음
			----------------------------------------------------------------- */
			
	// 범용 출력 포트에 데이터를 출력한다
	BOOL   CAMCset_output(INT16 axis, UINT8 value);
			/* -----------------------------------------------------------------
				axis    : 축번호
				value	: 데이터값, 4비트만 유효하다
					Bit0 : OUT0 (SERVO ON)
					Bit1 : OUT1 (Alarm clear)
					Bit2 : OUT2
					Bit3 : OUT3
				리턴값	: 0(FALSE)=출력 실패 / 1(TRUE)=출력 성공
			----------------------------------------------------------------- */

//%	// 범용 출력 포트에 출력한 데이터를 읽어 들인다			
//%	UINT8  CAMCget_output(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : 축번호
				리턴값	: 출력 포트 데이터값, 4비트만 유효하다
					Bit0 : OUT0 (SERVO ON)
					Bit1 : OUT1 (Alarm clear)
					Bit2 : OUT2
					Bit3 : OUT3
			----------------------------------------------------------------- */

	// 범용 입력 포트에서 데이터를 읽어 들인다
	UINT8  CAMCget_input(INT16 axis);
			/* -----------------------------------------------------------------
				axis    : 축번호
				리턴값	: 입력 포트 데이터값, 4비트만 유효하다
					Bit0 : IN0 (ORG)
					Bit1 : IN1 (Phase-Z)
					Bit2 : IN2
					Bit3 : IN3
			----------------------------------------------------------------- */

//%	// 범용 출력 포트의 지정한 비트의 상태를 읽어 들인다
//%	BOOL   CAMCoutput_bit_on(INT16 axis, UINT8 bitNo);
			/* -----------------------------------------------------------------
				axis    : 축번호
				bitNo	: 비트 위치
					0	: OUT0 (SERVO ON)
					1	: OUT1 (Alarm clear)
					2	: OUT2
					3	: OUT3
				리턴값	: 
					0(OFF)	= OFF
					1(ON)	= ON
			----------------------------------------------------------------- */

//%	// 범용 입력 포트의 지정한 비트의 상태를 읽어 들인다
//%	BOOL   CAMCinput_bit_on(INT16 axis, UINT8 bitNo);
			/* -----------------------------------------------------------------
				axis    : 축번호
				bitNo	: 비트 위치
					0	: IN0 (ORG)
					1	: IN1 (Phase-Z)
					2	: IN2
					3	: IN3
				리턴값	: 
					0(OFF)	= OFF
					1(ON)	= ON
			----------------------------------------------------------------- */

//%	// 범용 출력 포트의 지정한 비트를 ON
//%	BOOL   CAMCset_output_bit(INT16 axis, UINT8 bitNo);
			/* -----------------------------------------------------------------
				axis    : 축번호
				bitNo	: 비트 위치
					0	: OUT0 (SERVO ON)
					1	: OUT1 (Alarm clear)
					2	: OUT2
					3	: OUT3
				리턴값	: 0(FALSE)=출력 실패 / 1(TRUE)=출력 성공
			----------------------------------------------------------------- */

//%	// 범용 출력 포트의 지정한 비트를 OFF
//%	BOOL   CAMCreset_output_bit(INT16 axis, UINT8 bitNo);
			/* -----------------------------------------------------------------
				axis    : 축번호
				bitNo	: 비트 위치
					0	: OUT0 (SERVO ON)
					1	: OUT1 (Alarm clear)
					2	: OUT2
					3	: OUT3
				리턴값	: 0(FALSE)=출력 실패 / 1(TRUE)=출력 성공
			----------------------------------------------------------------- */

//%	// 범용 출력 포트의 지정한 비트를 ON 또는 OFF
//%	BOOL   CAMCchange_output_bit(INT16 axis, UINT8 bitNo, UINT8 state);
			/* -----------------------------------------------------------------
				axis    : 축번호
				bitNo	: 비트 위치
					0	: OUT0 (SERVO ON)
					1	: OUT1 (Alarm clear)
					2	: OUT2
					3	: OUT3
				state	: 출력 데이터
					0(OFF)	= OFF
					1(ON)	= ON
				리턴값	: 0(FALSE)=출력 실패 / 1(TRUE)=출력 성공
			----------------------------------------------------------------- */
#endif