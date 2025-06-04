//××××××××××××××××
// FileDialog_ReadOnly.cpp: implementation of a read-only File Open and
// File Save common-control dialog box.
//
// Works for standard Win32 GetOpenFileName() and GetSaveFileName() dialogs.
//
// How To Use:
//
//  (1) #include "FileDialog_ReadOnly.h", somewhere in your file
//  (2) instantiate a CFileDialog_ReadOnly object, with the parameters you want
//  (3) call the object's DoModal() method
//
// Note: see remark below, about InitCommonControlsEx().
//××××××××××××××××

//================================
// Acknowledgements:
//
//  (1) Most of the code in this file was derived from code written by the
//      Win32 shell-programming guru Dino Esposito.  As of Jan 2004, his
//      original Microsoft article (MSJ, August 1999 issue), including
//      downloadable source code, can be found at:
//
//      http://www.microsoft.com/msj/0899/logo/logo.aspx
//
//      The article is entitled "The Logo and Beyond: Solutions for Writing 
//      Great Windows 2000-based Apps".  As the title suggests, it focuses 
//      on issues other than implementing a read-only File Open dialog box.
//      But the source code gives some very useful insight on how to do so.
//
//  (2) Also used is code derived from the article "Customizing the Windows 
//      Common File Open Dialog" written by author "S h a n x", posted at
//      codeproject.com.  As of Jan 2004, the original Codeproject article,
//      including downloadable source code, can be found at:
//
//      http://www.codeproject.net/dialog/customize_dialog.asp
//
//      S h a n x describes a method whereby toolbar buttons, present in
//      the Toolbar of Explorer-style common dialog boxes, can be disabled.
//      Other interesting customizations are also described.
//
//  (3) I recommend reading the MSDN documentation on Microsoft's web site
//      on the Common Dialogs.  As is usual for Microsoft documentation,
//      the information is of interest but doesn't give enough details to
//      really enable you to do anything.  Still, it's worth reading 
//      because it gives you some information that's hard to come by any
//      other way.  Search for "Customizing Common Dialog Boxes" on the
//      MSDN web site,
//
//      http://msdn.microsoft.com       
//
//      to uncover useful articles.
//================================


// Programmer's Note: this application uses the "new" Explorer-style
// common controls.  In order to use Explorer-style common controls, you
// must call Win32 ::InitCommonControlsEx().  This ensures the
// appropriate Window classes are registered in the system and that the
// DLLs containing the controls are loaded.
// 
// You don't have to worry about this if you're using MFC, because MFC
// does it for you.  The original Dino Esposito code explicitly calls
// InitCommonControlsEx() before doing anything else, just to ensure the
// new Common Controls are available.  It's possible that with the later
// versions of Windows, InitCommonControlsEx() is automatically loaded.
// I'm not sure.  On the other hand, calling it doesn't hurt.


// Programmer's Note: we use here the MFC CString class, so, we have to
// #include the MFC header file that contains the CString definition.  No
// other MFC functionality is used however.  If you wish, you can rework
// the code to use std::string or any other string class you prefer.
// Nothing special about CString, it's just familiar and therefore
// convenient for me.

#include "stdafx.h"     // needed for CString

#include "DLGS.H"       // needed for chx1, or any other standard ID's that you use

#include "FileDialog_ReadOnly.h"

// 'static' means the variable is not visible by name outside the file.
// But we can still access the variable by its memory address.

static HHOOK g_OldKeybdHook = NULL;             // original keyboard handler
static WNDPROC g_OldShellDefWndProc = NULL;     // original SHELLDLL_DefView window proc
static WNDPROC g_OldListViewWndProc = NULL;     // original SysListView32 window proc
static WNDPROC g_OldToolbarWndProc = NULL;      // original ToolbarWindow32 window proc

static HWND hwndParentDlg = NULL;   // handle to parent dialog window
static HWND hwndShDefView = NULL;   // handle to SHELLDLL_DefView control
static HWND hwndListView = NULL;    // handle to SysListView32 control
static HWND hwndToolBar = NULL;     // handle to ToolbarWindow32 control

static char prevFolder[ MAX_PATH ] = "";    // before receiving any CDN_FOLDERCHANGE
static LONG prevFolderLen = 0;              // before receiving any CDN_FOLDERCHANGE

// Virtual Key definition for normal ASCII characters 'X' and 'V'.  We
// need these because we want to trap <Ctrl-X> and <Ctrl-V>, so we need
// to recognize 'X' and 'V' keystrokes.
// 
// VK's for ASCII characters are not defined in WinUser.h.  We have to
// define them ourselves.

const WPARAM VK_V = 86;     // 86 = standard ANSI code for (uppercase) letter 'V'
const WPARAM VK_X = 88;     // 88 = standard ANSI code for (uppercase) letter 'X'

