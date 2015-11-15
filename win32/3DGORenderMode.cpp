// 3DGORenderMode.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "3DGORenderMode.h"
#include "3DGraphOptions.h"
#include "Color.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define EDGE 105
#define START_X 232
#define START_Y 51
#define GRADIENT_EDGE	105

/////////////////////////////////////////////////////////////////////////////
// C3DGORenderMode dialog


C3DGORenderMode::C3DGORenderMode(CWnd* pParent /*=NULL*/)
	: CDialog(C3DGORenderMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(C3DGORenderMode)
	m_RenderMode = 2;
	m_ShadingModel = 0;
	//}}AFX_DATA_INIT

	m_XminYmin.SetSelectionMode(CP_MODE_BK);
	m_XminYmax.SetSelectionMode(CP_MODE_BK);
	m_XmaxYmin.SetSelectionMode(CP_MODE_BK);
	m_XmaxYmax.SetSelectionMode(CP_MODE_BK);

	m_XminYmin.SetColour(RGB(255,0,0));
	m_XminYmax.SetColour(RGB(0,255,0));
	m_XmaxYmin.SetColour(RGB(0,0,255));
	m_XmaxYmax.SetColour(RGB(255,0,255));

	m_GradientDC = NULL;
	m_Modified = false;
	m_Mode = 0;
}


void C3DGORenderMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3DGORenderMode)
	DDX_Radio(pDX, IDC_RENDER_MODE, m_RenderMode);
	DDX_Radio(pDX, IDC_SHADING_MODEL, m_ShadingModel);
	DDX_Control(pDX, IDC_XMIN_YMIN_COLOR, m_XminYmin);
	DDX_Control(pDX, IDC_XMIN_YMAX_COLOR, m_XminYmax);
	DDX_Control(pDX, IDC_XMAX_YMIN_COLOR, m_XmaxYmin);
	DDX_Control(pDX, IDC_XMAX_YMAX_COLOR, m_XmaxYmax);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3DGORenderMode, CDialog)
	//{{AFX_MSG_MAP(C3DGORenderMode)
	ON_BN_CLICKED(IDC_XMAX_YMAX_COLOR, OnXmaxYmaxColor)
	ON_BN_CLICKED(IDC_XMAX_YMIN_COLOR, OnXmaxYminColor)
	ON_BN_CLICKED(IDC_XMIN_YMAX_COLOR, OnXminYmaxColor)
	ON_BN_CLICKED(IDC_XMIN_YMIN_COLOR, OnXminYminColor)
	ON_WM_PAINT()	
	ON_BN_CLICKED(IDC_SHADING_MODEL, OnShadingModel)
	ON_BN_CLICKED(IDC_SHADING_MODEL_ELEVATION, OnShadingModelElevation)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_RENDER_MODE, OnRenderMode)
	ON_BN_CLICKED(IDC_RENDER_SURFACE_TOPWIRES, OnRenderSurfaceTopwires)
	ON_BN_CLICKED(IDC_RENDER_SURFACE_WIRES, OnRenderSurfaceWires)
	ON_BN_CLICKED(IDC_RENDER_SURFCE, OnRenderSurfce)
    ON_MESSAGE(CPN_SELENDOK,     OnSelEndOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DGORenderMode message handlers

BOOL C3DGORenderMode::OnEraseBkgnd(CDC* pDC) 
{
     // Comment this line out
     return CDialog::OnEraseBkgnd(pDC);
     //return FALSE;
}


// Function name	: C3DGORenderMode::OnPaint
// Description	    : 
// Return type		: void 
void C3DGORenderMode::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	GenerateGradientSquare();

	CRect xminymax_color, xmaxymin_color;

	CWnd *pWndxn;
	pWndxn = GetDlgItem(IDC_XMIN_YMAX_COLOR);
	if(pWndxn != NULL){
		pWndxn->GetWindowRect(xminymax_color);
		ScreenToClient(xminymax_color);
	}

	CWnd *pWndnx;
	pWndnx = GetDlgItem(IDC_XMAX_YMIN_COLOR);
	if(pWndnx != NULL){
		pWndnx->GetWindowRect(xmaxymin_color);
		ScreenToClient(xmaxymin_color);
	}

	dc.StretchBlt(xminymax_color.right - 5 , xminymax_color.bottom + 3, 
		(xmaxymin_color.left + 5) - (xminymax_color.right - 5), (xmaxymin_color.top - 3) - (xminymax_color.bottom + 3),
		m_GradientDC,
		0,0,
		GRADIENT_EDGE-1,GRADIENT_EDGE-1,
		SRCCOPY);

	//dc.BitBlt(START_X,START_Y, GRADIENT_EDGE,GRADIENT_EDGE,m_GradientDC,0,0,SRCCOPY);
}

