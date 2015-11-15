#include "2DGraphParametric.h"
extern CCalculator *g_Calculator;

extern VariableT GetVariable(CString var, long double num);
struct SPoint;
extern SPoint g_DrawFontSize;

C2DGraphParametric::C2DGraphParametric(){
	m_Tmin = 0;
	m_Tmax = 10;
	m_Tstep = 0.1;
	
	m_Ymin = m_PrevYmin = -10;
	m_Ymax = m_PrevYmax = 10;
	m_Yscl = m_PrevYscl = 1;
	m_Xmin = m_PrevXmin = 0;
	m_Xmax = m_PrevXmax = 100;
	m_Xscl = m_PrevXscl = 10;

	m_Equations[0].xt = "t^2";
	m_Equations[0].yt = "tan(t)";
	m_Equations[0].disp = true;
	m_Equations[0].color = RGB(128,0,0);
	m_Equations[1].xt = "sin(t)";
	m_Equations[1].yt = "sqrt(t)";
	m_Equations[1].disp = true;
	m_Equations[1].color = RGB(0,128,0);
	m_Equations[2].xt.Empty();
	m_Equations[2].yt.Empty();
	m_Equations[2].disp = false;
	m_Equations[2].color = RGB(0,0,128);
	m_Equations[3].xt.Empty();
	m_Equations[3].yt.Empty();
	m_Equations[3].disp = false;
	m_Equations[3].color = RGB(128,128,0);
	m_Equations[4].xt.Empty();
	m_Equations[4].yt.Empty();
	m_Equations[4].disp = false;
	m_Equations[4].color = RGB(0,128,128);
}

C2DGraphParametric::~C2DGraphParametric(){

}

/*********************************************************/
// CGraphView::StoreCurrentRange()
// Pre: none
// Post: range is stored
// Return Value: none
// Intent: to store the current range
/*********************************************************/
void C2DGraphParametric::StoreCurrentRange()
{
	m_PrevYmin = m_Ymin;
	m_PrevYmax = m_Ymax;
	m_PrevYscl = m_Yscl;
	m_PrevXmin = m_Xmin;
	m_PrevXmax = m_Xmax;
	m_PrevXscl = m_Xscl;
}

/*********************************************************/
// CGraphView::SetPreviousRange()
// Pre: none
// Post: none
// Return Value: none
// Intent: sets the previous range
/*********************************************************/
void C2DGraphParametric::SetPreviousRange()
{
	m_Ymin = m_PrevYmin;
	m_Ymax = m_PrevYmax;
	m_Yscl = m_PrevYscl;
	m_Xmin = m_PrevXmin;
	m_Xmax = m_PrevXmax;
	m_Xscl = m_PrevXscl;
}

/*********************************************************/
// CGraphView::SwapPrevCurRanges()
// Pre: none
// Post: ranges are swapped
// Return Value: none
// Intent: to swp the previous range with the current one
/*********************************************************/
void C2DGraphParametric::SwapPrevCurRanges()
{
	double xmax = m_Xmax;
	double xmin = m_Xmin;
	double xscl = m_Xscl;
	double ymax = m_Ymax;
	double ymin = m_Ymin;
	double yscl = m_Yscl;
	
	m_Ymin = m_PrevYmin;
	m_Ymax = m_PrevYmax;
	m_Yscl = m_PrevYscl;
	m_Xmin = m_PrevXmin;
	m_Xmax = m_PrevXmax;
	m_Xscl = m_PrevXscl;
	
	m_PrevYmin = ymin;
	m_PrevYmax = ymax;
	m_PrevYscl = yscl;
	m_PrevXmin = xmin;
	m_PrevXmax = xmax;
	m_PrevXscl = xscl;
}