//-----------------------------------------------------------------------------
UINT CALLBACK FileDialogHookProc( 
        HWND hChildDlgWnd,
        UINT uiMsg,
        WPARAM wParam,
        LPARAM lParam
    )
{
    // A Common Dialog is the top-most dialog window.  The caller customizes
    // the common dialog by adding a "child dialog window" to it, which
    // contains additional controls over and above whatever default controls
    // the top-most dialog window contained.
    //
    // The hChildDlgWnd window handle passed to us here in the dialog
    // procedure is the handle of this "child dialog window", not the handle
    // of the top-most dialog.  To find the handle of the top-most dialog, we
    // must call Win32 GetParent(), as explained in the MSDN on-line help
    // under the "OFNHookProc" topic.
    //
    // Investigation using Visual Studio 'Spy++' utility shows that for
    // ::GetOpenFileName(), the "child dialog window" is actually the toolbar
    // (class ToolbarWindow32) that appears at the top of the dialog.  See
    // also the codeproject article by S h a n x.

    switch (uiMsg)
    {
        case WM_NOTIFY:
        {
            // For WM_NOTIFY, lParam is a ptr to an OFNOTIFYEX struct.

            LPOFNOTIFYEX pNotify = reinterpret_cast< LPOFNOTIFYEX >( lParam );

            switch (pNotify->hdr.code)      // examine the notification code
            {
                // A CDN_INITDONE notification message is sent by an Explorer-style Open
                // or Save As dialog box when the system has finished arranging the
                // controls in the dialog box.

                case CDN_INITDONE:          // dialog has finished initialization
                {
                    // The File Open dialog box installs a custom keyboard hook.  Therefore,
                    // the dialog gets to act on keyboard messages before they are seen by
                    // the dialog window procedure.  This presents a problem if we want to
                    // prevent certain keystrokes, such as <Delete>, from having any effect.
                    // Subclassing the dialog procedure does not work, because by the time
                    // the dialog procedure sees the keystroke (as a WM_KEYDOWN message),
                    // it's already been acted on by the keyboard hook routine.
                    // 
                    // To detect keystrokes before they are acted on, we have to install our
                    // own keyboard hook.  Do so here, once the dialog has finished all its
                    // initializations.  By waiting until the dialog has finished
                    // initializing, we ensure that its keyboard hook is already installed.
                    // When we install our own hook, it gets installed after the original one
                    // in sequence.  This ensures our keyboard hook gets called first, before
                    // the original one.
                    // 
                    // We use the keyboard hook to prevent <Delete>, <Shift-Delete>,
                    // <Ctrl-X>, and <Ctrl-V>.

                    InstallKeyboardHook( TRUE );        // insert our keyboard hook

#ifdef FIND_TOOLBAR_BUTTON_IDS

                    // If you want to discover the control ID's of the toolbar buttons in the
                    // ToolbarWindow32 control that appears at the top of the dialog window,
                    // you have to intercept WM_NOTIFY messages sent to the ToolbarWindow32.
                    //
                    // You need the control ID's in order to disable buttons in the toolbar.
                    // Once you've discovered the control ID's (one-time) for your particular
                    // OS (Win98, Win2K, WinXP, whatever), you don't need to hook the dialog
                    // procedure anymore.  So in general you don't need this code.

                    SetToolbarWindowProc();     // intercept WM_NOTIFY messages, find ID's

#else
                    // (If you have the toolbar button ID's): hide the buttons that you don't
                    // want to have available in the toolbar.

                    HideToolbarButtons();       // hide "new folder" Toolbar button
#endif
                }

                break;      // CDN_INITDONE

                // The CDN_FOLDERCHANGE notification message is sent by an Explorer-style
                // Open or Save As dialog box when a new folder is opened.

                case CDN_FOLDERCHANGE:      // user navigated to a different folder
                {
                    // Whenever the user navigates to a different folder, the dialog's
                    // SHELLDLL_DefView and ListView controls lose any custom settings
                    // (including subclassing) that we imposed.  The reason for this is that
                    // the existing controls are destroyed and new ones are created from
                    // scratch, each time the user changes folders.  This can be verified by
                    // using a spy utility such as 'Spy++', or the freeware 'WinDowse' window
                    // dowsing utility.
                    // 
                    // Therefore, whenever the user navigates to a new folder, we have to
                    // re-discover the SysListView32 and SHELLDLL_DefView window handles, and
                    // re-implement the styles and window procedures we want.
                    // 
                    // Modification 07 Jan 2004: Code Project poster WREY (builder@shocking.com)
                    // pointed out that if the user scrolls in the "Look In" combobox but
                    // then closes the combobox without actually *changing* the current
                    // folder, the dialog box process exits (crashes) due to a stack
                    // overflow.
                    //
                    // Investigation shows that, if the user opens the combobox, the system
                    // ends up sending a CDN_FOLDERCHANGE notification even if the folder
                    // doesn't change.  This is bogus.
                    //
                    // Experiments show that the CDN_FOLDERCHANGE notification is sent only
                    // if the user actually opens the combobox (that is, the notification is
                    // only sent if the combobox's drop-down listbox (class "ComboLBox") is
                    // created).  If the user merely places focus on the combobox but doesn't
                    // actually create the drop-down, no CDN_FOLDERCHANGE is sent.
                    //
                    // I consider this to be a bug in how the 'File Open' and 'File Save'
                    // Common Dialogs work.  No CDN_FOLDERCHANGE message should be sent if
                    // the folder didn't actually change.  It ends up being a false
                    // notification.
                    //
                    // Solutions:
                    //
                    //  (1) we can use the CDM_GETFOLDERPATH message to determine the path
                    //      of the "new" folder after each CDN_FOLDERCHANGE notification.
                    //      If the folder didn't really change, we can ignore the message.
                    //
                    //  (2) or, we can examine the SysListView32 and SHELLDLL_DefView
                    //      controls and see if we've already subclassed these particular 
                    //      windows.  If we have, make sure we don't subclass them again.  
                    //      Recursive subclassing is what led to the stack overflow problem 
                    //      in the first place.
                    //
                    // I have tried both methods.  Both of them work.  Normally, the
                    // receiving of a CDN_FOLDERCHANGE notification means that new
                    // SysListView32 and SHELLDLL_DefView controls have been created.  But if
                    // the folder didn't actually change then it turns out new controls are
                    // not created (not too surprising).  So, checking (for example) the
                    // window handles to see if they've changed ends up being equivalent to
                    // determining if the folder really changed.
                    //
                    // Of course, we don't really know how Microsoft has set things up.
                    // Perhaps new controls can "sometimes" be created even when the folder
                    // doesn't change.  Or perhaps the folder does change, and by a perverse
                    // coincidence new controls end up being created by the system that just
                    // happen to have the same window handles as the old controls that were
                    // just destroyed.  In this latter case, examining only the window
                    // handles would erroneously lead us to believe that the controls were
                    // already subclassed.

                    char currFolder[ MAX_PATH ];                // after receiving CDN_FOLDERCHANGE

                    // Find the current folder.

                    LRESULT currFolderLen = ::SendMessage( 
                        hwndParentDlg,
                        CDM_GETFOLDERPATH,
                        MAX_PATH,
                        reinterpret_cast< LPARAM >( currFolder )
                    );

                    // Compare current folder to "previous" folder.  Did the folder really change?
                    //
                    // We compare lengths first, because if the lengths are different we
                    // immediately know that the folder changed (it's a cheap test).  If the
                    // lengths are the same, then we take the next step and do an actual
                    // string comparison.

                    if ((currFolderLen != prevFolderLen) ||
                        (::lstrcmp( currFolder, prevFolder ) != 0))     // folder did change?
                    {

                        // The folder really did change, so update the "before" values, ready
                        // for next time.

                        prevFolderLen = currFolderLen;          // copy lengths

                        ::lstrcpy( prevFolder, currFolder );    // copy strings

                        // Since there was a change, find the latest window handles for the
                        // dialog controls.

                        GetWindowHandles();

                        // Set the ListView styles to the ones we want.  Specifically, we 
                        // disable <F2> and mouse 'click-pause-click' editing of the filename.
                        // Mouse filename editing is actually initiated by a left-click on a
                        // filename that's already highlighted.
                        // 
                        // As well, un-register the ListView from being a drop target.  By
                        // default, the ListView control in the File Open dialog box is
                        // registered as a drop target.  That is, files from outside the dialog
                        // box can be dragged and dropped into the ListView.  In order to disable
                        // this behaviour, we have to un-register the ListView control.

                        AdjustListViewStyle();          // prevent filename edits and outside-dialog drag-n-drop

                        // To prevent the right-mouse-button from bringing up a context menu, we
                        // subclass the SysListView32 window procedure and trap context menu
                        // messages (WM_CONTEXTMENU).  To prevent mouse right-button drags, we
                        // also trap WM_RBUTTONDOWN and WM_RBUTTONUP messages.  But we lose this
                        // subclassing every time the user navigates to a different folder, since
                        // the SysListView32 control gets recreated.  So, re-subclass the
                        // SysListView32 window proc.

                        SetListViewWindowProc();        // prevent right-mouse context menu

                        // To prevent file dragging within the ListView itself, we subclass the
                        // SHELLDLL_DefView window procedure and trap LVN_BEGINDRAG messages.
                        // But we lose the subclassing every time the user navigates to a
                        // different folder, since the control gets recreated.  So, re-subclass
                        // the SHELLDLL_DefView window proc.

                        SetSHELLDefViewWindowProc();    // prevent file-drag within the ListView

                    }  // if (folder did change)
                }

                break;      // CDN_FOLDERCHANGE

            }  // switch (pNotify->hdr.code)
        }

        break;      // WM_NOTIFY

        case WM_DESTROY:                    // dialog box is closing
        {
            InstallKeyboardHook( FALSE );    // remove the keyboard hook we installed

            // Clean up, ready for next time (since these are static variables).

            hwndParentDlg = NULL;   // handle to parent dialog window     
            hwndToolBar   = NULL;   // handle to ToolbarWindow32 control
            hwndShDefView = NULL;   // handle to SHELLDLL_DefView control 
            hwndListView  = NULL;   // handle to SysListView32 control      

            prevFolder[ 0 ] = '\0';     // forget the most recent folder
            prevFolderLen = 0;
        }

        break;      // WM_DESTROY

        case WM_INITDIALOG:
        {
            // The WM_INITDIALOG message is sent to the dialog box procedure
            // immediately before a dialog box is displayed.  Dialog box procedures
            // typically use this message to initialize controls and carry out any
            // other initialization tasks that affect the appearance of the dialog
            // box.

            // Programmer's Remark: the WM_INITDIALOG is received here *during*
            // execution of the parent's WM_INITDIALOG.  The parent dialog has
            // already been created, and it is paused, waiting for us to add any new
            // child controls that we want, or hide any existing controls that we
            // don't want.
            // 
            // Once we finish processing our WM_INITDIALOG, the parent dialog's
            // initialization will continue.  When it's completely finished, the
            // parent will send a CDN_INITDONE notification.  This sequence of
            // messages is described in the MSDN documentation.

            // Only find hwndParentDlg and hwndToolBar one-time.  Reason: they're
            // constant once the File Open dialog box has been created.  The window
            // handles to the SysListView32 and SHELLDLL_DefView change when the user
            // navigates to a new folder, but the parent dialog window and its
            // associated toolbar window do not.

            // Reminder: we're in the Child dialog.  Search "upwards" in the window
            // heirarchy to find the handle of the actual common-control (parent)
            // dialog box.

            hwndParentDlg = ::GetParent( hChildDlgWnd );    // find top-most dialog window

            // Having the parent dialog handle, now search "downwards" among the
            // child windows for the ToolbarWindow32.  This is needed for hiding any
            // buttons that you don't want to appear in the toolbar.

            hwndToolBar = ::FindWindowEx( hwndParentDlg, NULL, "ToolbarWindow32", NULL );

            // One reason for detecting WM_INITDIALOG here is if you want to hide
            // some of the standard dialog items.  For example, I prefer to hide the
            // "Open as read-only" checkbox since I think it's misleading.  (It
            // makes you think the file will be opened read-only, but of course the
            // dialog box can't dictate how a file is opened; that's up to the
            // calling application.  So the checkbox gives you a false sense of
            // security that is not justified).
            // 
            // The MSDN documentation for "Open and Save As Dialog Boxes" provides a
            // list of the ID's for the hide-able items.  They are actually #defined
            // in DLGS.H.  The ID for the read-only checkbox is 'chx1'.
            //
            // Hide the "read-only" checkbox.  For the CDM_HIDECONTROL message,
            // SendMessage() returns no valid value, so ignore it.

            ::SendMessage(
                hwndParentDlg,                  // handle to parent dialog
                CDM_HIDECONTROL,                // message
                static_cast< WPARAM >( chx1 ),  // ID of the control to hide; #defined in DLGS.H
                0                               // not used, must be zero 
            );
        }

        break;      // WM_INITDIALOG

        case WM_ACTIVATE:
        {
            OutputDebugString( "--- WM_ACTIVATE\n" );
        }

        break;

    }  // switch (uiMsg)
        
    // Return 0 if you want the default dialog procedure to process the message.
    // Return non-zero if you want the default dialog process to ignore the message.

    return 0;   // allow the default proc to execute

}  // FileDialogHookProc

