#if !defined(GLOBALS_FILE)
#define GLOBALS_FILE

#include "CCalculator.h"

// needed for accelerator keys
extern HWND    				ghDlg;          // Handle to main dialog box
extern HACCEL  				ghAccelTable;   // Handle to accelerator table

extern CCalculator 		*g_Calculator;
extern CString 			g_strApplicationDirectory;
extern bool				g_fQuitScript;


// GRAPHING
#define GRAPH_THRESHOLD		10000
#define MAX_3D_EQS	6
#define MAX_2D_PARAMETRIC_EQS 5
#define MAX_POALR_GRID_ANGLE_RADIANS	PI
#define MAX_POALR_GRID_ANGLE_DEGREES	180

// MISC
#define NULL 0
#define HTML_HELP_DIR	"/Make/html/"
#define ANSWER_HISTORY	20
#define MAXTABS 4
#define MAX_NUMBER_COMMANDS	178
#define Assert ASSERT
#define BUTTON_PALLETE_WIDTH 245
#define BUTTON_PALLETE_HEIGHT \
			((button_height * 7) + \
			(button_spacing * 7))

#define Trace(a) TRACE0(a)

#ifdef DEBUG
	#define AUTO_PARAMETRIC
#endif

#ifndef GRAPHCALC_LIGHT
	#define GRAPH2D_INFOBAR
#endif

#ifdef GRAPH2D_INFOBAR
 #define GraphInfoBar(e) e
#else
 #define GraphInfoBar(e)
#endif 

#ifdef GRAPHCALC_LIGHT
 #define GraphCalcFull(e) 
#else
 #define GraphCalcFull(e) e
#endif 

#define FActiveWindowWnd(wnd) \
	(GetActiveWindow() == wnd)
	
#define HaltRedrawWnd(wnd) \
	if(FActiveWindowWnd(wnd)) \
		SetRedraw(false)

#define InvalidateRedrawWnd(wnd) \
	if(FActiveWindowWnd(wnd)) \
		{ 			   \
		SetRedraw(true); \
		Invalidate();	\
		}


#define FActiveWindow() \
	(GetActiveWindow() == this)

#define HaltRedraw() \
	if(FActiveWindow()) \
		SetRedraw(false)

#define InvalidateRedraw() \
	if(FActiveWindow()) \
		{ 			   \
		SetRedraw(true); \
		Invalidate();	\
		}

#define GRAPH2D_INFOBAR_WIDTH			236

// user defined messages
#define WM_USER_CHANGE_OBJECT_PROPERTIES 		(WM_USER + 1)
#define WM_GRAPH_MODE_CHANGE 					(WM_USER + 2)
#define WM_3DOPTIONS_CHANGE 					(WM_USER + 3)
#define WM_2DGRAPH_CENTER 						(WM_USER + 4)
#define WM_2DGRAPH_N_SLIDER_UPDATE				(WM_USER + 5)
#define WM_2DGRAPH_N_SLIDER_CLOSING				(WM_USER + 5)
#define WM_SETFULLWINDOW						(WM_USER + 112)
#define WM_RESIZEPAGE 							(WM_USER + 111)


enum {HELP_PAGE_2D_TABLEVIEW=0,
	   HELP_PAGE_2D_EQUATIONINTERSECTION,
	   HELP_PAGE_2D_EQUATIONINTERCEPTS,
	   HELP_PAGE_2D_EQUATIONMINMAX,
	   HELP_PAGE_BASES,
	   HELP_PAGE_EQUATIONSOLVER,
	   HELP_PAGE_2D_RANGE,
	   HELP_PAGE_2D_THETARANGE,
	   HELP_PAGE_2D_MISCDISPLAYCOMPONENTS,
	   HELP_PAGE_2D_EUCLIDEANVSPOLAREQUATIONS};

extern void LoadHelpFile(UINT page);
extern void CleanupAnswer(CString &ans);
extern void CleanupFormatAnswer(CString &ans);
extern void ConvertCleanupFormatAnswer(CString &ans);
extern void DecimalForDisplay(CString &ans);
extern CString ConvertForDisplay(long double dAns);

// dAns - value to convert
// nMaxDecPlaces - maximum number of decimal places to show
extern CString ConvertForDisplay(long double dAns, int nMaxDecPlaces); 
extern void ProcessMessages();


#endif
