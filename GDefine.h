#ifndef _GDEFINE_H_
#define _GDEFINE_H_

// lee do yeon 24-06-19
//typedef signed char 

typedef enum _ACK5
{
    ACK5_Normal = 0,    // ¸Þ½ÃÁö Á¤»ó ¼ö½Å
    ACK5_Error = 1      // Error, not Accepted
} ACK5;

typedef enum _ACK6
{
    ACK6_Normal = 0,    // ¸Þ½ÃÁö Á¤»ó ¼ö½Å
    ACK6_Error = 1      // Error, not Accepted
} ACK6;

typedef enum _ACKC7
{
    ACKC7_Normal = 0,            // Recipe Download Á¤»ó
    ACKC7_Permission_Denied = 1, // Permission not granted
    ACKC7_LenError = 2,          // Length Error
    ACKC7_Matrix_Overflow = 3,   // Matrix_Overflow
    ACKC7_PPID_Null = 4,         // PPID not found
    ACKC7_Mode_Unsupport = 5,    // Mode Unsupported
    ACKC7_Reserved_1 = 6,
    ACKC7_Reserved_2 = 7,
    ACKC7_Reserved_3 = 8,
    ACKC7_Reserved_4 = 9,
    ACKC7_Reserved_5 = 10,
    ACKC7_Reserved_6 = 11,
    ACKC7_Reserved_7 = 12,
    ACKC7_Reserved_8 = 13,
    ACKC7_Reserved_9 = 14,
    ACKC7_Reserved_10 = 15,
    ACKC7_Reserved_11 = 16,
    ACKC7_Reserved_12 = 17,
    ACKC7_Reserved_13 = 18,
    ACKC7_Reserved_14 = 19,
    ACKC7_Reserved_15 = 20,
    ACKC7_Reserved_16 = 21,
    ACKC7_Reserved_17 = 22,
    ACKC7_Reserved_18 = 23,
    ACKC7_Reserved_19 = 24,
    ACKC7_Reserved_20 = 25,
    ACKC7_Reserved_21 = 26,
    ACKC7_Reserved_22 = 27,
    ACKC7_Reserved_23 = 28,
    ACKC7_Reserved_24 = 29,
    ACKC7_Reserved_25 = 30,
    ACKC7_Reserved_26 = 31,
    ACKC7_Reserved_27 = 32,
    ACKC7_Reserved_28 = 33,
    ACKC7_Reserved_29 = 34,
    ACKC7_Reserved_30 = 35,
    ACKC7_Reserved_31 = 36,
    ACKC7_Reserved_32 = 37,
    ACKC7_Reserved_33 = 38,
    ACKC7_Reserved_34 = 39,
    ACKC7_Reserved_35 = 40,
    ACKC7_Reserved_36 = 41,
    ACKC7_Reserved_37 = 42,
    ACKC7_Reserved_38 = 43,
    ACKC7_Reserved_39 = 44,
    ACKC7_Reserved_40 = 45,
    ACKC7_Reserved_41 = 46,
    ACKC7_Reserved_42 = 47,
    ACKC7_Reserved_43 = 48,
    ACKC7_Reserved_44 = 49,
    ACKC7_Reserved_45 = 50,
    ACKC7_Reserved_46 = 51,
    ACKC7_Reserved_47 = 52,
    ACKC7_Reserved_48 = 53,
    ACKC7_Reserved_49 = 54,
    ACKC7_Reserved_50 = 55,
    ACKC7_Reserved_51 = 56,
    ACKC7_Reserved_52 = 57,
    ACKC7_Reserved_53 = 58,
    ACKC7_Reserved_54 = 59,
    ACKC7_Reserved_55 = 60,
    ACKC7_Reserved_56 = 61,
    ACKC7_Reserved_57 = 62,
    ACKC7_Reserved_58 = 63
} ACKC7;

typedef enum _ALCD
{
	ALCD_Set = 128,
	ALCD_Clear = 0
} ALCD;

typedef enum _ALID
{
	// ¹ß»ý ¾Ë¶÷º° À¯´ÏÅ© ¾ÆÀÌµð


} ALID;

typedef enum _ALKD
{
    ALKD_Minor = 0, // °æ¾Ë¶÷
    ALKD_Major = 1  // Áß¾Ë¶÷
} ALKD;
				// CEID Á¤ÀÇ //
