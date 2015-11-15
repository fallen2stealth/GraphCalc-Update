// 3DGraph.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "3DGraph.h"
#include "Color.h"
#include "ClientCapture.h"
#include <math.h>
#include "CPrintGraph.h"
#include "GrphCalcDlg.h"
#include "3DGraphEvaluateDlg.h"

extern bool g_Registered;
extern void TrimNumber(CString &str);
//#include "Print.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_TICKS 1000

/////////////////////////////////////////////////////////////////////////////
// C3DGraph property page

IMPLEMENT_DYNCREATE(C3DGraph, CPropertyPage)

C3DGraph::C3DGraph() : CPropertyPage(C3DGraph::IDD)
{
	//{{AFX_DATA_INIT(C3DGraph)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_fSaveSettings = false;
	
	m_bXAutoRotate = false;
	m_bYAutoRotate = false;
	m_bZAutoRotate = false;
	m_bAllAutoRotate = false;
	m_iRotateSpeed = 2;

	m_xScale = 1.0f;
	m_yScale = 1.0f;
	m_zScale = 1.0f;

	m_xRotate = -30;
	m_yRotate = 0;
	m_zRotate = 0;

	m_xTranslate = 0.0f;
	m_yTranslate = 0.0f;
	m_zTranslate = -20.0f;
	m_ZoomSpeed = 4;

	m_bLButtonDown = false;
	m_bRButtonDown = false;

	//m_GraphOptions = new C3DGraphOptions("3D Graphing Options");

	// Default graphing options //
	m_bg_color.red = 0;
	m_bg_color.green = 0;
	m_bg_color.blue = 0;

	m_wire_resolution		= 2;
	m_offset				= 0.01;
	m_gridline_width		= 1.0;

	m_axes					= true;
	m_axes_labels			= true;
	m_axes_width			= 2.0;
	m_axes_length_multiplier= 1.1;
	m_origin_x				= 0.0;
	m_origin_y				= 0.0;
	m_origin_z				= 0.0;
	m_x_color.red			= 0.0;
	m_x_color.green			= 0.0;
	m_x_color.blue			= 0.7;
	m_y_color.red			= 0.0;
	m_y_color.green			= 0.7;
	m_y_color.blue			= 0.0;
	m_z_color.red			= 0.7;
	m_z_color.green			= 0.0;
	m_z_color.blue			= 0.0;

	m_theta_step			= PI/6;

	m_tickMarks				= true;
	m_tick_custom_color		= false;
	m_x_tick_interval		= 2.0;
	m_y_tick_interval		= 2.0;
	m_z_tick_interval		= 2.0;
	m_x_tick_color.red		= 0.0;
	m_x_tick_color.blue		= 0.7;
	m_x_tick_color.green	= 0.0;
	m_y_tick_color.red		= 0.0;
	m_y_tick_color.blue		= 0.0;
	m_y_tick_color.green	= 0.7;
	m_z_tick_color.red		= 0.7;
	m_z_tick_color.blue		= 0.0;
	m_z_tick_color.green	= 0.0;
	m_tick_width			= 1.0;
	m_tick_length			= 1.0;

	m_x_interval			= 50;
	m_y_interval			= 50;
	m_x_min					= -5;
	m_x_max					= 5;
	m_y_min					= -5;
	m_y_max					= 5;
	m_z_min					= -3;
	m_z_max					= 3;


	m_progress				= 0.0;
	m_progress_ratio		= 2.0;
	m_master_count			= 1;
	m_master_percent		= 0;
	m_iEquationsOn			= 0;
	m_bFailedEquationGeneration = false;
	m_bCalculateEquations = true;
	m_bUseProgressBar		= true;
	
	for(int i(0); i < MAX_3D_EQS; ++i){
		m_RedrawEq[i] = true;

		m_3DEquations[i].eq.Empty();
		m_3DEquations[i].on = false;
		m_3DEquations[i].wires = CW;
		m_3DEquations[i].color.type = FOUR_COLOR;
		
		m_3DEquations[i].color.color1.red = 0;
		m_3DEquations[i].color.color1.green = .2;
		m_3DEquations[i].color.color1.blue = 0;
		
		m_3DEquations[i].color.color2.red = 1;
		m_3DEquations[i].color.color2.green = 1;
		m_3DEquations[i].color.color2.blue = 0;
		
		m_3DEquations[i].color.color3.red = .8;
		m_3DEquations[i].color.color3.green = 0;
		m_3DEquations[i].color.color3.blue = 0;
		
		m_3DEquations[i].color.color4.red = 0;
		m_3DEquations[i].color.color4.green = 0;
		m_3DEquations[i].color.color4.blue = .5;
	}

	// SET DEFAULT EQUATIONS
	m_astrEquationsRaw[0] = m_3DEquations[0].eq = "(cos(sqrt(((x+0)^2)+((y+0)^2))) + cos(sqrt(((x+.913*2pi)^2)+((y+0)^2))) + cos(sqrt(((x-.913*2pi)^2)+((y+0)^2))))";
	m_astrEquationsRaw[1] = m_3DEquations[1].eq = "4*cos (3*sqrt(x^2 + y^2))*e^(-0.3*(sqrt(x^2 + y^2)))";
	m_astrEquationsRaw[2] = m_3DEquations[2].eq = "sin (x*y/4)+frand(0:1)";
	m_astrEquationsRaw[3] = m_3DEquations[3].eq = "cos(3*r)*cos(5*t)*e^(-.3r)*3";
	m_astrEquationsRaw[4] = m_3DEquations[4].eq = "(r+t)*.5";
	m_astrEquationsRaw[5] = m_3DEquations[5].eq = "sin(r*t)";
	// END SET DEFAULT EQUATIONS

	m_NoRePaint = false;
	m_Polar = false;

	m_Frames = 0;
	m_FPS = 0;
	m_PrevSecond = 0;
}

C3DGraph::~C3DGraph()
{
	//CleanUp(GetSafeHwnd());
}

void C3DGraph::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DGraph)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DGraph, CPropertyPage)
	//{{AFX_MSG_MAP(C3DGraph)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_3DGRAPH_COPYGRAPH, OnCopyGraph)
	ON_COMMAND(ID_3DGRAPH_PRINT, OnPrint)
	ON_COMMAND(ID_3DGRAPH_SAVEASBITMAP, OnSaveAsBitmap)
	ON_COMMAND(ID_3DGRAPH_ZOOM_IN_Z, OnZoomInZ)
	ON_COMMAND(ID_3DGRAPH_ZOOM_OUT_Z, OnZoomOutZ)
	ON_COMMAND(ID_3DGRAPH_EXPORTTODFX, OnExportDXF)
	ON_COMMAND(ID_3DGRAPH_EVALUATE, OnEvaluate)
	ON_COMMAND(ID_3DGRAPH_RECOMPUTE, OnReCompute)
	ON_COMMAND(ID_3DGRAPH_CENTERVIEW, OnCenterView)
	ON_WM_KEYDOWN()
	ON_WM_GETDLGCODE()
	ON_WM_TIMER()
	ON_WM_INITMENUPOPUP()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_3DGRAPH_EQUATIONS, ID_3DGRAPH_OPTIONS, OnOptions)
	ON_COMMAND_RANGE(ID_3DGRAPH_AUTOROTATE_ALLAXIS, ID_3DGRAPH_AUTOROTATE_DECREASESPEED, OnAutoRotate)
	ON_UPDATE_COMMAND_UI_RANGE(ID_3DGRAPH_AUTOROTATE_ALLAXIS, ID_3DGRAPH_AUTOROTATE_DECREASESPEED, OnUpdate3DAutoRotate)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DGraph message handlers

void C3DGraph::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	InitGLView(cx, cy);
}

void C3DGraph::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	
	CleanUpOpenGL();
}

void C3DGraph::CleanUpOpenGL()
{
	if(wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL,NULL);
	
	if(m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}	
}

BOOL C3DGraph::OnEraseBkgnd(CDC* pDC) 
{
     // TODO: Add your message handler code here and/or call
     // default

     // Comment this line out
     // return CView::OnEraseBkgnd(pDC);

     return TRUE; // OpenGL will erase the background
}

int C3DGraph::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	HWND hWnd = GetSafeHwnd();
	InitOpenGl(GRAPH_DESTINATION_WINDOW, ::GetDC(hWnd));

	return 0;
}

// Function name	: C3DGraph::CreateViewGLContext
// Description	    : 
// Return type		: bool 
// Argument         : HDC hDC
bool C3DGraph::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	
	if(m_hGLContext==NULL)
		return false;
	
	if(wglMakeCurrent(hDC,m_hGLContext)==FALSE)
		return false;
	
	return true;
}


// Function name	: C3DGraph::SetWindowPixelFormat
// Description	    : 
// Return type		: bool 
// Argument         : HDC hDC
bool C3DGraph::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	
	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | 
						PFD_SUPPORT_OPENGL |	
						PFD_DOUBLEBUFFER |
						PFD_STEREO_DONTCARE |
						PFD_GENERIC_ACCELERATED;
	
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;
	
	m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
	if(m_GLPixelIndex==0) // Choose default
	{
		m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_GLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
		{
			return false;
		}
	}
	
	if(SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc)==FALSE)
	{
		return false;
	}
	
	return TRUE;
}

bool C3DGraph::SetBitmapPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	
	pixelDesc.dwFlags = PFD_DRAW_TO_BITMAP | 
						PFD_SUPPORT_OPENGL |
						PFD_STEREO_DONTCARE;
	
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	CBitmap* pBitmap = CDC::FromHandle(hDC)->GetCurrentBitmap() ;
	BITMAP bmInfo ;
	pBitmap->GetObject(sizeof(BITMAP), &bmInfo) ;
	pixelDesc.cColorBits = (BYTE)bmInfo.bmBitsPixel;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.cDepthBits = 32;
	
	m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
	if(m_GLPixelIndex==0) // Choose default
	{
		m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_GLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
		{
			return false;
		}
	}
	
	if(SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc)==FALSE)
	{
		return false;
	}
	
	return TRUE;
}

bool C3DGraph::SetPrinterPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;
	
	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;
	
	pixelDesc.dwFlags = PFD_DRAW_TO_BITMAP | 
						PFD_SUPPORT_OPENGL |
						PFD_STEREO_DONTCARE;
	
	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	CBitmap* pBitmap = CDC::FromHandle(hDC)->GetCurrentBitmap() ;
	BITMAP bmInfo ;
	pBitmap->GetObject(sizeof(BITMAP), &bmInfo) ;
	pixelDesc.cColorBits = (BYTE)bmInfo.bmBitsPixel;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;
	pixelDesc.cRedBits = 8;
	pixelDesc.cRedShift = 16;
	pixelDesc.cGreenBits = 8;
	pixelDesc.cGreenShift = 8;
	pixelDesc.cBlueBits = 8;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 64;
	pixelDesc.cAccumRedBits = 16;
	pixelDesc.cAccumGreenBits = 16;
	pixelDesc.cAccumBlueBits = 16;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 8;
	pixelDesc.cAuxBuffers = 0;
	
	m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);

	if(m_GLPixelIndex==0) // Choose default
	{
		m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_GLPixelIndex,
			sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc)==0)
		{
			return false;
		}
	}
	
	if(SetPixelFormat(hDC,m_GLPixelIndex,&pixelDesc)==FALSE)
	{
		return false;
	}
	
	return TRUE;
}


void C3DGraph::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(m_NoRePaint)
		return;

	CCalculatorView *pWnd = (CCalculatorView*)GetParent();
	MoveWindow(&pWnd->m_PageRect); 

	m_NoRePaint = true;
	RenderGraph();
	SwapBuffers(dc.m_ps.hdc);
	m_NoRePaint = false;

	/*CRect clientR;
	GetClientRect(&clientR);
	CBrush brush(RGB(192,192,192));
	dc.FillRect(CRect(0,0,5,clientR.bottom), &brush);*/
/*
	++m_Frames;
	
	if(m_FPS > 0){
		CString str;
		str.Format("%d", m_FPS);
		dc.TextOut(15+(dc.GetDeviceCaps(LOGPIXELSX)*0.02), 15+(dc.GetDeviceCaps(LOGPIXELSY)*0.001), str);
	}
	
	CTime tm;
	tm = tm.GetCurrentTime();
	int second = tm.GetSecond();
	if(second != m_PrevSecond){
		m_PrevSecond = second;
		m_FPS = m_Frames;
		m_Frames = 0;
	}
*/
}

void C3DGraph::DrawAxes(long double x_axes_min, long double x_axes_max,
						long double y_axes_min, long double y_axes_max,
						long double z_axes_min, long double z_axes_max){
		glLineWidth(GLfloat(m_axes_width));
		//glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINES);

		if (m_Polar){
			glColor3f(m_z_color.red,m_z_color.green,m_z_color.blue); // Z-axis
			doVertex( m_origin_x, m_origin_y, z_axes_min);
			doVertex( m_origin_x, m_origin_y, z_axes_max);
			double length = .5 * (y_axes_max - y_axes_min);
			for (double t = 0.0; t < (m_pCalculator->m_trig_state == RADIAN ? 2*PI : 360); t += m_theta_step){ 
				glColor3f(m_y_color.red,m_y_color.green,m_y_color.blue); // Y-axis
				doVertex(length, t, m_origin_z);
				doVertex(m_origin_x, m_origin_y, m_origin_z);
			}
		}
		else{
			glColor3f(m_z_color.red,m_z_color.green,m_z_color.blue); // Z-axis
			glVertex3d( m_origin_x, m_origin_y, z_axes_min);
			glVertex3d( m_origin_x, m_origin_y, z_axes_max);
			glColor3f(m_y_color.red,m_y_color.green,m_y_color.blue); // Y-axis
			glVertex3d( m_origin_x, y_axes_min, m_origin_z);
			glVertex3d( m_origin_x, y_axes_max, m_origin_z);
			glColor3f(m_x_color.red,m_x_color.green,m_x_color.blue); // X-axis
			glVertex3d( x_axes_min, m_origin_y, m_origin_z);
			glVertex3d( x_axes_max, m_origin_y, m_origin_z);
		}
		glEnd();
		//glDisable(GL_LINE_SMOOTH);
}