bool C2DGraphParametric::DrawEquation(int nEq, SEquationStyle &style, CRect &window, CDC *pDC)
{
	Assert(nEq < MAX_2D_PARAMETRIC_EQS);

	CPen *pen = new CPen, *pOldPen;
	ErrorT error;
	pen->CreatePen(PS_SOLID, style.size, m_Equations[nEq].color);
	pOldPen = pDC->SelectObject(pen);

	int j=0;
	long double xt, yt;	
	long double points = (m_Tmax - m_Tmin) / m_Tstep;

	bool first(true);
	int prev_y, y_coord(0), x_coord(0);
	CRect Threshold(0, 0 - GRAPH_THRESHOLD, window.Width(), window.Height() + GRAPH_THRESHOLD);
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	
	for(j=0; j < points; ++j){		
		if((error = g_Calculator->Compute(m_Equations[nEq].xt, "t", (m_Tmin + (j*m_Tstep)), xt, 0)) != SUCCESSFULL){
			if(DIV_ZERO == error)
				continue; // we can just ignore this and continue
				
			g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
			pDC->SelectObject(pOldPen);
			delete pen;	
			return false;
		}
		
		if((error = g_Calculator->Compute(m_Equations[nEq].yt, "t", (m_Tmin + (j*m_Tstep)), yt, 0)) != SUCCESSFULL){
			if(DIV_ZERO == error)
				continue; // we can just ignore this and continue
				
			g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
			pDC->SelectObject(pOldPen);
			delete pen;	
			return false;
		}
		
		prev_y = y_coord;
		y_coord = GraphToScreenY(window, yt);
		x_coord = GraphToScreenX(window, xt);		
				
		if(style.line == GRAPH_STYLE_LINE){
			if(first){
				pDC->MoveTo(x_coord, y_coord);
				first = false;
			}
			else
				pDC->LineTo(x_coord, y_coord);
		}
		else if(style.line == GRAPH_STYLE_POINT){
			pDC->SetPixel(x_coord, y_coord, m_Equations[nEq].color);
		}
	}
	
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	pDC->SelectObject(pOldPen);
	delete pen;	
	return true;
}


void C2DGraphParametric::DrawXLabel(long double x, CRect window, CDC *pDC, 
						DrawE destination, double font_size, COLORREF color)
{
	pDC->SetTextColor(color);
	CFont fontText;
	CString str;

	if(destination == PRINT)
		fontText.CreateFont(pDC->GetDeviceCaps(LOGPIXELSY)*0.08, 
							pDC->GetDeviceCaps(LOGPIXELSX)*0.05,
							0,0,400,FALSE,FALSE,0,ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH | FF_SWISS, "Arial");
	else
		fontText.CreateFont(font_size-2,0,0,0,400,FALSE,FALSE,0,ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH | FF_SWISS, "Arial");

	CFont *pOldFont = (CFont*) pDC->SelectObject(&fontText);
	pDC->SetBkMode(TRANSPARENT);

	str.Format("%.5f", x);
	DecimalForDisplay(str);
		
	pDC->SetTextAlign(TA_CENTER);

	if(destination != PRINT)
		pDC->TextOut(GraphToScreenX(window, x), GetXAxisY(window)-(2+font_size), str);
	else
		;  // TODO: enable this for printing	

	pDC->SelectObject(pOldFont);	
}