//////////////////////////////////////////////////
#define	CEID_CommState_OffLine			1001	//
#define	CEID_CommState_OnLine			1002	//
#define	CEID_Operation_AutoStart		1011	//
#define	CEID_Operation_AutoStop			1012	//
#define	CEID_Operation_Manual			1013	//
#define	CEID_Operation_Auto				1014	//
#define	CEID_Operation_DownStart		1015	//
#define	CEID_Operation_DownEnd			1016	//
#define	CEID_Process_Ready				1021	//
#define	CEID_Processing					1022	//
#define	CEID_Process_Idle				1023	//
#define	CEID_Process_Pause				1024	//
#define	CEID_Change_Setting_StartReq	1025	//
#define	CEID_Change_Setting_EndReq		1026	//
#define	CEID_Dummy_Cell_Start			1027	//
#define	CEID_Dummy_Cell_End				1028	//
#define	CEID_Main_Start					1031	//
#define	CEID_Main_End					1032	//
#define	CEID_MaxState_INPRG				1041	//
#define	CEID_MaxState_QUAL				1042	//
#define	CEID_MaxState_COMP				1043	//
#define	CEID_MaxState_REFRESH			1044	//
#define	CEID_PCState_Report_AutoRun		1051	//
#define	CEID_PCState_Report_AutoStop	1052	//
#define	CEID_PCState_Report_Pause		1054	//
#define	CEID_Machine_Interlock_Set		2001	//
#define	CEID_Machine_Interlock_Release	2002	//
#define	CEID_Machine_Warning			2003	//
#define	CEID_Interlock_OffReq			2004	//
#define	CEID_Recipe_DownloadReq			3001	//
#define	CEID_SVChange					3002	//
#define	CEID_Meterial_IDReading			3003	//
#define	CEID_Recipe_Confirm				3004	//
#define	CEID_Recipe_Setting_Complete	3005	//
#define	CEID_JobChange_Report			3006	//
#define	CEID_Meterials_Changed			3007	//
#define	CEID_Next_RecipeReq				3009	//
#define	CEID_Data_Collection_Report		4001	//
#define	CEID_TransferIn					4002	//
#define	CEID_TransferOut				4003	//
#define	CEID_IdxTimeData_Report			4004	//
#define	CEID_LoginReq					4005	//
#define	CEID_WorkOrder_DownloadReq		4006	//
#define	CEID_WorkOrder_Changing			4022	//
#define	CEID_NG_Data_Report				6021	//
#define	CEID_LotChange_Report			4008	//
#define	CEID_LotCreate_Report			4009	//
#define	CEID_BatchCreate_Report			4010	//
#define	CEID_EQtoEQ						4011	//
#define	CEID_LotInformationReq			4012	//
#define	CEID_BatchInformationReq		4013	//
#define	CEID_LotStart_Report			4014	//
#define	CEID_LotEnd_Report				4015	//
#define	CEID_Maximo_LoginReq			4016	//
#define	CEID_MccData_Report				4017	//
#define	CEID_Interlock_LoginReq			4018	//
#define	CEID_Recipe_LoginReq			4019	//
#define	CEID_UBM_ResetReq				4025	//
#define	CEID_UBM_LoginReq				4026	//
#define	CEID_Window_LotStart			4225	//
#define	CEID_Window_LotEnd				4226	//
//////////////////////////////////////////////////



#define CODE_43010847 43010847
#define CODE_43010848 43010848
#define CODE_43010849 43010849
#define CODE_43010850 43010850
#define CODE_43010851 43010851
#define CODE_43010852 43010852
#define CODE_43010853 43010853
#define CODE_43010854 43010854
#define CODE_43010855 43010855
#define CODE_43010856 43010856
#define CODE_43010857 43010857
#define CODE_43010858 43010858
#define CODE_43010859 43010859
#define CODE_43010860 43010860
#define CODE_43010861 43010861
#define CODE_43010862 43010862
#define CODE_43010863 43010863
#define CODE_43010864 43010864
#define CODE_43010865 43010865
#define CODE_43010866 43010866
#define CODE_43010867 43010867
#define CODE_43010868 43010868
#define CODE_43010869 43010869
#define CODE_43010870 43010870
#define CODE_43010871 43010871
#define CODE_43010872 43010872
#define CODE_43010873 43010873
#define CODE_43010874 43010874
#define CODE_43010875 43010875
#define CODE_43010876 43010876
#define CODE_43010877 43010877
#define CODE_43010878 43010878
#define CODE_43010879 43010879
#define CODE_43010880 43010880
#define CODE_43010881 43010881
#define CODE_43010882 43010882
#define CODE_43010883 43010883
#define CODE_43010884 43010884
#define CODE_43010885 43010885
#define CODE_43010886 43010886
#define CODE_43010887 43010887
#define CODE_43010888 43010888
#define CODE_43010889 43010889
#define CODE_43010890 43010890