//-----------------------------------------------------------------------------
void GetWindowHandles()
{
    //××××××××××××××××××××××××××××××××
    // Given a handle to the Parent dialog window, find the handles of the
    // other windows of interest:
    //
    //  (1) the SHELLDLL_DefView window, child of the parent dialog
    //  (2) the SysListView32 window, child of the SHELLDLL_DefView
    //××××××××××××××××××××××××××××××××

    // Remark: 'ListView' is the Microsoft name for the ListView control.
    // The ListView control's actual window class name (as seen by Spy++)
    // is 'SysListView32'.  I use the terms "ListView" and "SysListView32"
    // more or less interchangeably.

    // SHELLDLL_DefView is the parent container of ListView.
    // SHELLDLL_DefView is what implements drag-n-drop functionality and
    // file-manipulation capabilities (such as Delete or Copy) for the
    // dialog.  When the user is manipulating files in the list,
    // SHELLDLL_DefView is usually doing most of the work.  ListView is
    // mostly just a way of arranging the view.
    // 
    // Using the parent dialog handle, search "downwards" among the child
    // windows for the SHELLDLL_DefView, which is the parent of the ListView.

    hwndShDefView = ::FindWindowEx( hwndParentDlg, NULL, "SHELLDLL_DefView", NULL );

    // Having the handle of the SHELLDLL_DefView, search "downwards" among its
    // child windows for the ListView control.

    hwndListView = ::FindWindowEx( hwndShDefView, NULL, "SysListView32", NULL );
    
    return;

}  // GetWindowHandles