void C2DGraphParametric::DrawGrid(const SLineStyle &style, bool &grid_on, 
									const CRect window, CDC *pDC,
							   		DrawE destination, double font_size, 
							   		COLORREF color, int label_interval)
{
	int x, y;
	double x_ratio, y_ratio;
	int height, width, vert_y, vert_x, horz_y, horz_x;

	x_ratio = (m_Xmax-m_Xmin)/window.Width();
	y_ratio = (m_Ymax-m_Ymin)/window.Height();


	long double x_scale = m_Xscl;
	long double y_scale = m_Yscl;

	/////////  VALIDATE GRID DENSITY //////////////
	if((x_scale/x_ratio) < 4)
		x_scale = x_ratio*4;

	if((y_scale/y_ratio) < 4)
		y_scale = y_ratio*4;
	/////////  END VALIDATE GRID DENSITY //////////////

	// calculate x and y coordiantes which start x and y axis
	x = GetYAxisX(window);
	y = GetXAxisY(window);

	while(x < 0)
		x = int(x + x_scale/x_ratio);
	
	while(x > window.Width())
		x = int(x - x_scale/x_ratio);

	while(y < 0)
		y = int(y + y_scale/y_ratio);
	
	while(y > window.Height())
		y = int(y - y_scale/y_ratio);

	// determine length of lines
	if(grid_on){
		height = window.Height();
		width = window.Width();
		vert_y = 0;
		horz_x = 0;
	}
	else{
		height = 10;
		width = 10;
		vert_y = y - height/2;
		horz_x = x - width/2;
	}

	// Brush needed Draw the x and y axis
	CPen *grid, *pOldPen;
	grid = new CPen;
	grid->CreatePen(PS_SOLID, style.size, style.color);
	pOldPen = pDC->SelectObject(grid);
	/////////////////////////////////////
	int count;

	// convert values to offset in window
	vert_y += window.top;
	horz_x += window.left;

	// draw lines left of y axis
	count = 1;
	vert_x = GraphToScreenX(window, -1 * x_scale * count++);
	
	while((vert_x > 0) && ((m_Ymin <= 0 && m_Ymax >= 0) || grid_on)){
		if(vert_x >= window.left){
			pDC->MoveTo(CPoint(vert_x, vert_y));
			pDC->LineTo(CPoint(vert_x, vert_y + height));

			// draw x value
			if((label_interval != 0) && (count % label_interval) == 0)
				DrawXLabel(-1 * x_scale * (count-1), window, pDC, SCRN, font_size, color);
		}
		vert_x = GraphToScreenX(window, -1 * x_scale * count++);
	}
	
	// draw lines right of y axis
	count = 1;
	vert_x = GraphToScreenX(window, x_scale * count++);
	
	while((vert_x < window.Width()) && ((m_Ymin <= 0 && m_Ymax >= 0) || grid_on)){
		if(vert_x <= window.right){
			pDC->MoveTo(CPoint(vert_x, vert_y));
			pDC->LineTo(CPoint(vert_x, vert_y + height));
			
			// draw x value
			if((label_interval != 0) && (count % label_interval) == 0)
				DrawXLabel(x_scale * (count-1), window, pDC, SCRN, font_size, color);
		}
		vert_x = GraphToScreenX(window, x_scale * count++);
	}
	
	// draw lines above x axis
	count = 1;
	horz_y = GraphToScreenY(window, y_scale * count++);
	
	while((horz_y > 0) && ((m_Xmin <= 0 && m_Xmax >= 0) || grid_on)){
		if(horz_y >= window.top){
			pDC->MoveTo(CPoint(horz_x, horz_y));
			pDC->LineTo(CPoint(horz_x + width, horz_y));
		}
		horz_y = GraphToScreenY(window, y_scale * count++);
	}
	
	// draw lines below x axis
	count = 1;
	horz_y = GraphToScreenY(window, -1 * y_scale * count++);
	
	while((horz_y < window.Height()) && ((m_Xmin <= 0 && m_Xmax >= 0) || grid_on)){
		if(horz_y <= window.bottom){
			pDC->MoveTo(CPoint(horz_x, horz_y));
			pDC->LineTo(CPoint(horz_x + width, horz_y));
		}
		horz_y = GraphToScreenY(window, -1 * y_scale * count++);
	}

	pDC->SelectObject(pOldPen);
	delete grid;
}

/*********************************************************/
// DrawAxis
// Pre: none
// Post: axis are drawn to pDC
// Return Value: none
// Intent: to draw the axis of the graph
/*********************************************************/
void C2DGraphParametric::DrawAxis(const SLineStyle &style, 
							   const CRect window, 
							   CDC *pDC)
{
	int y_axis_x, y_axis_y, x_axis_y, x_axis_x;

	y_axis_x = int(window.Width() - ((m_Xmax * window.Width()) / (m_Xmax-m_Xmin)));
	y_axis_y = int(window.Height());
	x_axis_y = int((m_Ymax * window.Height()) / (m_Ymax-m_Ymin));
	x_axis_x = int(window.Width());

	CPen *axis = new CPen, *pOldPen;
	axis->CreatePen(PS_SOLID, style.size, style.color);
	pOldPen = pDC->SelectObject(axis);

	// Draw Y-axis
	pDC->MoveTo(y_axis_x + window.left, window.top);
	pDC->LineTo(y_axis_x + window.left, y_axis_y + window.top);
	// Draw X-axis
	pDC->MoveTo(window.left, x_axis_y + window.top);
	pDC->LineTo(x_axis_x + window.left, x_axis_y + window.top);

	pDC->SelectObject(pOldPen);
	delete axis;
}


