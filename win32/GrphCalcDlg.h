// GrphCalcDlg.h : header file
//

#if !defined(AFX_GRPHCALCDLG_H__50D4ADC9_B16E_11D2_98BC_00104B0D20F9__INCLUDED_)
#define AFX_GRPHCALCDLG_H__50D4ADC9_B16E_11D2_98BC_00104B0D20F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "GraphView.h"	// Added by ClassView
#include "CCalculator.h"	// Added by ClassView
#include "CGCCommand.h"
#include "OutputView.h"	// Added by ClassView
#include "CalculatorView.h"
#include "Wave.h"
#include "GraphOptionsZero.h"	// Added by ClassView
#include "Mode.h"	// Added by ClassView
#include "Tfxdatatip.h"
#include "3DGraph.h"	// Added by ClassView
#include "SettingsIO.h"
#include "progdlg.h"		// Progress Bar Class
#include "CJComboBox.h"

bool IsEquation(CString equation, char variable);

// Constants usedin displaying buttons
const int button_spacing = 3;
const int button_width = 45;
const int button_height = 24;

// constants used for custom menus
#define conv_start  41000
#define conv_end 52500
#define cons_start 52501
#define cons_end 55000
#define script_start 55001
#define script_end 56000
#define ans_history_start 56001
#define ans_history_end 57000

///////////// DO NOT CHANGE ///////////////////////
#define TABS_HEIGHT			23
#define SHEET_TAB_DIFFERENCE	2
#define TAB_PAGE_DIFFERENCE_X	(SHEET_TAB_DIFFERENCE + 13)
#define TAB_PAGE_DIFFERENCE_Y	(SHEET_TAB_DIFFERENCE + 33)
#define SHEET_MARGIN_LEFT	2
#define SHEET_MARGIN_TOP	0
#define DEFAULT_TAB_WIDTH	385
#define DEFAULT_TAB_HEIGHT	420
///////////// END DO NOT CHANGE ///////////////////////

#define TAB_MARGIN_LEFT		5
#define TAB_MARGIN_TOP		2

/////////////////////////////////////////////////////////////////////////////
// CGrphCalcDlg dialog

enum ButtonStateE {BUTTON_STATE_UP=0, BUTTON_STATE_DOWN};

struct ButtonT{
	CBitmap up;
	CBitmap down;
	ButtonStateE state;
};

struct MenuBmp{
	CBitmap bmp;
	bool loaded;
};

struct ScriptsT{
	CString name;
	CArray<CString, CString> entries;
	CArray<ScriptsT, ScriptsT> sub_menu;
};

enum PaleteE{NONE,PROB,MATH,TEST,STATS,LETTERS};

class CGrphCalcDlg : public CDialog
{
// Construction
public:
	CGraphView		m_GraphViewList[MAXTABS];
	OutputView		m_OutputV;

	void AddScriptLibraryMenu(CMenu &menu, int tools_position);
	
	bool Is3DGraphActive();
	bool IsActive2DGraph(int i);

	void EvaluateFormula(CString formula, bool auto_change_tabs=true);

	int GetActiveGraphTabIndex();
	void RunScript(CString filenameS);
	bool ParseScript(CString filenameS, CArray<CString, CString> *commands);
	void Evaluate2DEquation(long double eq, long double x);
	void Evaluate3DEquation(long double eq, long double x, long double y);
	void GraphTangentLine(long double eq, long double x);
	void FindGraphArea(bool fAbsolute, long double eq1, long double eq2, long double Xmin, long double Xmax);
	void FindGraphDistance(long double eq1, long double eq2, long double Xmin, long double Xmax);
	void RenameGraphTab(CString val);
	void RemoveGraphTab(CString tab);
	void SetEquation(int eq, CString val);
	void SetEquationState(int eq, bool val);
	void SetEquationColor(int eq, CString val);
	void SetSndEffects(bool val);
	void SetSaveSettings(bool val);
	void SetDetailedOutput(bool val);
	void SetTooltips(bool val);
	void SetFullScreen(bool val);
	void SetAlwaysOnTop(bool val);
	void SetTab(CString val);
	void SetShowCommandErrors(bool val){ m_bShowCommandErrors = val; }

