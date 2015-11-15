#include "CPrintGraph.h"








CPrintGraph::CPrintGraph(int width, int height, CCalculator *pCalc, CArray<SGraphPrintLegend, SGraphPrintLegend> *Equations)
{
	m_PrintOptions.m_graph_height	= height;
	m_PrintOptions.m_graph_width	= width;
	m_pCalculator					= pCalc;
	m_PrintOptions.m_Calculator		= pCalc;
	m_Equations						= Equations;
}


bool CPrintGraph::DisplayOptions()
{
	if(m_PrintOptions.DoModal() == IDCANCEL)
		return false;

	return true;
}

void CPrintGraph::InitializePrinting()
{
	m_DC.Attach(m_PrintOptions.m_PrintDlg.GetPrinterDC());         // Attach a printer DC
	m_DC.SetViewportOrg(0,0);
    m_DC.m_bPrinting = TRUE;
	
	DOCINFO di;                                 // Initialise print document details
    ::ZeroMemory (&di, sizeof (DOCINFO));
    di.cbSize = sizeof (DOCINFO);
    di.lpszDocName = "GraphCalc Graph";
	
	m_bPrintingOK = m_DC.StartDoc(&di);        // Begin a new print job
	
    // Get the printing extents and store in the m_rectDraw field of a 
    // CPrintInfo object
    m_Info.m_rectDraw.SetRect(0,0, 
		m_DC.GetDeviceCaps(HORZRES), 
		m_DC.GetDeviceCaps(VERTRES));
    m_Info.m_nCurPage = 1;
	
	// SET COORDINATES AND MAPPING
	m_DC.SetMapMode(MM_ANISOTROPIC);
	
	if(!m_bPrintingOK){
		//MessageBox("There was an error initializing the printing.  It could be that you have run out of memory or your printer is not set up correctly.",
			//"Error Printing", MB_OK | MB_ICONEXCLAMATION | MB_SETFOREGROUND);
		return;
	}
	
	m_DC.StartPage();    	

	m_DC.SetWindowExt(m_Info.m_rectDraw.Width(), m_Info.m_rectDraw.Height());
	m_DC.SetViewportExt(m_Info.m_rectDraw.Width(), m_Info.m_rectDraw.Height());
	m_DC.SelectClipRgn(NULL);

	SetGraphSize();
	CalcGraphPosition();

	
}

void CPrintGraph::BeginPrinting()
{
	if(m_PrintOptions.m_bTitleOn)
		DrawTitle();

	m_DC.SetViewportOrg(m_GraphOrigin.x, m_GraphOrigin.y);

	if(m_PrintOptions.m_bEquations)
		DrawEquationList();

}


void CPrintGraph::EndPrinting()
{
	m_bPrintingOK = (m_DC.EndPage() > 0);       // end page

	if (m_bPrintingOK)
        m_DC.EndDoc();                            // end a print job
    else
        m_DC.AbortDoc();                          // abort job.
	
    m_DC.Detach();                                // detach the printer DC
}