int nParamCode[] = {
	// Ãß°¡ ÄÚµå
	33010712, 33010713, 33010714, 33010715, 33010716,
	33010723, 33010726, 33010727, 33010728, 33010729,
	33010730, 33010731, 33010732, 33010737, 33010738,
	33010739, 33010740, 33010741, 33010742, 
	
	33010749, 33010750, 33010751, 33010752, 33010753, 
	33010760, 33010763, 33010764, 33010765, 33010766, 
	33010767, 33010768, 33010769, 33010774, 33010775, 
	33010776, 33010777, 33010778, 33010779, 
	
	43010756, 43010757,
	43010758, 43010759,

	43010847, 43010848, 
	
	43010849, 43010850, 43010851, 43010852, 43010853, 
	43010854, 43010855, 43010856, 43010857, 43010858, 
	43010859, 43010860, 43010861, 43010862, 43010863, 
	43010864, 43010865, 43010866, 43010867, 43010868, 
	43010869,
	
	43010870, 43010871, 43010872, 43010873, 43010874, 
	43010875, 43010876, 43010877, 43010878, 43010879,
	43010880, 43010881, 43010882, 43010883, 43010884, 
	43010885, 43010886, 43010887, 43010888, 43010889,
	43010890,

	53010087, 53010088,

	23010960,
	33010207,
	33010208,
	33010209,
	43010766
};



CString sParamName[] = {
	// Ãß°¡ÄÚµå
	"(46)[À½±Ø][³ëÄª] ÇÇµù ½ºÇÇµå",
	"(46)[À½±Ø][³ëÄª] ÀüÃ¼ ÆÐÅÏ ±æÀÌ",
	"(46)[À½±Ø][³ëÄª] ³ëÄª ±æÀÌ",
	"(46)[À½±Ø][³ëÄª] ³ëÄª ³ôÀÌ1",
	"(46)[À½±Ø][³ëÄª] ³ëÄª ³ôÀÌ2",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ ±æÀÌ",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ ÆÐÅÏ °³¼ö",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ Æø1",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ Æø2",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ Æø3",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ Æø4",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ Æø5",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ Æø6",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ °³¼ö1",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ °³¼ö2",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ °³¼ö3",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ °³¼ö4",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ °³¼ö5",
	"(46)[À½±Ø][³ëÄª] ÄÆÆÃ °³¼ö6",


	"(46)[¾ç±Ø][³ëÄª] ÇÇµù ½ºÇÇµå",
	"(46)[¾ç±Ø][³ëÄª] ÀüÃ¼ ÆÐÅÏ ±æÀÌ",
	"(46)[¾ç±Ø][³ëÄª] ³ëÄª ±æÀÌ",
	"(46)[¾ç±Ø][³ëÄª] ³ëÄª ³ôÀÌ1",
	"(46)[¾ç±Ø][³ëÄª] ³ëÄª ³ôÀÌ2",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ ±æÀÌ",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ ÆÐÅÏ °³¼ö",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ Æø1",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ Æø2",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ Æø3",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ Æø4",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ Æø5",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ Æø6",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ °³¼ö1",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ °³¼ö2",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ °³¼ö3",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ °³¼ö4",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ °³¼ö5",
	"(46)[¾ç±Ø][³ëÄª] ÄÆÆÃ °³¼ö6",


	"(46)[¾ç±Ø][³ëÄª] ³ëÄª H1 °¢µµ",
	"(46)[¾ç±Ø][³ëÄª] ³ëÄª H2 °¢µµ",
	"(46)[À½±Ø][³ëÄª] ³ëÄª H1 °¢µµ",
	"(46)[À½±Ø][³ëÄª] ³ëÄª H2 °¢µµ",

	"[46][À½±Ø] Ä¿ÆÃ ÃÑ °³¼ö",
	"[46][¾ç±Ø] Ä¿ÆÃ ÃÑ °³¼ö", 

	"[46][À½±Ø] Cutting Speed", // 
	"[46][À½±Ø] Cuting Ext Speed", // 
	"[46][À½±Ø] Cutting Line Speed",
	"[46][À½±Ø] Notching Line Speed",
	"[46][À½±Ø] Notching Inout Speed",  // ?
	"[46][À½±Ø] Jump Speed", 
	"[46][À½±Ø] Cutting Laser Power",
	"[46][À½±Ø] Notching Laser Power", 
	"[46][À½±Ø] Cutting Laser Frequency",
	"[46][À½±Ø] Notching Laser Frequency", 
	"[46][À½±Ø] Laser On Delay",
	"[46][À½±Ø] Laser Off Delay",
	"[46][À½±Ø] Mark Delay",
	"[46][À½±Ø] Jump Delay", 
	"[46][À½±Ø] Polygon Delay",
	"[46][À½±Ø] Starting Offset", 
	"[46][À½±Ø] Ending Offset",
	"[46][À½±Ø] Laser Pulse width",
	"[46][À½±Ø] Encoder Offset",
	"[46][À½±Ø] X Offset", 
	"[46][À½±Ø] Y Offset",

	"[46][¾ç±Ø] Cutting Speed", "[46][¾ç±Ø] Cuting Ext Speed", "[46][¾ç±Ø] Cutting Line Speed", "[46][¾ç±Ø] Notching Line Speed",
	"[46][¾ç±Ø] Notching Inout Speed", "[46][¾ç±Ø] Jump Speed", "[46][¾ç±Ø] Cutting Laser Power", "[46][¾ç±Ø] Notching Laser Power", "[46][¾ç±Ø] Cutting Laser Frequency",
	"[46][¾ç±Ø] Notching Laser Frequency", "[46][¾ç±Ø] Laser On Delay", "[46][¾ç±Ø] Laser Off Delay", "[46][¾ç±Ø] Mark Delay", "[46][¾ç±Ø] Jump Delay", "[46][¾ç±Ø] Polygon Delay",
	"[46][¾ç±Ø] Starting Offset", "[46][¾ç±Ø] Ending Offset", "[46][¾ç±Ø] Laser Pulse width", "[46][¾ç±Ø] Encoder Offset", "[46][¾ç±Ø] X Offset", "[46][¾ç±Ø] Y Offset",

	"[46][À½±Ø] Notching Offset", "[46][¾ç±Ø] Notching Offset",

	"[46][ÁýÁø±â] ÁýÁø±â Àü·ù",
	"[46][ÁýÁø±â] ÁýÁø±â ¿Âµµ",
	"[46][ÁýÁø±â] ÁýÁø±â À¯¼Ó",
	"[46][ÁýÁø±â] ¼Ò¼®È¸ ¹«°Ô",
	"[46][ÁýÁø±â] ÁýÁø±â Â÷¾Ð"

};

