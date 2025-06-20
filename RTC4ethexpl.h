//-----------------------------------------------------------------------------
//  File: RTC4ethexpl.h                           Copyright (c) 2015 SCANLAB AG
//-----------------------------------------------------------------------------
//
//
//
//  Abstract
//      RTC4eth function prototypes for explicitly linking - also known as
//      dynamic load linking - to the RTC4ethDLL.DLL
//
//  Authors
//      Gerald Schmid
//
//  Revision History
//      +-----+---------+--------+------------------------------------------+
//      | Mod |  Date   | Author | Description                              |
//      +-----+---------+--------+------------------------------------------+
//      | 0.0 | 28Jan15 | GS     | * initial release                        |
//      |     |         |        |                                          |
//      +-----+---------+--------+------------------------------------------+
//
//-----------------------------------------------------------------------------

//------------------------ DLL Handling ---------------------------------------

int RTC4open(void);
void RTC4close(void);

typedef unsigned long (__stdcall *ACQUIRE_RTC)(unsigned long ip);
typedef unsigned long (__stdcall *RELEASE_RTC)(unsigned long ip);
typedef unsigned long (__stdcall *CONVERT_STRING_TO_IP)(const char* ip);
typedef void (__stdcall *CONVERT_IP_TO_STRING)(unsigned long ip, const char* cpip);
typedef void (__stdcall *CONVERT_MAC_TO_STRING)(__int64 mac, const char* cpmac);
typedef unsigned long (__stdcall *RTC_SEARCH_CARDS)(unsigned short *cards, unsigned long ip, unsigned long netmask);
typedef __int64 (__stdcall *GET_MAC_ADDRESS)(unsigned short cardno);
typedef unsigned long (__stdcall *GET_IP_ADDRESS)(unsigned short cardno);
typedef unsigned long (__stdcall *GET_SERIAL)(unsigned short cardno);
typedef unsigned short (__stdcall *GET_CONNECTION_STATUS)(unsigned short cardno);
typedef unsigned long (__stdcall *GET_MASTER_IP_ADDRESS)(unsigned short cardno);
typedef unsigned long (__stdcall *GET_MASTER_ID)(unsigned short cardno, const char* id);
typedef void (__stdcall *SET_TIMEOUT)(unsigned long timeout);
typedef unsigned long (__stdcall *SET_STATIC_IP)(unsigned long ip, unsigned long netmask);
typedef unsigned long (__stdcall *GET_STATIC_IP)(unsigned long *ip, unsigned long *netmask);
typedef unsigned long (__stdcall *GET_MCU_FW_VERSION)(unsigned short cardno);
typedef unsigned long (__stdcall *GET_NIC_IP_COUNT)(unsigned short *count);
typedef void (__stdcall *GET_NIC_IP)(unsigned short count, unsigned long *ip, unsigned long *nm);
typedef void (__stdcall *N_GET_WAVEFORM)(unsigned short n, unsigned short channel, unsigned short istop, signed short *memptr);
typedef void (__stdcall *GET_WAVEFORM)(unsigned short channel, unsigned short istop, signed short *memptr);
typedef void (__stdcall *N_MEASUREMENT_STATUS)(unsigned short n, unsigned short *busy, unsigned short *position);
typedef void (__stdcall *MEASUREMENT_STATUS)(unsigned short *busy, unsigned short *position);
typedef short (__stdcall *N_LOAD_VARPOLYDELAY)(unsigned short n, const char* stbfilename, unsigned short tableno);
typedef short (__stdcall *LOAD_VARPOLYDELAY)(const char* stbfilename, unsigned short tableno);
typedef short (__stdcall *N_LOAD_PROGRAM_FILE)(unsigned short n, const char* name);
typedef short (__stdcall *LOAD_PROGRAM_FILE)(const char* name);
typedef short (__stdcall *N_LOAD_CORRECTION_FILE)(unsigned short n, const char* filename, short cortable, double kx, double ky, double phi, double xoffset, double yoffset);
typedef short (__stdcall *LOAD_CORRECTION_FILE)(const char* filename, short cortable, double kx, double ky, double phi, double xoffset, double yoffset);
typedef short (__stdcall *N_LOAD_Z_TABLE)(unsigned short n, double a, double b, double c);
typedef short (__stdcall *LOAD_Z_TABLE)(double a, double b, double c);
typedef void (__stdcall *N_LIST_NOP)(unsigned short n);
typedef void (__stdcall *LIST_NOP)(void);
typedef void (__stdcall *N_SET_END_OF_LIST)(unsigned short n);
typedef void (__stdcall *SET_END_OF_LIST)(void);
typedef void (__stdcall *N_JUMP_ABS_3D)(unsigned short n, short x, short y, short z);
typedef void (__stdcall *JUMP_ABS_3D)(short x, short y, short z);
typedef void (__stdcall *N_JUMP_ABS)(unsigned short n, short x, short y);
typedef void (__stdcall *JUMP_ABS)(short x, short y);
typedef void (__stdcall *N_MARK_ABS_3D)(unsigned short n, short x, short y, short z);
typedef void (__stdcall *MARK_ABS_3D)(short x, short y, short z);
typedef void (__stdcall *N_MARK_ABS)(unsigned short n, short x, short y);
typedef void (__stdcall *MARK_ABS)(short x, short y);
typedef void (__stdcall *N_JUMP_REL_3D)(unsigned short n, short dx, short dy, short dz);
typedef void (__stdcall *JUMP_REL_3D)(short dx, short dy, short dz);
typedef void (__stdcall *N_JUMP_REL)(unsigned short n, short dx, short dy);
typedef void (__stdcall *JUMP_REL)(short dx, short dy);
typedef void (__stdcall *N_MARK_REL_3D)(unsigned short n, short dx, short dy, short dz);
typedef void (__stdcall *MARK_REL_3D)(short dx, short dy, short dz);
typedef void (__stdcall *N_MARK_REL)(unsigned short n, short dx, short dy);
typedef void (__stdcall *MARK_REL)(short dx, short dy);
typedef void (__stdcall *N_WRITE_8BIT_PORT_LIST)(unsigned short n, unsigned short value);
typedef void (__stdcall *WRITE_8BIT_PORT_LIST)(unsigned short value);
typedef void (__stdcall *N_WRITE_DA_1_LIST)(unsigned short n, unsigned short value);
typedef void (__stdcall *WRITE_DA_1_LIST)(unsigned short value);
typedef void (__stdcall *N_WRITE_DA_2_LIST)(unsigned short n, unsigned short value);
typedef void (__stdcall *WRITE_DA_2_LIST)(unsigned short value);
typedef void (__stdcall *N_SET_MATRIX_LIST)(unsigned short n, unsigned short i, unsigned short j, double mij);
typedef void (__stdcall *SET_MATRIX_LIST)(unsigned short i, unsigned short j, double mij);
typedef void (__stdcall *N_SET_DEFOCUS_LIST)(unsigned short n, short value);
typedef void (__stdcall *SET_DEFOCUS_LIST)(short value);
typedef void (__stdcall *N_SET_CONTROL_MODE_LIST)(unsigned short n, unsigned short mode);
typedef void (__stdcall *SET_CONTROL_MODE_LIST)(unsigned short mode);
typedef void (__stdcall *N_SET_OFFSET_LIST)(unsigned short n, short xoffset, short yoffset);
typedef void (__stdcall *SET_OFFSET_LIST)(short xoffset, short yoffset);
typedef void (__stdcall *N_LONG_DELAY)(unsigned short n, unsigned short value);
typedef void (__stdcall *LONG_DELAY)(unsigned short value);
typedef void (__stdcall *N_LASER_ON_LIST)(unsigned short n, unsigned short value);
typedef void (__stdcall *LASER_ON_LIST)(unsigned short value);
typedef void (__stdcall *N_SET_JUMP_SPEED)(unsigned short n, double speed);
typedef void (__stdcall *SET_JUMP_SPEED)(double speed);
typedef void (__stdcall *N_SET_MARK_SPEED)(unsigned short n, double speed);
typedef void (__stdcall *SET_MARK_SPEED)(double speed);
typedef void (__stdcall *N_SET_LASER_DELAYS)(unsigned short n, short ondelay, short offdelay);
typedef void (__stdcall *SET_LASER_DELAYS)(short ondelay, short offdelay);
typedef void (__stdcall *N_SET_SCANNER_DELAYS)(unsigned short n, unsigned short jumpdelay, unsigned short markdelay, unsigned short polydelay);
typedef void (__stdcall *SET_SCANNER_DELAYS)(unsigned short jumpdelay, unsigned short markdelay, unsigned short polydelay);
typedef void (__stdcall *N_SET_LIST_JUMP)(unsigned short n, unsigned short position);
typedef void (__stdcall *SET_LIST_JUMP)(unsigned short position);
typedef void (__stdcall *N_SET_INPUT_POINTER)(unsigned short n, unsigned short pointer);
typedef void (__stdcall *SET_INPUT_POINTER)(unsigned short pointer);
typedef void (__stdcall *N_LIST_CALL)(unsigned short n, unsigned short position);
typedef void (__stdcall *LIST_CALL)(unsigned short position);
typedef void (__stdcall *N_LIST_RETURN)(unsigned short n);
typedef void (__stdcall *LIST_RETURN)(void);
typedef void (__stdcall *N_Z_OUT_LIST)(unsigned short n, short z);
typedef void (__stdcall *Z_OUT_LIST)(short z);
typedef void (__stdcall *N_SET_STANDBY_LIST)(unsigned short n, unsigned short half_period, unsigned short pulse);
typedef void (__stdcall *SET_STANDBY_LIST)(unsigned short half_period, unsigned short pulse);
typedef void (__stdcall *N_TIMED_JUMP_ABS)(unsigned short n, short x, short y, double time);
typedef void (__stdcall *TIMED_JUMP_ABS)(short x, short y, double time);
typedef void (__stdcall *N_TIMED_MARK_ABS)(unsigned short n, short x, short y, double time);
typedef void (__stdcall *TIMED_MARK_ABS)(short x, short y, double time);
typedef void (__stdcall *N_TIMED_JUMP_REL)(unsigned short n, short dx, short dy, double time);
typedef void (__stdcall *TIMED_JUMP_REL)(short dx, short dy, double time);
typedef void (__stdcall *N_TIMED_MARK_REL)(unsigned short n, short dx, short dy, double time);
typedef void (__stdcall *TIMED_MARK_REL)(short dx, short dy, double time);
typedef void (__stdcall *N_SET_LASER_TIMING)(unsigned short n, unsigned short halfperiod, unsigned short pulse1, unsigned short pulse2, unsigned short timebase);
typedef void (__stdcall *SET_LASER_TIMING)(unsigned short halfperiod, unsigned short pulse1, unsigned short pulse2, unsigned short timebase);
typedef void (__stdcall *N_SET_WOBBEL_XY)(unsigned short n, unsigned short long_wob, unsigned short trans_wob, double frequency);
typedef void (__stdcall *SET_WOBBEL_XY)(unsigned short long_wob, unsigned short trans_wob, double frequency);
typedef void (__stdcall *N_SET_WOBBEL)(unsigned short n, unsigned short amplitude, double frequency);
typedef void (__stdcall *SET_WOBBEL)(unsigned short amplitude, double frequency);
typedef void (__stdcall *N_SET_FLY_X)(unsigned short n, double kx);
typedef void (__stdcall *SET_FLY_X)(double kx);
typedef void (__stdcall *N_SET_FLY_Y)(unsigned short n, double ky);
typedef void (__stdcall *SET_FLY_Y)(double ky);
typedef void (__stdcall *N_SET_FLY_ROT)(unsigned short n, double resolution);
typedef void (__stdcall *SET_FLY_ROT)(double resolution);
typedef void (__stdcall *N_FLY_RETURN)(unsigned short n, short x, short y);
typedef void (__stdcall *FLY_RETURN)(short x, short y);
typedef void (__stdcall *N_CALCULATE_FLY)(unsigned short n, unsigned short direction, double distance);
typedef void (__stdcall *CALCULATE_FLY)(unsigned short direction, double distance);
typedef void (__stdcall *N_WRITE_IO_PORT_LIST)(unsigned short n, unsigned short value);
typedef void (__stdcall *WRITE_IO_PORT_LIST)(unsigned short value);
typedef void (__stdcall *N_SELECT_COR_TABLE_LIST)(unsigned short n, unsigned short heada, unsigned short headb);
typedef void (__stdcall *SELECT_COR_TABLE_LIST)(unsigned short heada, unsigned short headb);
typedef void (__stdcall *N_SET_WAIT)(unsigned short n, unsigned short value);
typedef void (__stdcall *SET_WAIT)(unsigned short value);
typedef void (__stdcall *N_SIMULATE_EXT_START)(unsigned short n, short delay, short encoder);
typedef void (__stdcall *SIMULATE_EXT_START)(short delay, short encoder);
typedef void (__stdcall *N_WRITE_DA_X_LIST)(unsigned short n, unsigned short x, unsigned short value);
typedef void (__stdcall *WRITE_DA_X_LIST)(unsigned short x, unsigned short value);
typedef void (__stdcall *N_SET_PIXEL_LINE)(unsigned short n, unsigned short pixelmode, unsigned short pixelperiod, double dx, double dy);
typedef void (__stdcall *SET_PIXEL_LINE)(unsigned short pixelmode, unsigned short pixelperiod, double dx, double dy);
typedef void (__stdcall *N_SET_PIXEL)(unsigned short n, unsigned short pulswidth, unsigned short davalue, unsigned short adchannel);
typedef void (__stdcall *SET_PIXEL)(unsigned short pulswidth, unsigned short davalue, unsigned short adchannel);
typedef void (__stdcall *N_SET_EXTSTARTPOS_LIST)(unsigned short n, unsigned short position);
typedef void (__stdcall *SET_EXTSTARTPOS_LIST)(unsigned short position);
typedef void (__stdcall *N_LASER_SIGNAL_ON_LIST)(unsigned short n);
typedef void (__stdcall *LASER_SIGNAL_ON_LIST)(void);
typedef void (__stdcall *N_LASER_SIGNAL_OFF_LIST)(unsigned short n);
typedef void (__stdcall *LASER_SIGNAL_OFF_LIST)(void);
typedef void (__stdcall *N_SET_FIRSTPULSE_KILLER_LIST)(unsigned short n, unsigned short fpk);
typedef void (__stdcall *SET_FIRSTPULSE_KILLER_LIST)(unsigned short fpk);
typedef void (__stdcall *N_SET_IO_COND_LIST)(unsigned short n, unsigned short mask_1, unsigned short mask_0, unsigned short mask_set);
typedef void (__stdcall *SET_IO_COND_LIST)(unsigned short mask_1, unsigned short mask_0, unsigned short mask_set);
typedef void (__stdcall *N_CLEAR_IO_COND_LIST)(unsigned short n, unsigned short mask_1, unsigned short mask_0, unsigned short mask_clear);
typedef void (__stdcall *CLEAR_IO_COND_LIST)(unsigned short mask_1, unsigned short mask_0, unsigned short mask_clear);
typedef void (__stdcall *N_LIST_JUMP_COND)(unsigned short n, unsigned short mask_1, unsigned short mask_0, unsigned short position);
typedef void (__stdcall *LIST_JUMP_COND)(unsigned short mask_1, unsigned short mask_0, unsigned short position);
typedef void (__stdcall *N_LIST_CALL_COND)(unsigned short n, unsigned short mask_1, unsigned short mask_0, unsigned short position);
typedef void (__stdcall *LIST_CALL_COND)(unsigned short mask_1, unsigned short mask_0, unsigned short position);
typedef void (__stdcall *N_SAVE_AND_RESTART_TIMER)(unsigned short n);
typedef void (__stdcall *SAVE_AND_RESTART_TIMER)(void);
typedef void (__stdcall *N_SET_EXT_START_DELAY_LIST)(unsigned short n, short delay, short encoder);
typedef void (__stdcall *SET_EXT_START_DELAY_LIST)(short delay, short encoder);
typedef void (__stdcall *N_SET_TRIGGER)(unsigned short n, unsigned short sampleperiod, unsigned short channel1, unsigned short channel2);
typedef void (__stdcall *SET_TRIGGER)(unsigned short sampleperiod, unsigned short signal1, unsigned short signal2);
typedef void (__stdcall *N_ARC_REL)(unsigned short n, short dx, short dy, double angle);
typedef void (__stdcall *ARC_REL)(short dx, short dy, double angle);
typedef void (__stdcall *N_ARC_ABS)(unsigned short n, short x, short y, double angle);
typedef void (__stdcall *ARC_ABS)(short x, short y, double angle);
typedef void (__stdcall *DRILLING)(short pulsewidth, short relencoderdelay);
typedef void (__stdcall *REGULATION)(void);
typedef void (__stdcall *FLYLINE)(short encoderdelay);
typedef long (__stdcall *N_ETH_STATUS)(unsigned short n);
typedef long (__stdcall *ETH_STATUS)(void);
typedef unsigned short (__stdcall *N_GET_INPUT_POINTER)(unsigned short n);
typedef unsigned short (__stdcall *GET_INPUT_POINTER)(void);
typedef void (__stdcall *SELECT_RTC)(unsigned short cardno);
typedef unsigned short (__stdcall *RTC4_COUNT_CARDS)(void);
typedef void (__stdcall *N_GET_STATUS)(unsigned short n, unsigned short *busy, unsigned short *position);
typedef void (__stdcall *GET_STATUS)(unsigned short *busy, unsigned short *position);
typedef unsigned short (__stdcall *N_READ_STATUS)(unsigned short n);
typedef unsigned short (__stdcall *READ_STATUS)(void);
typedef unsigned short (__stdcall *N_GET_STARTSTOP_INFO)(unsigned short n);
typedef unsigned short (__stdcall *GET_STARTSTOP_INFO)(void);
typedef unsigned short (__stdcall *N_GET_MARKING_INFO)(unsigned short n);
typedef unsigned short (__stdcall *GET_MARKING_INFO)(void);
typedef unsigned short (__stdcall *GET_DLL_VERSION)(void);
typedef void (__stdcall *N_SET_START_LIST_1)(unsigned short n);
typedef void (__stdcall *SET_START_LIST_1)(void);
typedef void (__stdcall *N_SET_START_LIST_2)(unsigned short n);
typedef void (__stdcall *SET_START_LIST_2)(void);
typedef void (__stdcall *N_SET_START_LIST)(unsigned short n, unsigned short listno);
typedef void (__stdcall *SET_START_LIST)(unsigned short listno);
typedef void (__stdcall *N_EXECUTE_LIST_1)(unsigned short n);
typedef void (__stdcall *EXECUTE_LIST_1)(void);
typedef void (__stdcall *N_EXECUTE_LIST_2)(unsigned short n);
typedef void (__stdcall *EXECUTE_LIST_2)(void);
typedef void (__stdcall *N_EXECUTE_LIST)(unsigned short n, unsigned short listno);
typedef void (__stdcall *EXECUTE_LIST)(unsigned short listno);
typedef void (__stdcall *N_WRITE_8BIT_PORT)(unsigned short n, unsigned short value);
typedef void (__stdcall *WRITE_8BIT_PORT)(unsigned short value);
typedef void (__stdcall *N_WRITE_IO_PORT)(unsigned short n, unsigned short value);
typedef void (__stdcall *WRITE_IO_PORT)(unsigned short value);
typedef void (__stdcall *N_AUTO_CHANGE)(unsigned short n);
typedef void (__stdcall *AUTO_CHANGE)(void);
typedef void (__stdcall *N_AUTO_CHANGE_POS)(unsigned short n, unsigned short start);
typedef void (__stdcall *AUTO_CHANGE_POS)(unsigned short start);
typedef void (__stdcall *AUT_CHANGE)(void);
typedef void (__stdcall *N_START_LOOP)(unsigned short n);
typedef void (__stdcall *START_LOOP)(void);
typedef void (__stdcall *N_QUIT_LOOP)(unsigned short n);
typedef void (__stdcall *QUIT_LOOP)(void);
typedef void (__stdcall *N_SET_LIST_MODE)(unsigned short n, unsigned short mode);
typedef void (__stdcall *SET_LIST_MODE)(unsigned short mode);
typedef void (__stdcall *N_STOP_EXECUTION)(unsigned short n);
typedef void (__stdcall *STOP_EXECUTION)(void);
typedef unsigned short (__stdcall *N_READ_IO_PORT)(unsigned short n);
typedef unsigned short (__stdcall *READ_IO_PORT)(void);
typedef void (__stdcall *N_WRITE_DA_1)(unsigned short n, unsigned short value);
typedef void (__stdcall *WRITE_DA_1)(unsigned short value);
typedef void (__stdcall *N_WRITE_DA_2)(unsigned short n, unsigned short value);
typedef void (__stdcall *WRITE_DA_2)(unsigned short value);
typedef void (__stdcall *N_SET_MAX_COUNTS)(unsigned short n, long counts);
typedef void (__stdcall *SET_MAX_COUNTS)(long counts);
typedef long (__stdcall *N_GET_COUNTS)(unsigned short n);
typedef long (__stdcall *GET_COUNTS)(void);
typedef void (__stdcall *N_SET_MATRIX)(unsigned short n, double m11, double m12, double m21, double m22);
typedef void (__stdcall *SET_MATRIX)(double m11, double m12, double m21, double m22);
typedef void (__stdcall *N_SET_OFFSET)(unsigned short n, short xoffset, short yoffset);
typedef void (__stdcall *SET_OFFSET)(short xoffset, short yoffset);
typedef void (__stdcall *N_GOTO_XYZ)(unsigned short n, short x, short y, short z);
typedef void (__stdcall *GOTO_XYZ)(short x, short y, short z);
typedef void (__stdcall *N_GOTO_XY)(unsigned short n, short x, short y);
typedef void (__stdcall *GOTO_XY)(short x, short y);
typedef unsigned short (__stdcall *N_GET_HEX_VERSION)(unsigned short n);
typedef unsigned short (__stdcall *GET_HEX_VERSION)(void);
typedef void (__stdcall *N_DISABLE_LASER)(unsigned short n);
typedef void (__stdcall *DISABLE_LASER)(void);
typedef void (__stdcall *N_ENABLE_LASER)(unsigned short n);
typedef void (__stdcall *ENABLE_LASER)(void);
typedef void (__stdcall *N_STOP_LIST)(unsigned short n);
typedef void (__stdcall *STOP_LIST)(void);
typedef void (__stdcall *N_RESTART_LIST)(unsigned short n);
typedef void (__stdcall *RESTART_LIST)(void);
typedef void (__stdcall *N_GET_XYZ_POS)(unsigned short n, short *x, short *y, short *z);
typedef void (__stdcall *GET_XYZ_POS)(short *x, short *y, short *z);
typedef void (__stdcall *N_GET_XY_POS)(unsigned short n, short *x, short *y);
typedef void (__stdcall *GET_XY_POS)(short *x, short *y);
typedef void (__stdcall *N_SELECT_LIST)(unsigned short n, unsigned short list_2);
typedef void (__stdcall *SELECT_LIST)(unsigned short list_2);
typedef void (__stdcall *N_Z_OUT)(unsigned short n, short z);
typedef void (__stdcall *Z_OUT)(short z);
typedef void (__stdcall *N_SET_FIRSTPULSE_KILLER)(unsigned short n, unsigned short fpk);
typedef void (__stdcall *SET_FIRSTPULSE_KILLER)(unsigned short fpk);
typedef void (__stdcall *N_SET_STANDBY)(unsigned short n, unsigned short half_period, unsigned short pulse);
typedef void (__stdcall *SET_STANDBY)(unsigned short half_period, unsigned short pulse);
typedef void (__stdcall *N_LASER_SIGNAL_ON)(unsigned short n);
typedef void (__stdcall *LASER_SIGNAL_ON)(void);
typedef void (__stdcall *N_LASER_SIGNAL_OFF)(unsigned short n);
typedef void (__stdcall *LASER_SIGNAL_OFF)(void);
typedef void (__stdcall *N_SET_DELAY_MODE)(unsigned short n, unsigned short varpoly, unsigned short directmove3d, unsigned short edgelevel, unsigned short minjumpdelay, unsigned short jumplengthlimit);
typedef void (__stdcall *SET_DELAY_MODE)(unsigned short varpoly, unsigned short directmove3d, unsigned short edgelevel, unsigned short minjumpdelay, unsigned short jumplengthlimit);
typedef void (__stdcall *N_SET_PISO_CONTROL)(unsigned short n, unsigned short l1, unsigned short l2);
typedef void (__stdcall *SET_PISO_CONTROL)(unsigned short l1, unsigned short l2);
typedef void (__stdcall *N_SELECT_STATUS)(unsigned short n, unsigned short mode);
typedef void (__stdcall *SELECT_STATUS)(unsigned short mode);
typedef void (__stdcall *N_GET_ENCODER)(unsigned short n, short *zx, short *zy);
typedef void (__stdcall *GET_ENCODER)(short *zx, short *zy);
typedef void (__stdcall *N_SELECT_COR_TABLE)(unsigned short n, unsigned short heada, unsigned short headb);
typedef void (__stdcall *SELECT_COR_TABLE)(unsigned short heada, unsigned short headb);
typedef void (__stdcall *N_EXECUTE_AT_POINTER)(unsigned short n, unsigned short position);
typedef void (__stdcall *EXECUTE_AT_POINTER)(unsigned short position);
typedef unsigned short (__stdcall *N_GET_HEAD_STATUS)(unsigned short n, unsigned short head);
typedef unsigned short (__stdcall *GET_HEAD_STATUS)(unsigned short head);
typedef void (__stdcall *N_SIMULATE_ENCODER)(unsigned short n, unsigned short channel);
typedef void (__stdcall *SIMULATE_ENCODER)(unsigned short channel);
typedef void (__stdcall *N_SET_HI)(unsigned short n, double galvogainx, double galvogainy, short galvooffsetx, short galvooffsety, short head);
typedef void (__stdcall *SET_HI)(double galvogainx, double galvogainy, short galvooffsetx, short galvooffsety, short head);
typedef void (__stdcall *N_RELEASE_WAIT)(unsigned short n);
typedef void (__stdcall *RELEASE_WAIT)(void);
typedef unsigned short (__stdcall *N_GET_WAIT_STATUS)(unsigned short n);
typedef unsigned short (__stdcall *GET_WAIT_STATUS)(void);
typedef void (__stdcall *N_SET_CONTROL_MODE)(unsigned short n, unsigned short mode);
typedef void (__stdcall *SET_CONTROL_MODE)(unsigned short mode);
typedef void (__stdcall *N_SET_LASER_MODE)(unsigned short n, unsigned short mode);
typedef void (__stdcall *SET_LASER_MODE)(unsigned short mode);
typedef void (__stdcall *N_SET_EXT_START_DELAY)(unsigned short n, short delay, short encoder);
typedef void (__stdcall *SET_EXT_START_DELAY)(short delay, short encoder);
typedef void (__stdcall *N_HOME_POSITION)(unsigned short n, short xhome, short yhome);
typedef void (__stdcall *HOME_POSITION)(short xhome, short yhome);
typedef void (__stdcall *N_SET_ROT_CENTER)(unsigned short n, long center_x, long center_y);
typedef void (__stdcall *SET_ROT_CENTER)(long center_x, long center_y);
typedef void (__stdcall *N_DSP_START)(unsigned short n);
typedef void (__stdcall *DSP_START)(void);
typedef void (__stdcall *N_WRITE_DA_X)(unsigned short n, unsigned short x, unsigned short value);
typedef void (__stdcall *WRITE_DA_X)(unsigned short x, unsigned short value);
typedef unsigned short (__stdcall *N_READ_AD_X)(unsigned short n, unsigned short x);
typedef unsigned short (__stdcall *READ_AD_X)(unsigned short x);
typedef unsigned short (__stdcall *N_READ_PIXEL_AD)(unsigned short n, unsigned short pos);
typedef unsigned short (__stdcall *READ_PIXEL_AD)(unsigned short pos);
typedef short (__stdcall *N_GET_Z_DISTANCE)(unsigned short n, short x, short y, short z);
typedef short (__stdcall *GET_Z_DISTANCE)(short x, short y, short z);
typedef unsigned short (__stdcall *N_GET_IO_STATUS)(unsigned short n);
typedef unsigned short (__stdcall *GET_IO_STATUS)(void);
typedef double (__stdcall *N_GET_TIME)(unsigned short n);
typedef double (__stdcall *GET_TIME)(void);
typedef void (__stdcall *N_SET_DEFOCUS)(unsigned short n, short value);
typedef void (__stdcall *SET_DEFOCUS)(short value);
typedef void (__stdcall *N_SET_SOFTSTART_MODE)(unsigned short n, unsigned short mode, unsigned short number, unsigned short restartdelay);
typedef void (__stdcall *SET_SOFTSTART_MODE)(unsigned short mode, unsigned short number, unsigned short resetdelay);
typedef void (__stdcall *N_SET_SOFTSTART_LEVEL)(unsigned short n, unsigned short index, unsigned short level);
typedef void (__stdcall *SET_SOFTSTART_LEVEL)(unsigned short index, unsigned short level);
typedef void (__stdcall *N_CONTROL_COMMAND)(unsigned short n, unsigned short head, unsigned short axis, unsigned short data);
typedef void (__stdcall *CONTROL_COMMAND)(unsigned short head, unsigned short axis, unsigned short data);
typedef short (__stdcall *LOAD_COR)(const char* filename);
typedef short (__stdcall *LOAD_PRO)(const char* filename);
typedef unsigned short (__stdcall *N_GET_SERIAL_NUMBER)(unsigned short n);
typedef unsigned short (__stdcall *GET_SERIAL_NUMBER)(void);
typedef long (__stdcall *N_GET_SERIAL_NUMBER_32)(unsigned short n);
typedef long (__stdcall *GET_SERIAL_NUMBER_32)(void);
typedef unsigned short (__stdcall *N_GET_RTC_VERSION)(unsigned short n);
typedef unsigned short (__stdcall *GET_RTC_VERSION)(void);
typedef void (__stdcall *GET_HI_DATA)(unsigned short *x1, unsigned short *x2, unsigned short *y1, unsigned short *y2);
typedef short (__stdcall *N_AUTO_CAL)(unsigned short n, unsigned short head, unsigned short command);
typedef short (__stdcall *AUTO_CAL)(unsigned short head, unsigned short command);
typedef unsigned short (__stdcall *N_GET_LIST_SPACE)(unsigned short n);
typedef unsigned short (__stdcall *GET_LIST_SPACE)(void);
typedef short (__stdcall *TEACHIN)(const char* filename, short xin, short yin, short zin, double ll0, short *xout, short *yout, short *zout);
typedef short (__stdcall *N_GET_VALUE)(unsigned short n, unsigned short signal);
typedef short (__stdcall *GET_VALUE)(unsigned short signal);
typedef void (__stdcall *N_SET_IO_BIT)(unsigned short n, unsigned short mask1);
typedef void (__stdcall *SET_IO_BIT)(unsigned short mask1);
typedef void (__stdcall *N_CLEAR_IO_BIT)(unsigned short n, unsigned short mask0);
typedef void (__stdcall *CLEAR_IO_BIT)(unsigned short mask0);
typedef void (__stdcall *SET_DUTY_CYCLE_TABLE)(unsigned short index, unsigned short dutycycle);
typedef void (__stdcall *N_MOVE_TO)(unsigned short n, unsigned short position);
typedef void (__stdcall *MOVE_TO)(unsigned short position);

