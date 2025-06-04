// SIDDKAPI.h

// This file needs to be included with the driver and with all calling applications

// which use the DeviceIOControl() WIN32 interface to the SI-DDK PCI Driver



#ifndef CTL_CODE

#pragma message(" ")

#pragma message("CTL_CODE undefined. Using the code copied from winioctl.h (or devioctl.h).")

#pragma message("If you are compiling for WDM, include winioctl.h or devioctl.h before this file.")

#pragma message(" ")



// These are all taken from DEVIOCTL.H



#define FILE_DEVICE_UNKNOWN             0x00000022



//

// Macro definition for defining IOCTL and FSCTL function control codes.  Note

// that function codes 0-2047 are reserved for Microsoft Corporation, and

// 2048-4095 are reserved for customers.

//



#define CTL_CODE( DeviceType, Function, Method, Access ) (((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method))



//

// Define the method codes for how buffers are passed for I/O and FS controls

//



#define METHOD_BUFFERED                 0

#define METHOD_IN_DIRECT                1

#define METHOD_OUT_DIRECT               2

#define METHOD_NEITHER                  3



//

// Define the access check value for any access

//

//

// The FILE_READ_ACCESS and FILE_WRITE_ACCESS constants are also defined in

// ntioapi.h as FILE_READ_DATA and FILE_WRITE_DATA. The values for these

// constants *MUST* always be in sync.

//



#define FILE_ANY_ACCESS                 0

#define FILE_READ_ACCESS          ( 0x0001 )

#define FILE_WRITE_ACCESS         ( 0x0002 )



#endif

//

// define the unified IOCTL codes

//



#define IOCTL_SHELDON_MAILBOX_READ	CTL_CODE(FILE_DEVICE_UNKNOWN,	0x801,	METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_MAILBOX_WRITE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_OPREG_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_OPREG_WRITE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_PASSTHROUGH_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_PASSTHROUGH_WRITE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x806, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_FIFO_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x807, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_FIFO_WRITE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x808, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_NVRAM_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x809, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_NVRAM_WRITE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80A, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_CONFIG_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80B, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_CONFIG_WRITE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80C, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_BUSMASTERED_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80D, METHOD_OUT_DIRECT,	FILE_READ_ACCESS)
#define IOCTL_SHELDON_BUSMASTERED_WRITE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80E, METHOD_IN_DIRECT, FILE_WRITE_ACCESS)
#define IOCTL_SHELDON_DEBUG	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80F, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_SETUP_CALLBACK	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x821, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_CANCEL_BUSMASTERING	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x822, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_SET_TIMEOUT	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x823, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_GET_BADDR	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x824, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_RELEASE_BADDR	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x825, METHOD_BUFFERED, FILE_ANY_ACCESS)


// Begin: Chipset Optional defines

//		These are optional calls that are chipset specific.

//		AMCC supports 8/16 bit modes, so these are present.

#define IOCTL_SHELDON_PASSTHROUGH_READ16 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x812, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_PASSTHROUGH_WRITE16 CTL_CODE(FILE_DEVICE_UNKNOWN,	0x813, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_PASSTHROUGH_READ8	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x814, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_PASSTHROUGH_WRITE8 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x815, METHOD_BUFFERED, FILE_ANY_ACCESS)
// End: Chipset Optional defines



// Begin: OS Optional defines

//		these are only for Windows 95 and are not needed under NT

//		However, NT does have dummy functions, so these calls are harmless

#define IOCTL_SHELDON_NUMBER_OF_BOARDS	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x810, METHOD_BUFFERED, FILE_ANY_ACCESS)

// this is just another name for the above function and should be identical to it

#define IOCTL_SHELDON_NUMBER_OF_DEVICES	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x810, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_REGISTER_NEW_BOARD CTL_CODE(FILE_DEVICE_UNKNOWN, 0x811, METHOD_BUFFERED, FILE_ANY_ACCESS)

// this is just another name for the above function and should be identical to it

#define IOCTL_SHELDON_REGISTER_NEW_DEVICE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x811, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SHELDON_CONFIG_RESTORE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x820, METHOD_BUFFERED, FILE_ANY_ACCESS)

// End: OS Optional defines



// Begin: SIHW Optional defines

//	Following calls are specific only to Sheldon Instruments boards.

//	If the DDK is not used for Sheldon Instruments boards, these calls

//		can be removed. Leaving them in place does not affect the 

//		operation of the driver as long as the application does not call

//		these IOCTL values.

//	Following locations contain DUAL_ACCESS related functions.

//		- Here.

//		- Function declaration header file.

//		- IOControl handler case statement.

