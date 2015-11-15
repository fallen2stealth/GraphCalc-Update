#if !defined(AFX_3DGRAPH_H__71165B20_D9A8_11D3_9D44_0050DA62956A__INCLUDED_)
#define AFX_3DGRAPH_H__71165B20_D9A8_11D3_9D44_0050DA62956A__INCLUDED_

#include "3DGraphOptions.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3DGraph.h : header file
//
#include <afxtempl.h>
#include "Structs.h"
#include "CCalculator.h"	// Added by ClassView
#include "progdlg.h"		// Progress Bar Class
//#include "ClientCapture.h"	// Added by ClassView
/////////////////////////////////////////////////////////////////////////////
// C3DGraph dialog

struct innerArray {
	CArray <double, double> results_y;
};

enum GraphDestination{GRAPH_DESTINATION_WINDOW, 
					  GRAPH_DESTINATION_BITMAP,
					  GRAPH_DESTINATION_PRINTER};


class C3DGraph : public CPropertyPage
{
	DECLARE_DYNCREATE(C3DGraph)

// Construction
public:

	void ExpandEquations();
	void AllEquationsOff();
	void Paint();
	void RotateXIncrease();
	void RotateXIncrease(double degrees);
	void RotateYIncrease();
	void RotateYIncrease(double degrees);
	void RotateZIncrease();
	void RotateZIncrease(double degrees);
	
	void RotateXDecrease();
	void RotateXDecrease(double degrees);
	void RotateYDecrease();
	void RotateYDecrease(double degrees);
	void RotateZDecrease();
	void RotateZDecrease(double degrees);

	inline void ReCompute(){ OnReCompute(); }
	inline void CenterView(){ OnCenterView(); }

	void ExportDXF(CString filename);
	void Message(UINT nID);
	void SaveBitmap(CString file);
	void Options(UINT tab);
	void CopyGraph();
	void ApplyOptions();
	void InitVariables(CCalculator *Calc);
	C3DGraph();
	~C3DGraph();

	double GetBlue(COLORREF color);
	double GetGreen(COLORREF color);
	double GetRed(COLORREF color);
	
	void ZoomOutZ(bool bSlow);
	void ZoomInZ(bool bSlow);

	bool m_bCalculateEquations;

	///////////////
	// Get variables

	ColorT GetBGColor(){ return m_bg_color; }
	
	bool GetGraphModePolar(){ return m_Polar; }

	S3DEquation GetEquation(int i){ return m_3DEquations[i - 1]; }
	CString GetEquationRaw(int i){ return m_astrEquationsRaw[i - 1]; }

	// AutoRotate variables
	bool IsXAutoRotate(){ return m_bXAutoRotate; }
	bool IsYAutoRotate(){ return m_bYAutoRotate; }
	bool IsZAutoRotate(){ return m_bZAutoRotate; }
	bool IsAllAutoRotate(){ return m_bAllAutoRotate; }

	// Wireframe Options
	int	GetWireResolution(){ return	m_wire_resolution; }
	long double	GetOffset(){ return	m_offset; }
	int	GetGridlineWidth(){ return m_gridline_width; }
	
	// Axis Options
	bool GetAxesOn(){ return m_axes; }
	bool GetAxesLabelsOn(){ return m_axes_labels; }
	int GetAxesWidth(){ return m_axes_width; }
	long double GetAxesLengthMult(){ return m_axes_length_multiplier; }
	ColorT GetXColor(){ return m_x_color; }
	ColorT GetYColor(){ return m_y_color; }
	ColorT GetZColor(){ return m_z_color; }
	long double GetOriginX(){ return m_origin_x; }
	long double GetOriginY(){ return m_origin_y; }
	long double GetOriginZ(){ return m_origin_z; }

	// Tick mark Options
	bool			GetTicksOn(){ return m_tickMarks; }
	bool			GetTickCustomColor(){ return m_tick_custom_color; }
	long double		GetTickXInterval(){ return m_x_tick_interval; }
	long double		GetTickYInterval(){ return m_y_tick_interval; }
	long double		GetTickZInterval(){ return m_z_tick_interval; }
	ColorT			GetTickXColor(){ return m_x_tick_color; }
	ColorT			GetTickYColor(){ return m_y_tick_color; }
	ColorT			GetTickZColor(){ return m_z_tick_color; }
	long double		GetTickWidth(){ return m_tick_width; }
	long double		GetTickLength(){ return m_tick_length; }