extern ACQUIRE_RTC acquire_rtc;
extern RELEASE_RTC release_rtc;
extern CONVERT_STRING_TO_IP convert_string_to_ip;
extern CONVERT_IP_TO_STRING convert_ip_to_string;
extern CONVERT_MAC_TO_STRING convert_mac_to_string;
extern RTC_SEARCH_CARDS rtc_search_cards;
extern GET_MAC_ADDRESS get_mac_address;
extern GET_IP_ADDRESS get_ip_address;
extern GET_SERIAL get_serial;
extern GET_CONNECTION_STATUS get_connection_status;
extern GET_MASTER_IP_ADDRESS get_master_ip_address;
extern GET_MASTER_ID get_master_id;
extern SET_TIMEOUT set_timeout;
extern SET_STATIC_IP set_static_ip;
extern GET_STATIC_IP get_static_ip;
extern GET_MCU_FW_VERSION get_mcu_fw_version;
extern GET_NIC_IP_COUNT get_nic_ip_count;
extern GET_NIC_IP get_nic_ip;
extern N_GET_WAVEFORM n_get_waveform;
extern GET_WAVEFORM get_waveform;
extern N_MEASUREMENT_STATUS n_measurement_status;
extern MEASUREMENT_STATUS measurement_status;
extern N_LOAD_VARPOLYDELAY n_load_varpolydelay;
extern LOAD_VARPOLYDELAY load_varpolydelay;
extern N_LOAD_PROGRAM_FILE n_load_program_file;
extern LOAD_PROGRAM_FILE load_program_file;
extern N_LOAD_CORRECTION_FILE n_load_correction_file;
extern LOAD_CORRECTION_FILE load_correction_file;
extern N_LOAD_Z_TABLE n_load_z_table;
extern LOAD_Z_TABLE load_z_table;
extern N_LIST_NOP n_list_nop;
extern LIST_NOP list_nop;
extern N_SET_END_OF_LIST n_set_end_of_list;
extern SET_END_OF_LIST set_end_of_list;
extern N_JUMP_ABS_3D n_jump_abs_3d;
extern JUMP_ABS_3D jump_abs_3d;
extern N_JUMP_ABS n_jump_abs;
extern JUMP_ABS jump_abs;
extern N_MARK_ABS_3D n_mark_abs_3d;
extern MARK_ABS_3D mark_abs_3d;
extern N_MARK_ABS n_mark_abs;
extern MARK_ABS mark_abs;
extern N_JUMP_REL_3D n_jump_rel_3d;
extern JUMP_REL_3D jump_rel_3d;
extern N_JUMP_REL n_jump_rel;
extern JUMP_REL jump_rel;
extern N_MARK_REL_3D n_mark_rel_3d;
extern MARK_REL_3D mark_rel_3d;
extern N_MARK_REL n_mark_rel;
extern MARK_REL mark_rel;
extern N_WRITE_8BIT_PORT_LIST n_write_8bit_port_list;
extern WRITE_8BIT_PORT_LIST write_8bit_port_list;
extern N_WRITE_DA_1_LIST n_write_da_1_list;
extern WRITE_DA_1_LIST write_da_1_list;
extern N_WRITE_DA_2_LIST n_write_da_2_list;
extern WRITE_DA_2_LIST write_da_2_list;
extern N_SET_MATRIX_LIST n_set_matrix_list;
extern SET_MATRIX_LIST set_matrix_list;
extern N_SET_DEFOCUS_LIST n_set_defocus_list;
extern SET_DEFOCUS_LIST set_defocus_list;
extern N_SET_CONTROL_MODE_LIST n_set_control_mode_list;
extern SET_CONTROL_MODE_LIST set_control_mode_list;
extern N_SET_OFFSET_LIST n_set_offset_list;
extern SET_OFFSET_LIST set_offset_list;
extern N_LONG_DELAY n_long_delay;
extern LONG_DELAY long_delay;
extern N_LASER_ON_LIST n_laser_on_list;
extern LASER_ON_LIST laser_on_list;
extern N_SET_JUMP_SPEED n_set_jump_speed;
extern SET_JUMP_SPEED set_jump_speed;
extern N_SET_MARK_SPEED n_set_mark_speed;
extern SET_MARK_SPEED set_mark_speed;
extern N_SET_LASER_DELAYS n_set_laser_delays;
extern SET_LASER_DELAYS set_laser_delays;
extern N_SET_SCANNER_DELAYS n_set_scanner_delays;
extern SET_SCANNER_DELAYS set_scanner_delays;
extern N_SET_LIST_JUMP n_set_list_jump;
extern SET_LIST_JUMP set_list_jump;
extern N_SET_INPUT_POINTER n_set_input_pointer;
extern SET_INPUT_POINTER set_input_pointer;
extern N_LIST_CALL n_list_call;
extern LIST_CALL list_call;
extern N_LIST_RETURN n_list_return;
extern LIST_RETURN list_return;
extern N_Z_OUT_LIST n_z_out_list;
extern Z_OUT_LIST z_out_list;
extern N_SET_STANDBY_LIST n_set_standby_list;
extern SET_STANDBY_LIST set_standby_list;
extern N_TIMED_JUMP_ABS n_timed_jump_abs;
extern TIMED_JUMP_ABS timed_jump_abs;
extern N_TIMED_MARK_ABS n_timed_mark_abs;
extern TIMED_MARK_ABS timed_mark_abs;
extern N_TIMED_JUMP_REL n_timed_jump_rel;
extern TIMED_JUMP_REL timed_jump_rel;
extern N_TIMED_MARK_REL n_timed_mark_rel;
extern TIMED_MARK_REL timed_mark_rel;
extern N_SET_LASER_TIMING n_set_laser_timing;
extern SET_LASER_TIMING set_laser_timing;
extern N_SET_WOBBEL_XY n_set_wobbel_xy;
extern SET_WOBBEL_XY set_wobbel_xy;
extern N_SET_WOBBEL n_set_wobbel;
extern SET_WOBBEL set_wobbel;
extern N_SET_FLY_X n_set_fly_x;
extern SET_FLY_X set_fly_x;
extern N_SET_FLY_Y n_set_fly_y;
extern SET_FLY_Y set_fly_y;
extern N_SET_FLY_ROT n_set_fly_rot;
extern SET_FLY_ROT set_fly_rot;
extern N_FLY_RETURN n_fly_return;
extern FLY_RETURN fly_return;
extern N_CALCULATE_FLY n_calculate_fly;
extern CALCULATE_FLY calculate_fly;
extern N_WRITE_IO_PORT_LIST n_write_io_port_list;
extern WRITE_IO_PORT_LIST write_io_port_list;
extern N_SELECT_COR_TABLE_LIST n_select_cor_table_list;
extern SELECT_COR_TABLE_LIST select_cor_table_list;
extern N_SET_WAIT n_set_wait;
extern SET_WAIT set_wait;
extern N_SIMULATE_EXT_START n_simulate_ext_start;
extern SIMULATE_EXT_START simulate_ext_start;
extern N_WRITE_DA_X_LIST n_write_da_x_list;
extern WRITE_DA_X_LIST write_da_x_list;
extern N_SET_PIXEL_LINE n_set_pixel_line;
extern SET_PIXEL_LINE set_pixel_line;
extern N_SET_PIXEL n_set_pixel;
extern SET_PIXEL set_pixel;
extern N_SET_EXTSTARTPOS_LIST n_set_extstartpos_list;
extern SET_EXTSTARTPOS_LIST set_extstartpos_list;
extern N_LASER_SIGNAL_ON_LIST n_laser_signal_on_list;
extern LASER_SIGNAL_ON_LIST laser_signal_on_list;
extern N_LASER_SIGNAL_OFF_LIST n_laser_signal_off_list;
extern LASER_SIGNAL_OFF_LIST laser_signal_off_list;
extern N_SET_FIRSTPULSE_KILLER_LIST n_set_firstpulse_killer_list;
extern SET_FIRSTPULSE_KILLER_LIST set_firstpulse_killer_list;
extern N_SET_IO_COND_LIST n_set_io_cond_list;
extern SET_IO_COND_LIST set_io_cond_list;
extern N_CLEAR_IO_COND_LIST n_clear_io_cond_list;
extern CLEAR_IO_COND_LIST clear_io_cond_list;
extern N_LIST_JUMP_COND n_list_jump_cond;
extern LIST_JUMP_COND list_jump_cond;
extern N_LIST_CALL_COND n_list_call_cond;
extern LIST_CALL_COND list_call_cond;
extern N_SAVE_AND_RESTART_TIMER n_save_and_restart_timer;
extern SAVE_AND_RESTART_TIMER save_and_restart_timer;
extern N_SET_EXT_START_DELAY_LIST n_set_ext_start_delay_list;
extern SET_EXT_START_DELAY_LIST set_ext_start_delay_list;
extern N_SET_TRIGGER n_set_trigger;
extern SET_TRIGGER set_trigger;
extern N_ARC_REL n_arc_rel;
extern ARC_REL arc_rel;
extern N_ARC_ABS n_arc_abs;
extern ARC_ABS arc_abs;
extern DRILLING drilling;
extern REGULATION regulation;
extern FLYLINE flyline;
extern N_ETH_STATUS n_eth_status;
extern ETH_STATUS eth_status;
extern N_GET_INPUT_POINTER n_get_input_pointer;
extern GET_INPUT_POINTER get_input_pointer;
extern SELECT_RTC select_rtc;
extern RTC4_COUNT_CARDS rtc4_count_cards;
extern N_GET_STATUS n_get_status;
extern GET_STATUS get_status;
extern N_READ_STATUS n_read_status;
extern READ_STATUS read_status;
extern N_GET_STARTSTOP_INFO n_get_startstop_info;
extern GET_STARTSTOP_INFO get_startstop_info;
extern N_GET_MARKING_INFO n_get_marking_info;
extern GET_MARKING_INFO get_marking_info;
extern GET_DLL_VERSION get_dll_version;
extern N_SET_START_LIST_1 n_set_start_list_1;
extern SET_START_LIST_1 set_start_list_1;
extern N_SET_START_LIST_2 n_set_start_list_2;
extern SET_START_LIST_2 set_start_list_2;
extern N_SET_START_LIST n_set_start_list;
extern SET_START_LIST set_start_list;
extern N_EXECUTE_LIST_1 n_execute_list_1;
extern EXECUTE_LIST_1 execute_list_1;
extern N_EXECUTE_LIST_2 n_execute_list_2;
extern EXECUTE_LIST_2 execute_list_2;
extern N_EXECUTE_LIST n_execute_list;
extern EXECUTE_LIST execute_list;
extern N_WRITE_8BIT_PORT n_write_8bit_port;
extern WRITE_8BIT_PORT write_8bit_port;
extern N_WRITE_IO_PORT n_write_io_port;
extern WRITE_IO_PORT write_io_port;
extern N_AUTO_CHANGE n_auto_change;
extern AUTO_CHANGE auto_change;
extern N_AUTO_CHANGE_POS n_auto_change_pos;
extern AUTO_CHANGE_POS auto_change_pos;
extern AUT_CHANGE aut_change;
extern N_START_LOOP n_start_loop;
extern START_LOOP start_loop;
extern N_QUIT_LOOP n_quit_loop;
extern QUIT_LOOP quit_loop;
extern N_SET_LIST_MODE n_set_list_mode;
extern SET_LIST_MODE set_list_mode;
extern N_STOP_EXECUTION n_stop_execution;
extern STOP_EXECUTION stop_execution;
extern N_READ_IO_PORT n_read_io_port;
extern READ_IO_PORT read_io_port;
extern N_WRITE_DA_1 n_write_da_1;
extern WRITE_DA_1 write_da_1;
extern N_WRITE_DA_2 n_write_da_2;
extern WRITE_DA_2 write_da_2;
extern N_SET_MAX_COUNTS n_set_max_counts;
extern SET_MAX_COUNTS set_max_counts;
extern N_GET_COUNTS n_get_counts;
extern GET_COUNTS get_counts;
extern N_SET_MATRIX n_set_matrix;
extern SET_MATRIX set_matrix;
extern N_SET_OFFSET n_set_offset;
extern SET_OFFSET set_offset;
extern N_GOTO_XYZ n_goto_xyz;
extern GOTO_XYZ goto_xyz;
extern N_GOTO_XY n_goto_xy;
extern GOTO_XY goto_xy;
extern N_GET_HEX_VERSION n_get_hex_version;
extern GET_HEX_VERSION get_hex_version;
extern N_DISABLE_LASER n_disable_laser;
extern DISABLE_LASER disable_laser;
extern N_ENABLE_LASER n_enable_laser;
extern ENABLE_LASER enable_laser;
extern N_STOP_LIST n_stop_list;
extern STOP_LIST stop_list;
extern N_RESTART_LIST n_restart_list;
extern RESTART_LIST restart_list;
extern N_GET_XYZ_POS n_get_xyz_pos;
extern GET_XYZ_POS get_xyz_pos;
extern N_GET_XY_POS n_get_xy_pos;
extern GET_XY_POS get_xy_pos;
extern N_SELECT_LIST n_select_list;
extern SELECT_LIST select_list;
extern N_Z_OUT n_z_out;
extern Z_OUT z_out;
extern N_SET_FIRSTPULSE_KILLER n_set_firstpulse_killer;
extern SET_FIRSTPULSE_KILLER set_firstpulse_killer;
extern N_SET_STANDBY n_set_standby;
extern SET_STANDBY set_standby;
extern N_LASER_SIGNAL_ON n_laser_signal_on;
extern LASER_SIGNAL_ON laser_signal_on;
extern N_LASER_SIGNAL_OFF n_laser_signal_off;
extern LASER_SIGNAL_OFF laser_signal_off;
extern N_SET_DELAY_MODE n_set_delay_mode;
extern SET_DELAY_MODE set_delay_mode;
extern N_SET_PISO_CONTROL n_set_piso_control;
extern SET_PISO_CONTROL set_piso_control;
extern N_SELECT_STATUS n_select_status;
extern SELECT_STATUS select_status;
extern N_GET_ENCODER n_get_encoder;
extern GET_ENCODER get_encoder;
extern N_SELECT_COR_TABLE n_select_cor_table;
extern SELECT_COR_TABLE select_cor_table;
extern N_EXECUTE_AT_POINTER n_execute_at_pointer;
extern EXECUTE_AT_POINTER execute_at_pointer;
extern N_GET_HEAD_STATUS n_get_head_status;
extern GET_HEAD_STATUS get_head_status;
extern N_SIMULATE_ENCODER n_simulate_encoder;
extern SIMULATE_ENCODER simulate_encoder;
extern N_SET_HI n_set_hi;
extern SET_HI set_hi;
extern N_RELEASE_WAIT n_release_wait;
extern RELEASE_WAIT release_wait;
extern N_GET_WAIT_STATUS n_get_wait_status;
extern GET_WAIT_STATUS get_wait_status;
extern N_SET_CONTROL_MODE n_set_control_mode;
extern SET_CONTROL_MODE set_control_mode;
extern N_SET_LASER_MODE n_set_laser_mode;
extern SET_LASER_MODE set_laser_mode;
extern N_SET_EXT_START_DELAY n_set_ext_start_delay;
extern SET_EXT_START_DELAY set_ext_start_delay;
extern N_HOME_POSITION n_home_position;
extern HOME_POSITION home_position;
extern N_SET_ROT_CENTER n_set_rot_center;
extern SET_ROT_CENTER set_rot_center;
extern N_DSP_START n_dsp_start;
extern DSP_START dsp_start;
extern N_WRITE_DA_X n_write_da_x;
extern WRITE_DA_X write_da_x;
extern N_READ_AD_X n_read_ad_x;
extern READ_AD_X read_ad_x;
extern N_READ_PIXEL_AD n_read_pixel_ad;
extern READ_PIXEL_AD read_pixel_ad;
extern N_GET_Z_DISTANCE n_get_z_distance;
extern GET_Z_DISTANCE get_z_distance;
extern N_GET_IO_STATUS n_get_io_status;
extern GET_IO_STATUS get_io_status;
extern N_GET_TIME n_get_time;
extern GET_TIME get_time;
extern N_SET_DEFOCUS n_set_defocus;
extern SET_DEFOCUS set_defocus;
extern N_SET_SOFTSTART_MODE n_set_softstart_mode;
extern SET_SOFTSTART_MODE set_softstart_mode;
extern N_SET_SOFTSTART_LEVEL n_set_softstart_level;
extern SET_SOFTSTART_LEVEL set_softstart_level;
extern N_CONTROL_COMMAND n_control_command;
extern CONTROL_COMMAND control_command;
extern LOAD_COR load_cor;
extern LOAD_PRO load_pro;
extern N_GET_SERIAL_NUMBER n_get_serial_number;
extern GET_SERIAL_NUMBER get_serial_number;
extern N_GET_SERIAL_NUMBER_32 n_get_serial_number_32;
extern GET_SERIAL_NUMBER_32 get_serial_number_32;
extern N_GET_RTC_VERSION n_get_rtc_version;
extern GET_RTC_VERSION get_rtc_version;
extern GET_HI_DATA get_hi_data;
extern N_AUTO_CAL n_auto_cal;
extern AUTO_CAL auto_cal;
extern N_GET_LIST_SPACE n_get_list_space;
extern GET_LIST_SPACE get_list_space;
extern TEACHIN teachin;
extern N_GET_VALUE n_get_value;
extern GET_VALUE get_value;
extern N_SET_IO_BIT n_set_io_bit;
extern SET_IO_BIT set_io_bit;
extern N_CLEAR_IO_BIT n_clear_io_bit;
extern CLEAR_IO_BIT clear_io_bit;
extern SET_DUTY_CYCLE_TABLE set_duty_cycle_table;
extern N_MOVE_TO n_move_to;
extern MOVE_TO move_to;