void C3DGraph::DrawTickMarks(long double x_axes_min, long double x_axes_max,
							 long double y_axes_min, long double y_axes_max,
							 long double z_axes_min, long double z_axes_max){
		glLineWidth(GLfloat(m_tick_width));
		//glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINES);
		long double i;
		long double adder(-.3);  // how much luminosity to add
		if (!m_Polar){
			for (i = m_origin_x + m_x_tick_interval; i < x_axes_max; i+= m_x_tick_interval){ //+X Ticks
				if (m_tick_custom_color){
					glColor3f(m_x_tick_color.red, m_x_tick_color.green, m_x_tick_color.blue);
				}
				else{
					glColor3f(m_x_color.red+adder,m_x_color.green+adder,m_x_color.blue+adder);
				}
				glVertex3d( i, m_origin_y, m_tick_length+m_origin_z		);
				glVertex3d( i, m_origin_y, (-1*m_tick_length)+m_origin_z	);
			}
			for (i = m_origin_x - m_x_tick_interval; i > x_axes_min; i-= m_x_tick_interval){ //-X Ticks
				if (m_tick_custom_color){
					glColor3f(m_x_tick_color.red, m_x_tick_color.green, m_x_tick_color.blue);
				}
				else{
					glColor3f(m_x_color.red+adder,m_x_color.green+adder,m_x_color.blue+adder);
				}
				glVertex3d( i, m_origin_y, m_tick_length+m_origin_z		);
				glVertex3d( i, m_origin_y, (-1*m_tick_length)+m_origin_z	);
			}
			
			for (i = m_origin_y + m_y_tick_interval; i < y_axes_max; i+= m_y_tick_interval){ //+Y Ticks
				if (m_tick_custom_color){
					glColor3f(m_y_tick_color.red, m_y_tick_color.green, m_y_tick_color.blue);
				}
				else{
					glColor3f(m_y_color.red+adder,m_y_color.green+adder,m_y_color.blue+adder);
				}
				glVertex3d( m_origin_x, i , m_tick_length+m_origin_z);
				glVertex3d( m_origin_x, i , (-1*m_tick_length)+m_origin_z);
			}
			for (i = m_origin_y - m_y_tick_interval; i > y_axes_min; i-= m_y_tick_interval){ //-Y Ticks
				if (m_tick_custom_color){
					glColor3f(m_y_tick_color.red, m_y_tick_color.green, m_y_tick_color.blue);
				}
				else{
					glColor3f(m_y_color.red+adder,m_y_color.green+adder,m_y_color.blue+adder);
				}
				glVertex3d( m_origin_x, i , m_tick_length+m_origin_z);
				glVertex3d( m_origin_x, i , (-1*m_tick_length)+m_origin_z);
			}
		}
		else{
			double length = .5 * (y_axes_max - y_axes_min);
			for (double t = 0.0; t < (m_pCalculator->m_trig_state == RADIAN ? 2*PI : 360); t += m_theta_step){ 
				for (i = m_origin_x; i < length; i+= m_y_tick_interval){ //+Y Ticks
					if (m_tick_custom_color){
						glColor3f(m_y_tick_color.red, m_y_tick_color.green, m_y_tick_color.blue);
					}
					else{
						glColor3f(m_y_color.red+adder,m_y_color.green+adder,m_y_color.blue+adder);
					}
					doVertex( i, t , m_tick_length);
					doVertex( i, t , -1*m_tick_length);
				}
			}
		}

		long double z_tick_interval = m_z_tick_interval;

		if ( ((z_axes_max-m_origin_z)/z_tick_interval) > MAX_TICKS)
			z_tick_interval = (z_axes_max-m_origin_z) / MAX_TICKS;
		else if ( ((m_origin_z-z_axes_min)/z_tick_interval) > MAX_TICKS)
			z_tick_interval = (z_axes_max-m_origin_z) / MAX_TICKS;
		

		for (i = m_origin_z + z_tick_interval; i < z_axes_max; i+= z_tick_interval){ //+Z Ticks
			if (m_tick_custom_color){
				glColor3f(m_z_tick_color.red, m_z_tick_color.green, m_z_tick_color.blue);
			}
			else{
				glColor3f(m_z_color.red+adder,m_z_color.green+adder,m_z_color.blue+adder);
			}
			glVertex3d( m_tick_length+m_origin_x, m_origin_y, i);
			glVertex3d( (-1*m_tick_length)+m_origin_x, m_origin_y, i);
		}
		for (i = m_origin_z - z_tick_interval; i > z_axes_min; i-= z_tick_interval){ //-Z Ticks
			if (m_tick_custom_color){
				glColor3f(m_z_tick_color.red, m_z_tick_color.green, m_z_tick_color.blue);
			}
			else{
				glColor3f(m_z_color.red+adder,m_z_color.green+adder,m_z_color.blue+adder);
			}
			glVertex3d( m_tick_length+m_origin_x, m_origin_y, i);
			glVertex3d( (-1*m_tick_length)+m_origin_x, m_origin_y, i);
		}
		glEnd();
		//glDisable(GL_LINE_SMOOTH);
}

void C3DGraph::DrawLetterPlus(long double pos_x, long double pos_y, long double pos_z,
					long double plus_height, long double plus_width){
	glVertex3d( pos_x-(0.5*plus_width), pos_y , pos_z+(-0.5*plus_height));
	glVertex3d( pos_x-(0.5*plus_width), pos_y , pos_z+(0.5*plus_height));
	glVertex3d( pos_x                 , pos_y , pos_z);
	glVertex3d( pos_x-plus_width      , pos_y , pos_z);
}

void C3DGraph::DrawLetterMinus(long double pos_x, long double pos_y, long double pos_z,
					 long double minus_width){
	glVertex3d( pos_x             , pos_y , pos_z);
	glVertex3d( pos_x-minus_width , pos_y , pos_z);
}

void C3DGraph::DrawLetterX(long double pos_x, long double pos_y, long double pos_z,
				 long double x_height, long double x_width){
	glVertex3d( pos_x + x_width, pos_y , pos_z+(-1*x_height));
	glVertex3d( pos_x          , pos_y , pos_z+x_height);
	glVertex3d( pos_x          , pos_y , pos_z+(-1*x_height));
	glVertex3d( pos_x + x_width, pos_y , pos_z+x_height);
}

void C3DGraph::DrawLetterY(long double pos_x, long double pos_y, long double pos_z,
				 long double y_height, long double y_width){
	glVertex3d( pos_x+(0.5*y_width), pos_y, pos_z-(0.4*y_height));
	glVertex3d( pos_x+(0.5*y_width), pos_y, pos_z);
	glVertex3d( pos_x              , pos_y, pos_z+(0.6*y_height));
	glVertex3d( pos_x+(0.5*y_width), pos_y, pos_z);
	glVertex3d( pos_x+y_width      , pos_y, pos_z+(0.6*y_height));
	glVertex3d( pos_x+(0.5*y_width), pos_y, pos_z);
}

void C3DGraph::DrawLetterZ(long double pos_x, long double pos_y, long double pos_z,
				 long double z_height, long double z_width){
	glVertex3d( pos_x + z_width, pos_y , pos_z+(-1*z_height));
	glVertex3d( pos_x          , pos_y , pos_z+(-1*z_height));
	glVertex3d( pos_x          , pos_y , pos_z+(-1*z_height));
	glVertex3d( pos_x + z_width, pos_y , pos_z+z_height);
	glVertex3d( pos_x + z_width, pos_y , pos_z+z_height);
	glVertex3d( pos_x          , pos_y , pos_z+z_height);
}

void C3DGraph::DrawLetterTheta(long double pos_x, long double pos_y, long double pos_z,
				 long double theta_height, long double theta_width){
	glVertex3d( pos_x + (0.00 * theta_width), pos_y , pos_z );
	glVertex3d( pos_x + (0.25 * theta_width), pos_y , pos_z+(0.8*theta_height));
	glVertex3d( pos_x + (0.25 * theta_width), pos_y , pos_z+(0.8*theta_height));
	glVertex3d( pos_x + (0.50 * theta_width), pos_y , pos_z+(1.0*theta_height));
	glVertex3d( pos_x + (0.50 * theta_width), pos_y , pos_z+(1.0*theta_height));
	glVertex3d( pos_x + (0.75 * theta_width), pos_y , pos_z+(0.8*theta_height));
	glVertex3d( pos_x + (0.75 * theta_width), pos_y , pos_z+(0.8*theta_height));
	glVertex3d( pos_x + (1.00 * theta_width), pos_y , pos_z );
	glVertex3d( pos_x + (1.00 * theta_width), pos_y , pos_z );
	glVertex3d( pos_x + (0.75 * theta_width), pos_y , pos_z-(0.8*theta_height));
	glVertex3d( pos_x + (0.75 * theta_width), pos_y , pos_z-(0.8*theta_height));
	glVertex3d( pos_x + (0.50 * theta_width), pos_y , pos_z-(1.0*theta_height));
	glVertex3d( pos_x + (0.50 * theta_width), pos_y , pos_z-(1.0*theta_height));
	glVertex3d( pos_x + (0.25 * theta_width), pos_y , pos_z-(0.8*theta_height));
	glVertex3d( pos_x + (0.25 * theta_width), pos_y , pos_z-(0.8*theta_height));
	glVertex3d( pos_x + (0.00 * theta_width), pos_y , pos_z );
	glVertex3d( pos_x + (0.00 * theta_width), pos_y , pos_z );
	glVertex3d( pos_x + (1.00 * theta_width), pos_y , pos_z );
}

void C3DGraph::DrawLabels(long double x_axes_min, long double x_axes_max,
						  long double y_axes_min, long double y_axes_max,
						  long double z_axes_min, long double z_axes_max){
	glLineWidth(GLfloat(1.0));
	//glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
		long double x_axes_length = x_axes_max-x_axes_min;
		long double y_axes_length = y_axes_max-y_axes_min;
		long double z_axes_length = z_axes_max-z_axes_min;
		long double x_offset =  0.035*x_axes_length;
		long double y_offset = -0.02*y_axes_length;
		long double z_offset =  0.03*x_axes_length;

		long double x_scale  = 0.03*x_axes_length, y_scale  = 0.03*y_axes_length;
		long double font_scale = (x_scale+y_scale)/2.0;

		if (!m_Polar){
			glColor3f(m_x_color.red,m_x_color.green,m_x_color.blue);
			DrawLetterPlus (x_axes_max+x_offset	, y_offset + m_origin_y, m_origin_z, font_scale, font_scale);
			DrawLetterMinus(x_axes_min-x_offset	, y_offset + m_origin_y, m_origin_z, font_scale);
			DrawLetterX    (x_axes_max+x_offset	, y_offset + m_origin_y, m_origin_z, font_scale, font_scale);
			DrawLetterX    (x_axes_min-x_offset	, y_offset + m_origin_y, m_origin_z, font_scale, font_scale);
			
			glColor3f(m_y_color.red,m_y_color.green,m_y_color.blue);
			DrawLetterPlus ( x_offset + m_origin_x, y_axes_max-y_offset, m_origin_z, font_scale, font_scale);
			DrawLetterMinus( x_offset + m_origin_x, y_axes_min+y_offset, m_origin_z, font_scale);
			DrawLetterY    ( x_offset + m_origin_x, y_axes_max-y_offset, m_origin_z, font_scale, font_scale);
			DrawLetterY    ( x_offset + m_origin_x, y_axes_min+y_offset, m_origin_z, font_scale, font_scale);
		}
		else{		
			glColor3f(m_y_color.red,m_y_color.green,m_y_color.blue);
			DrawLetterTheta    (  x_offset + m_origin_x, y_axes_max-y_offset, m_origin_z, font_scale, font_scale);
		}

		glColor3f(m_z_color.red,m_z_color.green,m_z_color.blue);
		DrawLetterPlus ( x_offset + m_origin_x, y_offset + m_origin_y, z_axes_max+z_offset, font_scale, font_scale);
		DrawLetterMinus( x_offset + m_origin_x, y_offset + m_origin_y, z_axes_min-z_offset, font_scale);
		DrawLetterZ    ( x_offset + m_origin_x, y_offset + m_origin_y, z_axes_max+z_offset, font_scale, font_scale);
		DrawLetterZ    ( x_offset + m_origin_x, y_offset + m_origin_y, z_axes_min-z_offset, font_scale, font_scale);
	glEnd();
	//glDisable(GL_LINE_SMOOTH);
}

void C3DGraph::RenderGraph()
{
	BuildEquations();

	glClearColor(m_bg_color.red,
				 m_bg_color.green,
				 m_bg_color.blue,
				 1.0); // sets the background color

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	// Position / translation
	glTranslated(m_xTranslate,m_yTranslate,m_zTranslate);
	glRotated(m_xRotate, 1.0, 0.0, 0.0);
	glRotated(m_yRotate, 0.0, 1.0, 0.0);
	glRotated(m_zRotate, 0.0, 0.0, 1.0);
	glScalef(m_xScale,m_yScale,m_zScale);


	// Validate variables
	if(m_theta_step <= 0)
		m_theta_step = (m_pCalculator->m_trig_state == RADIAN ? PI/6 : 30);

	if(m_x_tick_interval <= 0) m_x_tick_interval = 1;
	if(m_y_tick_interval <= 0) m_y_tick_interval = 1;
	if(m_z_tick_interval <= 0) m_z_tick_interval = 1;
	// End Validate variables
		
	double x_side(m_x_max-m_x_min), y_side(m_y_max-m_y_min);

	long double x_axes_max, x_axes_min,
				y_axes_max, y_axes_min,
				z_axes_max, z_axes_min;

	if (m_Polar){
		x_axes_max = m_x_max + (m_axes_length_multiplier-1)*(m_x_max-m_x_min);
		x_axes_min = -1 * x_axes_max;
		y_axes_max = x_axes_max;
		y_axes_min = x_axes_min;
		z_axes_max = m_z_max + (1.5*m_axes_length_multiplier-1)*(m_z_max-m_z_min);
		z_axes_min = m_z_min - (1.5*m_axes_length_multiplier-1)*(m_z_max-m_z_min);
	}
	else{
		x_axes_max = m_x_max + (m_axes_length_multiplier-1)*(m_x_max-m_x_min);
		x_axes_min = m_x_min - (m_axes_length_multiplier-1)*(m_x_max-m_x_min);
		y_axes_max = m_y_max + (m_axes_length_multiplier-1)*(m_y_max-m_y_min);
		y_axes_min = m_y_min - (m_axes_length_multiplier-1)*(m_y_max-m_y_min);
		z_axes_max = m_z_max + (1.5*m_axes_length_multiplier-1)*(m_z_max-m_z_min);
		z_axes_min = m_z_min - (1.5*m_axes_length_multiplier-1)*(m_z_max-m_z_min);
		if (m_x_min > m_origin_x) x_axes_min = m_origin_x - (m_axes_length_multiplier-1)*(m_x_max-m_x_min);
		if (m_x_max < m_origin_x) x_axes_max = m_origin_x + (m_axes_length_multiplier-1)*(m_x_max-m_x_min);
		if (m_y_min > m_origin_y) y_axes_min = m_origin_y - (m_axes_length_multiplier-1)*(m_y_max-m_y_min);
		if (m_y_max < m_origin_y) y_axes_max = m_origin_y + (m_axes_length_multiplier-1)*(m_y_max-m_y_min);
		if (m_z_min > m_origin_z) z_axes_min = m_origin_z - (1.5*m_axes_length_multiplier-1)*(m_z_max-m_z_min);
		if (m_z_max < m_origin_z) z_axes_max = m_origin_z + (1.5*m_axes_length_multiplier-1)*(m_z_max-m_z_min);
	}
	

	long double min_axes = min((x_axes_max-x_axes_min),(y_axes_max-y_axes_min));
	if ((z_axes_max - z_axes_min) < min_axes){
		long double additional_length = (min_axes - (z_axes_max - z_axes_min)) / 2.0;
		z_axes_max += additional_length;
		z_axes_min -= additional_length;
	}

	if (m_axes_labels){
		DrawLabels(x_axes_min, x_axes_max,
				   y_axes_min, y_axes_max,
				   z_axes_min, z_axes_max);
	}
	if (m_tickMarks){
		DrawTickMarks(x_axes_min, x_axes_max,
				      y_axes_min, y_axes_max,
					  z_axes_min, z_axes_max);
	}
	if (m_axes){
		DrawAxes(x_axes_min, x_axes_max,
				 y_axes_min, y_axes_max,
				 z_axes_min, z_axes_max);
	}

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(.0,1.5);
	for (int m = 0; m < MAX_3D_EQS; ++m){
		if(m_3DEquations[m].on && !m_bFailedEquationGeneration){
			glCallList(m_GLlist[m]);
		}
	}
	glDisable(GL_POLYGON_OFFSET_FILL);

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	for (m = 0; m < MAX_3D_EQS; ++m){
		if(m_3DEquations[m].wires != C && !m_bFailedEquationGeneration){
			glCallList(m_GLWirelist[m]);
		}
	}

	glPopMatrix();
}