	// Range Options
	int GetXInterval(){ return m_x_interval; }
	int GetYInterval(){ return m_y_interval; }
	long double GetXmin(){ return m_x_min; }
	long double GetXmax(){ return m_x_max; }
	long double GetYmin(){ return m_y_min; }
	long double GetYmax(){ return m_y_max; }
	long double GetZoomSpeed(){ return m_ZoomSpeed; }
	long double GetThetaStep(){ return m_theta_step; }

	// view parameters
	GLdouble GetXRotate(){	return m_xRotate; }
	GLdouble GetYRotate(){	return m_yRotate; }
	GLdouble GetZRotate(){	return m_zRotate; }
	GLdouble GetXTranslate(){	return m_xTranslate; }
	GLdouble GetYTranslate(){	return m_yTranslate; }
	GLdouble GetZTranslate(){	return m_zTranslate; }
	float GetXScale(){		return m_xScale; }
	float GetYScale(){		return m_yScale; }
	float GetZScale(){		return m_zScale; }

	///////////////
	// Set variables

	void SetBGColor(ColorT val){ m_bg_color = val; }
	void SetGraphModePolar(bool val){ m_Polar = val; }

	// only call when loading settings, this calls ExpandEquations()
	void SetEquation(int i, S3DEquation val)
		{
		m_3DEquations[i - 1] = val;
		m_3DEquations[i - 1].eq.Empty();
		m_astrEquationsRaw[i - 1] = val.eq;
		m_RedrawEq[i-1] = true;
		}

	// call this whenever setting an equation, it calls ExpanEquations()
	void SetEquationRawString(int i, CString val)
		{ 
		m_astrEquationsRaw[i - 1] = val;
		m_RedrawEq[i-1] = true;
		ExpandEquations();
		}
	
	void SetEquationWireMode(int i, WiresE val){ m_3DEquations[i - 1].wires = val;  m_RedrawEq[i-1] = true;}
	void SetEquationShadeMode(int i, ShadingTypeE val){ m_3DEquations[i - 1].color.type = val;  m_RedrawEq[i-1] = true;}
	void SetEquationColorXmaxYmax(int i, ColorT val){ m_3DEquations[i - 1].color.color4 = val;  m_RedrawEq[i-1] = true;}
	void SetEquationColorXmaxYmin(int i, ColorT val){ m_3DEquations[i - 1].color.color2 = val;  m_RedrawEq[i-1] = true;}
	void SetEquationColorXminYmin(int i, ColorT val){ m_3DEquations[i - 1].color.color3 = val;  m_RedrawEq[i-1] = true;}
	void SetEquationColorXminYmax(int i, ColorT val){ m_3DEquations[i - 1].color.color1 = val;  m_RedrawEq[i-1] = true;}
	void SetEquationOn(int i, bool val){ m_3DEquations[i - 1].on = val;}

	// Wireframe Options
	void SetWireResolution(int val){ m_wire_resolution = val; }
	void SetOffset(long double val){ m_offset = val; }
	void SetGridlineWidth(int val){ m_gridline_width = val; }
	
	// Axis Options
	void SetAxesOn(bool val){ m_axes = val; }
	void SetAxesLabelsOn(bool val){ m_axes_labels = val; }
	void SetAxesWidth(int val){ m_axes_width = val; }
	void SetAxesLengthMult(long double val){ m_axes_length_multiplier = val; }
	void SetXColor(ColorT val){ m_x_color = val; }
	void SetYColor(ColorT val){ m_y_color = val; }
	void SetZColor(ColorT val){ m_z_color = val; }
	void SetOriginX(long double val){ m_origin_x = val; }
	void SetOriginY(long double val){ m_origin_y = val; }
	void SetOriginZ(long double val){ m_origin_z = val; }