CString getCodeName(int code)
{
	for(int i = 0; i < 86; i++)
	{
		if(code == nParamCode[i])
		{
			return sParamName[i];
		}
	}

	return "Err Code";

};



// Collected Event Enable/Disable Code ( CEED )
#define CEED_ENABLE  TRUE  // Enable
#define CEED_DISABLE FALSE // Disable



typedef enum _CPVAL
{
	// CPNAME_Command_ParamVal_1
	// char / 20
} CPVAl;

#define _DATAID 0

typedef enum _DSPER
{
	// TRACE µ¥ÀÌÅÍ ¼öÁý ÁÖ±â ( hhmmss )
	// type : char , length : 6
} DSPER;

typedef enum _DRACK
{
    DRACK_Accept = 0,
    DRACK_Denied_InsufficientSpace = 1,
    DRACK_Denied_InvalidFormat = 2,
    DRACK_Denied_AtLeastOne_RPTID_AlreadyDefined = 3,
    DRACK_Denied_AtLeast_VID_NotExist = 4,
    DRACK_Other_Errors = 5,
    DRACK_Reserved_1 = 6,
    DRACK_Reserved_2 = 7,
    DRACK_Reserved_3 = 8,
    DRACK_Reserved_4 = 9,
    DRACK_Reserved_5 = 10,
    DRACK_Reserved_6 = 11,
    DRACK_Reserved_7 = 12,
    DRACK_Reserved_8 = 13,
    DRACK_Reserved_9 = 14,
    DRACK_Reserved_10 = 15,
    DRACK_Reserved_11 = 16,
    DRACK_Reserved_12 = 17,
    DRACK_Reserved_13 = 18,
    DRACK_Reserved_14 = 19,
    DRACK_Reserved_15 = 20,
    DRACK_Reserved_16 = 21,
    DRACK_Reserved_17 = 22,
    DRACK_Reserved_18 = 23,
    DRACK_Reserved_19 = 24,
    DRACK_Reserved_20 = 25,
    DRACK_Reserved_21 = 26,
    DRACK_Reserved_22 = 27,
    DRACK_Reserved_23 = 28,
    DRACK_Reserved_24 = 29,
    DRACK_Reserved_25 = 30,
    DRACK_Reserved_26 = 31,
    DRACK_Reserved_27 = 32,
    DRACK_Reserved_28 = 33,
    DRACK_Reserved_29 = 34,
    DRACK_Reserved_30 = 35,
    DRACK_Reserved_31 = 36,
    DRACK_Reserved_32 = 37,
    DRACK_Reserved_33 = 38,
    DRACK_Reserved_34 = 39,
    DRACK_Reserved_35 = 40,
    DRACK_Reserved_36 = 41,
    DRACK_Reserved_37 = 42,
    DRACK_Reserved_38 = 43,
    DRACK_Reserved_39 = 44,
    DRACK_Reserved_40 = 45,
    DRACK_Reserved_41 = 46,
    DRACK_Reserved_42 = 47,
    DRACK_Reserved_43 = 48,
    DRACK_Reserved_44 = 49,
    DRACK_Reserved_45 = 50,
    DRACK_Reserved_46 = 51,
    DRACK_Reserved_47 = 52,
    DRACK_Reserved_48 = 53,
    DRACK_Reserved_49 = 54,
    DRACK_Reserved_50 = 55,
    DRACK_Reserved_51 = 56,
    DRACK_Reserved_52 = 57,
    DRACK_Reserved_53 = 58,
    DRACK_Reserved_54 = 59,
    DRACK_Reserved_55 = 60,
    DRACK_Reserved_56 = 61,
    DRACK_Reserved_57 = 62,
    DRACK_Reserved_58 = 63
} DRACK;