//-----------------------------------------------------------------------------
void InstallKeyboardHook( BOOL bInstalling )
{
    //××××××××××××××××××××××××××××××××
    // Hook or un-hook the keyboard.
    //
    // Reason: to intercept and discard unwanted keystrokes.
    //××××××××××××××××××××××××××××××××

    if (bInstalling)    // installing our keyboard hook
    {
        // Our new keyboard proc will get called before the old (original)
        // keyboard proc.

        g_OldKeybdHook = ::SetWindowsHookEx( 
            WH_KEYBOARD,                // type of hook
            reinterpret_cast< HOOKPROC >( NewKeybdHook ),   // address of new keybd proc
            NULL,                       // not using DLL module handle
            ::GetCurrentThreadId()      // which thread to hook (this thread)
        );
    }
    else    // uninstalling our keyboard hook
    {
        ::UnhookWindowsHookEx( g_OldKeybdHook );    // restore original keybd proc
    }

    return;

}  // InstallKeyboardHook

//-----------------------------------------------------------------------------
void SetListViewWindowProc()
{
    static HWND hwndListView_Org = NULL;        // handle to SysListView32 control

    //××××××××××××××××××××××××××××××××
    // Subclass the window procedure of the dialog window's SysListView32
    // control.
    // 
    // Reason: to disable the context menu (mouse right-click) within the
    // ListView.
    //××××××××××××××××××××××××××××××××

    // Subclass the window procedure of the SysListView32 control, diverting all
    // message traffic to our 'NewListViewWndProc' procedure.
    //
    // Programmer's Note: SubclassWindow() is actually a (Microsoft) macro.
    // The real call is to ::GetWindowLong() using the GWL_WNDPROC flag.

    g_OldListViewWndProc = SubclassWindow(
        hwndListView,                                       // which window
        reinterpret_cast< WNDPROC >( NewListViewWndProc )   // address of new window proc
    );

    hwndListView_Org = hwndListView;

    return;

}  // SetListViewWindowProc

//-----------------------------------------------------------------------------
void SetSHELLDefViewWindowProc()
{
    static HWND hwndShDefView_Org = NULL;       // handle to SHELLDLL_DefView control

    //××××××××××××××××××××××××××××××××
    // Subclass the window procedure of the dialog window's SHELLDLL_DefView
    // control.
    // 
    // Reason: to disable file drag operations within the ListView itself.
    //××××××××××××××××××××××××××××××××

    // Subclass the window procedure of the SHELLDLL_DefView, diverting all
    // message traffic to our 'NewShellDefWndProc' procedure.
    //
    // Programmer's Note: SubclassWindow() is actually a (Microsoft) macro.
    // The real call is to ::GetWindowLong() using the GWL_WNDPROC flag.

    g_OldShellDefWndProc = SubclassWindow(
        hwndShDefView,                                      // which window
        reinterpret_cast< WNDPROC >( NewShellDefWndProc )   // address of new window proc
    );

    hwndShDefView_Org = hwndShDefView;

    return;

}  // SetSHELLDefViewWindowProc

//-----------------------------------------------------------------------------
#ifdef FIND_TOOLBAR_BUTTON_IDS

void SetToolbarWindowProc()
{
    //××××××××××××××××××××××××××××××××
    // Subclass the window procedure of the dialog window's ToolbarWindow32
    // control.
    // 
    // Reason: to determine the ID's of the various toolbar buttons.  These
    // can then be used in the HideToolbarButtons() routine.
    //××××××××××××××××××××××××××××××××

    // Subclass the window procedure of the ToolbarWindow32 control,
    // diverting all message traffic to our 'NewToolbarWndProc' procedure.
    //
    // Programmer's Note: SubclassWindow() is actually a (Microsoft) macro.
    // The real call is to ::GetWindowLong() using the GWL_WNDPROC flag.

    g_OldToolbarWndProc = SubclassWindow(
        hwndToolBar,                                        // which window
        reinterpret_cast< WNDPROC >( NewToolbarWndProc )    // address of new window proc
    );

    return;

}  // SetToolbarWindowProc

#endif

//-----------------------------------------------------------------------------
LRESULT CALLBACK NewShellDefWndProc( HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam )
{
    //××××××××××××××××××××××××××××××××
    // NewShellDefWndProc: new window procedure for the SHELLDLL_DefView window,
    // which is the parent of the SysListView32 control.
    //××××××××××××××××××××××××××××××××

    // Reminder: SHELLDLL_DefView is the parent of the ListView control.
    // Although the ListView is responsible for the visual display of the
    // files and folders, it's the SHELLDLL_DefView parent that actually
    // handles most of the file operations (such as drag-n-drop within the
    // ListView).
    // 
    // Here, we monitor the SHELLDLL_DefView for file-drag notification
    // messages.  We want to prevent files from being moved into a different
    // folder, either within the ListView, or elsewhere: disable drag-n-drop.

    switch (uiMsg)
    {
        case WM_NOTIFY: 

        // We don't allow the user to drag files around, because dragging to a
        // different location, in effect renames the file.  And we don't want to
        // allow file renaming.
        //
        // Of course, WM_NOTIFY messages are sent for more than just file-drag
        // operations.  We have to see if the WM_NOTIFY is the one we want.  The
        // ones we're interested in have an LVN_BEGINDRAG notification code.
        // 
        // Remark: this section of code has nothing to do with files that are
        // dropped onto the dialog box from outside.  That behaviour is
        // implemented by the COM 'IDropTarget' interface.  LVN_BEGINDRAG applies
        // only to file drags originating within the ListView itself.

        {
            // The way file drag works is: the ListView sends notification messages
            // (WM_NOTIFY) to its parent, which is the SHELLDLL_DefView window.  We
            // therefore watch for WM_NOTIFY's here.  If we detect one that has the
            // LVN_BEGINDRAG code, indicating that the user started a drag, we eat
            // the message: we don't pass it on to the original SHELLDLL_DefView
            // window procedure (g_OldShellDefWndProc).  Instead we just return zero.
            // 
            // Microsoft on-line documentation for "Default List-View Message
            // Processing" says (under WM_LBUTTONDOWN): "If dragging begins over an
            // item, the list-view control selects and sets the focus to the item.
            // Then it sends an LVN_BEGINDRAG notification message to the parent
            // window.  The parent window is responsible for actually carrying out
            // the drag operation."  See:
            // 
            //      http://msdn.microsoft.com/library/default.asp?url=/library
            //      /en-us/shellcc/platform/commctls/listview/listview_overview.asp 
            // 
            // This means drag-n-drop operations are actually handled by the parent.
            // The ListView recognizes when a drag begins, but its only role in the
            // drag is to notify its parent SHELLDLL_DefView.  It has no further
            // duties or responsibilities after that.  The highlighting of the
            // dragged file, the new mouse drag-cursor, the highlighting of folder as
            // the dragged file passes over it (drop target) -- all of that is
            // handled by the parent window SHELLDLL_DefView, not by the SysListView32.
            // 
            // Therefore, if we eat the LVN_BEGINDRAG message, there's nothing else
            // to do: the parent SHELLDLL_DefView never realizes a drag was
            // attempted, so nothing happens.  No file dragging occurs.  It's
            // perfect: exactly what we want.
            //
            // See if this WM_NOTIFY has an LVN_BEGINDRAG notification code.  lParam
            // is a ptr to an NMHDR, which contains the notification code.

            NMHDR* pnmhdr = reinterpret_cast< NMHDR *>( lParam );

            if (pnmhdr->code == LVN_BEGINDRAG)      // notification code is "begin drag"?
            {
                return 0;   // eat this message: don't pass on to g_OldShellDefWndProc
            }
        }

        break;  // case WM_NOTIFY

    }  // switch (uiMsg)

    // Pass the message on to the original SHELLDLL_DefView window proc, for
    // standard handling.

    return ::CallWindowProc( g_OldShellDefWndProc, hwnd, uiMsg, wParam, lParam );

}  // NewShellDefWndProc