	// Tick mark Options
	void SetTicksOn(bool val){ m_tickMarks = val; }
	void SetTickCustomColor(bool val){ m_tick_custom_color = val; }
	void SetTickXInterval(long double val){ m_x_tick_interval = val; }
	void SetTickYInterval(long double val){ m_y_tick_interval = val; }
	void SetTickZInterval(long double val){ m_z_tick_interval = val; }
	void SetTickXColor(ColorT val){ m_x_tick_color = val; }
	void SetTickYColor(ColorT val){ m_y_tick_color = val; }
	void SetTickZColor(ColorT val){ m_z_tick_color = val; }
	void SetTickWidth(long double val){ m_tick_width = val; }
	void SetTickLength(long double val){ m_tick_length = val; }

	// Range Options
	void SetXInterval(int val){ m_x_interval = val; }
	void SetYInterval(int val){ m_y_interval = val; }
	void SetXmin(long double val){ m_x_min = val; }
	void SetXmax(long double val){ m_x_max = val; }
	void SetYmin(long double val){ m_y_min = val; }
	void SetYmax(long double val){ m_y_max = val; }
	void SetZoomSpeed(long double val){ m_ZoomSpeed = val; }
	void SetThetaStep(long double val){ m_theta_step = val; }
	
	// view parameters
	void SetXRotate(GLdouble val){	m_xRotate = val; }
	void SetYRotate(GLdouble val){	m_yRotate = val; }
	void SetZRotate(GLdouble val){	m_zRotate = val; }
	void SetXTranslate(GLdouble val){	m_xTranslate = val; }
	void SetYTranslate(GLdouble val){	m_yTranslate = val; }
	void SetZTranslate(GLdouble val){	m_zTranslate = val; }
	void SetXScale(float val){		m_xScale = val; }
	void SetYScale(float val){		m_yScale = val; }
	void SetZScale(float val){		m_zScale = val; }

	S3DEquation m_3DEquations[MAX_3D_EQS];
	bool m_fSaveSettings;

// Dialog Data
	//{{AFX_DATA(C3DGraph)
	enum { IDD = IDD_3DGRAPH };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(C3DGraph)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(C3DGraph)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnCopyGraph();
	afx_msg void OnPrint();
	afx_msg void OnSaveAsBitmap();
	afx_msg void OnZoomInZ();
	afx_msg void OnZoomOutZ();
	afx_msg void OnExportDXF();
	afx_msg void OnEvaluate();
	afx_msg void OnReCompute();
	afx_msg void OnCenterView();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnOptions(UINT nID);
	afx_msg void OnAutoRotate(UINT nID);
	afx_msg void OnUpdate3DAutoRotate(CCmdUI* pCmdUI);

private:
	
	bool ExpandEq(int eq, CString &expnEq);
	bool ExpandEq(int eq, CString &expnEq, CString strEqStack);
	CString m_astrEquationsRaw[6];
	
	void StopAutoRotate();
	int m_iRotateSpeed;
	int m_FPS;
	int m_PrevSecond;
	int m_Frames;
	void TranslateXY(CPoint change, bool slow);
	bool m_bUseProgressBar;
	bool m_bFailedEquationGeneration;

	void InitProgressBar(bool alleqs);
	void CleanUpProgressBar();

	void BuildEquations();
	short m_iEquationsOn;
	bool m_NoRePaint;
	void DrawTitle(CDC *pDC, const CSize &graph_size, const CString title);
	void PrintGraph();
	void DrawGraphToBitmap(CBitmap &bitmap, CSize size, GraphDestination dest);

	void CleanUpOpenGL();
	void InitGLView(int w, int h);
	bool SetBitmapPixelFormat(HDC hDC);
	bool SetWindowPixelFormat(HDC hDC);
	bool SetPrinterPixelFormat(HDC hDC);
	int InitOpenGl(GraphDestination dest, HDC hDC);

	void Print();

	void ReBuildEquations();
	void SnapClient();
	void StoreGraphOptions();

	void InitOptionsDlg();
	CCalculator *m_pCalculator;
	C3DGraphOptions *m_GraphOptions;

	
	void doVertex(double x, double y, double result);
	void BuildList(int eq);
	bool CreateViewGLContext(HDC hDC);