void CPrintGraph::SetGraphSize()
{
	switch(m_PrintOptions.m_iPageSize){
	case 1: // autoscale
		{
			double scale;
			if((double(m_Info.m_rectDraw.Width()) / double(m_PrintOptions.m_graph_width)) > 
				(double(m_Info.m_rectDraw.Height()) / double(m_PrintOptions.m_graph_height)))
				scale = (double(m_Info.m_rectDraw.Height()) / 2.0) / double(m_PrintOptions.m_graph_height);
			else
				scale = (double(m_Info.m_rectDraw.Width()) / 2.0) / double(m_PrintOptions.m_graph_width);
			
			m_PrintOptions.m_graph_height *= scale;
			m_PrintOptions.m_graph_width  *= scale;
			break;
		}
	case 0: // full page
		{
			m_PrintOptions.m_graph_width = m_Info.m_rectDraw.Width();
			m_PrintOptions.m_graph_height = m_Info.m_rectDraw.Height();
			break;
		}
	default: // user specified size
		{
			long double ww, hh;
			m_pCalculator->StringToDecimal(m_PrintOptions.m_sWidth, 10, ww);
			m_pCalculator->StringToDecimal(m_PrintOptions.m_sHeight, 10, hh);
			ww = m_pCalculator->abs(ww);
			hh = m_pCalculator->abs(hh);
			
			if(ww == 0)
				ww = 4;
			if(hh == 0)
				hh = 4;
			
			if(m_PrintOptions.m_sWUnits == "cm")
				ww *= 0.39370078740157;
			m_PrintOptions.m_graph_width = m_DC.GetDeviceCaps(LOGPIXELSX) * ww;
			
			if(m_PrintOptions.m_sHUnits == "cm")
				hh *= 0.39370078740157;
			m_PrintOptions.m_graph_height = m_DC.GetDeviceCaps(LOGPIXELSY) * hh;
			break;
		}
	}
	////////
	// we now have the graph width and height set in pixels
	////////
	
	m_MaxSize.x = m_Info.m_rectDraw.Width();
	m_MaxSize.y = m_Info.m_rectDraw.Height();

	m_GraphOrigin.x = 0;
	m_GraphOrigin.y = 0;
	
	if(m_PrintOptions.m_bTitleOn){
		m_GraphOrigin.y += (m_DC.GetDeviceCaps(LOGPIXELSY) * (0.25 + 0.125));
		m_MaxSize.y -= (m_DC.GetDeviceCaps(LOGPIXELSY) * (0.25 + 0.125));
	}
	if(m_PrintOptions.m_bEquations)
		m_MaxSize.y -= (m_DC.GetDeviceCaps(LOGPIXELSY) * (1.5 + 0.125));
	
	if(m_PrintOptions.m_graph_width > m_MaxSize.x)
		m_PrintOptions.m_graph_width = m_MaxSize.x;
	if(m_PrintOptions.m_graph_height > m_MaxSize.y)
		m_PrintOptions.m_graph_height = m_MaxSize.y;
	
	////////
	// we now have the width and height of graph that we will display with
	// and also the max width and height possible
	////////
}

void CPrintGraph::CalcGraphPosition()
{
	if(m_PrintOptions.m_bCenter == 1){
		m_GraphOrigin.x = (double(m_Info.m_rectDraw.Width()) / 2.0) - (double(m_PrintOptions.m_graph_width) / 2.0);
		
		double hh(m_PrintOptions.m_graph_height);
		if(m_PrintOptions.m_bTitleOn)
			hh += (m_DC.GetDeviceCaps(LOGPIXELSY) * (0.25 + 0.125));
		if(m_PrintOptions.m_bEquations)
			hh += (m_DC.GetDeviceCaps(LOGPIXELSY) * (1.5 + 0.125));
		
		m_GraphOrigin.y += (double(m_Info.m_rectDraw.Height()) / 2.0) - (hh / 2.0);
	}
}

void CPrintGraph::DrawTitle()
{
	CFont titleFont;
	m_DC.SetViewportOrg(0, 0);

	// replot
	titleFont.CreateFont(m_DC.GetDeviceCaps(LOGPIXELSY)*0.35, 
						 m_DC.GetDeviceCaps(LOGPIXELSX)*0.18,
						 0,0,
						 FW_BOLD,
						 FALSE,FALSE,
						 0,
						 ANSI_CHARSET, OUT_DEFAULT_PRECIS,
						 DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, 
						 DEFAULT_PITCH | FF_SWISS, 
						 "Arial");
	
	CFont *pOldFont = m_DC.SelectObject(&titleFont);
	m_DC.SetBkMode(TRANSPARENT);
	m_DC.SetTextColor(RGB(0,0,0));
	m_DC.SetTextAlign(TA_LEFT);
	m_DC.TextOut(0, 0, m_PrintOptions.m_sTitle);
	m_DC.SelectObject(pOldFont);
}

