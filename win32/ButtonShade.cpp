// ButtonShade.cpp : implementation file
//

#include "stdafx.h"
#include "GrphCalc.h"
#include "ButtonShade.h"
#include "Color.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonShade

CButtonShade::CButtonShade()
{
}

CButtonShade::~CButtonShade()
{
}


BEGIN_MESSAGE_MAP(CButtonShade, CButton)
	//{{AFX_MSG_MAP(CButtonShade)
	//ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
/////////////////////////////////////////////////////////////////////////////
// CButtonShade message handlers

extern double intensity(double x, double y, int corner);

void CButtonShade::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct);
    
    CDC*    pDC     = CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect   rect    = lpDrawItemStruct->rcItem;
    UINT    state   = lpDrawItemStruct->itemState;
    CString m_strText;

    CSize Margins(::GetSystemMetrics(SM_CXEDGE), ::GetSystemMetrics(SM_CYEDGE));

	if(108 != GetState())
		pDC->DrawEdge(rect, EDGE_RAISED, BF_RECT);
	else{
		pDC->DrawEdge(rect, EDGE_SUNKEN, BF_RECT);
		rect.left += 2;
		rect.top += 2;
	}
    
	// Must reduce the size of the "client" area of the button due to edge thickness.
    rect.DeflateRect(2*Margins.cx, 2*Margins.cy);

	/////////  draw shading		
	
	CColor ul(m_3DRenderDlg.m_XminYmax.GetColour()), ur, 
		ll(m_3DRenderDlg.m_XminYmin.GetColour()), lr;

	if(m_3DRenderDlg.m_ShadingModel == 0){
		ur = m_3DRenderDlg.m_XmaxYmax.GetColour();
		lr = m_3DRenderDlg.m_XmaxYmin.GetColour();
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
	int width_x(2);
	int width_y(2);

	int steps_x(int(double(rect.Width()) / width_x));
	int steps_y(int(double(rect.Height()) / width_y) + 1);

	double interval_x(1.0/double(steps_x));
	double interval_y(1.0/double(steps_y));

	for(int j(0); j < steps_y; ++j){
		x = 0;
		for(int i(0); i < steps_x; ++i){

			int red, green, blue, mix;
			COLORREF clr;
			
			if(IsWindowEnabled()){
					red = int((intensity(x,y,3)*x_max_y_min_red) + 
							  (intensity(x,y,2)*x_max_y_max_red) + 
							  (intensity(x,y,4)*x_min_y_min_red) + 
							  (intensity(x,y,1)*x_min_y_max_red));
				
					green = int((intensity(x,y,3)*x_max_y_min_green) + 
							    (intensity(x,y,2)*x_max_y_max_green) + 
								(intensity(x,y,4)*x_min_y_min_green) + 
								(intensity(x,y,1)*x_min_y_max_green));
				
					blue = int((intensity(x,y,3)*x_max_y_min_blue) + 
							   (intensity(x,y,2)*x_max_y_max_blue) + 
							   (intensity(x,y,4)*x_min_y_min_blue) + 
							   (intensity(x,y,1)*x_min_y_max_blue));
					clr = RGB(red, green, blue);
			}
			else{
				mix = (int( ((intensity(x,y,3)*x_max_y_min_red) + 
						   (intensity(x,y,2)*x_max_y_max_red) + 
						   (intensity(x,y,4)*x_min_y_min_red) + 
						   (intensity(x,y,1)*x_min_y_max_red) +
				
						   (intensity(x,y,3)*x_max_y_min_green) + 
						   (intensity(x,y,2)*x_max_y_max_green) + 
						   (intensity(x,y,4)*x_min_y_min_green) + 
						   (intensity(x,y,1)*x_min_y_max_green) +
				
						   (intensity(x,y,3)*x_max_y_min_blue) + 
						   (intensity(x,y,2)*x_max_y_max_blue) + 
						   (intensity(x,y,4)*x_min_y_min_blue) + 
						   (intensity(x,y,1)*x_min_y_max_blue))  / 3.0));

				clr = RGB(mix,mix,mix);
			}

			pDC->FillSolidRect(rect.left + i*width_x, rect.top + j*width_y, width_x, width_y, clr);
			
			x += interval_x;
		}
		y += interval_y;
	}

    // Draw focus rect
    if (state & ODS_FOCUS) 
    {
        rect.DeflateRect(1,1);
        pDC->DrawFocusRect(rect);
    }
}

bool CButtonShade::OnClicked() 
{
	m_3DRenderDlg.DoModal();
	return m_3DRenderDlg.GetModified();
}

void CButtonShade::PreSubclassWindow() 
{
	ModifyStyle(0, BS_OWNERDRAW);        // Make it owner drawn
    CButton::PreSubclassWindow();
    SetWindowSize();                     // resize appropriately
	
	CButton::PreSubclassWindow();
}

void CButtonShade::SetWindowSize()
{
    CRect rect;
    GetWindowRect(rect);

    CWnd* pParent = GetParent();
    if (pParent)
        pParent->ScreenToClient(rect);

    MoveWindow(rect.left, rect.top, 32, 25, TRUE);
}

int CButtonShade::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetWindowSize();    // resize appropriately	
	return 0;
}

void CButtonShade::ClearModified()
{
	m_3DRenderDlg.SetModified(false);
}