/*********************************************************/
// C2DGraphParametric::DrawCoordsLabels(CDC *pDC)
// Pre: none
// Post: coordinates and/or labels drawn on graph
// Return Value: none
// Intent: to draw coordinates and labels on graph
/*********************************************************/
void C2DGraphParametric::DrawCoordsLabels(const double font_size,
									   const bool coords,
									   const bool labels,
									   const COLORREF color,
									   const CRect window, 
									   DrawE destination,
									   CDC *pDC)
{
	// calculate x and y coordiantes which start x and y axis
	int x = GetYAxisX(window) + window.left;
	int y = GetXAxisY(window) + window.top;

	pDC->SetTextColor(color);
	CFont fontText;
	CString str;

	if(destination == PRINT)
		fontText.CreateFont(pDC->GetDeviceCaps(LOGPIXELSY)*0.08, 
							pDC->GetDeviceCaps(LOGPIXELSX)*0.05,
							0,0,400,FALSE,FALSE,0,ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH | FF_SWISS, "Arial");
	else
		fontText.CreateFont(font_size,0,0,0,400,FALSE,FALSE,0,ANSI_CHARSET, OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, DEFAULT_PITCH | FF_SWISS, "Arial");

	CFont *pOldFont = (CFont*) pDC->SelectObject(&fontText);
	pDC->SetBkMode(TRANSPARENT);

	// draw -x information ///////////////////////////
	if(labels && coords)
		str = "-X: " + ConvertForDisplay(m_Xmin, 4);
	else if(coords)
		str = ConvertForDisplay(m_Xmin, 4);
	else if(labels)
		str = "-X";
	pDC->SetTextAlign(TA_LEFT);
	if(destination == PRINT)
		pDC->TextOut((pDC->GetDeviceCaps(LOGPIXELSX)*0.02), y+(pDC->GetDeviceCaps(LOGPIXELSY)*0.001), str);
	else
		pDC->TextOut(2, y+6, str);

	// draw x information ///////////////////////////
	if(labels && coords)
		str = "X: " + ConvertForDisplay(m_Xmax, 4);
	else if(coords)
		str = ConvertForDisplay(m_Xmax, 4);
	else if(labels)
		str = "X";
	pDC->SetTextAlign(TA_RIGHT);
	if(destination == PRINT)
		pDC->TextOut(window.right-(pDC->GetDeviceCaps(LOGPIXELSX)*0.02), y+(pDC->GetDeviceCaps(LOGPIXELSY)*0.001), str);
	else
		pDC->TextOut(window.right-2, y+6, str);

	// draw y information ///////////////////////////
	if(labels && coords)
		str = "Y: " + ConvertForDisplay(m_Ymax, 4);
	else if(coords)
		str = ConvertForDisplay(m_Ymax, 4);
	else if(labels)
		str = "Y";
	pDC->SetTextAlign(TA_CENTER);
	if(destination == PRINT)
		pDC->TextOut(x, (pDC->GetDeviceCaps(LOGPIXELSY)*0.02), str);
	else
		pDC->TextOut(x, 2, str);

	// draw -y information ///////////////////////////
	if(labels && coords)
		str = "-Y: " + ConvertForDisplay(m_Ymin, 4);
	else if(coords)
		str = ConvertForDisplay(m_Ymin, 4);
	else if(labels)
		str = "-Y";
	if(destination == PRINT)
		pDC->TextOut(x, window.bottom-(pDC->GetDeviceCaps(LOGPIXELSY)*0.1), str);
	else
		pDC->TextOut(x, window.bottom - font_size - 1, str);
	
	pDC->SelectObject(pOldFont);
}



// gets the x-coord, relative to the upper left corner of the graph, of the y axis
int C2DGraphParametric::GetYAxisX(CRect window)
{
	return int(window.Width() - ((m_Xmax * window.Width()) / (m_Xmax-m_Xmin)));
}

// gets the y-coord, relative to the upper left corner of the graph, of the x axis
int C2DGraphParametric::GetXAxisY(CRect window)
{
	return int(((m_Ymax * window.Height()) / (m_Ymax-m_Ymin)));
}

int C2DGraphParametric::GraphToScreenX(const CRect window,long double x)
{
	double points = double(window.Width());
	double increment = double((m_Xmax - m_Xmin) / points);
	return int((x - m_Xmin) / increment) + window.left;
}


int C2DGraphParametric::GraphToScreenY(const CRect window, long double y)
{
	long double y_ratio = double((m_Ymax-m_Ymin))/double(window.Height());
	return int((m_Ymax - y) / y_ratio) + window.top;
}

long double C2DGraphParametric::ScreenToGraphX(const CRect window, int x)
{
	double points = double(window.Width());
	double increment = double((m_Xmax - m_Xmin) / points);
	return (m_Xmin + (double(x - window.left) * increment));
}

