#ifndef	__AXT_CNT_DEFINE_H__
#define	__AXT_CNT_DEFINE_H__

/* Main clock							*/
#define F_50M_CLK						50000000L			/* 50.000 MHz */


/* Read/Write port							*/
typedef enum _CNTPORT_DATA_WRITE
{
	CnCommand	= 0x10,
	CnData1		= 0x12,
	CnData2		= 0x14,
	CnData3		= 0x16,
	CnData4		= 0x18
}CNTPORT_DATA;

typedef enum _CNTRAM_DATA
{
	CnRamAddr1	= 0x28,
	CnRamAddr2	= 0x2A,
	CnRamAddr3	= 0x2C
}CNTRAM_DATA;

typedef enum _PHASE_SEL
{
	CnAbPhase	= 0x0,
	CnZPhase	= 0x1
} PHASE_SEL;

typedef enum _COUNTER_INPUT
{
	CnUpDownMode = 0x0,					// Up/Down
	CnSqr1Mode   = 0x1,					// 1체배
	CnSqr2Mode   = 0x2,					// 2체배
	CnSqr4Mode   = 0x3					// 4체배
} COUNTER_INPUT;

/* CNT COMMAND LIST						*/
typedef enum _CNTCOMMAND
{
    // CH-1 Group Register
    CnCh1CounterRead					= 0x10,				// CH1 COUNTER READ, 24BIT
    CnCh1CounterWrite					= 0x90,				// CH1 COUNTER WRITE
    CnCh1CounterModeRead				= 0x11,				// CH1 COUNTER MODE READ, 8BIT
    CnCh1CounterModeWrite				= 0x91,				// CH1 COUNTER MODE WRITE
    CnCh1TriggerRegionLowerDataRead		= 0x12,				// CH1 TRIGGER REGION LOWER DATA READ, 24BIT
    CnCh1TriggerRegionLowerDataWrite	= 0x92,				// CH1 TRIGGER REGION LOWER DATA WRITE
    CnCh1TriggerRegionUpperDataRead		= 0x13,				// CH1 TRIGGER REGION UPPER DATA READ, 24BIT
    CnCh1TriggerRegionUpperDataWrite	= 0x93,				// CH1 TRIGGER REGION UPPER DATA WRITE
    CnCh1TriggerPeriodRead				= 0x14,				// CH1 TRIGGER PERIOD READ, 24BIT, RESERVED
    CnCh1TriggerPeriodWrite				= 0x94,				// CH1 TRIGGER PERIOD WRITE
    CnCh1TriggerPulseWidthRead			= 0x15,				// CH1 TRIGGER PULSE WIDTH READ
    CnCh1TriggerPulseWidthWrite			= 0x95,				// CH1 RIGGER PULSE WIDTH WRITE
    CnCh1TriggerModeRead				= 0x16,				// CH1 TRIGGER MODE READ
    CnCh1TriggerModeWrite				= 0x96,				// CH1 RIGGER MODE WRITE
	CnCh1TriggerStatusRead				= 0x17,				// CH1 TRIGGER STATUS READ
    CnCh1NoOperation_97					= 0x97,				// 
	CnCh1TriggerEnable					= 0x98,
	CnCh1TriggerDisable					= 0x99,
	CnCh1TimeTriggerFrequencyRead		= 0x1A,
	CnCh1TimeTriggerFrequencyWrite		= 0x9A,
	CnCh1ComparatorValueRead			= 0x1B,
	CnCh1ComparatorValueWrite			= 0x9B,
	CnCh1CompareatorConditionRead		= 0x1D,
	CnCh1CompareatorConditionWrite		= 0x9D,

    // CH-2 Group Register
    CnCh2CounterRead					= 0x20,				// CH2 COUNTER READ, 24BIT
    CnCh2CounterWrite					= 0xA1,				// CH2 COUNTER WRITE
    CnCh2CounterModeRead				= 0x21,				// CH2 COUNTER MODE READ, 8BIT
    CnCh2CounterModeWrite				= 0xA1,				// CH2 COUNTER MODE WRITE
    CnCh2TriggerRegionLowerDataRead		= 0x22,				// CH2 TRIGGER REGION LOWER DATA READ, 24BIT
    CnCh2TriggerRegionLowerDataWrite	= 0xA2,				// CH2 TRIGGER REGION LOWER DATA WRITE
    CnCh2TriggerRegionUpperDataRead		= 0x23,				// CH2 TRIGGER REGION UPPER DATA READ, 24BIT
    CnCh2TriggerRegionUpperDataWrite	= 0xA3,				// CH2 TRIGGER REGION UPPER DATA WRITE
    CnCh2TriggerPeriodRead				= 0x24,				// CH2 TRIGGER PERIOD READ, 24BIT, RESERVED
    CnCh2TriggerPeriodWrite				= 0xA4,				// CH2 TRIGGER PERIOD WRITE
    CnCh2TriggerPulseWidthRead			= 0x25,				// CH2 TRIGGER PULSE WIDTH READ, 24BIT
    CnCh2TriggerPulseWidthWrite			= 0xA5,				// CH2 RIGGER PULSE WIDTH WRITE
    CnCh2TriggerModeRead				= 0x26,				// CH2 TRIGGER MODE READ
    CnCh2TriggerModeWrite				= 0xA6,				// CH2 RIGGER MODE WRITE
	CnCh2TriggerStatusRead				= 0x27,				// CH2 TRIGGER STATUS READ
    CnCh2NoOperation_A7					= 0xA7,				//
	CnCh2TriggerEnable					= 0xA8,
	CnCh2TriggerDisable					= 0xA9,
	CnCh2TimeTriggerFrequencyRead		= 0x2A,
	CnCh2TimeTriggerFrequencyWrite		= 0xAA,
	CnCh2ComparatorValueRead			= 0x2B,
	CnCh2ComparatorValueWrite			= 0xAB,
	CnCh2CompareatorConditionRead		= 0x2D,
	CnCh2CompareatorConditionWrite		= 0xAD,
	
    // Ram Access Group Register
    CnRamDataWithRamAddress				= 0x30,				// READ RAM DATA WITH RAM ADDR PORT ADDRESS
    CnRamDataWrite						= 0xB0,				// RAM DATA WRITE
    CnRamDataRead						= 0x31,				// RAM DATA READ, 32BIT

}CNTCOMMAND;
#endif