typedef enum _ERACK
{
    ERACK_Accepted = 0,
    ERACK_DeniedAtLeastOne_CEID_NotExist = 1,
    ERACK_Reserved_1 = 2,
    ERACK_Reserved_2 = 3,
    ERACK_Reserved_3 = 4,
    ERACK_Reserved_4 = 5,
    ERACK_Reserved_5 = 6,
    ERACK_Reserved_6 = 7,
    ERACK_Reserved_7 = 8,
    ERACK_Reserved_8 = 9,
    ERACK_Reserved_9 = 10,
    ERACK_Reserved_10 = 11,
    ERACK_Reserved_11 = 12,
    ERACK_Reserved_12 = 13,
    ERACK_Reserved_13 = 14,
    ERACK_Reserved_14 = 15,
    ERACK_Reserved_15 = 16,
    ERACK_Reserved_16 = 17,
    ERACK_Reserved_17 = 18,
    ERACK_Reserved_18 = 19,
    ERACK_Reserved_19 = 20,
    ERACK_Reserved_20 = 21,
    ERACK_Reserved_21 = 22,
    ERACK_Reserved_22 = 23,
    ERACK_Reserved_23 = 24,
    ERACK_Reserved_24 = 25,
    ERACK_Reserved_25 = 26,
    ERACK_Reserved_26 = 27,
    ERACK_Reserved_27 = 28,
    ERACK_Reserved_28 = 29,
    ERACK_Reserved_29 = 30,
    ERACK_Reserved_30 = 31,
    ERACK_Reserved_31 = 32,
    ERACK_Reserved_32 = 33,
    ERACK_Reserved_33 = 34,
    ERACK_Reserved_34 = 35,
    ERACK_Reserved_35 = 36,
    ERACK_Reserved_36 = 37,
    ERACK_Reserved_37 = 38,
    ERACK_Reserved_38 = 39,
    ERACK_Reserved_39 = 40,
    ERACK_Reserved_40 = 41,
    ERACK_Reserved_41 = 42,
    ERACK_Reserved_42 = 43,
    ERACK_Reserved_43 = 44,
    ERACK_Reserved_44 = 45,
    ERACK_Reserved_45 = 46,
    ERACK_Reserved_46 = 47,
    ERACK_Reserved_47 = 48,
    ERACK_Reserved_48 = 49,
    ERACK_Reserved_49 = 50,
    ERACK_Reserved_50 = 51,
    ERACK_Reserved_51 = 52,
    ERACK_Reserved_52 = 53,
    ERACK_Reserved_53 = 54,
    ERACK_Reserved_54 = 55,
    ERACK_Reserved_55 = 56,
    ERACK_Reserved_56 = 57,
    ERACK_Reserved_57 = 58,
    ERACK_Reserved_58 = 59,
    ERACK_Reserved_59 = 60,
    ERACK_Reserved_60 = 61,
    ERACK_Reserved_61 = 62,
    ERACK_Reserved_62 = 63
} ERACK;