long double C2DGraphParametric::ScreenToGraphY(const CRect window, int y)
{
	long double y_ratio = double((m_Ymax-m_Ymin))/double(window.Height());
	return m_Ymax - (y * y_ratio);
}
void C2DGraphParametric::ValidateRanges()
{
	if(m_Xmax > 99999999999999999.0)
		m_Xmax = 99999999999999999.0;
	if(m_Xmin < -99999999999999999.0)
		m_Xmin = -99999999999999999.0;
	if(m_Xscl <= 0)
		m_Xscl = 1;
	if(m_Ymax > 99999999999999999.0)
		m_Ymax = 999999999999999990.0;
	if(m_Ymin < -999999999999999990.0)
		m_Ymin = -99999999999999999.0;
	if(m_Yscl <= 0)
		m_Yscl = 1;
	
	if(m_Ymin >= m_Ymax){
		m_Ymax = 10;
		m_Ymin = -10;
	}
	if(m_Xmin >= m_Xmax){
		m_Xmax = 10;
		m_Xmin = -10;	
	}
	
	if(m_Xscl <= 0)
		m_Xscl = 1;
	if(m_Yscl <= 0)
		m_Yscl = 1;

	// validate time range
	if(m_Tmin >= m_Tmax){
		m_Tmax = 10;
		m_Tmin = -10;	
	}
	if(m_Tstep < 0.00001)
		m_Tstep = 0.01;
}


bool C2DGraphParametric::InitializeTrace(int &nTraceEq)
{
	m_TraceT = m_PrevTraceT = m_Tmin;

	for(nTraceEq = 0; nTraceEq < MAX_2D_PARAMETRIC_EQS; ++nTraceEq){
		if(m_Equations[nTraceEq].disp)
			 break;
	}
	if(nTraceEq > MAX_2D_PARAMETRIC_EQS)
		return false;
	return true;
}