double intensity(double x, double y, int corner){
	double d1 = 1- sqrt(pow(x,2)+pow(y,2));
	double d2 = 1- sqrt(pow(1-x,2)+pow(y,2));
	double d3 = 1- sqrt(pow(1-x,2)+pow(1-y,2));
	double d4 = 1- sqrt(pow(x,2)+pow(1-y,2));
	
	if (d1 < 0) d1 = 0;
	if (d2 < 0) d2 = 0;
	if (d3 < 0) d3 = 0;
	if (d4 < 0) d4 = 0;

	switch(corner){
	case 1: return (d1/(d1+d2+d3+d4));
	case 2: return (d2/(d1+d2+d3+d4));
	case 3: return (d3/(d1+d2+d3+d4));
	case 4: return (d4/(d1+d2+d3+d4));
	}
	return 0;
}
 
/*
	EUCLIDEAN: x,y,z values

	POLAR:	   r,t,z
			   where t is in the same units as m_pCalculator->m_trig_state
*/
void C3DGraph::doVertex(double x, double y, double result){
	if (m_Polar){
		if (m_pCalculator->m_trig_state == RADIAN)
			glVertex3d(x * sin(y), x* cos(y), result);
		else
			glVertex3d(x * sin(m_pCalculator->DegToRadian(y)), x * cos(m_pCalculator->DegToRadian(y)), result);
	}
	else
		glVertex3d(x, y, result);
}

void C3DGraph::BuildList(int eq)
{
/* PERFORMANCE NOTES
********************

  Standard function: sin(x*y), -5,5 -5,5, 100x100, elevation shading, viewed in large window

  - GL_QUADS          14 fps
  - GL_TRIANGLES      14 fps
  - GL_TRIANGLE_STRIP 18 fps

*********************/

	if(m_3DEquations[eq].eq.IsEmpty()){
		m_3DEquations[eq].on = false;
		return;
	}

	::glNewList(m_GLlist[eq],GL_COMPILE);

	int oldbase = m_pCalculator->m_base;
	m_pCalculator->m_base = 10;


	double x_high_amount, x_low_amount, y_high_amount, y_low_amount;
	double x_side(m_x_max-m_x_min), y_side(m_y_max-m_y_min);
	double x_step(x_side/m_x_interval), y_step(y_side/m_y_interval);

	glLineWidth(m_gridline_width);
	long double result;
	int x_count, y_count;
	double x,y;					// for counters (non-configurable)
	int row(0), col(0);

	CArray<innerArray, innerArray> results_x;
	results_x.SetSize(m_x_interval+1, 1);
	for (int dummy = 0; dummy < m_x_interval+1; ++dummy){
		results_x[dummy].results_y.SetSize(m_y_interval + 1, 1);
	}

	CArray<VariableT, VariableT> mmvariables; 
	VariableT var;
	if (m_Polar) var.str = "r";
	else         var.str = "x";
	var.num = m_x_min;
	mmvariables.Add(var);
	if (m_Polar) var.str = "t";
	else         var.str = "y";
	var.num = m_y_min;
	mmvariables.Add(var);
	
	m_pCalculator->SetErrorMode(TRANSLATE);
	if(m_pCalculator->Compute3D(m_3DEquations[eq].eq, &mmvariables, m_z_max, 0) != SUCCESSFULL){
		m_pCalculator->SetErrorMode(COMPLETE);
		
		if (m_bUseProgressBar){
			m_bFailedEquationGeneration = true;
			m_bCalculateEquations = false;
			::glEndList();
		}
		return;		
	}
	
	//m_z_min = m_z_max = 0;
	m_z_min = -3;  //arbitrary numbers
	m_z_max = 3;

	CString status;

	if(m_bUseProgressBar && m_iEquationsOn){
		status = "Computing Points for Equation z";
		status += char(eq+'1');
		m_ProgressBar.SetStatus(status);
	}
	
	// PreCompute All Data Points
	for (x = m_x_min, x_count = 0; x_count <= m_x_interval; ++x_count, x+=x_step){
		for (y = m_y_min, y_count = 0; y_count <= m_y_interval; ++y_count, y+=y_step, ++m_master_count){
			
			if (m_bUseProgressBar && m_iEquationsOn && !(m_master_count % m_master_percent)){
				if(m_ProgressBar.CheckCancelButton()){
					m_bFailedEquationGeneration = true;
					m_bCalculateEquations = false;
					::glEndList();
					EndWaitCursor(); 
					return;
				}
					
				m_ProgressBar.StepIt();
			}

			CArray<VariableT, VariableT> variables; 
			VariableT var;
			if (m_Polar) var.str = "r";
			else         var.str = "x";
			var.num = x;
			variables.Add(var);
			if (m_Polar) var.str = "t";
			else         var.str = "y";
			var.num = y;
			variables.Add(var);
			
			m_pCalculator->SetErrorMode(TRANSLATE);
			if(m_pCalculator->Compute3D(m_3DEquations[eq].eq, &variables, result, 0) != SUCCESSFULL){
				
				m_pCalculator->SetErrorMode(COMPLETE);
				
				if (m_bUseProgressBar){
					m_bFailedEquationGeneration = true;
					m_bCalculateEquations = false;
					::glEndList();
				}
				return;
			}
			m_pCalculator->SetErrorMode(COMPLETE);
			
			
			if ((result != HUGE_VAL) && (result != -HUGE_VAL)){
				if (result > m_z_max){
					m_z_max = result;
				}
				if (result < m_z_min){
					m_z_min = result;
				}				
				results_x[x_count].results_y[y_count] = result;
			}
			else{
				results_x[x_count].results_y[y_count] = HUGE_VAL;
			}
		}
	}

	if(m_bUseProgressBar && m_iEquationsOn){
		status = "Initializing OpenGL for Equation z";
		status += char(eq+'1');
		m_ProgressBar.SetStatus(status);
	}

	if (m_3DEquations[eq].wires != W){ // if not just wires, do the surface
		for (x = m_x_min, x_count = 0; x_count < m_x_interval; ++x_count, x+=x_step){
			glBegin(GL_TRIANGLE_STRIP);
			for (y = m_y_min, y_count = 0; y_count < m_y_interval; ++y_count, y+=y_step, ++m_master_count){
				
				if (m_bUseProgressBar && m_iEquationsOn && !(m_master_count % m_master_percent)){
					if(m_ProgressBar.CheckCancelButton()){
						m_bFailedEquationGeneration = true;
						m_bCalculateEquations = false;
						::glEndList();
						EndWaitCursor(); 
						return;
					}
					
					m_ProgressBar.StepIt();
				}
				
				x_high_amount = (((x+x_step)-m_x_min)/x_side);
				y_high_amount = (((y+y_step)-m_y_min)/y_side);
				x_low_amount  =  ((x-m_x_min)/x_side);
				y_low_amount  =  ((y-m_y_min)/y_side);
				
				////  LOWER LEFT  ////
				if (results_x[x_count].results_y[y_count] != HUGE_VAL){
					if (m_3DEquations[eq].color.type == TWO_COLOR){
						result = results_x[x_count].results_y[y_count];
						
						glColor3f(m_3DEquations[eq].color.color1.red   * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.red   * ((m_z_max-result)/(m_z_max-m_z_min)),
							m_3DEquations[eq].color.color1.green * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.green * ((m_z_max-result)/(m_z_max-m_z_min)),
							m_3DEquations[eq].color.color1.blue  * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.blue  * ((m_z_max-result)/(m_z_max-m_z_min)));
					}
					else{
						glColor3f((intensity( x_low_amount,   y_low_amount, 4) * m_3DEquations[eq].color.color1.red) + 
							(intensity( x_low_amount,   y_low_amount, 3) * m_3DEquations[eq].color.color2.red) + 
							(intensity( x_low_amount,   y_low_amount, 1) * m_3DEquations[eq].color.color3.red) + 
							(intensity( x_low_amount,   y_low_amount, 2) * m_3DEquations[eq].color.color4.red),
							
							(intensity( x_low_amount,   y_low_amount, 4) * m_3DEquations[eq].color.color1.green) + 
							(intensity( x_low_amount,   y_low_amount, 3) * m_3DEquations[eq].color.color2.green) + 
							(intensity( x_low_amount,   y_low_amount, 1) * m_3DEquations[eq].color.color3.green) + 
							(intensity( x_low_amount,   y_low_amount, 2) * m_3DEquations[eq].color.color4.green),
							
							(intensity( x_low_amount,   y_low_amount, 4) * m_3DEquations[eq].color.color1.blue) + 
							(intensity( x_low_amount,   y_low_amount, 3) * m_3DEquations[eq].color.color2.blue) + 
							(intensity( x_low_amount,   y_low_amount, 1) * m_3DEquations[eq].color.color3.blue) + 
							(intensity( x_low_amount,   y_low_amount, 2) * m_3DEquations[eq].color.color4.blue));
					}
					doVertex(x, y, results_x[x_count].results_y[y_count]);
				}
				////  END LOWER LEFT  ////
				
				////  LOWER RIGHT  ////
				if (results_x[x_count+1].results_y[y_count] != HUGE_VAL){
					if (m_3DEquations[eq].color.type == TWO_COLOR){
						result = results_x[x_count + 1].results_y[y_count];
						
						glColor3f(m_3DEquations[eq].color.color1.red   * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.red   * ((m_z_max-result)/(m_z_max-m_z_min)),
							m_3DEquations[eq].color.color1.green * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.green * ((m_z_max-result)/(m_z_max-m_z_min)),
							m_3DEquations[eq].color.color1.blue  * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.blue  * ((m_z_max-result)/(m_z_max-m_z_min)));
					}
					else{
						glColor3f((intensity( x_high_amount,   y_low_amount, 4) * m_3DEquations[eq].color.color1.red) + 
							(intensity( x_high_amount,   y_low_amount, 3) * m_3DEquations[eq].color.color2.red) + 
							(intensity( x_high_amount,   y_low_amount, 1) * m_3DEquations[eq].color.color3.red) + 
							(intensity( x_high_amount,   y_low_amount, 2) * m_3DEquations[eq].color.color4.red),
							
							(intensity( x_high_amount,   y_low_amount, 4) * m_3DEquations[eq].color.color1.green) + 
							(intensity( x_high_amount,   y_low_amount, 3) * m_3DEquations[eq].color.color2.green) + 
							(intensity( x_high_amount,   y_low_amount, 1) * m_3DEquations[eq].color.color3.green) + 
							(intensity( x_high_amount,   y_low_amount, 2) * m_3DEquations[eq].color.color4.green),
							
							(intensity( x_high_amount,   y_low_amount, 4) * m_3DEquations[eq].color.color1.blue) + 
							(intensity( x_high_amount,   y_low_amount, 3) * m_3DEquations[eq].color.color2.blue) + 
							(intensity( x_high_amount,   y_low_amount, 1) * m_3DEquations[eq].color.color3.blue) + 
							(intensity( x_high_amount,   y_low_amount, 2) * m_3DEquations[eq].color.color4.blue));
					}
					
					doVertex(x+x_step, y, results_x[x_count + 1].results_y[y_count]);
				}
				////  END LOWER RIGHT ////
			} //// END INSIDE LOOP ////
			
			
			
			x_high_amount = (((x+x_step)-m_x_min)/x_side);
			y_high_amount = (((y+y_step)-m_y_min)/y_side);
			x_low_amount  =  ((x-m_x_min)/x_side);
			y_low_amount  =  ((y-m_y_min)/y_side);
			
			
			////  UPPER LEFT  ////
			if (results_x[x_count].results_y[m_y_interval] != HUGE_VAL){
				if (m_3DEquations[eq].color.type == TWO_COLOR){
					result = results_x[x_count].results_y[m_y_interval];
					
					glColor3f(m_3DEquations[eq].color.color1.red   * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.red   * ((m_z_max-result)/(m_z_max-m_z_min)),
						m_3DEquations[eq].color.color1.green * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.green * ((m_z_max-result)/(m_z_max-m_z_min)),
						m_3DEquations[eq].color.color1.blue  * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.blue  * ((m_z_max-result)/(m_z_max-m_z_min)));
				}
				else{
					glColor3f((intensity( x_low_amount,   y_high_amount, 4) * m_3DEquations[eq].color.color1.red) + 
						(intensity( x_low_amount,   y_high_amount, 3) * m_3DEquations[eq].color.color2.red) + 
						(intensity( x_low_amount,   y_high_amount, 1) * m_3DEquations[eq].color.color3.red) + 
						(intensity( x_low_amount,   y_high_amount, 2) * m_3DEquations[eq].color.color4.red),
						
						(intensity( x_low_amount,   y_high_amount, 4) * m_3DEquations[eq].color.color1.green) + 
						(intensity( x_low_amount,   y_high_amount, 3) * m_3DEquations[eq].color.color2.green) + 
						(intensity( x_low_amount,   y_high_amount, 1) * m_3DEquations[eq].color.color3.green) + 
						(intensity( x_low_amount,   y_high_amount, 2) * m_3DEquations[eq].color.color4.green),
						
						(intensity( x_low_amount,   y_high_amount, 4) * m_3DEquations[eq].color.color1.blue) + 
						(intensity( x_low_amount,   y_high_amount, 3) * m_3DEquations[eq].color.color2.blue) + 
						(intensity( x_low_amount,   y_high_amount, 1) * m_3DEquations[eq].color.color3.blue) + 
						(intensity( x_low_amount,   y_high_amount, 2) * m_3DEquations[eq].color.color4.blue));
				}
				doVertex(x, y, results_x[x_count].results_y[m_y_interval]);
			}
			////  END UPPER LEFT ////
			
			////  UPPER RIGHT  ////
			if (results_x[x_count+1].results_y[m_y_interval] != HUGE_VAL){
				if (m_3DEquations[eq].color.type == TWO_COLOR){
					result = results_x[x_count + 1].results_y[m_y_interval];
					
					glColor3f(m_3DEquations[eq].color.color1.red   * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.red   * ((m_z_max-result)/(m_z_max-m_z_min)),
						m_3DEquations[eq].color.color1.green * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.green * ((m_z_max-result)/(m_z_max-m_z_min)),
						m_3DEquations[eq].color.color1.blue  * ((result-m_z_min)/(m_z_max-m_z_min)) + m_3DEquations[eq].color.color3.blue  * ((m_z_max-result)/(m_z_max-m_z_min)));
				}
				else{
					
					glColor3f((intensity( x_high_amount,   y_high_amount, 4) * m_3DEquations[eq].color.color1.red) + 
						(intensity( x_high_amount,   y_high_amount, 3) * m_3DEquations[eq].color.color2.red) + 
						(intensity( x_high_amount,   y_high_amount, 1) * m_3DEquations[eq].color.color3.red) + 
						(intensity( x_high_amount,   y_high_amount, 2) * m_3DEquations[eq].color.color4.red),
						
						(intensity( x_high_amount,   y_high_amount, 4) * m_3DEquations[eq].color.color1.green) + 
						(intensity( x_high_amount,   y_high_amount, 3) * m_3DEquations[eq].color.color2.green) + 
						(intensity( x_high_amount,   y_high_amount, 1) * m_3DEquations[eq].color.color3.green) + 
						(intensity( x_high_amount,   y_high_amount, 2) * m_3DEquations[eq].color.color4.green),
						
						(intensity( x_high_amount,   y_high_amount, 4) * m_3DEquations[eq].color.color1.blue) + 
						(intensity( x_high_amount,   y_high_amount, 3) * m_3DEquations[eq].color.color2.blue) + 
						(intensity( x_high_amount,   y_high_amount, 1) * m_3DEquations[eq].color.color3.blue) +
						(intensity( x_high_amount,   y_high_amount, 2) * m_3DEquations[eq].color.color4.blue));
				}
				doVertex(x+x_step, y, results_x[x_count + 1].results_y[m_y_interval]);
			}
			////  END UPPER RIGHT  ////
			
			
			glEnd();
	} //// END OUTSIDE LOOP ////
} //// END IF NOT WIREFRAME ////

	::glEndList();
	::glNewList(m_GLWirelist[eq],GL_COMPILE);

	for (x = m_x_min, x_count = 0; x_count < m_x_interval; ++x_count, x+=x_step){
		for (y = m_y_min, y_count = 0; y_count < m_y_interval; ++y_count, y+=y_step, ++m_master_count){	
			if (m_3DEquations[eq].wires != C){
				if ((results_x[x_count+1].results_y[y_count+1] != HUGE_VAL) &&
					(results_x[x_count].results_y[y_count] != HUGE_VAL) &&
					(results_x[x_count].results_y[y_count+1] != HUGE_VAL) &&
					(results_x[x_count+1].results_y[y_count] != HUGE_VAL)){
					if (m_3DEquations[eq].wires != W){
						if (!(row % m_wire_resolution)){ 
							glBegin(GL_LINES); // The top wires
							glColor3f(0,0,0);
							doVertex( x, y+y_step, results_x[x_count].results_y[y_count + 1] + m_offset);
							doVertex( x, y, results_x[x_count].results_y[y_count] + m_offset);
							glEnd();
						}
						if (!(col % m_wire_resolution)){ 
							glBegin(GL_LINES);
							glColor3f(0,0,0);
							doVertex( x+x_step, y, results_x[x_count + 1].results_y[y_count] + m_offset);
							doVertex( x, y, results_x[x_count].results_y[y_count] + m_offset);
							glEnd();
						}
					}
					else {
						if (!(row % m_wire_resolution)){ 
							glBegin(GL_LINES); // The top wires
							glColor3f(0,0,0);
							doVertex( x, y+y_step, results_x[x_count].results_y[y_count + 1]);
							doVertex( x, y, results_x[x_count].results_y[y_count]);
							glEnd();
						}
						if (!(col % m_wire_resolution)){ 
							glBegin(GL_LINES);
							glColor3f(0,0,0);
							doVertex( x+x_step, y, results_x[x_count + 1].results_y[y_count]);
							doVertex( x, y, results_x[x_count].results_y[y_count]);
							glEnd();
						}
					}
					if (m_3DEquations[eq].wires == CWW){
						if (!(row % m_wire_resolution)){
							glBegin(GL_LINES); // The bottom wires
								glColor3f(0,0,0);
								doVertex( x, y+y_step, results_x[x_count].results_y[y_count + 1] - m_offset);
								doVertex( x, y, results_x[x_count].results_y[y_count] - m_offset);
							glEnd();
						}
						if (!(col % m_wire_resolution)){ 
							glBegin(GL_LINES); // The bottom wires
								glColor3f(0,0,0);
								doVertex( x+x_step, y, results_x[x_count + 1].results_y[y_count] - m_offset);
								doVertex( x, y, results_x[x_count].results_y[y_count] - m_offset);
							glEnd();
						}
					}
				} //END OF if (wires)
				++col;
			} //END OF HUGE_VAL if
		} // END OF FOR Y LOOP
		if (m_3DEquations[eq].wires != C){
			if ((results_x[x_count].results_y[y_count] != HUGE_VAL) &&
				(results_x[x_count+1].results_y[y_count] != HUGE_VAL)){
				if ((results_x[x_count].results_y[y_count] != HUGE_VAL) &&
					(results_x[x_count + 1].results_y[y_count] != HUGE_VAL)){
					if (m_3DEquations[eq].wires != W) {
						glBegin(GL_LINES); // Last row of wires on top
							glColor3f(0,0,0);
							doVertex( x, y, results_x[x_count].results_y[y_count] + m_offset);
							doVertex( x+x_step, y, results_x[x_count + 1].results_y[y_count] + m_offset);
						glEnd();
					}
					else {
						glBegin(GL_LINES); // Last row of wires on top
							glColor3f(0,0,0);
							doVertex( x, y, results_x[x_count].results_y[y_count]);
							doVertex( x+x_step, y, results_x[x_count + 1].results_y[y_count]);
						glEnd();
					}
					if (m_3DEquations[eq].wires == CWW){		// Last row of wires on bottom
						glBegin(GL_LINES);
							glColor3f(0,0,0);
							doVertex( x, y, results_x[x_count].results_y[y_count] - m_offset);
							doVertex( x+x_step, y, results_x[x_count + 1].results_y[y_count] - m_offset);
						glEnd();
					}
				}
			}
		}
		col = 0;
		++row;
	} //END OF FOR X LOOP
	if (m_3DEquations[eq].wires != C){
		for (y = m_y_min, y_count = 0; y_count < m_y_interval; ++y_count, y+=y_step){ // Last column of wires on top
			if ((results_x[x_count].results_y[y_count] != HUGE_VAL) &&
				(results_x[x_count].results_y[y_count + 1] != HUGE_VAL)){
				if (m_3DEquations[eq].wires != W){
					glBegin(GL_LINES);
						glColor3f(0,0,0);
						doVertex( x, y+y_step, results_x[x_count].results_y[y_count + 1] + m_offset);
						doVertex( x, y, results_x[x_count].results_y[y_count] + m_offset);
					glEnd();
				}
				else {
					glBegin(GL_LINES);
						glColor3f(0,0,0);
						doVertex( x, y+y_step, results_x[x_count].results_y[y_count + 1]);
						doVertex( x, y, results_x[x_count].results_y[y_count]);
					glEnd();
				}
				if ((m_3DEquations[eq].wires != W) && (m_3DEquations[eq].wires != CW)){					// Last column of wires on bottom
					glBegin(GL_LINES);
						glColor3f(0,0,0);
						doVertex( x, y+y_step, results_x[x_count].results_y[y_count + 1] - m_offset);
						doVertex( x, y, results_x[x_count].results_y[y_count] - m_offset);
					glEnd();
				}
			}
		}	
	}
	
	::glEndList();
	m_pCalculator->m_base = oldbase;
	m_RedrawEq[eq] = false;
}