	void DrawTickMarks(long double x_axes_min, long double x_axes_max,
					   long double y_axes_min, long double y_axes_max,
					   long double z_axes_min, long double z_axes_max);
	void DrawAxes(long double x_axes_min, long double x_axes_max,
				  long double y_axes_min, long double y_axes_max,
				  long double z_axes_min, long double z_axes_max);
	void DrawLabels(long double x_axes_min, long double x_axes_max,
					long double y_axes_min, long double y_axes_max,
					long double z_axes_min, long double z_axes_max);
	void RenderGraph();

	void DrawLetterPlus(long double pos_x, long double pos_y, long double pos_z,
						long double plus_height, long double plus_width);
	void DrawLetterMinus(long double pos_x, long double pos_y, long double pos_z,
						long double plus_width);
	void DrawLetterX(long double pos_x, long double pos_y, long double pos_z,
						long double plus_height, long double plus_width);
	void DrawLetterY(long double pos_x, long double pos_y, long double pos_z,
						long double plus_height, long double plus_width);
	void DrawLetterZ(long double pos_x, long double pos_y, long double pos_z,
						long double plus_height, long double plus_width);
	void DrawLetterTheta(long double pos_x, long double pos_y, long double pos_z,
						long double theta_height, long double theta_width);

	void UpdateMenu(CMenu* pMenu);

	HGLRC		m_hGLContext;
	int			m_GLPixelIndex;
	CBitmap		m_GraphBitmap;
	
	CMenu m_Menu3DGraph;
	
	// Window Options
	ColorT m_bg_color;

	// Wireframe Options
	int				m_wire_resolution;
	long double		m_offset;
	int				m_gridline_width;
	
	// Axis Options
	bool			m_axes;
	bool			m_axes_labels;
	int				m_axes_width;
	long double		m_axes_length_multiplier;
	ColorT			m_x_color;
	ColorT			m_y_color;
	ColorT			m_z_color;
	long double		m_origin_x;
	long double		m_origin_y;
	long double		m_origin_z;
	long double		m_theta_step;
	
	// Tick mark Options
	bool			m_tickMarks;
	bool			m_tick_custom_color;
	long double		m_x_tick_interval;
	long double		m_y_tick_interval;
	long double		m_z_tick_interval;
	ColorT			m_x_tick_color;
	ColorT			m_y_tick_color;
	ColorT			m_z_tick_color;
	long double		m_tick_width;
	long double		m_tick_length;

	// Range Options
	int				m_x_interval;
	int				m_y_interval;
	long double		m_x_min;
	long double		m_x_max;
	long double		m_y_min;
	long double		m_y_max;
	long double		m_z_min;
	long double		m_z_max;

	double			m_ZoomSpeed;

	bool			m_Polar;

	// Movement and rotation options
	bool		m_bXAutoRotate;
	bool		m_bYAutoRotate;
	bool		m_bZAutoRotate;
	bool		m_bAllAutoRotate;

	GLdouble	m_xRotate;
	GLdouble	m_yRotate;
	GLdouble	m_zRotate;

	GLdouble	m_xTranslate;
	GLdouble	m_yTranslate;
	GLdouble	m_zTranslate;

	float		m_xScale;
	float		m_yScale;
	float		m_zScale;

	bool		m_bLButtonDown;
	bool		m_bRButtonDown;
	CPoint 		m_DownPoint;
	GLuint		m_GLlist[MAX_3D_EQS];
	GLuint		m_GLWirelist[MAX_3D_EQS];
	bool		m_RedrawEq[MAX_3D_EQS];

	//Progress Bar
	void IncrementPrecomputeProgress(int num_of_eqs);
	void IncrementOpenGLProgress(int num_of_eqs);
	CProgressDlg	m_ProgressBar;
	long double		m_progress;			// 0.0 to 1.0 of 3D graphing completion
	long double		m_progress_ratio;	// ratio between CCalculator computing and OpenGL computing time
	int				m_master_count;		// count of all cycles of precomuting and opengl init
	int				m_master_percent;	// 1% of the total count
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DGRAPH_H__71165B20_D9A8_11D3_9D44_0050DA62956A__INCLUDED_)