void C2DGraphParametric::ClearPrevTrace(UINT nEq,CBitmap &bitmap,CRect window,CDC *pDC)
{
	// draw graph bitmap just over section where cross was displayed
	long double x,y;

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	if(g_Calculator->Compute(m_Equations[nEq].xt, "t", m_PrevTraceT, x, 0) != SUCCESSFULL) return;
	if(g_Calculator->Compute(m_Equations[nEq].yt, "t", m_PrevTraceT, y, 0) != SUCCESSFULL) return;
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	
	int prev_x_coord = GraphToScreenX(window, x);
	int prev_y_coord = GraphToScreenY(window, y);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = MemDC.SelectObject(&bitmap);

	// draw graph bitmap over last position of cursor
	pDC->BitBlt(prev_x_coord - 20, prev_y_coord - 20, 
				40, 40, 
				&MemDC, 
				prev_x_coord - 20, prev_y_coord - 20, 
				SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	DeleteDC(MemDC);
}

TraceRedrawMode C2DGraphParametric::DrawTrace(UINT nEq,
								CRect window,
								DrawE destination,
								CPen *pPen,
								CDC *pDC)
{
	// figure out x and y coords of trace point
	long double x,y;

	if(g_Calculator->Compute(m_Equations[nEq].xt, "t", m_PrevTraceT, x, 0) != SUCCESSFULL) return TRACE_NONE;
	if(g_Calculator->Compute(m_Equations[nEq].yt, "t", m_PrevTraceT, y, 0) != SUCCESSFULL) return TRACE_NONE;

	while(-HUGE_VAL == y || HUGE_VAL == y){
		if(m_TraceT > m_PrevTraceT){
			m_PrevTraceT -= m_Tstep;
			m_TraceT -= m_Tstep;
		}
		else{
			m_PrevTraceT += m_Tstep;
			m_TraceT += m_Tstep;
		}
		
		if(g_Calculator->Compute(m_Equations[nEq].xt, "t", m_PrevTraceT, x, 0) != SUCCESSFULL) return TRACE_NONE;
		if(g_Calculator->Compute(m_Equations[nEq].yt, "t", m_PrevTraceT, y, 0) != SUCCESSFULL) return TRACE_NONE;
	}

	if(AutoPan(x, y)) return TRACE_PAN; 

	int x_coord = GraphToScreenX(window, x);
	int y_coord = GraphToScreenY(window, y);

	// draw the cross
	CPen *pOldPen = pDC->SelectObject(pPen);
	int rop = pDC->GetROP2();
	pDC->SetROP2(R2_NOT);
	pDC->MoveTo(x_coord, y_coord - 10);
	pDC->LineTo(x_coord, y_coord + 10);
	pDC->MoveTo(x_coord - 10, y_coord);
	pDC->LineTo(x_coord + 10, y_coord);
	pDC->SelectObject(pOldPen);
	pDC->SetROP2(rop);

	return TRACE_NONE;
}


bool C2DGraphParametric::AutoPan(long double x, long double y)
{
	long double rangex(m_Xmax - m_Xmin);
	long double rangey(m_Ymax - m_Ymin);

	long double distx(g_Calculator->abs(0.1 * rangex));
	long double disty(g_Calculator->abs(0.1 * rangey));

	long double borderx(g_Calculator->abs(0.01 * rangex));
	long double bordery(g_Calculator->abs(0.01 * rangey));

	if(x >= (m_Xmax - borderx)){	
		m_Xmax = x + distx;
		m_Xmin = m_Xmax - rangex;
		return true;
	}
	else if(x <= (m_Xmin + borderx)){
		m_Xmin = x - distx;
		m_Xmax = m_Xmin + rangex;
		return true;
	}
	if(y >= (m_Ymax - bordery)){
		m_Ymax = y + disty;
		m_Ymin = m_Ymax - rangey;
		return true;
	}
	else if(y <= (m_Ymin + bordery)){
		m_Ymin = y - disty;
		m_Ymax = m_Ymin + rangey;
		return true;
	}
	return false;
}

void C2DGraphParametric::IncreaseTraceT(){	
	if((m_TraceT + m_Tstep + 0.00001) <= m_Tmax){
		m_PrevTraceT = m_TraceT;
		m_TraceT += m_Tstep; 
	}
}
void C2DGraphParametric::DecreaseTraceT(){	
	if((m_TraceT - m_Tstep + 0.00001) >= m_Tmin){
		m_PrevTraceT = m_TraceT;
		m_TraceT -= m_Tstep; 
	}
}

void C2DGraphParametric::NextTraceEq(int direction, int &nTraceEq)
{
	if(direction == 1){
		if(nTraceEq >= 4)
			nTraceEq = 0;
		else
			++nTraceEq;
		
		for(nTraceEq; nTraceEq < MAX_2D_PARAMETRIC_EQS; ++nTraceEq){
			
			if(m_Equations[nTraceEq].disp)
				break;
			else if(nTraceEq == 4)
				nTraceEq = -1;
		}
	}
	else{
		if(nTraceEq <= 0)
			nTraceEq = 4;
		else
			--nTraceEq;
		
		for(nTraceEq; nTraceEq >= 0; --nTraceEq){
			if(m_Equations[nTraceEq].disp)
				break;
			else if(nTraceEq == 0)
				nTraceEq = 5;
		}
	}
}

CString C2DGraphParametric::GetTraceCoordsStr(UINT nEq)
{
	long double x,y;
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	if(g_Calculator->Compute(m_Equations[nEq].xt, "t", m_TraceT, x, 0) != SUCCESSFULL)
		{
		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
		return "";
		}
	if(g_Calculator->Compute(m_Equations[nEq].yt, "t", m_TraceT, y, 0) != SUCCESSFULL)
		{
		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
		return "";
		}
	
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);

	CString strX, strY, strT;
	g_Calculator->DecimalToStringSci(strX, x,5);
	g_Calculator->DecimalToStringSci(strY, y,5);
	g_Calculator->DecimalToStringSci(strT, m_TraceT,5);
	return "x = " + strX + ", y = " + strY + ", t = " + strT;
}

ErrorT C2DGraphParametric::DyDx(CString eqX, CString eqY, 
							    long double t, long double &outAns)
{
	long double t1, t2, x1, x2, y1, y2, delta_t = 0.000001;
	ErrorT ec = SUCCESSFULL;
	t1 = t - delta_t;
	t2 = t + delta_t;
	outAns = 0;

	if((ec = g_Calculator->Compute(eqX, "t" , t1, x1, 0)) != SUCCESSFULL)	return ec;
	if((ec = g_Calculator->Compute(eqY, "t" , t1, y1, 0)) != SUCCESSFULL)	return ec;
	
	if((ec = g_Calculator->Compute(eqX, "t" , t2, x2, 0)) != SUCCESSFULL)	return ec;
	if((ec = g_Calculator->Compute(eqY, "t" , t2, y2, 0)) != SUCCESSFULL)	return ec;

	outAns = ((y2-y1)/(x2-x1));
	return ec;
}