//		- Actual function called from IOControl handler.


#define IOCTL_SHELDON_DUAL_ACCESS_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x81A, METHOD_OUT_DIRECT,	FILE_READ_ACCESS)
#define IOCTL_SHELDON_DUAL_ACCESS_WRITE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x81B, METHOD_IN_DIRECT, FILE_WRITE_ACCESS)

// End: SIHW Optional defines



// The following defines specify the array index of information passed

// to and from the driver in an array of 32 bit numbers



#define	SI_MAILBOX_NUM_INDEX			0

#define	SI_MAILBOX_WRITE_DATA_INDEX		1

#define	SI_MAILBOX_WRITE_TOSIZE			2*sizeof(ULONG)

#define	SI_MAILBOX_WRITE_FROMSIZE		0					



#define	SI_MAILBOX_READ_DATA_INDEX		0

#define	SI_MAILBOX_READ_TOSIZE			1*sizeof(ULONG)

#define	SI_MAILBOX_READ_FROMSIZE		1*sizeof(ULONG)					





#define	SI_OPREG_NUM_INDEX				0

#define	SI_OPREG_WRITE_DATA_INDEX		1

#define	SI_OPREG_WRITE_TOSIZE			2*sizeof(ULONG)

#define	SI_OPREG_WRITE_FROMSIZE			0					



#define	SI_OPREG_READ_DATA_INDEX		0

#define	SI_OPREG_READ_TOSIZE			1*sizeof(ULONG)

#define	SI_OPREG_READ_FROMSIZE			1*sizeof(ULONG)					



#define SI_FIFO_READ_DATA_INDEX			0

#define SI_FIFO_WRITE_DATA_INDEX		0

#define SI_FIFO_READ_TOSIZE				0

#define SI_FIFO_WRITE_TOSIZE			1*sizeof(ULONG)

#define SI_FIFO_READ_FROMSIZE			1*sizeof(ULONG)

#define SI_FIFO_WRITE_FROMSIZE			0



#define SI_PASSTHROUGH_REGION_INDEX		0

#define SI_PASSTHROUGH_OFFSET_INDEX		1

#define SI_PASSTHROUGH_COUNT_INDEX		2



#define SI_PASSTHROUGH_READ_TOSIZE		3*sizeof(ULONG)		

#define SI_PASSTHROUGH_READ_FROMSIZE	0				

#define SI_PASSTHROUGH_READ_DATA_INDEX	0



#define SI_PASSTHROUGH_WRITE_TOSIZE		3*sizeof(ULONG)		

#define SI_PASSTHROUGH_WRITE_FROMSIZE	0				

#define SI_PASSTHROUGH_WRITE_DATA_INDEX	3



#define SI_CONFIG_READ_TOSIZE			2*sizeof(ULONG)

#define SI_CONFIG_WRITE_TOSIZE			2*sizeof(ULONG)

#define SI_CONFIG_READ_FROMSIZE			0

#define SI_CONFIG_WRITE_FROMSIZE		0



#define SI_CONFIG_OFFSET_INDEX			0

#define SI_CONFIG_COUNT_INDEX			1

#define SI_CONFIG_WRITE_DATA_INDEX		2

#define SI_CONFIG_READ_DATA_INDEX		0



#define SI_NV_OFFSET_INDEX				0

#define SI_NV_READ_TOSIZE				1*sizeof(ULONG)

#define SI_NV_READ_FROMSIZE				1*sizeof(ULONG)

#define SI_NV_READ_DATA_INDEX			0

#define SI_NV_WRITE_TOSIZE				2*sizeof(ULONG)

#define SI_NV_WRITE_FROMSIZE			0

#define SI_NV_WRITE_DATA_INDEX			1



#define SI_BUSMASTERED_READ_TOSIZE		1*sizeof(ULONG)

#define SI_BUSMASTERED_READ_FROMSIZE	0

#define SI_BUSMASTERED_READ_COUNT_INDEX	0



#define SI_BUSMASTERED_WRITE_TOSIZE		0

#define SI_BUSMASTERED_WRITE_FROMSIZE		0

#define SI_BUSMASTERED_WRITE_COUNT_INDEX	0



#define SI_CALLBACK_HANDLE_INDEX		0

#define SI_SETUP_CALLBACK_TOSIZE		4



#define SI_SET_TIMEOUT_INDEX			0

#define SI_SET_TIMEOUT_TOSIZE			4



#define SI_GET_BADDR_FROMSIZE			20



// This value is in miliseconds and should be the same as one page in Version 1.2

// Set INITIAL TIMEOUT to zero to disable timeout

#define INITIAL_TIMEOUT					5096