	void SetSettingsFile(CString str){ m_SettingsFile = str; }
	void SetStartUpScriptFile(CString str){ m_sScriptFile = str; }
	void SetStartUpScript(bool on){ m_bStartupScript = on; }
	void SetSaveExpression(bool on){ m_bSaveExprHistory = on; }
	void SetSaveOutput(bool on){ m_bSaveOutputHistory = on; }

	void SetGraphBool(CString param, bool val);
	void SetGraphNumber(CString param, long double val);
	void SetGraphString(CString param, CString val);
	void Solve(CString expression, long double guess, CString var = "x");
	void Graph2DEqIntersection(int eq1, int eq2, long double guess);
	void Graph2DXIntercept(int eq, long double guess);
	void Graph2DYIntercept(int eq);
	void Graph2DStationaryPoint(int eq, long double lbound, long double ubound);
	void Graph2DDyDx(int eq, long double x);

	void KeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	#ifdef STRESS_TEST
	void StressTestCalculator();
	#endif


	CCalculatorView m_view;	

#ifndef GRAPHCALC_LIGHT
	C3DGraph *m_3DGraphView;
#endif

	CCalculator m_Calculator;
	CGrphCalcDlg(CWnd* pParent = NULL);	// standard constructor
	~CGrphCalcDlg();
	