CString C2DGraphParametric::GetDyDxStr(UINT nEq, long double t)
{
	long double slope;
	CString str;
	
	if(DIV_ZERO == DyDx(m_Equations[nEq].xt, m_Equations[nEq].yt, t, slope))
		str = "undefined";
	else if(-HUGE_VAL == slope || HUGE_VAL == slope)
		str = "dy/dx = vertical line: infinite slope";
	else
		str.Format("%.10f", slope);

	return str;
}

CString C2DGraphParametric::GetTraceXStr(CString eq)
{
	long double traceX;
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	if(g_Calculator->Compute(eq, "t", m_TraceT, traceX, 0) != SUCCESSFULL)
		{
		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
		return "";
		}
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);

	CString str;
	g_Calculator->DecimalToStringSci(str, traceX, 10);
	return str;
}

CString C2DGraphParametric::GetTraceYStr(CString eq)
{
	long double traceY;
	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	if(g_Calculator->Compute(eq, "t", m_TraceT, traceY, 0) != SUCCESSFULL)
		{
		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
		return "";
		}
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);

	CString str;
	g_Calculator->DecimalToStringSci(str, traceY, 10);
	return str;
}

CString C2DGraphParametric::GetTraceTStr()
{
	CString str;
	g_Calculator->DecimalToStringSci(str, m_TraceT, 10);
	return str;
}

CString C2DGraphParametric::GetTangentEquation(CString eqX, CString eqY, long double t)
{
	long double x, y, m, b;
	DyDx(eqX, eqY, t, m);

	if(g_Calculator->Compute(eqX, "t" , t, x, 0) != SUCCESSFULL)	return "0";
	if(g_Calculator->Compute(eqY, "t" , t, y, 0) != SUCCESSFULL)	return "0";
	b = y - (m*x);

	CString yS, mS, bS;
	g_Calculator->DecimalToString(yS, y);
	g_Calculator->DecimalToString(mS, m);
	g_Calculator->DecimalToString(bS, b);
	return mS + " * x + " + bS;
}

void C2DGraphParametric::DrawTangentLine(int nEq,
									  long double &t, 
									  SEquationStyle &style, 
									  CRect window, 
									  CDC *pDC)
{
	CString tangentEq = GetTangentEquation(m_Equations[nEq].xt, m_Equations[nEq].yt, t);

	long double y1, y2;

	if(g_Calculator->Compute(tangentEq, "x" , m_Xmin, y1, 0) != SUCCESSFULL)	return;
	if(g_Calculator->Compute(tangentEq, "x" , m_Xmax, y2, 0) != SUCCESSFULL)	return;
	
	int y_coord_1 = GraphToScreenY(window, y1);
	int x_coord_1 = GraphToScreenX(window, m_Xmin);
	int y_coord_2 = GraphToScreenY(window, y2);
	int x_coord_2 = GraphToScreenX(window, m_Xmax);

	CPen *pen = new CPen, *pOldPen;
	pen->CreatePen(PS_SOLID, style.size, m_Equations[nEq].color);
	pOldPen = pDC->SelectObject(pen);

	pDC->MoveTo(x_coord_1, y_coord_1);
	pDC->LineTo(x_coord_2, y_coord_2);
	
	pDC->SelectObject(pOldPen);
	delete pen;
}
									  
