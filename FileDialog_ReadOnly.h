#ifndef _038d96a6_fcde_49f0_b746_d28903f6b98c_FILEDLG_RO
#   define _038d96a6_fcde_49f0_b746_d28903f6b98c_FILEDLG_RO

//××××××××××××××××
// FileDialog_ReadOnly.h: header file for implementing a read-only File
// Open and File Save common-control dialog box.
//
// Works for standard Win32 GetOpenFileName() and GetSaveFileName() dialogs.
//××××××××××××××××

// Programmer's Note: the code here doesn't really require MFC at all.
// MFC is used only because it provides the useful CString class.  If you
// wish, you can rework the code to use std::string or any other string
// class you prefer.  I use CString because it's familiar and convenient.
// 
// Here, we include <afxwin.h> to provide access to MFC classes without
// actually using the entire MFC framework.  But if you include afxwin.h,
// don't include <windows.h> -- the compiler will complain.

#include <afxwin.h>	    // provide access to CString

#include <windowsx.h>	    // needed for GetWindowStyle() macro (plus others)

//-----------------------------------------------------------------------------
// How to Discover Toolbar Buttons ID's
//
//  (1)	#define FIND_TOOLBAR_BUTTON_IDS, then compile the application
//	in Debug mode (instead of Release mode).  Debug mode is required
//	so that OutputDebugString() can print info to the Visual Studio 
//	Debug output window.  In Release mode, OutputDebugString()
//	doesn't do anything.
//
//  (2) Run the application, then hover your mouse pointer over the 
//	toolbar button you want to discover the ID of.  Hovering
//	eventually causes a tooltip help window to appear, for that
//	toolbar button.
//
//  (3) When the tooltip help window appears, a series of WM_NOTIFY
//	messages is sent to the ToolbarWindow32 control.  These
//	messages are trapped by the NewToolbarWndProc().  Since 
//	WM_NOTIFY contains the ID of the control sending the message, 
//	the message can be used to discover the control's ID. 
//
//  (4) NewToolbarWndProc() parses the WM_NOTIFY message and prints 
//	the control's ID out in the Visual Studio Debug window.
//
// Any WM_NOTIFY message that the toolbar button sends is actually
// sufficient.  Hovering the mouse is one of the simplest and least
// invasive ways of triggering a WM_NOTIFY.  But you could use right
// mouse-click, or any other mouse activity, for example.

// #define FIND_TOOLBAR_BUTTON_IDS

//-----------------------------------------------------------------------------


// Declare the callback and hook procedures you need.  These have to be
// extern "C", and cannot be member functions of a CFileDialog_ReadOnly
// object since the operating system cannot pass a 'this' pointer as 
// one of the arguments.

extern "C" 
{
    // Dialog procedure, for the "child dialog window" created by the
    // standard Win32 ::GetOpenFileName() dialog call.  FileDialogHookProc()
    // gets called in place of the dialog procedure normally used by the
    // child dialog window.

    UINT CALLBACK FileDialogHookProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam );

    // NewKeybdHook() is the keyboard hook installed by InstallKeyboardHook().
    // Needed to detect and discard <Delete>, <Shift-Delete>, <Ctrl-X>, <Ctrl-V>.

    UINT CALLBACK NewKeybdHook( int nCode, WPARAM wParam, LPARAM lParam );  // new (custom) keyboard handler (hook)

    // NewShellDefWndProc() is the new window procedure installed by
    // SetSHELLDefViewWindowProc().  Needed to detect LVN_BEGINDRAG notifications.

    LRESULT CALLBACK NewShellDefWndProc( HWND, UINT, WPARAM, LPARAM );	    // custom window procedure

    // NewListViewWndProc() is the new window procedure installed by
    // SetListViewWindowProc().  Needed to detect mouse right-clicks.

    LRESULT CALLBACK NewListViewWndProc( HWND, UINT, WPARAM, LPARAM );	    // custom window procedure