void CPrintGraph::DrawEquationList()
{
	CBrush brush(RGB(255,255,255)), *pOldBrush;
	pOldBrush = m_DC.SelectObject(&brush);

	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 0, RGB(0,0,0));
	CPen* pOldPen = m_DC.SelectObject(&penBlack);
	m_DC.SelectObject(&brush);
	
	//////////// Draw Equations List Box
	CPoint estart;
	CPoint eend;
	
	// replot
	estart.x = 0;
	estart.y = m_PrintOptions.m_graph_height +(0.125 * m_DC.GetDeviceCaps(LOGPIXELSY));
	eend.x = m_PrintOptions.m_graph_width;
	eend.y = m_PrintOptions.m_graph_height + ((1.5 + 0.125) * m_DC.GetDeviceCaps(LOGPIXELSY));
	
	int ew(m_PrintOptions.m_graph_width);
	if(ew < (5 * m_DC.GetDeviceCaps(LOGPIXELSX))) // check for min eqs list size
		ew = (5 * m_DC.GetDeviceCaps(LOGPIXELSX));
	
	if(ew > (m_MaxSize.x * m_DC.GetDeviceCaps(LOGPIXELSX)))
		ew = m_MaxSize.x;
	if((eend.y - estart.y) > (m_MaxSize.y * m_DC.GetDeviceCaps(LOGPIXELSY)))
		eend.y = estart.y + m_MaxSize.y;
	
	estart.x = (double(m_PrintOptions.m_graph_width) / 2.0) - (double(ew) / 2.0);
	if(estart.x < (-1*m_GraphOrigin.x))
		estart.x = m_GraphOrigin.x;
	
	eend.x = estart.x + ew;
	// end replot


	m_DC.Rectangle(estart.x, estart.y, eend.x, eend.y);
	//////////// END Draw Equations List Box
	
	//////////// Draw Key boxes
	DrawEquationLegend(CRect(estart, eend));
	//////////// END Draw Key boxes
	
	m_DC.SelectObject(pOldBrush);
	m_DC.SelectObject(pOldPen);
}

void CPrintGraph::DrawEquationLegend(CRect eq_rect)
{
	double space_frac, size, space;

	CPoint start1;
	CPoint start2;

	// replot
	space_frac = 0.5;
	size = 1.5 / (5 + (6*space_frac));
	space = size * space_frac;
	
	size *= m_DC.GetDeviceCaps(LOGPIXELSY);
	space *= m_DC.GetDeviceCaps(LOGPIXELSY);
	
	start1.x = eq_rect.left + (0.25 * m_DC.GetDeviceCaps(LOGPIXELSX));
	start1.y = eq_rect.top;
	start2.x = eq_rect.left + (eq_rect.Width() / 2) + (0.25 * m_DC.GetDeviceCaps(LOGPIXELSX));
	start2.y = eq_rect.top;
	// end replot

	// count total displayed eqs
	int total_count(0), i, count;
	total_count = m_Equations->GetSize();

	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 0, RGB(0,0,0));
	CPen* pOldPen = m_DC.SelectObject(&penBlack);
	CFont eqFont;
	eqFont.CreateFont(size/1.5, 
					 (size/4.0),
						 0,0,
						 FW_REGULAR,
						 FALSE,FALSE,
						 0,
						 ANSI_CHARSET, OUT_DEFAULT_PRECIS,
						 DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, 
						 DEFAULT_PITCH | FF_SWISS, 
						 "Arial");
	CFont *pOldFont = m_DC.SelectObject(&eqFont);

	// do column 1
	count = (total_count / 2);
	count += (total_count % 2);
	int cur(-1);
	for(i = 0; cur < (count - 1); ++i){
		++cur;
		int x = start1.x;
		int y = start1.y + cur*size + (cur + 1)*space;
		
		m_DC.SetTextAlign(TA_LEFT);
		m_DC.SetTextColor(RGB(0,0,0));

		if(m_Equations->GetAt(i).type == 2){
			CBrush brush(m_Equations->GetAt(i).twod.color), *pOldBrush;
			pOldBrush = m_DC.SelectObject(&brush);
			m_DC.Rectangle(x, y, x+size, y+size);
			m_DC.SelectObject(pOldBrush);

			m_DC.TextOut( x + (1.5*size), y + (size/2) - ((size/1.5)/2.0), m_Equations->GetAt(i).twod.eq);
		}
		else if(m_Equations->GetAt(i).type == 3){
			m_DC.TextOut( x + (1.5*size), y + (size/2) - ((size/1.5)/2.0), m_Equations->GetAt(i).threed.eq);
			Draw3DSwatch(CRect(x, y, x+size, y+size), m_Equations->GetAt(i).threed);
		}
		
	}
	
	// do column 2
	count = (total_count / 2);
	cur = -1;
	for(; (cur < (count - 1)) && (i < m_Equations->GetSize()); ++i){
		++cur;
		int x = start2.x;
		int y = start2.y + cur*size + (cur + 1)*space;
		
		m_DC.SetTextAlign(TA_LEFT);
		m_DC.SetTextColor(RGB(0,0,0));

		if(m_Equations->GetAt(i).type == 2){
			CBrush brush(m_Equations->GetAt(i).twod.color), *pOldBrush;
			pOldBrush = m_DC.SelectObject(&brush);
			m_DC.Rectangle(x, y, x+size, y+size);
			m_DC.SelectObject(pOldBrush);

			m_DC.TextOut( x + (1.5*size), y + (size/2) - ((size/1.5)/2.0), m_Equations->GetAt(i).twod.eq);
		}
		else if(m_Equations->GetAt(i).type == 3){
			m_DC.TextOut( x + (1.5*size), y + (size/2) - ((size/1.5)/2.0), m_Equations->GetAt(i).threed.eq);
			Draw3DSwatch(CRect(x, y, x+size, y+size), m_Equations->GetAt(i).threed);
		}
	}
	
	m_DC.SelectObject(pOldPen);
	m_DC.SelectObject(pOldFont);
}