	void ReadSettings(CString file);
	void WriteSettings(CString file);

// Dialog Data
	//{{AFX_DATA(CGrphCalcDlg)
	enum { IDD = IDD_GRPHCALC_DIALOG };
	CCJComboBox	m_FormulaCtrl;
	CString	m_Formula;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrphCalcDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGrphCalcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnInitMenuPopup(CMenu* pMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOptionsMode();
	afx_msg void OnAppAbout();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEnter();
	afx_msg void OnViewFullscreen();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnGraphAddGraphTab();
	afx_msg void OnGraphRemovegraphtab();
	afx_msg void OnGraphZoomInXY();
	afx_msg void OnGraphZoomOutXY();
	afx_msg void OnGraphZoomInX();
	afx_msg void OnGraphZoomInY();
	afx_msg void OnGraphZoomDecimal();
	afx_msg void OnGraphZoomStandard();
	afx_msg void OnGraphZoomTrig();
	afx_msg void OnGraphZoomOutX();
	afx_msg void OnGraphZoomOutY();
	afx_msg void OnGraphZoomInteger();
	afx_msg void OnGraphZoomFit();
	afx_msg void OnGraphGraphtrace();
	afx_msg void OnHelp();
	afx_msg void OnGraphFindArea();
	afx_msg void OnGraphRenametab();
	afx_msg void OnOptionsSoundEffects();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnFileCatalog();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnFileOptionsTooltips();
	afx_msg void OnFileOptionsExpression();
	afx_msg void OnFileOptionsAnswer();
	afx_msg void OnGraphZoomPreviousRange();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnFileOptionsSavesettingsnow();
	afx_msg void OnFileOptionsSavesettingsonexit();
	afx_msg void OnFileLoadsettingsfile();
	afx_msg void OnFileSavesettingsas();
	afx_msg void OnAppExit();
	afx_msg void OnFileOptionsDisaplaydetailedoutput();
	afx_msg void OnGraphEvaluate();
	afx_msg void OnGraphTangentline();
	afx_msg void OnGraphDistance();
	afx_msg void OnGraphCopygraph();
	afx_msg void OnGraphCleartangentlines();
	afx_msg void OnOptionsAlwaysontop();
	afx_msg void OnEditchangeFormula();
	afx_msg void OnGraphPrint();
	afx_msg void OnFilePrint();
	afx_msg void OnFileRunscript();
	afx_msg void OnInsertCommand();
	afx_msg void OnOptionsProgramoptions();
	afx_msg void OnFileSaveScript();
	afx_msg void OnCtrlG();
	afx_msg void OnClose();
	afx_msg void OnUpdateOptionsSoundEffects(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGraphFindarea(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOptionsTooltips(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOptionsSavesettingsonexit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOptionsDisaplaydetailedoutput(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileLoadsettingsfile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileOptionsSavesettingsnow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGraphDistance(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOptionsAlwaysontop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGraphSaveAsBitmap();
	afx_msg void OnFileEquationSolver();
	afx_msg void On2DGraphAnalysisIntersectionof2equations();
	afx_msg void On2DGraphAnalysisIntercepts();
	afx_msg void OnUpdate2dgraphAnalysisIntercepts(CCmdUI* pCmdUI);
	afx_msg void OnUpdate2dgraphAnalysisIntersectionof2equations(CCmdUI* pCmdUI);
	afx_msg void OnAnalysisEqMinmax();
	afx_msg void OnUpdateAnalysisEqMinmax(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveOutput();
	afx_msg void OnOptionsOutputfontsettingsBase();
	afx_msg void OnOptionsOutputfontsettingsDetailedoutput();
	afx_msg void OnQuitScript();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void On2DGraphAnalysisTable();
	afx_msg void OnUpdate2DGraphCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdate2DGraphSaveAsBitmap(CCmdUI* pCmdUI);
	afx_msg void OnUpdate2DGraphPrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileEquationsolver(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileRunscript(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSavescript(CCmdUI* pCmdUI);
	afx_msg void On2DGraphAnalysisNslider();
	afx_msg void On2DGraphInfobar();
	afx_msg void OnUpdate2DGraphIInfobar(CCmdUI* pCmdUI);
	afx_msg void On2DGraphToolbar();
	afx_msg void OnUpdate2DGraphToolbar(CCmdUI* pCmdUI);
	afx_msg void On2DGraphAnimationScript();
	afx_msg void OnUpdate2DGraphAnimationScript(CCmdUI* pCmdUI);
	afx_msg void OnUpdate2DGraphNSlider(CCmdUI* pCmdUI);
	afx_msg void OnUpdate2dgraphAnalysisTable(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void Power(UINT nID);
	afx_msg void NaturalLN(UINT nID);
	afx_msg void EE(UINT nID);
	afx_msg void Sin(UINT nID);
	afx_msg void Cos(UINT nID);
	afx_msg void Tan(UINT nID);
	afx_msg void Log(UINT nID);
	afx_msg void Clear(UINT nID);
	afx_msg void Var(UINT nID);
	afx_msg void RootsMenu(UINT nID);
	afx_msg void Base(UINT nID);
	afx_msg void OnConvertMenu(UINT id);
	afx_msg void OnConstantMenu(UINT id);
	afx_msg void OnAltMenu(UINT nID);
	afx_msg void OnConvertBaseMenu(UINT id);
	afx_msg void OnOptionsGraph(UINT id);
	afx_msg void OnUpdateAltMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBaseMenu(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewFullscreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGraphGraphtrace(CCmdUI* pCmdUI);	

	afx_msg LRESULT OnGraphOptionsChanged(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT On3DGraphOptionsChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On2DCenterGraph(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On2DNSliderUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg void On3DCommand(UINT nID);

	afx_msg void OnUpdate3DAutoRotate(CCmdUI* pCmdUI);
	afx_msg void OnScriptLibraryMenu(UINT id);
	afx_msg void OnAnswerHistoryMenu(UINT id);
	afx_msg void OnSetFullWindow(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	void	LoadScriptLibrary();
	void	ReadScriptDIR(ScriptsT &scripts, CString dir);
	void	CreateScriptMenu(int &pos, CMenu &menu, ScriptsT &scripts);
	
	CString GetCurrentDirectory();
	void SaveAllSettings();
	void AddGraphTabs();
	void ClearGraphTabsToAdd();
	bool m_bShowCommandErrors;
	int m_iScriptLevel;
	void EvaluateFormula(bool auto_change_tabs=true);
	void AddGraphTab(int i);
	void Write2DGraphSettings(const CString section, int graph, CSettingsIO *io);
	void Read2DGraphSettings(const CString section, int graph, CSettingsIO *io);

	bool m_bSaveOutputHistory;
	bool m_bSaveExprHistory;
	CString m_sScriptFile;
	bool m_bStartupScript;

	void LoadExpressionHistory();
	void SaveExpressionHistory();
	void LoadAnswerHistory();
	void SaveAnswerHistory();
	SRGBString GetRGBString(CString r, CString g, CString b);
	
	bool m_UpdateDataOnEnter;
	
	void PrintString(char *p, DWORD pSize);
	void TestFile();
	MenuBmp m_OpenBmp;
	MenuBmp m_SaveBmp;
	MenuBmp m_CutBmp;
	MenuBmp m_CopyBmp;
	MenuBmp m_PasteBmp;
	void LoadSettings();
	///////////////////////////////////////////////////////////////////////////////////
	//////// MEMBER FUNCTIONS /////////
	///////////////////////////////////
	
	// Initialization Functions //////////
	void InitButtons();
	void CreateConvertMenus();
	void CreateConstantMenus();
	void CreateSubConstantMenu(int &pos, CMenu &menu, CArray<ConstCatT, ConstCatT> &cons);
	///////////////////////////////////////

	void ShowToolTips(CPoint point);
	void ResizeTabs(CSize new_size);
	void UpdateMenu(CMenu* pMenu);
	bool FullTab(int i, int &free_pos);

	CString		GetLine(::ifstream *infile);
	///////////////////////////////

	// Drawing of Buttons /////////
	void DrawButtons(CDC *pDC);
	void DrawButton(int i, int j, CDC* pDC=0);
	void DrawPaleteButton(int j, CDC *pDC=0);
	void DrawPaleteButtons(CDC *pDC);
	///////////////////////////////

	// Detect and handling of buttons ///////
	bool ButtonDetect(CPoint point, int &i, int &j);
	bool PaleteButtonDetect(CPoint point, int &j);
	
	void FormulaInsertion(CString value);
	void OnButtonSubmit(int i, int j, CPoint point);
	void OnContextMenuSubmit(int i, int j, CPoint point);
	void FindConstantMenu(int &pos, UINT id, CArray<ConstCatT, ConstCatT> &cons, CString menu_name);
	bool FindScriptLibraryMenu(int &pos, UINT id, ScriptsT &scripts);
	/////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////////
	//////// MEMBER VARIABLES /////////
	///////////////////////////////////
	bool m_StartProg;
	bool m_fEndProg;


	// Handle the viewing of the program ///
	bool			m_ActiveGraphView[MAXTABS];
	bool			m_bGraphTabsToAdd[MAXTABS];
	int				m_TotalGraphViews;
	bool			m_FullScreen;
	bool			m_AlwaysOnTop;
	PaleteE			m_CurrentPalete;
	/////////////////////////////////////////

	// Program settings //////
	bool m_Trace;
	bool m_SndEffects;
	bool m_SaveSettings;
	CString m_SettingsFile;
	bool	m_fNotShutdown;
	bool	m_fSaveFont;
	//////////////////////////

	// Different handling of buttons ///
	bool m_button_down;
	int	m_down_i;
	int m_down_j;
	CWave m_BDwave;
	CWave m_BUwave;
	TFXDataTip m_ToolTips;
	/////////////////////////////
	
	// Buttons //////////////
	ButtonT m_Buttons[5][7];
	CArray<ButtonT, ButtonT> m_ProbButtons;
	CArray<ButtonT, ButtonT> m_TestButtons;
	CArray<ButtonT, ButtonT> m_MathButtons;
	CArray<ButtonT, ButtonT> m_StatsButtons;
	CArray<ButtonT, ButtonT> m_LetterButtons;
	CPoint m_button_start;
	CPoint m_alt_button_start;
	/////////////////////////
	
	// Menus ////////////////
	int m_UserStart;
	CMenu m_MenuConvert;
	CMenu m_MenuConstant;

	// Scripts ///////////////
	bool			m_fShowScriptLibrary;
	CMenu 			m_MenuScripts;
	ScriptsT 		m_aScripts;
	bool			m_fShowScriptProgressDlg;
	CProgressDlg	m_ScriptProgressBar;
	/////////////////////////

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRPHCALCDLG_H__50D4ADC9_B16E_11D2_98BC_00104B0D20F9__INCLUDED_)