//-----------------------------------------------------------------------------
LRESULT CALLBACK NewListViewWndProc( HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam )
{
    //××××××××××××××××××××××××××××××××
    // NewListViewWndProc: new window procedure for the SysListView32 window,
    // which is the child of the SHELLDLL_DefView control.
    //××××××××××××××××××××××××××××××××

    // We have two goals here:
    //
    //  (1) prevent the mouse right-click context menu from popping up.  By 
    //      eating WM_CONTEXTMENU messages, we prevent the context menu from 
    //      ever being created.  (Thanks to: shue_20002000)
    //
    //  (2) prevent mouse right-button drag-n-drop operations.  By eating
    //      mouse right-button messages WM_RBUTTONDOWN and WM_RBUTTONUP, we
    //      prevent right drag-n-drop from being initiated.
    // 
    // In an earlier version of this code, only mouse right-button messages
    // WM_RBUTTONDOWN and WM_RBUTTONUP were trapped since this generally
    // worked prevent the context menu from being instantiated.  However
    // Codeproject user "andreopr@hotmail.com" discovered that clicking the
    // left mouse button while holding down the right button was still able
    // to trigger the context menu.  This unexpected behavior appears to be
    // an artifact of how the SysListView32 control is implemented.
    //
    // Codeproject user "shue_20002000" suggested that trapping WM_CONTEXTMENU 
    // messages would solve the context menu problems more effectively.  This
    // is indeed a superior solution for defeating the context menu.
    //      
    // However experiments show that we still have to trap mouse right-clicks
    // because otherwise, the user can right-drag items out of the dialog
    // box.  Left-mouse-drags are disabled by trapping LVN_BEGINDRAG in
    // NewShellDefWndProc(), but doing so does not disable right-mouse-drags.
    // Eating the mouse right-click messages here does disable right drags.

    switch (uiMsg)
    {
        case WM_CONTEXTMENU:    // trying to create context menu?
        {
            return 0;   // eat it: don't pass on to g_OldListViewWndProc
        }

        break;

        case WM_RBUTTONDOWN:    // detected any mouse right-click message?
        case WM_RBUTTONUP:      
        {
            return 0;   // eat it: no right-mouse dragging permitted
        }

        break;

    }  // switch

    return CallWindowProc( g_OldListViewWndProc, hwnd, uiMsg, wParam, lParam );

}  // NewListViewWndProc

//-----------------------------------------------------------------------------
UINT CALLBACK NewKeybdHook( int nCode, WPARAM wParam, LPARAM lParam )
{
    //××××××××××××××××××××××××××××××××
    // New keyboard hook function, for detecting and discarding keystrokes
    // that we don't want to be active in the dialog box.
    //
    // Needed for: disabling <Delete>, <Shift-Delete>, <Ctrl-X>, <Ctrl-V>.
    //××××××××××××××××××××××××××××××××

    // On-line documentation for HOOKPROC says: "if nCode < 0, the hook
    // procedure should pass the message to the CallNextHookEx() function
    // without further processing, and should return the value returned by
    // CallNextHookEx() to the caller."

    if (nCode < 0)      // don't process this message?
    {
        return ::CallNextHookEx( g_OldKeybdHook, nCode, wParam, lParam );
    }

    // To eat a keystroke, just return a non-zero value to the system.  This
    // prevents any further processing of the message.  Don't call
    // CallNextHookEx(), unless you want it to process the keystroke.

    // Here, we eat all <Del> keystrokes.  This includes <Shift-Del>, since
    // <Del> is part of that combination.  
    //
    // In the Old Days, <Shift-Del> was a synonym for <Ctrl-X> (Cut).  In the
    // Present Day, <Shift-Del> is used to delete a file directly without
    // first moving it to the trash (recycle) bin.  Either way, we don't want
    // <Shift-Del> to operate, so trapping <Del> is sufficient.

    if (wParam == VK_DELETE)    // user pressed the <Delete> key?
    {
        return 1;       // eat it: don't let dialog box see it
    }

    // We also want to disable <Ctrl-X> "Cut".  For a read-only file dialog,
    // we don't want to allow the user to cut files, because pasting (moving)
    // a file to a new location is, in effect, a way of renaming the file.
    //
    // To detect <Ctrl-X>, we have to detect the 'X' key, and then see if any
    // <Ctrl> modifier was also pressed.  We don't want to simply discard all
    // 'X' keystrokes, since 'X' is a valid alphabetic letter used for other
    // purposes in the dialog box.
    // 
    // Although symbol 'VK_X' is alluded to in the on-line Win32 help, there
    // is no such symbol actually #defined (as Rector and Newcomer point out,
    // in their book).  The value of wParam for 'X' is just the ASCII value
    // of (uppercase) 'X', which is 88.

    if (wParam == VK_X)         // 'X' key is pressed?
    {
        // GetKeyState() returns the state of <Ctrl>, <Shift>, or <Alt> keys.

        int keyState = ::GetKeyState( VK_CONTROL );     // get state of <Ctrl>

        if (keyState < 0)       // high bit is set (ie. was <Ctrl> pressed)?
        {
            return 1;           // was <Ctrl-X>, so eat this keystroke
        }
    }

    // Also disable <Ctrl-V> "Paste".  Even if you don't mind the user adding
    // new files to the folder, she might accidentally clobber an existing
    // file of the same name.  For a read-only file dialog, that's
    // unacceptable.

    if (wParam == VK_V)         // 'V' key is pressed?
    {
        int keyState = ::GetKeyState( VK_CONTROL );     // get state of <Ctrl>

        if (keyState < 0)       // high bit is set (ie. was <Ctrl> pressed)?
        {
            return 1;           // was <Ctrl-V>, so eat this keystroke
        }
    }

    // All other cases: allow default keystroke processing to proceed.

    return ::CallNextHookEx( g_OldKeybdHook, nCode, wParam, lParam );

}  // NewKeybdHook