extern double intensity(double x, double y, int corner);

void CPrintGraph::Draw3DSwatch(CRect rect, S3DEquation eq)
{
	switch(eq.wires){
	case W:
		Draw3DGrid(rect);
		break;
	case C:
		Draw3DColor(rect, eq);
		break;
	case CWW:
	case CW:
		Draw3DColor(rect, eq);
		Draw3DGrid(rect);
		break;
	}
}

void CPrintGraph::Draw3DGrid(CRect rect)
{
	int lines_x(7);
	int lines_y(7);
	
	double interval_x(double(rect.Width()) / (lines_x - 1));
	double interval_y(double(rect.Height()) / (lines_y - 1));
	
	double x(rect.left), y(rect.top);

	for(int j(0); j < lines_x; ++j){
		m_DC.MoveTo(rect.left, y);
		m_DC.LineTo(rect.right, y);
		y += interval_y;
	}

	for(int i(0); i < lines_y; ++i){
		m_DC.MoveTo(x, rect.top);
		m_DC.LineTo(x, rect.bottom);
		x += interval_x;		
	}
}

void CPrintGraph::Draw3DColor(CRect rect, S3DEquation eq)
{
	double x_min_y_min_red,   x_min_y_max_red, 
		   x_max_y_min_red,   x_max_y_max_red;
	double x_min_y_min_blue,  x_min_y_max_blue, 
		   x_max_y_min_blue,  x_max_y_max_blue;
	double x_min_y_min_green, x_min_y_max_green, 
		   x_max_y_min_green, x_max_y_max_green;
	
	x_min_y_min_red = eq.color.color3.red * 255;
	x_min_y_max_red = eq.color.color1.red * 255;
	x_max_y_min_red = eq.color.color4.red * 255; 
	x_max_y_max_red = eq.color.color2.red * 255;
	x_min_y_min_blue = eq.color.color3.blue * 255;
	x_min_y_max_blue = eq.color.color1.blue * 255;
	x_max_y_min_blue = eq.color.color4.blue * 255;
	x_max_y_max_blue = eq.color.color2.blue * 255;
	x_min_y_min_green = eq.color.color3.green * 255;
	x_min_y_max_green = eq.color.color1.green * 255;
	x_max_y_min_green = eq.color.color4.green * 255;
	x_max_y_max_green = eq.color.color2.green * 255;

	if(eq.color.type == 1){ 
		// if we are doing elevation shading set the other
		// 2 corners so that we only have 2 colors instead of 4

		x_max_y_max_red = x_min_y_max_red;
		x_max_y_max_green = x_min_y_max_green;
		x_max_y_max_blue = x_min_y_max_blue;

		x_max_y_min_red = x_min_y_min_red;
		x_max_y_min_green = x_min_y_min_green;
		x_max_y_min_blue = x_min_y_min_blue;
	}
	
	double x(0), y(0);
	double intervals_x(1.0/double(rect.Width()));
	double intervals_y(1.0/double(rect.Height()));

	for(int j(0); j < rect.Height(); ++j){
		x = 0;
		for(int i(0); i < rect.Width(); ++i){
			
			double ul = intensity(x,y,1);
			double ur = intensity(x,y,2);
			double lr = intensity(x,y,3);
			double ll = intensity(x,y,4);
			int red, green, blue;
			COLORREF clr;
			
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

			m_DC.FillSolidRect(rect.left + i, rect.top + j, 1, 1, clr);
			
			x += intervals_x;
		}
		y += intervals_y;
	}	
}