typedef enum _HCACK
{
	HCACK_Command_Exist = 0,
	HCACK_Command_NotExist = 1,
	HCACK_NotPerformNow = 2,
	HCACK_AtLeastOne_ParamIDVal = 3,
	HCACK_Reserved_1 = 4,
	HCACK_Reserved_2 = 5,
    HCACK_Reserved_3 = 6,
    HCACK_Reserved_4 = 7,
    HCACK_Reserved_5 = 8,
    HCACK_Reserved_6 = 9
} HCACK;

typedef enum _LRACK
{
    LRACK_Accepted = 0,
    LRACK_Denied_InsufficientSpace = 1,
    LRACK_Denied_InvalidFormat = 2,
    LRACK_Denied_AtLeastOne_CEID_LinkDefined = 3,
    LRACK_Denied_AtLeastOne_CEID_NotExist = 4,
    LRACK_Denied_AtLeastOne_RPTID_NotExist = 5,
    LRACK_Reserved_1 = 6,
    LRACK_Reserved_2 = 7,
    LRACK_Reserved_3 = 8,
    LRACK_Reserved_4 = 9,
    LRACK_Reserved_5 = 10,
    LRACK_Reserved_6 = 11,
    LRACK_Reserved_7 = 12,
    LRACK_Reserved_8 = 13,
    LRACK_Reserved_9 = 14,
    LRACK_Reserved_10 = 15,
    LRACK_Reserved_11 = 16,
    LRACK_Reserved_12 = 17,
    LRACK_Reserved_13 = 18,
    LRACK_Reserved_14 = 19,
    LRACK_Reserved_15 = 20,
    LRACK_Reserved_16 = 21,
    LRACK_Reserved_17 = 22,
    LRACK_Reserved_18 = 23,
    LRACK_Reserved_19 = 24,
    LRACK_Reserved_20 = 25,
    LRACK_Reserved_21 = 26,
    LRACK_Reserved_22 = 27,
    LRACK_Reserved_23 = 28,
    LRACK_Reserved_24 = 29,
    LRACK_Reserved_25 = 30,
    LRACK_Reserved_26 = 31,
    LRACK_Reserved_27 = 32,
    LRACK_Reserved_28 = 33,
    LRACK_Reserved_29 = 34,
    LRACK_Reserved_30 = 35,
    LRACK_Reserved_31 = 36,
    LRACK_Reserved_32 = 37,
    LRACK_Reserved_33 = 38,
    LRACK_Reserved_34 = 39,
    LRACK_Reserved_35 = 40,
    LRACK_Reserved_36 = 41,
    LRACK_Reserved_37 = 42,
    LRACK_Reserved_38 = 43,
    LRACK_Reserved_39 = 44,
    LRACK_Reserved_40 = 45,
    LRACK_Reserved_41 = 46,
    LRACK_Reserved_42 = 47,
    LRACK_Reserved_43 = 48,
    LRACK_Reserved_44 = 49,
    LRACK_Reserved_45 = 50,
    LRACK_Reserved_46 = 51,
    LRACK_Reserved_47 = 52,
    LRACK_Reserved_48 = 53,
    LRACK_Reserved_49 = 54,
    LRACK_Reserved_50 = 55,
    LRACK_Reserved_51 = 56,
    LRACK_Reserved_52 = 57,
    LRACK_Reserved_53 = 58,
    LRACK_Reserved_54 = 59,
    LRACK_Reserved_55 = 60,
    LRACK_Reserved_56 = 61,
    LRACK_Reserved_57 = 62,
    LRACK_Reserved_58 = 63
} LRACK;

typedef enum _MDLN
{
	// ¼³ºñ Model Number
	// type : char , length : 6
} MDLN;

typedef enum _OPERATOR_ID
{
	// ÀÛ¾÷ÀÚÀÇ ID
	// type : char , length : 10
} OPERATOR_ID;

typedef enum _PARMCD
{
	// Recipe Parameter Code
	// type : 
} PARMCD;
#endif