extern double intensity(double x, double y, int corner);

// Function name	: C3DGORenderMode::GenerateGradientSquare
// Description	    : 
// Return type		: void 
void C3DGORenderMode::GenerateGradientSquare()
{
	// create bitmap
	CBitmap *pGradientBmp;
	pGradientBmp = new CBitmap();
	pGradientBmp->CreateCompatibleBitmap(GetDC(), GRADIENT_EDGE - 1, GRADIENT_EDGE - 1);
	if(m_GradientDC)delete m_GradientDC;
	m_GradientDC = new CDC();
	
	// create m_GradientDC 
	m_GradientDC->CreateCompatibleDC( GetDC() );
	m_GradientDC->SelectObject(pGradientBmp);
	
	delete(pGradientBmp); // we don't need this object anymore


	// my code	
	CColor ul(m_XminYmax.GetColour()), ur, 
		   ll(m_XminYmin.GetColour()), lr;

	if(m_ShadingModel == 0){
		ur = m_XmaxYmax.GetColour();
		lr = m_XmaxYmin.GetColour();
	}
	else{
		ur = ul;
		lr = ll;
	}
	
	double x_min_y_min_red(ll.GetRed()), x_min_y_max_red(ul.GetRed()), 
		x_max_y_min_red(lr.GetRed()), x_max_y_max_red(ur.GetRed());
	double x_min_y_min_blue(ll.GetBlue()), x_min_y_max_blue(ul.GetBlue()), 
		x_max_y_min_blue(lr.GetBlue()), x_max_y_max_blue(ur.GetBlue());
	double x_min_y_min_green(ll.GetGreen()), x_min_y_max_green(ul.GetGreen()), 
		x_max_y_min_green(lr.GetGreen()), x_max_y_max_green(ur.GetGreen());
		
	double x(0), y(0);
	int width(int(double(GRADIENT_EDGE)/52.5));
	int steps(int(double(GRADIENT_EDGE) / width));	// width * steps must equal GRADIENT_EDGE

	double interval(1.0/double(steps));

	for(int j(0); j < steps; ++j){
		x = 0;
		for(int i(0); i < steps; ++i){
			
			double ul = intensity(x,y,1);
			double ur = intensity(x,y,2);
			double lr = intensity(x,y,3);
			double ll = intensity(x,y,4);
			int red, green, blue, mix;
			COLORREF clr;
			
			
			if(m_RenderMode != 0){
				red =   int((lr*x_max_y_min_red) + 
					(ur*x_max_y_max_red) + 
					(ll*x_min_y_min_red) + 
					(ul*x_min_y_max_red));
				green = int((lr*x_max_y_min_green) + 
					(ur*x_max_y_max_green) + 
					(ll*x_min_y_min_green) + 
					(ul*x_min_y_max_green));
				blue =  int((lr*x_max_y_min_blue) + 
					(ur*x_max_y_max_blue) + 
					(ll*x_min_y_min_blue) + 
					(ul*x_min_y_max_blue));
				clr = RGB(red, green, blue);
			}
			else
			{
				mix = int(((lr*x_max_y_min_red) + 
					(ur*x_max_y_max_red) + 
					(ll*x_min_y_min_red) + 
					(ul*x_min_y_max_red) +
					
					(lr*x_max_y_min_green) + 
					(ur*x_max_y_max_green) + 
					(ll*x_min_y_min_green) + 
					(ul*x_min_y_max_green) +
					
					(lr*x_max_y_min_blue) + 
					(ur*x_max_y_max_blue) + 
					(ll*x_min_y_min_blue) + 
					(ul*x_min_y_max_blue)) / 3.0);
				clr = RGB(mix, mix, mix);
			}

			m_GradientDC->FillSolidRect(i*width, j*width, width, width, clr);
			
			x += interval;
		}
		y += interval;
	}	
}


void C3DGORenderMode::OnXmaxYmaxColor() {	m_XmaxYmax.OnClicked(); SetModified(true);}
void C3DGORenderMode::OnXmaxYminColor() {	m_XmaxYmin.OnClicked(); SetModified(true);}
void C3DGORenderMode::OnXminYmaxColor() {	m_XminYmax.OnClicked(); SetModified(true);}
void C3DGORenderMode::OnXminYminColor() {	m_XminYmin.OnClicked(); SetModified(true);}


// Function name	: C3DGORenderMode::OnSelEndOK
// Description	    : 
// Return type		: LONG 
// Argument         : UINT lParam
// Argument         : LONG /*wParam*/
LONG C3DGORenderMode::OnSelEndOK(UINT lParam, LONG /*wParam*/){
	InvalidateSwatch();
	return 0;
}