//-----------------------------------------------------------------------------
void AdjustListViewStyle()
{
    //××××××××××××××××××××××××××××××××
    // Needed for: disabling <F2> and mouse left-button "click-on-highlighted
    // -item" editing.  Also needed for disabling file drag-n-drops that 
    // originate outside the dialog.
    //
    // The File Open dialog contains a ListView control, which is registered
    // under the "SysListView32" class name.  This is just a familiar Windows
    // Explorer-style control, which allows items within it to be displayed
    // by large icon, small icon, list, or by details.  
    //
    // The appearance of and behaviour of the ListView can be modified by
    // setting attribute (style) flags (LVS_xxx styles, see the Microsoft
    // on-line documentation).  In particular, the LVS_EDITLABELS style
    // allows the user to use <F2> or mouse click-pause-click to Rename a
    // file by editing its label in the ListView.
    //
    // Therefore, one step in making the ListView read-only is to remove the
    // LVS_EDITLABELS style from the ListView.  This disables both <F2> and
    // mouse click-pause-click renaming.
    //××××××××××××××××××××××××××××××××

    // We assume 'hwndListView' is a valid window handle to the SysListView32.
    //
    // Programmer's Note: GetWindowStyle() is actually a (Microsoft) macro.
    // The real call is to ::GetWindowLong() using the GWL_STYLE flag.

    DWORD dwStyle = GetWindowStyle( hwndListView );     // original style flags

    ::SetWindowLong( hwndListView, GWL_STYLE, dwStyle & ~LVS_EDITLABELS );      // new style flags

    // This next piece is optional.  Only use it if you want to set some
    // extended listview styles.
    //
    // Set some extended styles.  For a list of extended ListView styles, see
    // the MSDN on-line documentation.  Here we set the "full row select"
    // style, which is (I think) convenient if the user chooses the "Details"
    // view.  However this is a matter of taste.
    //
    // Programmer's Note: ListView_SetExtendedListViewStyle() is actually a
    // (Microsoft) macro.  The real call is to ::SendMessage() using the
    // LVM_GETEXTENDEDLISTVIEWSTYLE message.

    ListView_SetExtendedListViewStyle( hwndListView, LVS_EX_FULLROWSELECT );

    // Disable file drag-n-drops for any drags that originate outside the
    // dialog.
    //
    // File drag-n-drop between processes is handled by the COM IDropTarget
    // interface.  By calling this interface, a control (such as ListView)
    // "registers" itself as being able to accept file drop operations.
    // Any window can, in principle, register itself as a drop target in
    // this way.
    // 
    // To disable drag-n-drop on a window that has registered itself to
    // accept file drops, Microsoft provides RevokeDragDrop().  This
    // "unregisters" the window so it is no longer recognized as a valid drop
    // target.
    //
    // Question: if RevokeDragDrop() is sufficient to disable file drops onto
    // the dialog, shouldn't it also work to disable file drags starting
    // within the dialog?  After all, either you're disabling drag-n-drop or
    // you're not.  Drags originating within the dialog can't be so very
    // different from drags originating outside the dialog.
    // 
    // Experiments show that the answer is, RevokeDragDrop() does work to
    // disable file drag-n-drop as long as the drag and drop is strictly
    // within the ListView window.  But it still doesn't prevent dragging of
    // a file out of the dialog box and into some other window that's
    // registered as a drop target, such as Windows Explorer.
    // 
    // You can try this for yourself: don't call SetSHELLDefViewWindowProc(),
    // so the LVN_BEGINDRAG messages won't get trapped.  Then try dragging
    // files out of the dialog box onto a Windows Explorer window.  You'll
    // discover that if you hold the <Shift> key down as you do the actual
    // drop (ie. as you release the mouse button), the file is moved out of
    // the dialog box (rather than just copied).  This is no good.
    //
    // So RevokeDragDrop(), while definitely necessary, is not sufficient
    // to completely prevent unwanted file drag-n-drop.  You must also trap
    // the LVN_BEGINDRAG messages by subclassing the SHELLDLL_DefView control.
    //
    // Similar remarks apply to trapping WM_RBUTTONDOWN and WM_RBUTTONUP
    // messages.  Invoking RevokeDragDrop() is not sufficient to prevent a
    // file from being right-dragged out of the dialog and moved to a new
    // location.  So, mouse right-clicks must be detected and discarded by
    // subclassing the SysListView32 control.  See NewListViewWndProc() for
    // details.

    ::RevokeDragDrop( hwndListView );       // remove drag-n-drop registration

    return;     // all done

}  // AdjustListViewStyle

//-----------------------------------------------------------------------------
#ifdef FIND_TOOLBAR_BUTTON_IDS

LRESULT CALLBACK NewToolbarWndProc( HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam )
{
    // We subclass the ToolbarWindow32 only in order to find the toolbar button ID's.

    switch(uiMsg)
    {
        // A notification message is sent to the ToolbarWindow32 for any mouse
        // activity (such as right-mouse-click) over one of its buttons.  From
        // this WM_NOTIFY, you can find the ID for the control you're mousing
        // over.
        //
        // Then you can use the ID in HideToolbarButtons().
        //
        // Recommendation: simply hover the mouse over the toolbar button you
        // want.  When the system pops up the tooltip help for that button, a
        // series of WM_NOTIFY messages is sent for that button.  By examining
        // the NMHDR.idFrom data member, the ID of the button can be found.
        //
        // Here, the ID is just printed to the Visual Studio Debug window.

        case WM_NOTIFY: 
        {
            NMHDR* pnmhdr = (NMHDR *) lParam;   // ptr to a NMHDR, contains button info

            char buff[ 512 ];
            ::wsprintf( buff, "--- got a WM_NOTIFY for control ID %u\n", pnmhdr->idFrom );

            OutputDebugString( buff );      // display the control ID
        }
        break;
    }

    return CallWindowProc( g_OldToolbarWndProc, hwnd, uiMsg, wParam, lParam );

}  // NewToolbarWndProc