#ifdef FIND_TOOLBAR_BUTTON_IDS

    // If you want to discover the control ID's of the toolbar buttons in the
    // ToolbarWindow32 control that appears at the top of the dialog window,
    // you have to intercept WM_NOTIFY messages sent by the ToolbarWindow32
    // to the parent dialog.
    //
    // Once you've discovered the control ID's (one-time) for your particular
    // OS (Win98, Win2K, WinXP, whatever), you don't need to hook the dialog
    // procedure anymore.  So in general you don't need this code.

    LRESULT CALLBACK NewToolbarWndProc( HWND, UINT, WPARAM, LPARAM );	    // custom window procedure

#endif

}

// Other forward declarations.  These could be static member functions of
// the CFileDialog_ReadOnly object, in principle.

void InstallKeyboardHook( BOOL bInstalling );
void SetSHELLDefViewWindowProc();
void SetListViewWindowProc();
void AdjustListViewStyle();
void HideToolbarButtons();
void GetWindowHandles();

#ifdef FIND_TOOLBAR_BUTTON_IDS

void SetToolbarWindowProc();

#endif

//-----------------------------------------------------------------------------
class CFileDialog_ReadOnly
{
    public:

	OPENFILENAME m_ofn;	// standard OPENFILENAME struct
	
	// Constructor.  For an example, see the OnButtonClickMe() method in the
	// TestOpenFileDialogDlg.cpp file.

	// Programmer's Remark: to make the dialog modal with respect to an
	// "owner" window, you must provide the handle of the owner window.
	// Otherwise the dialog box doesn't act as if it were modal.  This is the
	// reason for requiring the 'hwndOwner' data member.

	CFileDialog_ReadOnly(
	    BOOL bOpenFileDialog,		// use TRUE for File Open dialog, FALSE for File Save dialog
	    HWND hwndOwner = NULL,		// dialog will be modal with respect to this window
	    LPCTSTR pInitialDirectory = ".",	// initial directory to open in
	    LPCTSTR pInitialFileName = NULL,	// initial filename to display
	    LPCTSTR pAllowedExts = NULL,	// list of allowed file extensions, that dialog will show
	    DWORD dwExtsBuffSize = 0,		// size of 'pAllowedExts' buffer (incl. null terminator)
	    LPCTSTR pDefaultFileExt = NULL,	// default extension to use when saving the file (no dot)
	    DWORD dwFlags = 0 			// flags controlling the dialog style
	);

	int DoModal();		    // returns IDOK or IDCANCEL, depending on how dialog box was closed

	// Assuming file "C:\Fred\barney.txt" as an example,

	CString GetPathName() const;	    // full path + filename of the file, eg. "C:\Fred\barney.txt"
	CString GetFileName() const;	    // unqualified filename + extension, eg. "barney.txt"
	CString GetFileExt() const;	    // extension only (no dot), eg. "txt"
	CString GetFileTitle() const;	    // bare filename, no extension, eg. "barney"
	CString GetDirName() const;	    // path only: folder containing the file, eg. "C:\Fred"

	// Event handler.  (Just a stub, not implemented in this version).

	virtual void OnFolderChange();	    // handler for common dialog notification CDN_FOLDERCHANGE

    private:

	char m_szFilter       [ MAX_PATH ];	// actual data buffers, for m_ofn data member pointers
	char m_szCustomFilter [ MAX_PATH ];
	char m_szFile         [ MAX_PATH ];
	char m_szFileTitle    [ MAX_PATH ];
	char m_szInitialDir   [ MAX_PATH ];
	char m_szTitle        [ MAX_PATH ];

	char m_szDefaultExt[ 4 ];   // max 3 characters, plus terminating null

	BOOL m_bOpenFileDialog;	    // TRUE = 'File Open' dialog, FALSE = 'File Save' dialog

	HWND m_hwndOwner;	    // handle to the "owner" window; needed to make dialog modal

};  // class CFileDialog_ReadOnly

//-----------------------------------------------------------------------------

#endif