/*


void C2DGraphParametric::DrawTangentLine(const EquationT &eqT,
									  const long double &x, 
									  const SEquationStyle &style, 
									  const CRect window, 
									  CCalculator *g_Calculator,
									  DrawE destination,
									  CDC *pDC)
{
	CString tangentEq = GetTangentEquation(eqT.eq, g_Calculator, x);

	long double y1, y2;

	if(g_Calculator->Compute(tangentEq, "x" , m_Xmin, y1, 0) != SUCCESSFULL)	return;
	if(g_Calculator->Compute(tangentEq, "x" , m_Xmax, y2, 0) != SUCCESSFULL)	return;
	
	int y_coord_1 = GraphToScreenY(window, y1);
	int x_coord_1 = GraphToScreenX(window, m_Xmin, 100);
	int y_coord_2 = GraphToScreenY(window, y2);
	int x_coord_2 = GraphToScreenX(window, m_Xmax, 100);

	CPen *pen = new CPen, *pOldPen;
	pen->CreatePen(PS_SOLID, style.size, eqT.color);
	pOldPen = pDC->SelectObject(pen);

	pDC->MoveTo(x_coord_1, y_coord_1);
	pDC->LineTo(x_coord_2, y_coord_2);
	
	pDC->SelectObject(pOldPen);
	delete pen;
}

CString C2DGraphParametric::GetTraceDyDxStr(const CString eq)
{
	long double slope;
	CString str;

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);
	
	if(DIV_ZERO == DyDx(eq, g_Calculator, m_TraceX, slope))
		str = "undefined";
	else if(-HUGE_VAL == slope || HUGE_VAL == slope)
		str = "vertical line: infinite slope";
	else
		g_Calculator->DecimalToStringSci(str, slope, 10);
	
	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);

	return str;
}


void C2DGraphParametric::DrawDistance(DistStatusE distance,
								   const CString &EqOne,
								   const CString &EqTwo,
								   const long double &OneX,
								   const long double &TwoX,
								   const COLORREF bgcolor,
								   const CRect window, 
								   DrawE destination,
								   const SEquationStyle &style, 
								   CCalculator *g_Calculator,
								   CDC *pDC)
{	
	
	long double y1, y2;

	if(g_Calculator->Compute(EqOne, "x", OneX, y1, 0) != SUCCESSFULL)	return;
	if(g_Calculator->Compute(EqTwo, "x", TwoX, y2, 0) != SUCCESSFULL)	return;
	
	int y_coord_1, x_coord_1, y_coord_2, x_coord_2;
	
	y_coord_1 = GraphToScreenY(window, y1);
	x_coord_1 = GraphToScreenX(window, OneX, m_LinePrec);
	y_coord_2 = GraphToScreenY(window, y2);
	x_coord_2 = GraphToScreenX(window, TwoX, m_LinePrec);
	
	CPen pen;
	int rop = pDC->GetROP2();
	
	if(distance == SECOND && destination != PRINT){
		pen.CreatePen(PS_SOLID, style.size, bgcolor);
		pDC->SetROP2(R2_NOT);
	}
	else if(destination == PRINT){
		pen.CreatePen(PS_SOLID, style.size, RGB(0,0,0));
		pDC->SetROP2(R2_COPYPEN);
	}
	else{
		pen.CreatePen(PS_SOLID, style.size, bgcolor);
		pDC->SetROP2(R2_NOTCOPYPEN);
	}

	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(x_coord_1, y_coord_1);
	pDC->LineTo(x_coord_2, y_coord_2);
	pDC->SetROP2(rop);
	pDC->SelectObject(pOldPen);
}

void C2DGraphParametric::EraseDistance(const CString &EqOne,
								   const CString &EqTwo,
								   const long double &OneX,
								   const long double &TwoX,
								   const COLORREF bgcolor,
								   const CRect window, 
								   const SEquationStyle &style, 
								   CCalculator *g_Calculator,
								   CDC *pDC)
{
		
	long double y1, y2;
	if(g_Calculator->Compute(EqOne, "x", OneX, y1, 0) != SUCCESSFULL)	return;
	if(g_Calculator->Compute(EqTwo, "x", TwoX, y2, 0) != SUCCESSFULL)	return;
	
	int y_coord_1 = GraphToScreenY(window, y1);
	int x_coord_1 = GraphToScreenX(window, OneX, m_LinePrec); 
	int y_coord_2 = GraphToScreenY(window, y2);
	int x_coord_2 = GraphToScreenX(window, TwoX, m_LinePrec);
	
	CPen* pOldPen;
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, style.size, bgcolor);
	pOldPen = pDC->SelectObject(&penBlack);
	
	int rop = pDC->GetROP2();
	pDC->SetROP2(R2_NOT);          // Erases the previous line 
	pDC->MoveTo(x_coord_1, y_coord_1);
	pDC->LineTo(x_coord_2, y_coord_2);
	pDC->SelectObject(pOldPen);
	pDC->SetROP2(rop);
}


CString C2DGraphParametric::GetDistanceStr( const CString &EqOne,
										 const CString &EqTwo,
										 const long double &OneX,
										 const long double &TwoX,
										 CCalculator *g_Calculator)
{
	CString str;
	long double y1, y2;

	if(g_Calculator->Compute(EqOne, "x", OneX, y1, 0) != SUCCESSFULL)	return "";
	if(g_Calculator->Compute(EqTwo, "x", TwoX, y2, 0) != SUCCESSFULL)	return "";
	
	double distance = sqrt( pow((TwoX - OneX), 2) + pow((y2 - y1), 2) );
	g_Calculator->DecimalToStringSci(str, distance);
	return str;
}


*/