// Function name	: C3DGORenderMode::OnShadingModel
// Description	    : 
// Return type		: void 
void C3DGORenderMode::OnShadingModel() 
{
	UpdateShadingMethod();	
	SetModified(true);
}


// Function name	: C3DGORenderMode::OnShadingModelElevation
// Description	    : 
// Return type		: void 
void C3DGORenderMode::OnShadingModelElevation() 
{
	UpdateShadingMethod();	
	SetModified(true);
}


// Function name	: C3DGORenderMode::UpdateShadingMethod
// Description	    : 
// Return type		: void 
void C3DGORenderMode::UpdateShadingMethod()
{
	UpdateData();

	CWnd *pXmaxYmax, *pXmaxYmin;

	pXmaxYmax = GetDlgItem(IDC_XMAX_YMAX_COLOR);
	pXmaxYmin = GetDlgItem(IDC_XMAX_YMIN_COLOR);

	if(m_ShadingModel == 0){
		pXmaxYmax->EnableWindow();
		pXmaxYmin->EnableWindow();
	}
	else{
		pXmaxYmax->EnableWindow(false);
		pXmaxYmin->EnableWindow(false);
	}
	
	InvalidateSwatch();
}

BOOL C3DGORenderMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	EnableColors();
	
	switch(m_Mode){
	case 0:
		GetDlgItem(IDC_SHADING_MODEL)->SetWindowText("x-y position");
		break;
	case 1:
		GetDlgItem(IDC_SHADING_MODEL)->SetWindowText("t-r position");
		break;
	}

	m_PrevRenderMode = m_RenderMode;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C3DGORenderMode::SetModified(bool val)
{
	m_Modified = val;
}

void C3DGORenderMode::OnRenderMode() 
{
	SetModified(true);
	UpdateData();
	EnableColors();
}

void C3DGORenderMode::OnRenderSurfaceTopwires() 
{
	SetModified(true);
	UpdateData();
	EnableColors();
}

void C3DGORenderMode::OnRenderSurfaceWires() 
{
	SetModified(true);
	UpdateData();
	EnableColors();
}

void C3DGORenderMode::OnRenderSurfce() 
{
	SetModified(true);
	UpdateData();
	EnableColors();
}

void C3DGORenderMode::EnableColors()
{
	CWnd *pSM, *pSME;
	
	pSM = GetDlgItem(IDC_SHADING_MODEL);
	pSME = GetDlgItem(IDC_SHADING_MODEL_ELEVATION);
	
	if(m_RenderMode != 0){
		m_XminYmax.ModifyStyle(WS_DISABLED, 0);
		m_XminYmin.ModifyStyle(WS_DISABLED, 0);
		
		CWnd *pXmaxYmax, *pXmaxYmin;
		pXmaxYmax = GetDlgItem(IDC_XMAX_YMAX_COLOR);
		pXmaxYmin = GetDlgItem(IDC_XMAX_YMIN_COLOR);
		
		if(m_ShadingModel == 0){
			pXmaxYmax->EnableWindow();
			pXmaxYmin->EnableWindow();
		}
		else{
			pXmaxYmax->EnableWindow(false);
			pXmaxYmin->EnableWindow(false);
		}
		
		pSM->EnableWindow();
		pSME->EnableWindow();
	}
	else{
		m_XmaxYmax.ModifyStyle(0, WS_DISABLED);
		m_XmaxYmin.ModifyStyle(0, WS_DISABLED);
		m_XminYmax.ModifyStyle(0, WS_DISABLED);
		m_XminYmin.ModifyStyle(0, WS_DISABLED);
		pSM->EnableWindow(false);
		pSME->EnableWindow(false);
	}

	m_XmaxYmax.Invalidate();
	m_XmaxYmin.Invalidate();
	m_XminYmax.Invalidate();
	m_XminYmin.Invalidate();

	
	if((m_PrevRenderMode == 0 && m_RenderMode >= 1)
	|| (m_PrevRenderMode >= 1 && m_RenderMode == 0))
			InvalidateSwatch();

	m_PrevRenderMode = m_RenderMode;
}

void C3DGORenderMode::InvalidateSwatch()
{
	CRect xminymax_color, xmaxymin_color;
	GetDlgItem(IDC_XMIN_YMAX_COLOR)->GetWindowRect(xminymax_color);
	ScreenToClient(xminymax_color);
	GetDlgItem(IDC_XMAX_YMIN_COLOR)->GetWindowRect(xmaxymin_color);
	ScreenToClient(xmaxymin_color);

	InvalidateRect(CRect(xminymax_color.right - 5 , xminymax_color.bottom + 3, xmaxymin_color.left + 5, xmaxymin_color.top - 3));
}