void C3DGraph::OnMouseMove(UINT nFlags, CPoint point) 
{
	SetFocus();

	if(m_bLButtonDown){
		// rotate about z axis
		if(nFlags == (MK_LBUTTON | MK_CONTROL)){
			int d_x;
			d_x = point.x - m_DownPoint.x;
			
			m_zRotate += d_x;
		}
		// rotate about z axis slowly
		else if(nFlags == (MK_LBUTTON | MK_SHIFT | MK_CONTROL)){
			int d_x;
			d_x = point.x - m_DownPoint.x;
			
			m_zRotate += d_x*0.1;
		}
		// rotate about x and y axes slowly
		else if(nFlags == (MK_LBUTTON | MK_SHIFT)){
			int d_x, d_y;
			d_x = point.x - m_DownPoint.x;
			d_y = point.y - m_DownPoint.y;
			
			m_yRotate += d_x*0.1;
			m_xRotate += d_y*0.1;
		}
		// rotate about x and y axes
		else if(nFlags == MK_LBUTTON) {
			int d_x, d_y;
			d_x = point.x - m_DownPoint.x;
			d_y = point.y - m_DownPoint.y;
			
			m_yRotate += d_x;
			m_xRotate += d_y;
		}
		m_DownPoint = point;

		InvalidateRect(NULL,FALSE);
	}
	else if((nFlags == (MK_CONTROL | MK_RBUTTON)) || (nFlags == MK_MBUTTON)){
		// translate graph
		TranslateXY(CPoint((point.x - m_DownPoint.x), (point.y - m_DownPoint.y)), false);
		
		m_DownPoint = point;
		InvalidateRect(NULL,FALSE);
	}
	else if((nFlags == (MK_CONTROL | MK_RBUTTON | MK_SHIFT)) || (nFlags == (MK_MBUTTON | MK_SHIFT))){
		// translate graph slowly
		TranslateXY(CPoint((point.x - m_DownPoint.x), (point.y - m_DownPoint.y)), true);
		
		m_DownPoint = point;
		InvalidateRect(NULL,FALSE);
	}
	
	CPropertyPage::OnMouseMove(nFlags, point);
}


void C3DGraph::TranslateXY(CPoint change, bool slow)
{
	CRect clientR;
	GetClientRect(&clientR);
	
	int og_y = abs(2*m_zTranslate * tan(0.78539816339745));
	int og_x = abs(double(clientR.Width() * og_y) / double(clientR.Height()));
	
	// translate in x
	double percent_x = double(change.x) / double(clientR.Width());

	if(slow)
		m_xTranslate += (percent_x * og_x * 0.1);
	else
		m_xTranslate += (percent_x * og_x);
	
	// translate in y
	double percent_y = double(change.y) / double(clientR.Height());
	
	if(slow)
		m_yTranslate -= (percent_y * og_y * 0.1);
	else
		m_yTranslate -= (percent_y * og_y);
}


BOOL C3DGraph::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{	
	bool slow;
	slow = (nFlags == MK_SHIFT) ? true : false;
	
	if(zDelta > 0)
		ZoomInZ(slow);
	else
		ZoomOutZ(slow);

	return CPropertyPage::OnMouseWheel(nFlags, zDelta, pt);
}

void C3DGraph::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bLButtonDown = true;
	m_DownPoint = point;
	StopAutoRotate();	
	CPropertyPage::OnLButtonDown(nFlags, point);
}

void C3DGraph::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bLButtonDown = false;
	CPropertyPage::OnLButtonUp(nFlags, point);
}

void C3DGraph::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_bRButtonDown = true;
	m_DownPoint = point;
	
	if(nFlags == 2){
		ClientToScreen(&point);

		CMenu graph;	
		graph.CreatePopupMenu();
		CMenu PopUp3DGraph;
		PopUp3DGraph.LoadMenu(IDR_3DGRAPH);
		graph.InsertMenu(3, MF_BYPOSITION|MF_POPUP|MF_ENABLED, (UINT)PopUp3DGraph.m_hMenu, "3D Graph");
		PopUp3DGraph.Detach();

		graph.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
											point.x, point.y, this);
		
		SetFocus();
	}
	
	CPropertyPage::OnRButtonDown(nFlags, point);
}

void C3DGraph::OnRButtonUp(UINT nFlags, CPoint point) 
{
	m_bRButtonDown = false;
	CPropertyPage::OnRButtonUp(nFlags, point);
}

void C3DGraph::OnMButtonDown(UINT nFlags, CPoint point) 
{
	StopAutoRotate();
	m_DownPoint = point;
	CPropertyPage::OnMButtonDown(nFlags, point);
}

void C3DGraph::InitVariables(CCalculator *Calc)
{
	m_pCalculator = Calc;
}

