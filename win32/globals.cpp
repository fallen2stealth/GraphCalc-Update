#include "globals.h"
#include <htmlhelp.h>

// needed for accelerator keys
HWND    		ghDlg;          // Handle to main dialog box
HACCEL  		ghAccelTable;   // Handle to accelerator table

CCalculator 	*g_Calculator;
CString 		g_strApplicationDirectory;
bool			g_fQuitScript;

void LoadHelpFile(UINT page)
{
	CString html_page;
	html_page.Empty();
	switch(page)
		{
		case HELP_PAGE_2D_TABLEVIEW: 					html_page = "EquationValuesTable.html"; break;
		case HELP_PAGE_2D_EQUATIONINTERSECTION: 		html_page = "EquationIntersection.html"; break;
	    case HELP_PAGE_2D_EQUATIONINTERCEPTS: 			html_page = "EquationIntercepts.html"; break;
	    case HELP_PAGE_2D_EQUATIONMINMAX: 				html_page = "EquationMinMax.html"; break;
	    case HELP_PAGE_BASES: 							html_page = "Bases.html"; break;
	    case HELP_PAGE_EQUATIONSOLVER: 					html_page = "EquationSolver.html"; break;
	    case HELP_PAGE_2D_RANGE: 						html_page = "Range.html"; break;
	    case HELP_PAGE_2D_THETARANGE: 					html_page = "ThetaRange.html"; break;
	    case HELP_PAGE_2D_MISCDISPLAYCOMPONENTS: 		html_page = "MiscDisplayComponents.html"; break;
	    case HELP_PAGE_2D_EUCLIDEANVSPOLAREQUATIONS: html_page = "EuclidianVsPolarEquations.html"; break;
		}
	if(!html_page.IsEmpty())
		HtmlHelp(NULL, g_strApplicationDirectory + "\\grphcalc.chm::" + HTML_HELP_DIR + html_page, HH_DISPLAY_TOPIC, 0);
}

void CleanupAnswer(CString &ans)
{
	CString delimiter = (g_Calculator->m_IntlMode == US) ? "." : ",";
	
	if(ans != "0" && ans.Find(delimiter) != -1)
		ans.TrimRight("0");

	ans.TrimRight(delimiter);
	
	if(ans.GetLength() == 2 && ans[0] == '-' && ans[1] == '0')
		ans.TrimLeft("-");
}

void CleanupFormatAnswer(CString &ans)
{
	CleanupAnswer(ans);
	g_Calculator->FormatString(ans);
}

void ConvertCleanupFormatAnswer(CString &ans)
{
	if(g_Calculator->m_IntlMode == EUROPEAN)
		ans.Replace('.',',');

	CleanupFormatAnswer(ans);
}

void DecimalForDisplay(CString &ans)
{ 
	ConvertCleanupFormatAnswer(ans);
}

inline CString ConvertForDisplay(long double dAns)
{ 
	return ConvertForDisplay(dAns, 0); // 0 for float
}

CString ConvertForDisplay(long double dAns, int nMaxDecPlaces)
{ 
	CString strAns;
	g_Calculator->DecimalToStringSci(strAns, dAns, nMaxDecPlaces);

	// only in this case because when nMaxDecPlaces is 0 then
	// DecimalTOStringSci takes care of the decimalfordisplay
	if(nMaxDecPlaces != 0) 	
		DecimalForDisplay(strAns);  
	return strAns;
}


void ProcessMessages()
{
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // let messages get through so the program doesn't hang
		{
		if(msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
			g_fQuitScript = true;			
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
}