#endif  // FIND_TOOLBAR_BUTTON_IDS

//-----------------------------------------------------------------------------
void HideToolbarButtons()
{
    // (Use the NewToolbarWndProc() routine to find these ID's).
    //
    // Experiments show these same ID's work for all Windows operating systems
    // that I have access to:  Win98SE, WinNT 4, Win2K, and WinXP.  I couldn't
    // test Win95 or WinNT earlier than v4.

    const int TB_BTN_BACK       = 40971;
    const int TB_BTN_UPONELEVEL = 40961;
    const int TB_BTN_NEWFOLDER  = 40962;
    const int TB_BTN_VIEWMENU   = 40970;

    // The technique used here was taken from the Code Project article by S h a n x.

    TBBUTTONINFO tbinfo;

    tbinfo.cbSize = sizeof( TBBUTTONINFO );
    tbinfo.dwMask = TBIF_STATE;
    tbinfo.fsState = TBSTATE_HIDDEN | TBSTATE_INDETERMINATE;

    // Send a message to the ToolbarWindow32 to hide the 'New Folder' button.

    ::SendMessage( hwndToolBar, TB_SETBUTTONINFO, (WPARAM)TB_BTN_NEWFOLDER, (LPARAM)&tbinfo );

}  // HideToolbarButtons

//-----------------------------------------------------------------------------
CFileDialog_ReadOnly::CFileDialog_ReadOnly(     // constructor
        BOOL bOpenFileDialog,       // use TRUE for File Open dialog, FALSE for File Save dialog
        HWND hwndOwner,             // dialog will be modal with respect to this window
        LPCTSTR pInitialDirectory,  // initial directory to open in
        LPCTSTR pInitialFileName,   // initial filename to display
        LPCTSTR pAllowedExts,       // list of allowed file extensions, that dialog will show
        DWORD dwExtsBuffSize,       // size of 'pAllowedExts' buffer 
        LPCTSTR pDefaultFileExt,    // default extension to use when saving the file
        DWORD dwFlags               // flags controlling the dialog style
    ) :
    m_bOpenFileDialog( bOpenFileDialog ),
    m_hwndOwner( hwndOwner )
{
    // typedef struct tagOFN {
    //     DWORD         lStructSize; 
    //     HWND          hwndOwner; 
    //     HINSTANCE     hInstance; 
    //     LPCTSTR       lpstrFilter;       [in]            
    //     LPTSTR        lpstrCustomFilter; [out]
    //     DWORD         nMaxCustFilter;    [in]            
    //     DWORD         nFilterIndex;      [out]
    //     LPTSTR        lpstrFile;         [in, out]       
    //     DWORD         nMaxFile;          [in]            
    //     LPTSTR        lpstrFileTitle;    [out]
    //     DWORD         nMaxFileTitle;     [in]            
    //     LPCTSTR       lpstrInitialDir;   [in]            
    //     LPCTSTR       lpstrTitle;        [in]            
    //     DWORD         Flags;             [in]            
    //     WORD          nFileOffset;       [out]
    //     WORD          nFileExtension;    [out] (no dot)
    //     LPCTSTR       lpstrDefExt;       [in] (no dot)   
    //     DWORD         lCustData;         [in]            
    //     LPOFNHOOKPROC lpfnHook;          [in]            
    //     LPCTSTR       lpTemplateName;    [in]            
    // } OPENFILENAME;

    ::ZeroMemory( &m_ofn, sizeof( OPENFILENAME ) );

    m_ofn.lStructSize = sizeof( OPENFILENAME );     // size of structure

    // Assign all pointer members in the m_ofn data member.
	strcpy(m_szInitialDir, pInitialDirectory);
    m_ofn.lpstrInitialDir = reinterpret_cast< LPTSTR >( m_szInitialDir );   // [in] starting directory (NULL is OK)

    m_ofn.lpstrFile = reinterpret_cast< LPTSTR >( m_szFile );           // [in] starting filename
    m_ofn.nMaxFile = MAX_PATH;                                          // size of filename buffer

    m_ofn.lpstrFilter = reinterpret_cast< LPTSTR >( m_szFilter );       // [in] which file extensions to show (NULL is OK)

    m_ofn.lpstrDefExt = reinterpret_cast< LPTSTR >( m_szDefaultExt );   // default file extension (no dot) (NULL is OK)

    m_ofn.Flags = dwFlags;                                              // user-specified flags
    m_ofn.Flags |= (OFN_ENABLEHOOK | OFN_EXPLORER | OFN_READONLY | OFN_ENABLESIZING );      // but, force the flags we want

    m_ofn.lpstrFileTitle = reinterpret_cast< LPSTR >( m_szFileTitle );  // [out] name of chosen file + extension (NULL is OK)
    m_ofn.nMaxFileTitle = MAX_PATH;                                     // size of buffer

    // Supplying a window handle as the "owner" makes the File common dialog
    // box modal with respect to that owner.  You Want This.  If you don't
    // supply an hwndOwner, the File common dialog ends up not being modal:
    // you can still activate the parent.  This is Not A Good Thing, because
    // the CFileDialog_ReadOnly class uses global static data: shouldn't
    // launch more than one CFileDialog_ReadOnly object at a time!

    m_ofn.hwndOwner = m_hwndOwner;      // assign owner window

    // Remark: in this version of the application, I don't use lpstrTitle or m_szTitle.
    //
    // m_ofn.lpstrTitle = reinterpret_cast< LPSTR >( m_szTitle );               // dialog titlebar text (NULL is OK)
    m_ofn.lpstrTitle = NULL;        // (not used)

    // Remark: in this version of the application, I don't use lpstrCustomFilter or m_szCustomFilter.
    //
    // m_ofn.lpstrCustomFilter = reinterpret_cast< LPTSTR >( m_szCustomFilter );        // [out] user-entered filter string (NULL is OK)
    // m_ofn.nMaxCustFilter = MAX_PATH;                                         // size of buffer
    m_ofn.lpstrCustomFilter = NULL;     // (not used)

    // Ensure valid defaults.

    m_szFilter     [ 0 ] = '\0';    // m_ofn.lpstrFilter    
    m_szFile       [ 0 ] = '\0';    // m_ofn.lpstrFile      
    m_szFileTitle  [ 0 ] = '\0';    // m_ofn.lpstrFileTitle 
    m_szInitialDir [ 0 ] = '\0';    // m_ofn.lpstrInitialDir
    m_szTitle      [ 0 ] = '\0';    // m_ofn.lpstrTitle     
    m_szDefaultExt [ 0 ] = '\0';    // m_ofn.lpstrDefExt    

    // Set the default file extension.  If the caller specified a leading dot 
    // by accident, remove it.

    CString extension( pDefaultFileExt );
    extension.Remove( '.' );

    // Programmer's Note: if the caller passed a list of allowed extensions
    // in 'pAllowedExts' and 'dwExtsBuffSize', then 'pDefaultFileExt' has to
    // be one of those.  If it's not, the system appends one of the
    // pAllowedExts extensions.  The rule is: if you pass a list of allowed
    // extensions, you can't use pDefaultFileExt to force the file to have an
    // extension that's not in the list.

    ::lstrcpyn( m_szDefaultExt, extension, 4 ); // default extension to use when saving the file

    // Set the initial filename the dialog will show.

    if (pInitialFileName != NULL)
    {
        ::lstrcpy( m_szFile, pInitialFileName );
    }

    // Set the initial directory the dialog will open on.

    if (pInitialDirectory != NULL)
    {
        ::lstrcpy( m_szInitialDir, pInitialDirectory );
    }

    // Set the allowed file extensions dialog will show.  This is specified
    // in the Win32 documentation as an LPCTSTR, but since the string
    // contains embedded nulls, it can't really be used as a normal string.
    // We have to use ::MoveMemory() instead of the simpler ::lstrcpy(), to
    // copy the string contents over to the holding buffer m_szFilter.
    //
    // Example buffer: 'Fred files\0*.fred;*.wilma\0Barney files\0*.barn\0\0'

    if (pAllowedExts != NULL)
    {
        ::MoveMemory( m_szFilter, pAllowedExts, dwExtsBuffSize );
    }
    else    // show all files
    {
        m_ofn.lpstrFilter = "All Files\0*.*\0";
    }

    // Assign the new dialog procedure (hook).

    m_ofn.lpfnHook = reinterpret_cast< LPOFNHOOKPROC >( FileDialogHookProc );

    return;

}  // CFileDialog_ReadOnly::CFileDialog_ReadOnly