void C3DGraph::InitOptionsDlg()
{
	m_GraphOptions = new C3DGraphOptions("3D Graphing Options");

	m_GraphOptions->m_Equations.m_Mode = m_Polar;

	m_GraphOptions->m_Equations.m_Eq = m_astrEquationsRaw[0];
	m_GraphOptions->m_Equations.m_Eq_On = m_3DEquations[0].on;
	m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_ShadingModel = m_3DEquations[0].color.type;
	m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_RenderMode = m_3DEquations[0].wires;
	m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XminYmin.SetColour(RGB(m_3DEquations[0].color.color3.red * 255,
																				m_3DEquations[0].color.color3.green * 255,
																				m_3DEquations[0].color.color3.blue * 255));
	m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XmaxYmin.SetColour(RGB(m_3DEquations[0].color.color4.red * 255,
																				m_3DEquations[0].color.color4.green * 255,
																				m_3DEquations[0].color.color4.blue * 255));
	m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XmaxYmax.SetColour(RGB(m_3DEquations[0].color.color2.red * 255,
																				m_3DEquations[0].color.color2.green * 255,
																				m_3DEquations[0].color.color2.blue * 255));
	m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XminYmax.SetColour(RGB(m_3DEquations[0].color.color1.red * 255,
																				m_3DEquations[0].color.color1.green * 255,
																				m_3DEquations[0].color.color1.blue * 255));
	m_GraphOptions->m_Equations.m_Eq2 = m_astrEquationsRaw[1];
	m_GraphOptions->m_Equations.m_Eq2_On = m_3DEquations[1].on;
	m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_ShadingModel = m_3DEquations[1].color.type;
	m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_RenderMode = m_3DEquations[1].wires;
	m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XminYmin.SetColour(RGB(m_3DEquations[1].color.color3.red * 255,
																				m_3DEquations[1].color.color3.green * 255,
																				m_3DEquations[1].color.color3.blue * 255));
	m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XmaxYmin.SetColour(RGB(m_3DEquations[1].color.color4.red * 255,
																				m_3DEquations[1].color.color4.green * 255,
																				m_3DEquations[1].color.color4.blue * 255));
	m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XmaxYmax.SetColour(RGB(m_3DEquations[1].color.color2.red * 255,
																				m_3DEquations[1].color.color2.green * 255,
																				m_3DEquations[1].color.color2.blue * 255));
	m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XminYmax.SetColour(RGB(m_3DEquations[1].color.color1.red * 255,
																				m_3DEquations[1].color.color1.green * 255,
																				m_3DEquations[1].color.color1.blue * 255));
	
	m_GraphOptions->m_Equations.m_Eq3 = m_astrEquationsRaw[2];
	m_GraphOptions->m_Equations.m_Eq3_On = m_3DEquations[2].on;
	m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_ShadingModel = m_3DEquations[2].color.type;
	m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_RenderMode = m_3DEquations[2].wires;
	m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XminYmin.SetColour(RGB(m_3DEquations[2].color.color3.red * 255,
																				m_3DEquations[2].color.color3.green * 255,
																				m_3DEquations[2].color.color3.blue * 255));
	m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XmaxYmin.SetColour(RGB(m_3DEquations[2].color.color4.red * 255,
																				m_3DEquations[2].color.color4.green * 255,
																				m_3DEquations[2].color.color4.blue * 255));
	m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XmaxYmax.SetColour(RGB(m_3DEquations[2].color.color2.red * 255,
																				m_3DEquations[2].color.color2.green * 255,
																				m_3DEquations[2].color.color2.blue * 255));
	m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XminYmax.SetColour(RGB(m_3DEquations[2].color.color1.red * 255,
																				m_3DEquations[2].color.color1.green * 255,
																				m_3DEquations[2].color.color1.blue * 255));
	
	m_GraphOptions->m_Equations.m_Eq4 = m_astrEquationsRaw[3];
	m_GraphOptions->m_Equations.m_Eq4_On = m_3DEquations[3].on;
	m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_ShadingModel = m_3DEquations[3].color.type;
	m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_RenderMode = m_3DEquations[3].wires;
	m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XminYmin.SetColour(RGB(m_3DEquations[3].color.color3.red * 255,
																				m_3DEquations[3].color.color3.green * 255,
																				m_3DEquations[3].color.color3.blue * 255));
	m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XmaxYmin.SetColour(RGB(m_3DEquations[3].color.color4.red * 255,
																				m_3DEquations[3].color.color4.green * 255,
																				m_3DEquations[3].color.color4.blue * 255));
	m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XmaxYmax.SetColour(RGB(m_3DEquations[3].color.color2.red * 255,
																				m_3DEquations[3].color.color2.green * 255,
																				m_3DEquations[3].color.color2.blue * 255));
	m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XminYmax.SetColour(RGB(m_3DEquations[3].color.color1.red * 255,
																				m_3DEquations[3].color.color1.green * 255,
																				m_3DEquations[3].color.color1.blue * 255));
	
	m_GraphOptions->m_Equations.m_Eq5 = m_astrEquationsRaw[4];
	m_GraphOptions->m_Equations.m_Eq5_On = m_3DEquations[4].on;
	m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_ShadingModel = m_3DEquations[4].color.type;
	m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_RenderMode = m_3DEquations[4].wires;
	m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XminYmin.SetColour(RGB(m_3DEquations[4].color.color3.red * 255,
																				m_3DEquations[4].color.color3.green * 255,
																				m_3DEquations[4].color.color3.blue * 255));
	m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XmaxYmin.SetColour(RGB(m_3DEquations[4].color.color4.red * 255,
																				m_3DEquations[4].color.color4.green * 255,
																				m_3DEquations[4].color.color4.blue * 255));
	m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XmaxYmax.SetColour(RGB(m_3DEquations[4].color.color2.red * 255,
																				m_3DEquations[4].color.color2.green * 255,
																				m_3DEquations[4].color.color2.blue * 255));
	m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XminYmax.SetColour(RGB(m_3DEquations[4].color.color1.red * 255,
																				m_3DEquations[4].color.color1.green * 255,
																				m_3DEquations[4].color.color1.blue * 255));
	
	m_GraphOptions->m_Equations.m_Eq6 = m_astrEquationsRaw[5];
	m_GraphOptions->m_Equations.m_Eq6_On = m_3DEquations[5].on;
	m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_ShadingModel = m_3DEquations[5].color.type;
	m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_RenderMode = m_3DEquations[5].wires;
	m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XminYmin.SetColour(RGB(m_3DEquations[5].color.color3.red * 255,
																				m_3DEquations[5].color.color3.green * 255,
																				m_3DEquations[5].color.color3.blue * 255));
	m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XmaxYmin.SetColour(RGB(m_3DEquations[5].color.color4.red * 255,
																				m_3DEquations[5].color.color4.green * 255,
																				m_3DEquations[5].color.color4.blue * 255));
	m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XmaxYmax.SetColour(RGB(m_3DEquations[5].color.color2.red * 255,
																				m_3DEquations[5].color.color2.green * 255,
																				m_3DEquations[5].color.color2.blue * 255));
	m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XminYmax.SetColour(RGB(m_3DEquations[5].color.color1.red * 255,
																				m_3DEquations[5].color.color1.green * 255,
																				m_3DEquations[5].color.color1.blue * 255));


	m_GraphOptions->m_RangeWire.m_WireInterval = m_wire_resolution;
	m_GraphOptions->m_RangeWire.m_WireWidth =  m_gridline_width;
	m_GraphOptions->m_RangeWire.m_XIntervals =  m_x_interval;
	m_GraphOptions->m_RangeWire.m_ZOffset = m_offset;
	m_GraphOptions->m_RangeWire.m_Xmin.Format("%.15f", m_x_min);
	TrimNumber(m_GraphOptions->m_RangeWire.m_Xmin);
	m_GraphOptions->m_RangeWire.m_Xmax.Format("%.15f",  m_x_max);
	TrimNumber(m_GraphOptions->m_RangeWire.m_Xmax);
	m_GraphOptions->m_RangeWire.m_YIntervals = m_y_interval;
	m_GraphOptions->m_RangeWire.m_Ymin.Format("%.15f",  m_y_min);
	TrimNumber(m_GraphOptions->m_RangeWire.m_Ymin);
	m_GraphOptions->m_RangeWire.m_Ymax.Format("%.15f",  m_y_max);
	TrimNumber(m_GraphOptions->m_RangeWire.m_Ymax);
	m_GraphOptions->m_RangeWire.m_BGcolor.SetColour(RGB(m_bg_color.red * 255,
														m_bg_color.green * 255,
														m_bg_color.blue * 255));


	m_GraphOptions->m_Axis.m_XOrigin.Format("%.15f",  m_origin_x);
	TrimNumber(m_GraphOptions->m_Axis.m_XOrigin);
	m_GraphOptions->m_Axis.m_YOrigin.Format("%.15f",  m_origin_y);
	TrimNumber(m_GraphOptions->m_Axis.m_YOrigin);
	m_GraphOptions->m_Axis.m_ZOrigin.Format("%.15f",  m_origin_z);
	TrimNumber(m_GraphOptions->m_Axis.m_ZOrigin);
	
	m_GraphOptions->m_Axis.m_Angle.Format("%.15f",  m_theta_step);
	TrimNumber(m_GraphOptions->m_Axis.m_Angle);

	m_GraphOptions->m_Axis.m_AxisOn =  m_axes;
	m_GraphOptions->m_Axis.m_LabelsOn =  m_axes_labels;
	m_GraphOptions->m_Axis.m_AxisWidth =  m_axes_width;
	
	m_GraphOptions->m_Axis.m_Xcolor.SetColour(RGB(m_x_color.red * 255,
												  m_x_color.green * 255,
												  m_x_color.blue * 255));
	m_GraphOptions->m_Axis.m_Ycolor.SetColour(RGB(m_y_color.red * 255,
												  m_y_color.green * 255,
												  m_y_color.blue * 255));
	m_GraphOptions->m_Axis.m_Zcolor.SetColour(RGB(m_z_color.red * 255,
												  m_z_color.green * 255,
												  m_z_color.blue * 255));

	m_GraphOptions->m_Ticks.m_bTicksOn = m_tickMarks;
	m_GraphOptions->m_Ticks.m_ColorMode = m_tick_custom_color ? 0 : 1;
	m_GraphOptions->m_Ticks.m_dXint = m_x_tick_interval;
	m_GraphOptions->m_Ticks.m_dYint = m_y_tick_interval;
	m_GraphOptions->m_Ticks.m_dZint = m_z_tick_interval;
	m_GraphOptions->m_Ticks.m_iLength = m_tick_length;
	m_GraphOptions->m_Ticks.m_iWidth = m_tick_width;
	m_GraphOptions->m_Ticks.m_Xclr.SetColour(RGB(m_x_tick_color.red * 255,
												 m_x_tick_color.green * 255,
												 m_x_tick_color.blue * 255));
	m_GraphOptions->m_Ticks.m_Yclr.SetColour(RGB(m_y_tick_color.red * 255,
												 m_y_tick_color.green * 255,
												 m_y_tick_color.blue * 255));
	m_GraphOptions->m_Ticks.m_Zclr.SetColour(RGB(m_z_tick_color.red * 255,
												 m_z_tick_color.green * 255,
												 m_z_tick_color.blue * 255));

}