//-----------------------------------------------------------------------------
int CFileDialog_ReadOnly::DoModal()
{
    // Call Win32 common dialog function ::GetOpenFileName() or
    // ::GetSaveFileName(), depending on the flag m_bOpenFileDialog.
    //
    // The return value is FALSE if the user clicks 'Cancel' (or if any errors).

       LPCSTR str = m_ofn.lpstrInitialDir;
	if (m_bOpenFileDialog)      // running a "File Open" dialog
    {
        return ::GetOpenFileName( &m_ofn );
    }
    else    // running a "File Save" dialog
    {
        return ::GetSaveFileName( &m_ofn );
    }

}  // CFileDialog_ReadOnly::DoModal

//-----------------------------------------------------------------------------
CString CFileDialog_ReadOnly::GetPathName() const
{
    // Return the fully-qualified path+filename+extension.
    //
    // Assuming file "C:\Fred\barney.txt" as an example,
    // we would return: "C:\Fred\barney.txt"

    return (m_ofn.lpstrFile);

}   // CFileDialog_ReadOnly::GetPathName

//-----------------------------------------------------------------------------
CString CFileDialog_ReadOnly::GetFileName() const
{
    // Return just the filename + extension, no path.
    //
    // Assuming file "C:\Fred\barney.txt" as an example,
    // we would return: "barney.txt"

    return (m_ofn.lpstrFileTitle);

}   // CFileDialog_ReadOnly::GetFileName

//-----------------------------------------------------------------------------
CString CFileDialog_ReadOnly::GetFileExt() const
{
    // Return just the file's extension (no dot).
    //
    // Assuming file "C:\Fred\barney.txt" as an example,
    // we would return: "txt"

    CString fileExtension( m_ofn.lpstrFileTitle );

    int lastDot = fileExtension.ReverseFind( '.' );     // find last dot

    if (lastDot >= 0)       // found?
    {
        fileExtension = fileExtension.Right( 
            fileExtension.GetLength() - lastDot - 1 );  // extract after last dot
    }
    else    // not found
    {
        fileExtension = "";     // no extension information
    }

    return fileExtension;

}   // CFileDialog_ReadOnly::GetFileExt

//-----------------------------------------------------------------------------
CString CFileDialog_ReadOnly::GetFileTitle() const
{
    // Return just the (bare) filename, no extension, no path.
    //
    // Assuming file "C:\Fred\barney.txt" as an example,
    // we would return: "barney"

    CString fileName( m_ofn.lpstrFileTitle );

    int lastDot = fileName.ReverseFind( '.' );  // find last dot

    if (lastDot >= 0)       // found?
    {
        fileName = fileName.Left( lastDot );    // extract before last dot
    }
    else    // not found
    {
        fileName = "";      // no filename information
    }

    return fileName;

}   // CFileDialog_ReadOnly::GetFileTitle

//-----------------------------------------------------------------------------
CString CFileDialog_ReadOnly::GetDirName() const
{
    // Return just the path (directory) name, no filename or extension.
    //
    // Assuming file "C:\Fred\barney.txt" as an example,
    // we would return: "C:\Fred"

    CString fileDirectory( m_ofn.lpstrFile );

    int lastSlash = fileDirectory.ReverseFind( '\\' );      // find last backslash

    if (lastSlash >= 0)     // found?
    {
        fileDirectory = fileDirectory.Left( lastSlash );    // extract up to last backslash
    }
    else    // not found
    {
        fileDirectory = "";     // no path information
    }

    return fileDirectory;

}   // CFileDialog_ReadOnly::GetDirName

//-----------------------------------------------------------------------------
void CFileDialog_ReadOnly::OnFolderChange()
{
    // This is just a stub.  To Be Implemented at some later date.
    // 
    // You'd have to do it using the CDN_FOLDERCHANGE notification somehow.

    return;

}  // CFileDialog_ReadOnly::OnFolderChange

//-----------------------------------------------------------------------------
// [EOF]