void C3DGraph::StoreGraphOptions()
{
	int oldbase = m_pCalculator->m_base;
	m_pCalculator->m_base = 10;
	
	if(m_astrEquationsRaw[0] != m_GraphOptions->m_Equations.m_Eq
		|| m_3DEquations[0].on != (m_GraphOptions->m_Equations.m_Eq_On == 1)
		|| m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.GetModified()
	   ){
		
		m_RedrawEq[0] = true;
		
		m_astrEquationsRaw[0] = m_GraphOptions->m_Equations.m_Eq;
		m_3DEquations[0].on = (m_GraphOptions->m_Equations.m_Eq_On == 1);
		m_3DEquations[0].color.type = (ShadingTypeE)m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_ShadingModel;
		m_3DEquations[0].wires = (WiresE)m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_RenderMode;
		m_3DEquations[0].color.color3.red =     GetRed(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[0].color.color3.green = GetGreen(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[0].color.color3.blue =   GetBlue(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[0].color.color4.red =     GetRed(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[0].color.color4.green = GetGreen(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[0].color.color4.blue =   GetBlue(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[0].color.color2.red =     GetRed(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[0].color.color2.green = GetGreen(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[0].color.color2.blue =   GetBlue(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[0].color.color1.red =     GetRed(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[0].color.color1.green = GetGreen(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[0].color.color1.blue =   GetBlue(m_GraphOptions->m_Equations.m_EqRenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
	}
	
	if(m_astrEquationsRaw[1] != m_GraphOptions->m_Equations.m_Eq2
		|| m_3DEquations[1].on != (m_GraphOptions->m_Equations.m_Eq2_On == 1)
		|| m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.GetModified()
		){
		
		m_RedrawEq[1] = true;
		
		m_astrEquationsRaw[1] = m_GraphOptions->m_Equations.m_Eq2;
		m_3DEquations[1].on = (m_GraphOptions->m_Equations.m_Eq2_On == 1);
		m_3DEquations[1].color.type = (ShadingTypeE)m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_ShadingModel;
		m_3DEquations[1].wires = (WiresE)m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_RenderMode;
		m_3DEquations[1].color.color3.red = GetRed(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[1].color.color3.green = GetGreen(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[1].color.color3.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[1].color.color4.red = GetRed(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[1].color.color4.green = GetGreen(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[1].color.color4.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[1].color.color2.red = GetRed(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[1].color.color2.green = GetGreen(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[1].color.color2.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[1].color.color1.red = GetRed(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[1].color.color1.green = GetGreen(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[1].color.color1.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq2RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
	}

	
	if(m_astrEquationsRaw[2] != m_GraphOptions->m_Equations.m_Eq3
		|| m_3DEquations[2].on != (m_GraphOptions->m_Equations.m_Eq3_On == 1)
		|| m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.GetModified()){
		
		m_RedrawEq[2] = true;
		
		m_astrEquationsRaw[2] = m_GraphOptions->m_Equations.m_Eq3;
		m_3DEquations[2].on = (m_GraphOptions->m_Equations.m_Eq3_On == 1);
		m_3DEquations[2].color.type = (ShadingTypeE)m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_ShadingModel;
		m_3DEquations[2].wires = (WiresE)m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_RenderMode;
		m_3DEquations[2].color.color3.red = GetRed(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[2].color.color3.green = GetGreen(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[2].color.color3.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[2].color.color4.red = GetRed(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[2].color.color4.green = GetGreen(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[2].color.color4.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[2].color.color2.red = GetRed(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[2].color.color2.green = GetGreen(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[2].color.color2.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[2].color.color1.red = GetRed(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[2].color.color1.green = GetGreen(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[2].color.color1.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq3RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
	}
	
	if(m_astrEquationsRaw[3] != m_GraphOptions->m_Equations.m_Eq4
		|| m_3DEquations[3].on != (m_GraphOptions->m_Equations.m_Eq4_On == 1)
		|| m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.GetModified()){
		
		m_RedrawEq[3] = true;
		
		m_astrEquationsRaw[3] = m_GraphOptions->m_Equations.m_Eq4;
		m_3DEquations[3].on = (m_GraphOptions->m_Equations.m_Eq4_On == 1);
		m_3DEquations[3].color.type = (ShadingTypeE)m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_ShadingModel;
		m_3DEquations[3].wires = (WiresE)m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_RenderMode;
		m_3DEquations[3].color.color3.red = GetRed(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[3].color.color3.green = GetGreen(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[3].color.color3.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[3].color.color4.red = GetRed(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[3].color.color4.green = GetGreen(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[3].color.color4.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[3].color.color2.red = GetRed(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[3].color.color2.green = GetGreen(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[3].color.color2.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[3].color.color1.red = GetRed(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[3].color.color1.green = GetGreen(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[3].color.color1.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq4RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
	}
	
	if(m_astrEquationsRaw[4] != m_GraphOptions->m_Equations.m_Eq5
		|| m_3DEquations[4].on != (m_GraphOptions->m_Equations.m_Eq5_On == 1)
		|| m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.GetModified()){
		
		m_RedrawEq[4] = true;
		
		m_astrEquationsRaw[4] = m_GraphOptions->m_Equations.m_Eq5;
		m_3DEquations[4].on = (m_GraphOptions->m_Equations.m_Eq5_On == 1);
		m_3DEquations[4].color.type = (ShadingTypeE)m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_ShadingModel;
		m_3DEquations[4].wires = (WiresE)m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_RenderMode;
		m_3DEquations[4].color.color3.red = GetRed(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[4].color.color3.green = GetGreen(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[4].color.color3.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[4].color.color4.red = GetRed(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[4].color.color4.green = GetGreen(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[4].color.color4.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[4].color.color2.red = GetRed(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[4].color.color2.green = GetGreen(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[4].color.color2.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[4].color.color1.red = GetRed(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[4].color.color1.green = GetGreen(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[4].color.color1.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq5RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
	}
	
	if(m_astrEquationsRaw[5] != m_GraphOptions->m_Equations.m_Eq6
		|| m_3DEquations[5].on != (m_GraphOptions->m_Equations.m_Eq6_On == 1)
		|| m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.GetModified()){
				
		m_RedrawEq[5] = true;

		m_astrEquationsRaw[5] = m_GraphOptions->m_Equations.m_Eq6;
		m_3DEquations[5].on = (m_GraphOptions->m_Equations.m_Eq6_On == 1);
		m_3DEquations[5].color.type = (ShadingTypeE)m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_ShadingModel;
		m_3DEquations[5].wires = (WiresE)m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_RenderMode;
		m_3DEquations[5].color.color3.red = GetRed(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[5].color.color3.green = GetGreen(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[5].color.color3.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XminYmin.GetColour());
		m_3DEquations[5].color.color4.red = GetRed(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[5].color.color4.green = GetGreen(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[5].color.color4.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XmaxYmin.GetColour());
		m_3DEquations[5].color.color2.red = GetRed(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[5].color.color2.green = GetGreen(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[5].color.color2.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XmaxYmax.GetColour());
		m_3DEquations[5].color.color1.red = GetRed(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[5].color.color1.green = GetGreen(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
		m_3DEquations[5].color.color1.blue = GetBlue(m_GraphOptions->m_Equations.m_Eq6RenderButton.m_3DRenderDlg.m_XminYmax.GetColour());
	}

	bool polar = (1 == m_GraphOptions->m_Equations.m_Mode);

	long double x_min, x_max, y_min, y_max;
	m_pCalculator->Compute(m_GraphOptions->m_RangeWire.m_Xmin, x_min, this->m_hWnd);
	m_pCalculator->Compute(m_GraphOptions->m_RangeWire.m_Xmax, x_max, this->m_hWnd);
	m_pCalculator->Compute(m_GraphOptions->m_RangeWire.m_Ymin, y_min, this->m_hWnd);
	m_pCalculator->Compute(m_GraphOptions->m_RangeWire.m_Ymax, y_max, this->m_hWnd);

	if(m_wire_resolution != m_GraphOptions->m_RangeWire.m_WireInterval
		|| m_gridline_width != m_GraphOptions->m_RangeWire.m_WireWidth
		|| m_x_interval != m_GraphOptions->m_RangeWire.m_XIntervals
		|| m_y_interval != m_GraphOptions->m_RangeWire.m_YIntervals
		|| m_offset != m_GraphOptions->m_RangeWire.m_ZOffset
		|| x_min != m_x_min
		|| x_max != m_x_max
		|| y_min != m_y_min
		|| y_max != m_y_max
		|| polar != m_Polar){
		
		m_wire_resolution = m_GraphOptions->m_RangeWire.m_WireInterval;
		m_gridline_width = m_GraphOptions->m_RangeWire.m_WireWidth;
		m_x_interval = m_GraphOptions->m_RangeWire.m_XIntervals;
		m_y_interval = m_GraphOptions->m_RangeWire.m_YIntervals;
		m_offset = m_GraphOptions->m_RangeWire.m_ZOffset;
		
		m_x_min = x_min;
		m_x_max = x_max;
		m_y_min = y_min;
		m_y_max = y_max;

		m_Polar = polar;

		for(int i(0); i < 6; ++i) m_RedrawEq[i] = true;
	}	

	m_bg_color.red = GetRed(m_GraphOptions->m_RangeWire.m_BGcolor.GetColour());
	m_bg_color.green = GetGreen(m_GraphOptions->m_RangeWire.m_BGcolor.GetColour());
	m_bg_color.blue = GetBlue(m_GraphOptions->m_RangeWire.m_BGcolor.GetColour());

	m_axes = (m_GraphOptions->m_Axis.m_AxisOn == 1);
	m_axes_labels = (m_GraphOptions->m_Axis.m_LabelsOn == 1);
	m_axes_width = m_GraphOptions->m_Axis.m_AxisWidth;

	m_pCalculator->Compute(m_GraphOptions->m_Axis.m_XOrigin,  m_origin_x, this->m_hWnd);
	m_pCalculator->Compute(m_GraphOptions->m_Axis.m_YOrigin,  m_origin_y, this->m_hWnd);
	m_pCalculator->Compute(m_GraphOptions->m_Axis.m_ZOrigin,  m_origin_z, this->m_hWnd);
	m_pCalculator->Compute(m_GraphOptions->m_Axis.m_Angle,  m_theta_step, this->m_hWnd);
	
	m_x_color.red = GetRed(m_GraphOptions->m_Axis.m_Xcolor.GetColour());
	m_x_color.green = GetGreen(m_GraphOptions->m_Axis.m_Xcolor.GetColour());
	m_x_color.blue = GetBlue(m_GraphOptions->m_Axis.m_Xcolor.GetColour());
	m_y_color.red = GetRed(m_GraphOptions->m_Axis.m_Ycolor.GetColour());
	m_y_color.green = GetGreen(m_GraphOptions->m_Axis.m_Ycolor.GetColour());
	m_y_color.blue = GetBlue(m_GraphOptions->m_Axis.m_Ycolor.GetColour());
	m_z_color.red = GetRed(m_GraphOptions->m_Axis.m_Zcolor.GetColour());
	m_z_color.green = GetGreen(m_GraphOptions->m_Axis.m_Zcolor.GetColour());
	m_z_color.blue = GetBlue(m_GraphOptions->m_Axis.m_Zcolor.GetColour());


	m_tickMarks = (m_GraphOptions->m_Ticks.m_bTicksOn == 1);
	m_tick_custom_color = (m_GraphOptions->m_Ticks.m_ColorMode == 0);
	m_x_tick_interval = m_GraphOptions->m_Ticks.m_dXint;
	m_y_tick_interval = m_GraphOptions->m_Ticks.m_dYint;
	m_z_tick_interval = m_GraphOptions->m_Ticks.m_dZint;
	m_tick_length = m_GraphOptions->m_Ticks.m_iLength;
	m_tick_width = m_GraphOptions->m_Ticks.m_iWidth;

	m_x_tick_color.red = GetRed(m_GraphOptions->m_Ticks.m_Xclr.GetColour());
	m_x_tick_color.green = GetGreen(m_GraphOptions->m_Ticks.m_Xclr.GetColour());
	m_x_tick_color.blue = GetBlue(m_GraphOptions->m_Ticks.m_Xclr.GetColour());
	m_y_tick_color.red = GetRed(m_GraphOptions->m_Ticks.m_Yclr.GetColour());
	m_y_tick_color.green = GetGreen(m_GraphOptions->m_Ticks.m_Yclr.GetColour());
	m_y_tick_color.blue = GetBlue(m_GraphOptions->m_Ticks.m_Yclr.GetColour());
	m_z_tick_color.red = GetRed(m_GraphOptions->m_Ticks.m_Zclr.GetColour());
	m_z_tick_color.green = GetGreen(m_GraphOptions->m_Ticks.m_Zclr.GetColour());
	m_z_tick_color.blue = GetBlue(m_GraphOptions->m_Ticks.m_Zclr.GetColour());

	ExpandEquations();

	m_pCalculator->m_base = oldbase;
}


double C3DGraph::GetRed(COLORREF color)
{
	CColor clr(color);
	return double(clr.GetRed()) / 255.0;
}

double C3DGraph::GetGreen(COLORREF color)
{
	CColor clr(color);
	return double(clr.GetGreen()) / 255.0;
}

double C3DGraph::GetBlue(COLORREF color)
{
	CColor clr(color);
	return double(clr.GetBlue()) / 255.0;
}

void C3DGraph::ApplyOptions()
{
	StoreGraphOptions();
	m_bCalculateEquations = true;
	Invalidate();
}


//extern void CopyBitmapToClipboard( const CWnd *pWnd, CBitmap& bitmap, CPalette* pPal );
extern void CopyWndToClipboard( CWnd *pWnd );

void C3DGraph::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	/*CMenu graph;
	graph.LoadMenu(IDR_3DGRAPH);	
	graph.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
		point.x, point.y, this);
	
	SetFocus();*/
}

void C3DGraph::OnCopyGraph() { 
	BeginWaitCursor(); 
	CopyWndToClipboard(this);
	EndWaitCursor(); 
}

void C3DGraph::InitProgressBar(bool alleqs){
	int n(0);
	m_iEquationsOn = 0;
	m_master_count = 1;

	for (n = 0; n < MAX_3D_EQS; ++n){
		if(!alleqs){
			if (m_RedrawEq[n] && m_3DEquations[n].on){
				++m_iEquationsOn;
			}
		}
		else if(m_3DEquations[n].on)
			++m_iEquationsOn;
	}

	if (m_bUseProgressBar && m_iEquationsOn){
		if (m_ProgressBar.Create()){
			m_master_percent = ceil ((2* m_iEquationsOn * (m_x_interval + 1) * (m_y_interval + 1))/100.0);
		}
		else { //something bad happened
			m_iEquationsOn = 0;
		}
	}
}
	

void C3DGraph::CleanUpProgressBar(){
	if(m_bUseProgressBar && m_iEquationsOn)
		m_ProgressBar.DestroyWindow();

	m_progress = 0.0;
	m_iEquationsOn = 0;
}

void C3DGraph::BuildEquations()
{
	if(!m_bCalculateEquations)
		return;

	InitProgressBar(false);

	m_bFailedEquationGeneration = false;
	for (int m = 0; m < MAX_3D_EQS; ++m){
		if (m_RedrawEq[m] && m_3DEquations[m].on && !m_bFailedEquationGeneration){
			BuildList(m);
//			BuildWireList(m);
		}
	}
	CleanUpProgressBar();
}

void C3DGraph::ReBuildEquations()
{
	if(!m_bCalculateEquations)
		return;

	InitProgressBar(true);
	m_bFailedEquationGeneration = false;
	for (int m = 0; m < MAX_3D_EQS; ++m){
		if (m_3DEquations[m].on && !m_bFailedEquationGeneration){
			BuildList(m);
//			BuildWireList(m);
		}
	}

	CleanUpProgressBar();
}

void C3DGraph::OnZoomInZ() {
	ZoomInZ(false);
}
void C3DGraph::OnZoomOutZ() {
	ZoomOutZ(false);
}

void C3DGraph::ZoomInZ(bool bSlow)
{
	double length = (((m_x_max - m_x_min) + (m_y_max - m_y_min))/2.0);
	double percent;
	
	percent = bSlow ? 0.01 : 0.04;
	
	m_zTranslate = m_zTranslate + percent*length + abs(m_zTranslate*(percent+0.05));
	InvalidateRect(NULL, FALSE);
}

void C3DGraph::ZoomOutZ(bool bSlow)
{
	double length = (((m_x_max - m_x_min) + (m_y_max - m_y_min))/2.0);
	double percent;
	
	percent = bSlow ? 0.01 : 0.04;
	
	m_zTranslate = m_zTranslate - (percent*length + abs(m_zTranslate*(percent+0.05)));
	InvalidateRect(NULL, FALSE);
}

void C3DGraph::OnOptions(UINT nID) 
{
	switch(nID){
	case ID_3DGRAPH_EQUATIONS:	Options(0); break;
	case ID_3DGRAPH_RANGEWIRE:	Options(1); break;
	case ID_3DGRAPH_AXES:		Options(2); break;
	case ID_3DGRAPH_TICKMARKS:	Options(3); break;
	case ID_3DGRAPH_OPTIONS:	Options(0); break;
	}
}


void C3DGraph::OnCenterView() 
{
	m_xScale = 1.0f;
	m_yScale = 1.0f;
	m_zScale = 1.0f;

	m_xRotate = -30;
	m_yRotate = 0;
	m_zRotate = 0;

	m_xTranslate = 0.0f;
	m_yTranslate = 0.0f;
	m_zTranslate = -20.0f;

	InvalidateRect(NULL,FALSE);	
}

void C3DGraph::CopyGraph(){		OnCopyGraph(); }

void C3DGraph::Options(UINT tab){ 
	
	InitOptionsDlg();

	m_GraphOptions->m_StartTab = tab;

	m_GraphOptions->m_Axis.m_Calculator = m_pCalculator;
	m_GraphOptions->m_Equations.m_Calculator = m_pCalculator;
	m_GraphOptions->m_RangeWire.m_Calculator = m_pCalculator;

	if(m_GraphOptions->DoModal() == IDOK){
		StoreGraphOptions();
		m_bCalculateEquations = true;
		Invalidate();
	}
	delete m_GraphOptions;	
}

void C3DGraph::OnReCompute() 
{
	m_bCalculateEquations = true;

	for(int i(0); i < MAX_3D_EQS; ++i)
		m_RedrawEq[i] = true;

	if(this->m_hWnd != NULL)
		Invalidate();
}

void C3DGraph::OnPrint() 
{
	BeginWaitCursor();
	PrintGraph();
	EndWaitCursor();
}

void C3DGraph::OnSaveAsBitmap() 
{
	CFileDialog FileDialog( FALSE, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Windows Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL );

	if(FileDialog.DoModal() == IDOK){
		BeginWaitCursor();
		SaveBitmap(FileDialog.GetPathName());
		EndWaitCursor();
	}
}

int C3DGraph::InitOpenGl(GraphDestination dest, HDC hDC)
{	
	switch(dest){
	case GRAPH_DESTINATION_WINDOW:
		if(SetWindowPixelFormat(hDC)==FALSE){
			MessageBox("Error creating WindowPixelFormat: Please contact GraphCalc for support", "Pixel Format Error", MB_OK | MB_ICONERROR);
			return 0;
		}
		break;
	case GRAPH_DESTINATION_BITMAP:
		if(SetBitmapPixelFormat(hDC)==FALSE){
			MessageBox("Error creating BitmapPixelFormat: Please contact GraphCalc for support", "Pixel Format Error", MB_OK | MB_ICONERROR);
			return 0;
		}
		break;
	case GRAPH_DESTINATION_PRINTER:
		if(SetPrinterPixelFormat(hDC)==FALSE){
			MessageBox("Error creating PrinterPixelFormat: Please contact GraphCalc for support", "Pixel Format Error", MB_OK | MB_ICONERROR);
			return 0;
		}
		break;
	default: return -1;
	}

	if(CreateViewGLContext(hDC)==FALSE)
		return 0;
	
	for (int n = 0; n < MAX_3D_EQS; ++n){
		m_GLlist[n] = glGenLists(1);
	}

	for (n = 0; n < MAX_3D_EQS; ++n){
		m_GLWirelist[n] = glGenLists(1);
	}

	ReBuildEquations();
	return 0;
}

void C3DGraph::InitGLView(int w, int h)
{
	GLdouble aspect;

	if(h==0)
		aspect = (GLdouble)w;
	else
		aspect = (GLdouble)w/(GLdouble)h;
	
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,aspect,0.001,1000000000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);

	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_DST_COLOR,GL_ZERO);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	
}

void C3DGraph::DrawGraphToBitmap(CBitmap &bitmap, CSize size, GraphDestination dest)
{
	CDC *pDC = GetDC();
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SetMapMode(MM_ANISOTROPIC);

	if(bitmap.m_hObject != NULL)
		bitmap.DeleteObject();

	bitmap.CreateCompatibleBitmap(pDC, size.cx, size.cy);
	CBitmap *pOldBitmap = MemDC.SelectObject(&bitmap);

	// clean up previous gl context
	CleanUpOpenGL();

	m_bUseProgressBar = false;

	// create new gl context
	InitOpenGl(dest, MemDC.m_hDC);
	InitGLView(size.cx, size.cy);

	//ReBuildEquations();//TAKE LINE OUT AFTER PRINTING IS WORKING
	RenderGraph();

	MemDC.SelectObject(&pOldBitmap);
	DeleteDC(MemDC);
	ReleaseDC(pDC);

	CleanUpOpenGL();

	// reset GL drawing context
	HWND hWnd = GetSafeHwnd();
	InitOpenGl(GRAPH_DESTINATION_WINDOW, ::GetDC(hWnd));

	CRect rcDIB;
	GetClientRect(rcDIB);
	InitGLView(rcDIB.Width(), rcDIB.Height());

	m_bUseProgressBar = true;
}

void C3DGraph::SaveBitmap(CString file)
{
	CClientCapture CapturedImage;
	CRect rcDIB;
	GetClientRect(rcDIB);
	CBitmap bitmap;
	DrawGraphToBitmap(bitmap, CSize(rcDIB.Width(), rcDIB.Height()), GRAPH_DESTINATION_BITMAP);
	//DrawGraphToBitmap(bitmap, CSize(3000, 3000), GRAPH_DESTINATION_BITMAP);
	CapturedImage.WriteBitmapToDIB(GetDC(), bitmap);	
	CapturedImage.WriteDIB(file);
	CapturedImage.Release();

	Invalidate();
}


void C3DGraph::PrintGraph() 
{
	CRect rcDIB;
	GetClientRect(rcDIB);
	int graph_width = rcDIB.Width();
	int graph_height = rcDIB.Height();

	// create equation list
	CArray<SGraphPrintLegend, SGraphPrintLegend> Equations;

	for(int i(0); i < MAX_3D_EQS; ++i){
		if(m_3DEquations[i].on){
			SGraphPrintLegend eqi;
			eqi.type = 3;
			eqi.threed = m_3DEquations[i];
			Equations.Add(eqi);
		}
	}

	// end create equation list
	
	CPrintGraph pg(graph_width, graph_height, m_pCalculator, &Equations);

	if(!pg.DisplayOptions()){
		EndWaitCursor(); 
		return;
	}

	pg.InitializePrinting();
	pg.BeginPrinting();

	// set background color to white
	ColorT bg_bak = m_bg_color;
	m_bg_color.red = 1;
	m_bg_color.green = 1;
	m_bg_color.blue = 1;

	double scale_factor(3.0);

	// draw graph to bitmap
	CBitmap bitmap;	
	DrawGraphToBitmap(bitmap, CSize(pg.GetGraphWidth()/scale_factor, pg.GetGraphHeight()/scale_factor), GRAPH_DESTINATION_PRINTER);
	
	
	CRect rcSrc(0,0,pg.GetGraphWidth()/scale_factor, pg.GetGraphHeight()/scale_factor);
	CRect rcDest(0,0,pg.GetGraphWidth(), pg.GetGraphHeight());

	CClientCapture CapturedImage;	
	
	//if(scale_factor > 1){
		CapturedImage.WriteBitmapToDIB(GetDC(), bitmap);
		CapturedImage.OnDraw(pg.m_DC.m_hDC, &rcDest, &rcSrc);
	//}
	//else if(scale_factor == 1)
		//CapturedImage.DrawBitmap(GetDC(), pg.m_DC.m_hDC, &rcSrc, &rcDest, bitmap);
	
	CapturedImage.Release();

	m_bg_color = bg_bak; // restore background color
	//////////////////////////////////////////////

	pg.EndPrinting();
}



void C3DGraph::DrawTitle(CDC *pDC, const CSize &graph_size, const CString title)
{
	CFont titleFont;
	pDC->SetViewportOrg(0, 0);

	// replot
	titleFont.CreateFont(pDC->GetDeviceCaps(LOGPIXELSY)*0.35, 
						 pDC->GetDeviceCaps(LOGPIXELSX)*0.18,
						 0,0,
						 FW_BOLD,
						 FALSE,FALSE,
						 0,
						 ANSI_CHARSET, OUT_DEFAULT_PRECIS,
						 DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, 
						 DEFAULT_PITCH | FF_SWISS, 
						 "Arial");
	
	CFont *pOldFont = pDC->SelectObject(&titleFont);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SetTextAlign(TA_LEFT);
	pDC->TextOut(0, 0, title);
	pDC->SelectObject(pOldFont);
}

BOOL C3DGraph::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::PreTranslateMessage(pMsg);
}

void C3DGraph::OnExportDXF() {	
	
	CFileDialog FileDialog( FALSE, _T("dxf"), _T("*.dxf"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("AutoCAD DXF File (*.dxf)|*.dxf|All Files (*.*)|*.*||"), NULL );

	if(FileDialog.DoModal() == IDOK)
		ExportDXF(FileDialog.GetPathName());
}


void C3DGraph::Message(UINT nID)
{
	switch(nID){
	case ID_3DGRAPH_COPYGRAPH:		OnCopyGraph(); break;
	case ID_3DGRAPH_SAVEASBITMAP:	OnSaveAsBitmap(); break;
	case ID_3DGRAPH_ZOOM_IN_Z:		OnZoomInZ(); break; 
	case ID_3DGRAPH_ZOOM_OUT_Z:		OnZoomOutZ(); break;
	case ID_3DGRAPH_CENTERVIEW:		OnCenterView(); break;
	case ID_3DGRAPH_RECOMPUTE:		OnReCompute(); break;
	case ID_3DGRAPH_PRINT:			OnPrint(); break;
	case ID_3DGRAPH_EQUATIONS:			
	case ID_3DGRAPH_RANGEWIRE:		
	case ID_3DGRAPH_AXES:			
	case ID_3DGRAPH_TICKMARKS:	
	case ID_3DGRAPH_OPTIONS:		OnOptions(nID); break;
	case ID_3DGRAPH_EXPORTTODFX:	OnExportDXF(); break;
	case ID_3DGRAPH_EVALUATE:		OnEvaluate();
	case ID_3DGRAPH_AUTOROTATE_ALLAXIS:
	case ID_3DGRAPH_AUTOROTATE_XAXIS:
	case ID_3DGRAPH_AUTOROTATE_YAXIS:
	case ID_3DGRAPH_AUTOROTATE_ZAXIS:
	case ID_3DGRAPH_AUTOROTATE_INCREASESPEED:
	case ID_3DGRAPH_AUTOROTATE_DECREASESPEED:
		OnAutoRotate(nID);
		break;
	}
}

void C3DGraph::ExportDXF(CString filename)
{
	m_NoRePaint = true;

	::ofstream outfile;
	outfile.open(filename);
	// outfile.write(&char or CString.GetBuffer, length of string or char)
	CString buffer;
	outfile << "0\n";
	outfile << "SECTION\n";
	outfile << "2\n";
	outfile << "ENTITIES\n";

	int oldbase = m_pCalculator->m_base;
	m_pCalculator->m_base = 10;

	int col(0);					// column counter (non-configurable)
	int row(0);					// row counter (non-configurable)
	double x,y;					// for counters (non-configurable)

	double x_side(m_x_max-m_x_min), y_side(m_y_max-m_y_min);
	double x_step(x_side/m_x_interval), y_step(y_side/m_y_interval);

	long double result;
	int x_count, y_count;

	if (m_bUseProgressBar){
		InitProgressBar(true);
	}
	CString status;

	for (int n = 0; n < 6; ++n){ // loop for each equation
		if (m_3DEquations[n].on){
			if(m_bUseProgressBar){
				status = "Computing Points for Equation z";
				status += char(n+'1');
				m_ProgressBar.SetStatus(status);
			}

			CArray<innerArray, innerArray> results_x;
			results_x.SetSize(m_x_interval+1, 1);
			for (int dummy = 0; dummy < m_x_interval+1; ++dummy){
				results_x[dummy].results_y.SetSize(m_y_interval + 1, 1);
			}
			
			CArray<VariableT, VariableT> mmvariables; 
			VariableT var;
			if (m_Polar) var.str = "r";
			else         var.str = "x";
			var.num = m_x_min;
			mmvariables.Add(var);
			if (m_Polar) var.str = "t";
			else         var.str = "y";
			var.num = m_y_min;
			mmvariables.Add(var);
			
			m_pCalculator->SetErrorMode(TRANSLATE);
			if(m_pCalculator->Compute3D(m_3DEquations[n].eq, &mmvariables, m_z_max, 0) != SUCCESSFULL)	m_pCalculator->SetErrorMode(COMPLETE);
			m_pCalculator->SetErrorMode(COMPLETE);
			
			for (x = m_x_min, x_count = 0; x_count <= m_x_interval; ++x_count, x+=x_step){
				for (y = m_y_min, y_count = 0; y_count <= m_y_interval; ++y_count, y+=y_step, ++m_master_count){
					
					if (m_bUseProgressBar && m_iEquationsOn && !(m_master_count % m_master_percent)){
						if(m_ProgressBar.CheckCancelButton()){
							outfile.close();
							CleanUpProgressBar();
							EndWaitCursor();
							m_NoRePaint = false;
							return;
						}
						m_ProgressBar.StepIt();
					}
					
					CArray<VariableT, VariableT> variables; 
					VariableT var;
					if (m_Polar) var.str = "r";
					else         var.str = "x";
					var.num = x;
					variables.Add(var);
					if (m_Polar) var.str = "t";
					else         var.str = "y";
					var.num = y;
					variables.Add(var);
					
					m_pCalculator->SetErrorMode(TRANSLATE);
					if(m_pCalculator->Compute3D(m_3DEquations[n].eq, &variables, result, 0) != SUCCESSFULL){
						m_pCalculator->SetErrorMode(COMPLETE);
						break;
					}
					m_pCalculator->SetErrorMode(COMPLETE);
					
					if ((result != HUGE_VAL) && (result != -HUGE_VAL)){
						results_x[x_count].results_y[y_count] = result;
					}
					else{
						results_x[x_count].results_y[y_count] = HUGE_VAL;
					}
				}
			}
			
			if(m_bUseProgressBar){
				status = "Exporting Equation z";
				status += char(n+'1');
				m_ProgressBar.SetStatus(status);
			}
			for (x = m_x_min, x_count = 0; x_count < m_x_interval; ++x_count, x+=x_step){
				for (y = m_y_min, y_count = 0; y_count < m_y_interval; ++y_count, y+=y_step, ++m_master_count){
					
					if (m_bUseProgressBar && m_iEquationsOn && !(m_master_count % m_master_percent)){
						if(m_ProgressBar.CheckCancelButton()){
							outfile.close();
							CleanUpProgressBar();
							EndWaitCursor(); 
							m_NoRePaint = false;
							return;
						}
						m_ProgressBar.StepIt();
					}
					
					if ((results_x[x_count].results_y[y_count] != HUGE_VAL) &&
						(results_x[x_count + 1].results_y[y_count] != HUGE_VAL) &&
						(results_x[x_count + 1].results_y[y_count + 1] != HUGE_VAL) &&
						(results_x[x_count].results_y[y_count + 1] != HUGE_VAL)){
						
						outfile << "0\n";
						outfile << "3DFACE\n";
						outfile << "8\n";
						outfile << "GC z" << char(n + '1') << "\n";
						outfile << "62\n";
						outfile << "7\n";
						
						outfile << "10\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << x * sin(y) << "\n";
							else
								outfile << x * sin(m_pCalculator->DegToRadian(y)) << "\n";
						}
						else         outfile << x << "\n";
						outfile << "20\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << x * cos(y) << "\n";
							else
								outfile << x * cos(m_pCalculator->DegToRadian(y)) << "\n";
						}
						else         outfile << y << "\n";
						outfile << "30\n";
						outfile << results_x[x_count].results_y[y_count] << "\n";
						
						
						outfile << "11\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << (x + x_step) * sin(y) << "\n";
							else
								outfile << (x + x_step) * sin(m_pCalculator->DegToRadian(y)) << "\n";
						}
						else         outfile << x + x_step << "\n";
						outfile << "21\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << (x + x_step) * cos(y) << "\n";
							else
								outfile << (x + x_step) * cos(m_pCalculator->DegToRadian(y)) << "\n";
						}
						else         outfile << y << "\n";
						outfile << "31\n";
						outfile << results_x[x_count + 1].results_y[y_count] << "\n";
						
						
						outfile << "12\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << (x + x_step) * sin(y + y_step) << "\n";
							else
								outfile << (x + x_step) * sin(m_pCalculator->DegToRadian(y + y_step)) << "\n";
						}
						else         outfile << x + x_step << "\n";
						outfile << "22\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << (x + x_step) * cos(y+ y_step) << "\n";
							else
								outfile << (x + x_step) * cos(m_pCalculator->DegToRadian(y + y_step)) << "\n";
						}
						else         outfile << y + y_step << "\n";
						outfile << "32\n";
						outfile << results_x[x_count + 1].results_y[y_count + 1] << "\n";
						
						
						outfile << "13\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << x * sin(y) << "\n";
							else
								outfile << x * sin(m_pCalculator->DegToRadian(y)) << "\n";
						}
						else         outfile << x << "\n";
						outfile << "23\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << x * cos(y) << "\n";
							else
								outfile << x * cos(m_pCalculator->DegToRadian(y)) << "\n";
						}
						else         outfile << y << "\n";
						outfile << "33\n";
						outfile << results_x[x_count].results_y[y_count] << "\n";
						
						
						
						outfile << "0\n";
						outfile << "3DFACE\n";
						outfile << "8\n";
						outfile << "GC z" << char(n + '1') << "\n";
						outfile << "62\n";
						outfile << "7\n";
						
						outfile << "10\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << x * sin(y) << "\n";
							else
								outfile << x * sin(m_pCalculator->DegToRadian(y)) << "\n";
						}
						else         outfile << x << "\n";
						outfile << "20\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << x * cos(y) << "\n";
							else
								outfile << x * cos(m_pCalculator->DegToRadian(y)) << "\n";
						}
						else         outfile << y << "\n";
						outfile << "30\n";
						outfile << results_x[x_count].results_y[y_count] << "\n";
						
						
						outfile << "11\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << (x + x_step) * sin(y + y_step) << "\n";
							else
								outfile << (x + x_step) * sin(m_pCalculator->DegToRadian(y + y_step)) << "\n";
						}
						else         outfile << x + x_step << "\n";
						outfile << "21\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << (x + x_step) * cos(y+ y_step) << "\n";
							else
								outfile << (x + x_step) * cos(m_pCalculator->DegToRadian(y + y_step)) << "\n";
						}
						else         outfile << y + y_step << "\n";
						outfile << "31\n"; 
						outfile << results_x[x_count + 1].results_y[y_count + 1] << "\n";
						
						
						outfile << "12\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << x * sin(y + y_step) << "\n";
							else
								outfile << x * sin(m_pCalculator->DegToRadian(y + y_step)) << "\n";
						}
						else         outfile << x << "\n";
						outfile << "22\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << x * cos(y + y_step) << "\n";
							else
								outfile << x * cos(m_pCalculator->DegToRadian(y + y_step)) << "\n";
						}
						else         outfile << y + y_step << "\n";
						outfile << "32\n";
						outfile << results_x[x_count].results_y[y_count + 1] << "\n";
						
						
						outfile << "13\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << x * sin(y) << "\n";
							else
								outfile << x * sin(m_pCalculator->DegToRadian(y)) << "\n";
						}
						else         outfile << x << "\n";
						outfile << "23\n";
						if (m_Polar){
							if (m_pCalculator->m_trig_state == RADIAN)
								outfile << x * cos(y) << "\n";
							else
								outfile << x * cos(m_pCalculator->DegToRadian(y)) << "\n";
						}
						else         outfile << y << "\n";
						outfile << "33\n";
						outfile << results_x[x_count].results_y[y_count] << "\n";
				}
			}
			} //END OF HUGE_VAL if
			
		}
	} // end loop for each equation

	
	outfile << "0\n";
	outfile << "ENDSEC\n";
	outfile << "0\n";
	outfile << "EOF\n";
	
	if (m_bUseProgressBar){
		m_ProgressBar.DestroyWindow();
	}
	outfile.close();
	m_NoRePaint = false;
}

void C3DGraph::SetUnregisteredEquations()
{
	// SET DEFAULT EQUATIONS
		m_astrEquationsRaw[0] = m_3DEquations[0].eq = "(cos(sqrt(((x+0)^2)+((y+0)^2))) + cos(sqrt(((x+.913*2pi)^2)+((y+0)^2))) + cos(sqrt(((x-.913*2pi)^2)+((y+0)^2))))";
		m_3DEquations[0].on = true;

		m_astrEquationsRaw[1] = m_3DEquations[1].eq = "4*cos (3*sqrt(x^2 + y^2))*e^(-0.3*(sqrt(x^2 + y^2)))";
		m_3DEquations[1].color.type = TWO_COLOR;

		m_astrEquationsRaw[2] = m_3DEquations[2].eq = "sin (x*y/4)+frand(0:1)";
		m_3DEquations[2].color.type = TWO_COLOR;
		m_3DEquations[2].wires = C;

		m_astrEquationsRaw[3] = m_3DEquations[3].eq = "cos(3*r)*cos(5*t)*e^(-.3r)*3";
		m_3DEquations[3].color.type = TWO_COLOR;

		m_astrEquationsRaw[4] = m_3DEquations[4].eq = "(r+t)*.5";

		m_astrEquationsRaw[5] = m_3DEquations[5].eq = "sin(r*t)";
		m_3DEquations[5].color.type = TWO_COLOR;
		m_3DEquations[5].wires = C;
		// END SET DEFAULT EQUATIONS
}

BOOL C3DGraph::OnSetActive() 
{
	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->SetMenu(&m_Menu3DGraph);
	m_fSaveSettings = true;
	
	if(!g_Registered)
		SetUnregisteredEquations();
	
	return CPropertyPage::OnSetActive();
}



// Snap OpenGL client and send it to ClipBoard 
// so that you can insert it in your favorite 
// image editor, Powerpoint, etc... 
// Replace CRenderView by your own CView-derived class 
/*void C3DGraph::SnapClient() 
{ 
	BeginWaitCursor(); 
	
	// Get client geometry 
	CRect rect; 
	GetClientRect(&rect); 
	CSize size(rect.Width(),rect.Height()); 
	TRACE("  client zone : (%d;%d)\n",size.cx,size.cy); 
	// Lines have to be 32 bytes aligned, suppose 24 bits per pixel 
	// I just cropped it 
	
	
	
	// Create a bitmap and select it in the device context 
	// Note that this will never be used ;-) but no matter 
	CBitmap bitmap; 
	CDC *pDC = GetDC(); 

	//size.cx -= size.cx % 4; 
	int bitsPerPixel = pDC->GetDeviceCaps(BITSPIXEL);
	switch(bitsPerPixel){
	case 8:
	case 24: size.cx -= size.cx % 4; break;
	case 16: size.cx -= size.cx % 2; break;
	case 32:
	default: break;
	}

	TRACE("  final client zone : (%d;%d)\n",size.cx,size.cy); 


	CDC MemDC; 
	VERIFY(MemDC.CreateCompatibleDC(NULL)); 
	VERIFY(bitmap.CreateCompatibleBitmap(pDC,size.cx,size.cy)); 
	MemDC.SelectObject(&bitmap); 
	
	// Alloc pixel bytes 
	int NbBytes = 3 * size.cx * size.cy; 
	unsigned char *pPixelData = new unsigned char[NbBytes]; 
	
	// Copy from OpenGL 
	::glReadPixels(0,0,size.cx,size.cy,GL_BGR_EXT,GL_UNSIGNED_BYTE,pPixelData); 
	
	// Fill header 
	BITMAPINFOHEADER header; 
	header.biWidth = size.cx; 
	header.biHeight = size.cy; 
	header.biSizeImage = NbBytes; 
	header.biSize = 40; 
	header.biPlanes = 1; 
	header.biBitCount =  3 * 8; // RGB 
	header.biCompression = 0; 
	header.biXPelsPerMeter = 0; 
	header.biYPelsPerMeter = 0; 
	header.biClrUsed = 0; 
	header.biClrImportant = 0; 
	
	// Generate handle 
	HANDLE handle = (HANDLE)::GlobalAlloc (GHND,sizeof(BITMAPINFOHEADER) + NbBytes); 
	if(handle != NULL) 
	{ 
		// Lock handle 
		char *pData = (char *) ::GlobalLock((HGLOBAL)handle); 
		// Copy header and data 
		memcpy(pData,&header,sizeof(BITMAPINFOHEADER)); 
		memcpy(pData+sizeof(BITMAPINFOHEADER),pPixelData,NbBytes); 
		// Unlock 
		::GlobalUnlock((HGLOBAL)handle); 
		
		// Push DIB in clipboard 
		OpenClipboard(); 
		EmptyClipboard(); 
		SetClipboardData(CF_DIB,handle); 
		CloseClipboard(); 
	} 
	
	// Cleanup 
	MemDC.DeleteDC(); 
	bitmap.DeleteObject(); 
	delete [] pPixelData; 
	
	EndWaitCursor(); 
} */

void C3DGraph::RotateXIncrease(double degrees){ m_xRotate += degrees; }
void C3DGraph::RotateXIncrease(){ RotateXIncrease(1); }
void C3DGraph::RotateYIncrease(double degrees){ m_yRotate += degrees; }
void C3DGraph::RotateYIncrease(){ RotateYIncrease(1); }
void C3DGraph::RotateZIncrease(double degrees){ m_zRotate += degrees; }
void C3DGraph::RotateZIncrease(){ RotateZIncrease(1); }

void C3DGraph::RotateXDecrease(double degrees){ m_xRotate -= degrees; }
void C3DGraph::RotateXDecrease(){ RotateXDecrease(1); }
void C3DGraph::RotateYDecrease(double degrees){ m_yRotate -= degrees; }
void C3DGraph::RotateYDecrease(){ RotateYDecrease(1); }
void C3DGraph::RotateZDecrease(double degrees){ m_zRotate -= degrees; }
void C3DGraph::RotateZDecrease(){ RotateZDecrease(1); }

void C3DGraph::Paint()
{
	OnPaint();
}

void C3DGraph::OnEvaluate() 
{
	bool found_eq(false);
	for(int i(0); i < MAX_3D_EQS; ++i){
		if(m_3DEquations[i].on)
			found_eq = true;
	}
	if(!found_eq){
		AfxMessageBox("You do not have any equations drawn to evaluate");
		return;
	}

	C3DGraphEvaluateDlg *eval = new C3DGraphEvaluateDlg;

	EGraphMode mode;
	if(m_Polar)
		mode = POLAR;
	else
		mode = EUCLIDEAN;

	eval->PassVars(m_3DEquations, m_pCalculator, mode);
	eval->DoModal();	
}

void C3DGraph::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
	{
	case VK_ADD:
		if(nFlags | 0x4)
			ZoomInZ(true);
		else
			ZoomInZ(false);
		break;
	case VK_SUBTRACT:
		if(nFlags | 0x4)
			ZoomOutZ(true);
		else
			ZoomOutZ(false);
		break;
	default :
		{}	
	}
	
	CPropertyPage::OnKeyDown(nChar, nRepCnt, nFlags);
}

void C3DGraph::AllEquationsOff()
{
	for(int i(0); i < MAX_3D_EQS; ++i){
		m_3DEquations[i].on = false;
	}
}

UINT C3DGraph::OnGetDlgCode( ){

	return(DLGC_WANTALLKEYS);
}

void C3DGraph::OnTimer(UINT nIDEvent) 
{
	if(m_bXAutoRotate || m_bAllAutoRotate)
		m_xRotate -= (1 * m_iRotateSpeed);
	if(m_bYAutoRotate || m_bAllAutoRotate)
		m_yRotate -= (1 * m_iRotateSpeed);
	if(m_bZAutoRotate || m_bAllAutoRotate)
		m_zRotate -= (1 * m_iRotateSpeed);

	InvalidateRect(NULL,FALSE);	
	CPropertyPage::OnTimer(nIDEvent);
}


void C3DGraph::OnAutoRotate(UINT nID){

	switch(nID)
		{
		case ID_3DGRAPH_AUTOROTATE_XAXIS:
		case ID_3DGRAPH_AUTOROTATE_YAXIS:
		case ID_3DGRAPH_AUTOROTATE_ZAXIS:
			if(m_bAllAutoRotate)
				{
				m_bXAutoRotate = true;
				m_bYAutoRotate = true;
				m_bZAutoRotate = true;
				}
		}

		
	switch(nID){
	case ID_3DGRAPH_AUTOROTATE_ALLAXIS:

		if(m_bAllAutoRotate)
			m_bAllAutoRotate = false;
		else
			m_bAllAutoRotate = true;

		m_bXAutoRotate = false;
		m_bYAutoRotate = false;
		m_bZAutoRotate = false;
		break;
	case ID_3DGRAPH_AUTOROTATE_XAXIS:
		m_bAllAutoRotate = false;

		if(m_bXAutoRotate)
			m_bXAutoRotate = false;
		else
			m_bXAutoRotate = true;
		break;
	case ID_3DGRAPH_AUTOROTATE_YAXIS:
		m_bAllAutoRotate = false;

		if(m_bYAutoRotate)
			m_bYAutoRotate = false;
		else
			m_bYAutoRotate = true;
		break;
	case ID_3DGRAPH_AUTOROTATE_ZAXIS:
		m_bAllAutoRotate = false;

		if(m_bZAutoRotate)
			m_bZAutoRotate = false;
		else
			m_bZAutoRotate = true;
		break;
	case ID_3DGRAPH_AUTOROTATE_INCREASESPEED:
		++m_iRotateSpeed;
		break;
	case ID_3DGRAPH_AUTOROTATE_DECREASESPEED:
		--m_iRotateSpeed;

		if(m_iRotateSpeed <= 0)
			m_iRotateSpeed = 1;
		break;
	}

	if(m_bXAutoRotate &&
	  m_bYAutoRotate &&
	  m_bZAutoRotate)
		{
		m_bAllAutoRotate = true;
		m_bXAutoRotate = false;
		m_bYAutoRotate = false;
		m_bZAutoRotate = false;
		}

	if(!m_bAllAutoRotate &&
	   !m_bXAutoRotate &&
	   !m_bYAutoRotate &&
	   !m_bZAutoRotate)
		KillTimer(0);
	else
		// set timer for autorotating
		SetTimer(0,10,NULL);
}

void C3DGraph::OnUpdate3DAutoRotate(CCmdUI* pCmdUI)
{
	switch(pCmdUI->m_nID){
	case ID_3DGRAPH_AUTOROTATE_ALLAXIS: 
		if(IsAllAutoRotate())pCmdUI->SetCheck(true);
		else				 pCmdUI->SetCheck(false);
		break;
	case ID_3DGRAPH_AUTOROTATE_XAXIS: 
		if(IsXAutoRotate())	pCmdUI->SetCheck(true);
		else				pCmdUI->SetCheck(false);
		break;
	case ID_3DGRAPH_AUTOROTATE_YAXIS: 
		if(IsYAutoRotate())	pCmdUI->SetCheck(true);
		else				pCmdUI->SetCheck(false);
		break;
	case ID_3DGRAPH_AUTOROTATE_ZAXIS: 
		if(IsZAutoRotate())	pCmdUI->SetCheck(true);
		else				pCmdUI->SetCheck(false);
		break;
	}
}

void C3DGraph::StopAutoRotate()
{
	m_bAllAutoRotate = false;
	m_bXAutoRotate = false;
	m_bYAutoRotate = false;
	m_bZAutoRotate = false;
	KillTimer(0);
}


/*********************************************************/
// C3DGraph::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles init stuff before handlign popup menu
/*********************************************************/
void C3DGraph::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	UpdateMenu(pPopupMenu);
}

/*********************************************************/
// CGraphView::UpdateMenu(CMenu* pMenu)
// Pre: none
// Post: none
// Return Value: none
// Intent: it updates the controls of the individual menu items
//		   this is needed because htis is a dialog based app
//		   and the updating is not automatically done for us
/*********************************************************/
void C3DGraph::UpdateMenu(CMenu* pMenu)
{
	CCmdUI cmdUI;
	for (UINT n = 0; n < pMenu->GetMenuItemCount(); ++n)
	{
	    CMenu* pSubMenu = pMenu->GetSubMenu(n);
	    if (pSubMenu == NULL)
	    {
			cmdUI.m_nIndexMax = pMenu->GetMenuItemCount();
			for (UINT i = 0; i < cmdUI.m_nIndexMax;++i)
			{
			    cmdUI.m_nIndex = i;
				cmdUI.m_nID = pMenu->GetMenuItemID(i);
				cmdUI.m_pMenu = pMenu;
				cmdUI.DoUpdate(this, FALSE);
			}
	    }
	}
}

void C3DGraph::ExpandEquations()
{
	for(int i=0; i < 6; ++i)
		if(!ExpandEq(i, m_3DEquations[i].eq))
			m_3DEquations[i].on = false;
}

// eq is the index of the eq
bool C3DGraph::ExpandEq(int eq, CString &expnEq)
{
	expnEq = m_astrEquationsRaw[eq];
	
	int i=0;
	for(i=0; i < 6; ++i)
		{
		CString eqs;
		eqs.Format("z%d", i+1);
		
		if(0 <= expnEq.Find("("+eqs+")"))
			{
			if(i == eq)
				return false;
			
			CString subExpnEq;
			if(ExpandEq(i, subExpnEq, "" + char('0' + eq)))
				expnEq.Replace(eqs, "("+subExpnEq+")");
			else
				{
				MessageBox("Equation self dependancy detected!","Self Dependancy", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
				return false; // error, infinite loop fo eq referrers
				}
			}
		}
	return true;
}

bool C3DGraph::ExpandEq(int eq, CString &expnEq, CString strEqStack)
{
	expnEq = m_astrEquationsRaw[eq];
	
	int i=0;

	for(i=0; i < 6; ++i)
		{
		CString eqs;
		eqs.Format("z%d", i+1);
		
		if(0 <= expnEq.Find("("+eqs+")"))
			{
			if(0 <= strEqStack.Find(char('0' + i)))
				return false;
			
			CString subExpnEq;
			if(ExpandEq(i, subExpnEq, strEqStack + char('0' + eq)))
				expnEq.Replace(eqs, "("+subExpnEq+")");
			else
				return false; // error, infinite loop fo eq referrers
			}
		}
	return true;
}

BOOL C3DGraph::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CMenu PopUp3DGraph;
	PopUp3DGraph.LoadMenu(IDR_3DGRAPH);
	m_Menu3DGraph.LoadMenu(IDR_MENU);

	CGrphCalcDlg* pDlg = (CGrphCalcDlg*)STATIC_DOWNCAST(CDialog, AfxGetMainWnd());
	pDlg->AddScriptLibraryMenu(m_Menu3DGraph, 3);
	
	m_Menu3DGraph.InsertMenu(3, MF_BYPOSITION|MF_POPUP|MF_ENABLED, (UINT)PopUp3DGraph.m_hMenu, "3D Graph");
	PopUp3DGraph.Detach();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
