#include "CalculatorView.h"

CDC* CGraphView::GetOffsetDC()
{
	CDC *pDC = GetDC();
	pDC->SetWindowOrg(0, m_fToolbarOn ? -ToolbarHeight() : 0);
	return pDC;
}

/*********************************************************/
// CGraphView::OnPaint() 
// Pre: none
// Post: redrawing is done
// Return Value: none
// Intent: called by the framework to handle redrawing of
//		   window
/*********************************************************/
void CGraphView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	/* NEEDED BECAUSE GOING INTO GRAPH OPTIONS MOVES
	   AND CHANGES THE SIZE OF THE WINDOW FOR SOME ODD REASON
	*/
	//CCalculatorView *pWnd = (CCalculatorView*)GetParent();
	//MoveWindow(&pWnd->m_PageRect); 
	// END POSITIONING OF WINDOW

	if(!m_Redraw){
		CDC *pDC = GetOffsetDC();
		DrawGraphBitmap(pDC);
		DrawText(pDC);
		DrawTrace(pDC);
		DrawDistance(pDC);
		ReleaseDC(pDC);
	}
	else{
		m_Redraw = false;
		//BeginWaitCursor();
		DrawAll();
		//EndWaitCursor();
	}

	GraphInfoBar(UpdateInfoBarEquationColors());

}

void CGraphView::DrawAll()
{
	DrawGraph(&m_MemBitmap);
	
	CDC *pDC = GetOffsetDC();
	DrawGraphBitmap(pDC);
	DrawText(pDC);
	DrawTrace(pDC);
	DrawDistance(pDC);	
	ReleaseDC(pDC);
}

void CGraphView::DrawText(CDC *pDC)
{
#ifdef GRAPH2D_INFOBAR
	if(m_fInfoBar)
		{
		UpdateInfoBar();
		UpdateInfoBarTrace();

		if(m_GraphDestination == SCRN)
			return;
		}
#endif
	
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = MemDC.SelectObject(&m_MemBitmap);
	
	pDC->SetTextColor(m_TextClr);
	CFont GraphFont;
	GraphFont.CreateFont(m_ActiveDrawFontSize.y, 0,
			0,0,FW_REGULAR,FALSE,FALSE,0,ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY, CLIP_DEFAULT_PRECIS, 
			DEFAULT_PITCH | FF_SWISS, 
			"Arial");
	CFont *pOldFont = pDC->SelectObject(&GraphFont);
	pDC->SetBkMode(TRANSPARENT);

	CSize pos;
	
	int text_height = m_ActiveDrawFontSize.y;

	//////////////////////////////
	// DRAW LOWER RIGHT TEXT ///
	//////////////////////////////
	
	int trace_y = text_height + 5;
	
	if(m_Trace){
		int dydx_y = text_height+trace_y+5;
		int height = (text_height*2)+4;
		
		//////// DRAW TRACE COORDINATES
		if(m_GraphDestination == SCRN)
			pDC->BitBlt(h_space, v_space + m_graph_height - dydx_y, m_graph_width, height, &MemDC, 0, m_graph_height - dydx_y, SRCCOPY);
		
		CString trace_coords(GetTraceCoordsStr());
		CString slope;

		switch(m_Mode){
		case EUCLIDEAN:
			{
				slope = GetDyDxStr(m_TraceEq, m_EuclideanGraph.GetTraceX());
				break;
			}
		case POLAR:
			{
				slope = GetDyDxStr(m_TraceEq, m_PolarGraph.GetTraceTheta());
				slope += "   " + m_PolarGraph.GetDrDthetaStr(m_Equations[m_TraceEq].eq, m_PolarGraph.GetTraceTheta(), m_Calculator);
				break;
			}
		case PARAMETRIC:
			{
				slope = "dy/dx = " + GetDyDxStr(m_TraceEq, m_ParametricGraph.m_TraceT);
				break;
			}
		}

		pDC->SetTextAlign(TA_RIGHT);
		
		switch(m_GraphDestination){
		case SCRN:
		case BMP:{
			pDC->TextOut(m_graph_width - 10, m_graph_height - trace_y, trace_coords);
			pDC->TextOut(m_graph_width - 10, m_graph_height - dydx_y, slope);
			break;
		}
		case PRINT:
			{
				
				pDC->TextOut(m_graph_width - (2*m_ActiveDrawFontSize.x), 
					m_graph_height - (2*m_ActiveDrawFontSize.y), 
					trace_coords);
				pDC->TextOut(m_graph_width - (2*m_ActiveDrawFontSize.x), 
					m_graph_height - (3*m_ActiveDrawFontSize.y), 
					slope);
				
				break;
		}
		}
		//////// END DRAW TRACE COORDINATES
	}
	
	if(m_FindArea){
		//////// DRAW AREA
		int area_y = (2*text_height)+trace_y+10;
		
		CString area(GetAreaStr());
		pDC->SetTextAlign(TA_RIGHT);

		switch(m_GraphDestination){
		case SCRN:	
		case BMP:	
			pDC->TextOut(m_graph_width - 10, m_graph_height - area_y, area);	break;
		case PRINT:
		{			
			pDC->TextOut(m_graph_width - (2*m_ActiveDrawFontSize.x), 
				m_graph_height - (4*m_ActiveDrawFontSize.y), 
				area);
			break;
		}
		}
		//////// END DRAW AREA
	}

	
	//////////////////////////////
	// DRAW UPPER LEFT TEXT ///
	//////////////////////////////
	
	if(m_CursorPos){
		//////// DRAW CURSOR POSITION
		if(m_GraphDestination == SCRN)
			pDC->BitBlt(h_space, v_space + 10, m_graph_width, text_height, &MemDC, 0, 10, SRCCOPY);

		CString cursor(GetCursorPosStr());
		pDC->SetTextAlign(TA_LEFT);

		switch(m_GraphDestination){
		case SCRN:	
		case BMP:	
			pDC->TextOut(10, 10, cursor);	break;
		case PRINT:
		{
			pDC->TextOut(2*m_ActiveDrawFontSize.x, 
				m_ActiveDrawFontSize.y, 
				cursor);
			break;
		}
		}
		//////// END CURSOR POSITION
	}
	
	if(m_Distance == SECOND || m_Distance == DONE){
		//////// DRAW DISTANCE
		int dist_y = text_height+12;
		
		if(m_GraphDestination == SCRN)
			pDC->BitBlt(h_space, v_space + dist_y, m_graph_width, text_height, &MemDC, 0, dist_y, SRCCOPY);

		CString distance;
		distance = "Distance = " + GetDistanceStr();
		pDC->SetTextAlign(TA_LEFT);

		switch(m_GraphDestination){
		case SCRN:	
		case BMP:	
			pDC->TextOut(10, dist_y, distance);	break;
		case PRINT:
		{
			pDC->TextOut(2*m_ActiveDrawFontSize.x, 
				2*m_ActiveDrawFontSize.y, 
				distance);
			break;
		}
		}
		//////// END DRAW DISTANCE
	}

	pDC->SelectObject(pOldFont); 
	MemDC.SelectObject(pOldBitmap);
	DeleteDC(MemDC);
}

void CGraphView::DrawGraphBitmap(CDC *pDC)
{	
	// Copy Bitmap to screen //
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = MemDC.SelectObject(&m_MemBitmap);
	pDC->BitBlt(h_space,v_space, m_graph_width, m_graph_height, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	DeleteDC(MemDC);
}


/*********************************************************/
// CGraphView::DrawGraph()
// Pre: InitVariables is called
// Post: graph is drawn
// Return Value: none
// Intent: to draw the graph and control al portions of the
//		   drawing, calls each component to be drawn
/*********************************************************/
void CGraphView::DrawGraph(CBitmap *bitmap)
{
	ValidateRanges();
	
	CDC *pDC = GetDC();
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	if(bitmap->m_hObject != NULL)
		bitmap->DeleteObject();

	bitmap->CreateCompatibleBitmap(pDC, m_graph_width, m_graph_height);
	CBitmap *pOldBitmap = MemDC.SelectObject(bitmap);

	// Draw Graph BG //
	CBrush brush(m_BackgroundClr), *pOldBrush;
	pOldBrush = MemDC.SelectObject(&brush);
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 0, RGB(0,0,0));
	CPen* pOldPen = MemDC.SelectObject(&penBlack);
	
	MemDC.Rectangle(0, 0, m_graph_width, m_graph_height);

	MemDC.SelectObject(pOldBrush);
	MemDC.SelectObject(pOldPen);
	pOldBrush = 0;
	delete pOldBrush;

	// Set clip rectangle //
	m_GraphRgn.SetRectRgn(1, 1, m_graph_width - 1, m_graph_height - 1);
	m_GraphThreshold = CRect(0, 0 - threshold, m_graph_width, m_graph_height + threshold);
	MemDC.SelectClipRgn(&m_GraphRgn);
	
	// Draw PARTS OF GRAPH //
	DrawArea(&MemDC);

	if(m_Grid)
		DrawGrid(&MemDC);
	if(m_Coords)
		DrawCoordsLabels(&MemDC);
	if(m_Axis)
		DrawAxis(&MemDC);
	
	DrawEquations(&MemDC);
	
	MemDC.SelectObject(&pOldBitmap);
	DeleteDC(MemDC);
	ReleaseDC(pDC);
}

void CGraphView::DrawEquations(CDC *pDC)
{
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	
	// loop through eah equation
	for(int i(0); i < (m_Mode == PARAMETRIC ? 5 : 10); ++i){
					
		switch(m_Mode){
		case EUCLIDEAN:
			{
				if(!m_Equations[i].disp)
					continue;
					
				if(m_EuclideanGraph.DrawEquation(m_Equations[i], m_Style, 
					CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space), 
					m_Calculator, pDC)){
						
					if(m_TangentLine[i])
						DrawTangentLine(i, pDC);
				}
				else
					{
					m_Equations[i].disp = false;
					GraphInfoBar(UpdateInfoBarEquation(i));
					}
				break;
			}
		case POLAR:
			{
				if(!m_Equations[i].disp)
					continue;
					
				if(m_PolarGraph.DrawEquation(m_Equations[i],  m_Style, 
					CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space), 
					m_Calculator, pDC)){
					
					if(m_TangentLine[i])
						DrawTangentLine(i, pDC);
				}
				else
					{
					m_Equations[i].disp = false;
					GraphInfoBar(UpdateInfoBarEquation(i));
					}
				break;
			}
		case PARAMETRIC:
			{
					
				if(!m_ParametricGraph.m_Equations[i].disp)
					continue;
				
				if(m_ParametricGraph.DrawEquation(i,  m_Style, 
					CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space), 
					pDC)){
					if(m_TangentLine[i])
						DrawTangentLine(i, pDC);
				}
				else
					{
					m_ParametricGraph.m_Equations[i].disp = false;
					GraphInfoBar(UpdateInfoBarEquation(i));
					}
				break;
			}
		}
	}	

	m_Calculator->m_base = old_base;
}

void CGraphView::DrawTangentLine(int eq, CDC *pDC)
{
	switch(m_Mode){
	case EUCLIDEAN:
		{
			m_EuclideanGraph.DrawTangentLine(m_Equations[eq], 
				m_Tangent[eq], m_Style, 
				CRect(0, 0, m_graph_width, m_graph_height ), 
				m_Calculator, m_GraphDestination, pDC);
			break;
		}
	case POLAR:
		{
			m_PolarGraph.DrawTangentLine(m_Equations[eq], 
				m_Tangent[eq], m_Style,  
				CRect(0, 0, m_graph_width, m_graph_height), 
				m_Calculator, m_GraphDestination, pDC);
			break;
		}
	case PARAMETRIC:
		{
			m_ParametricGraph.DrawTangentLine(eq, 
				m_Tangent[eq], m_Style, 
				CRect(0, 0, m_graph_width, m_graph_height ), 
				pDC);
			break;
		}
	}
}


void CGraphView::DrawCoordsLabels(CDC *pDC)
{
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	switch(m_Mode){
	case EUCLIDEAN:
		{
			m_EuclideanGraph.DrawCoordsLabels(m_ActiveDrawFontSize.y, m_Coords, m_Labels, m_CoordsClr, 
				CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space), 
				m_GraphDestination, pDC);
			break;
		}
	case POLAR:
		{
			m_PolarGraph.DrawCoordsLabels(m_ActiveDrawFontSize.y, m_Coords, m_Labels,  m_CoordsClr, 
				CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space), 
				m_GraphDestination, pDC);
			break;
		}
	case PARAMETRIC:
		{
			m_ParametricGraph.DrawCoordsLabels(m_ActiveDrawFontSize.y, m_Coords, m_Labels,  m_CoordsClr, 
				CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space), 
				m_GraphDestination, pDC);
			break;
		}
	}
	m_Calculator->m_base = old_base;
}


/*********************************************************/
// CGraphView::DrawAxis(CDC *pDC)
// Pre: none
// Post: axis are drawn on m_MemBitmap
// Return Value: none
// Intent: to draw the axis of the graph
/*********************************************************/
void CGraphView::DrawAxis(CDC *pDC)
{
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	switch(m_Mode){
	case EUCLIDEAN:
		{			
			m_EuclideanGraph.DrawAxis(m_AxisStyle, 
				CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space), 
				pDC);
			break;
		}
	case POLAR: 
		{ 
			m_PolarGraph.DrawAxis(m_AxisStyle,  
				CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space), 
				pDC);
			break; 
		}
	case PARAMETRIC: 
		{ 
			m_ParametricGraph.DrawAxis(m_AxisStyle,  
				CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space), 
				pDC);
			break; 
		}
	}
	m_Calculator->m_base = old_base;
}
	
/*********************************************************/
// CGraphView::DrawGrid(CDC *pDC)
// Pre: m_EuclideanGraph.m_EuclideanRange.Xmax > m_EuclideanGraph.m_EuclideanRange.Xmin && m_EuclideanGraph.m_EuclideanRange.Ymax > m_EuclideanGraph.m_EuclideanRange.Ymin
// Post: grid or has marks are drawn on graph
// Return Value: none
// Intent: to draw hash marks on graph, or if 
//		   m_Grid is true draw a grid too
/*********************************************************/
void CGraphView::DrawGrid(CDC *pDC)
{
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	switch(m_Mode){
	case EUCLIDEAN:
		{
			m_EuclideanGraph.DrawGrid(m_GridStyle, m_Grid, 
				CRect(0, 0, m_graph_width, m_graph_height ),
				pDC, m_GraphDestination, m_ActiveDrawFontSize.y, m_CoordsClr, m_nGridLabelInterval); 				
			break;
		}
	case POLAR: 
		{ 
			m_PolarGraph.DrawGrid(m_GridStyle,  
				CRect(0, 0, m_graph_width, m_graph_height), 
				pDC, m_Calculator); 
			break; 
		}
	case PARAMETRIC: 
		{ 
			m_ParametricGraph.DrawGrid(m_GridStyle,  m_Grid,
				CRect(0, 0, m_graph_width, m_graph_height), pDC, 
				m_GraphDestination, m_ActiveDrawFontSize.y, m_CoordsClr, m_nGridLabelInterval); 
			break; 
		}
	}
	m_Calculator->m_base = old_base;
}

/*********************************************************/
// CGraphView::DrawArea(CDC *pDC)
// Pre: none
// Post: shaded area is drawn
// Return Value: none
// Intent: to shade the area being calculated and to 
//		   display the value of the area on the graph
/*********************************************************/
void CGraphView::DrawArea(CDC *pDC)
{	
	if(!m_FindArea)
		return;
	
	Assert(m_Mode == EUCLIDEAN);

	if(m_AreaEq2 != -1 && !m_Equations[m_AreaEq2].disp){
		m_FindArea = false;
		return;
	}

	if(m_Equations[m_AreaEq].disp){

		ErrorT error;
		int old_base = m_Calculator->m_base;
		m_Calculator->m_base = 10;
		g_Calculator->SetErrorMode(ERROR_MODE_SILENT);

		long double x_ratio = double((m_EuclideanGraph.m_EuclideanRange.Xmax-m_EuclideanGraph.m_EuclideanRange.Xmin))/double(m_graph_width);
		long double y_ratio = double((m_EuclideanGraph.m_EuclideanRange.Ymax-m_EuclideanGraph.m_EuclideanRange.Ymin))/double(m_graph_height);
		int num_points = int((double(m_EuclideanGraph.GetLinePrec())/100.0)*m_graph_width);
		int total_pts = num_points + 1;
		double increment = (m_EuclideanGraph.m_EuclideanRange.Xmax-m_EuclideanGraph.m_EuclideanRange.Xmin) / num_points;
		
		++num_points;
		int j = (double(m_AreaXmin - m_EuclideanGraph.m_EuclideanRange.Xmin)/double(m_EuclideanGraph.m_EuclideanRange.Xmax-m_EuclideanGraph.m_EuclideanRange.Xmin)) * double(num_points);
		num_points *= ((m_AreaXmax-m_AreaXmin)/(m_EuclideanGraph.m_EuclideanRange.Xmax-m_EuclideanGraph.m_EuclideanRange.Xmin));
		
		int end_pt = num_points + j;
		int x_axis_coord = int(m_EuclideanGraph.m_EuclideanRange.Ymax / y_ratio);	

		// calculation of points
		for(j; j < end_pt; ++j){
			
			long double next_y1, next_y2;
			int y_coord_1, y_coord_2;
			
			// first equation
			CArray<VariableT, VariableT> mmvariables; 
			
			mmvariables.Add(GetVariable("x" , (m_EuclideanGraph.m_EuclideanRange.Xmin + (j*increment))));
			if((error = m_Calculator->Compute(m_Equations[m_AreaEq].eq, &mmvariables, next_y1, this->m_hWnd)) != SUCCESSFULL)
				{
				if(DIV_ZERO == error)
					continue; // just skip this line
				else
					break;
				}

			if(-HUGE_VAL == next_y1 || HUGE_VAL == next_y1)
				y_coord_1 = -1;
			else
				y_coord_1 = GraphToScreenY(next_y1);
			////////////////

			if(m_AreaEq2 != -1)
			{
				// second equation
				CArray<VariableT, VariableT> mmvariables; 
				
				mmvariables.Add(GetVariable("x" , (m_EuclideanGraph.m_EuclideanRange.Xmin + (j*increment))));
				if((error = m_Calculator->Compute(m_Equations[m_AreaEq2].eq, &mmvariables, next_y2, this->m_hWnd)) != SUCCESSFULL)
					{
					if(DIV_ZERO == error)
						continue; // just skip this line
					else
						break;
					}
				
				if(-HUGE_VAL == next_y2 || HUGE_VAL == next_y2)
					y_coord_2 = -1;
				else
					y_coord_2 = GraphToScreenY(next_y2);
			}
			else
				y_coord_2 = x_axis_coord;
			
			CPen *pen = new CPen, *pOldPen;
			pen->CreatePen(PS_SOLID, 1, m_AreaClr);
			pOldPen = pDC->SelectObject(pen);
			
			if(-1 != y_coord_1 && -1 != y_coord_2){
				pDC->MoveTo(1+(j * m_graph_width / total_pts), y_coord_1);
				pDC->LineTo(1+(j * m_graph_width / total_pts), y_coord_2);
			}
			
			pDC->SelectObject(pOldPen);
			delete pen;	

			m_Calculator->m_base = old_base;
		}

		g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	}
}
CString CGraphView::GetAreaStr()
{
	CString str;
	if(-HUGE_VAL == m_Area || HUGE_VAL == m_Area)
		str = "Area = infinitely large";
	else
		str.Format("Area = %.4f", m_Area);
	return str;
}

/*********************************************************/
// CGraphView::DrawCursorPos(CPoint point)
// Pre: none
// Post: none
// Return Value: none
// Intent: to redisplay the graph with the cursor position
//		   displayed
/*********************************************************/
CString CGraphView::GetCursorPosStr()
{
	CString str;
	if(m_cursor_pos.x > h_space && m_cursor_pos.x < (h_space + m_graph_width) &&
		m_cursor_pos.y > v_space && m_cursor_pos.y < (v_space + m_graph_height)){	

		switch(m_Mode){
		case PARAMETRIC:
		case EUCLIDEAN:
			str.Format("X = %.5f, Y = %.5f", ScreenToGraphX(m_cursor_pos.x, 100), ScreenToGraphY(m_cursor_pos.y));
			break;
		case POLAR:
			long double x(ScreenToGraphX(m_cursor_pos.x, 100)), y(ScreenToGraphY(m_cursor_pos.y));
			long double theta=0, r;
	
			r = sqrt(powf(x, 2.0) + powf(y,2.0));

			if(y == 0 && x == 0)
				theta = 0;
			else if(y == 0 && x > 0)
				theta = 0;
			else if(y > 0 && x > 0)
				theta = atan(y/x);
			else if(y > 0 && x == 0)
				theta = PI/2.0;
			else if(y > 0 && x < 0)
				theta = PI - m_Calculator->abs(atan(y/x));
			else if(y == 0 && x < 0)
				theta = PI;
			else if(y < 0 && x < 0)
				theta = m_Calculator->abs(atan(y/x)) + PI;
			else if(y < 0 && x == 0)
				theta = PI + (PI/2.0);
			else if(y < 0 && x > 0)
				theta = (PI - m_Calculator->abs(atan(y/x))) + PI;

			str.Format("X = %.5f, Y = %.5f, R = %.5f, Theta = %.5f", x, y, r, theta);
			break;
		}
	}
	return str;
}

/*********************************************************/
// CGraphView::DrawTrace()
// Pre: none
// Post: the tracing cross is drawn
// Return Value: none
// Intent: to draw the cross for tracing and display the
//		   DY/DX at the current tracing point
/*********************************************************/
void CGraphView::DrawTrace(CDC *pDC)
{
	if(!m_Trace)
		return;
	
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	
	m_GraphRgn.SetRectRgn(1, 1, m_graph_width - 1, m_graph_height - 1);
	pDC->SelectClipRgn(&m_GraphRgn);

	CRect window(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space);

	CPen *pen = new CPen;
	pen->CreatePen(PS_SOLID, m_Style.size + 1, RGB(0,0,0));

	switch(m_Mode){
	case EUCLIDEAN:
		{
			if(m_GraphDestination == SCRN)
				m_EuclideanGraph.ClearPrevTrace(m_Equations[m_PrevTraceEq].eq,
												m_MemBitmap,
												window,
												m_Calculator,
												pDC);
			
			if(TRACE_PAN == m_EuclideanGraph.DrawTrace(m_Equations[m_TraceEq].eq,
												window,
												m_GraphDestination,
												m_Calculator,
												pen,
												pDC)){

				RePaintNow();
				return;
			}
			break;
		}
		
	case POLAR:
		{
			if(m_GraphDestination == SCRN)
				m_PolarGraph.ClearPrevTrace(m_Equations[m_PrevTraceEq].eq,
												m_MemBitmap,
												window,
												m_Calculator,
												pDC);
			
			if(TRACE_PAN == m_PolarGraph.DrawTrace(m_Equations[m_TraceEq].eq,
												window,
												m_GraphDestination,
												m_Calculator,
												pen,
												pDC)){

				RePaintNow();
				return;
			}
			break;
		}
	case PARAMETRIC:
		{
			if(m_GraphDestination == SCRN)
				m_ParametricGraph.ClearPrevTrace(m_PrevTraceEq,
												m_MemBitmap,
												window,
												pDC);
			
			if(TRACE_PAN == m_ParametricGraph.DrawTrace(m_TraceEq,
														window,
														m_GraphDestination,
														pen,
														pDC)){

				RePaintNow();
				return;
			}
			break;
		}
	}

	delete pen;

	m_Calculator->m_base = old_base;
}

void CGraphView::EraseDistance(CDC *pDC)
{
	if(m_Distance != SECOND)
		return;
		
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	
	switch(m_Mode){
	case EUCLIDEAN:
		{
			m_EuclideanGraph.EraseDistance(m_Equations[m_DistanceEqOne].eq,
				m_Equations[m_PrevTraceEq].eq,
				m_DistanceOneX,
				m_DistancePrevX,
				m_BackgroundClr,
				CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space),
				m_Style,
				m_Calculator,
				pDC); 
			
			break;
		}
	case POLAR:
		{
			m_PolarGraph.EraseDistance(m_Equations[m_DistanceEqOne].eq,
				m_Equations[m_PrevTraceEq].eq,
				m_BackgroundClr,
				CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space),
				m_Style,
				m_Calculator,
				pDC); 
			break;
		}
	case PARAMETRIC:
		{
			;
			break;
		}
	}
		
	m_DistancePrevX = m_DistanceTwoX;
	m_Calculator->m_base = old_base;
}

void CGraphView::DrawDistance(CDC *pDC)
{
	if(m_Distance != SECOND && m_Distance != DONE) return;

	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	switch(m_Mode){
	case EUCLIDEAN:
		{
			m_EuclideanGraph.DrawDistance(m_Distance, 
										  m_Equations[m_DistanceEqOne].eq,
										  m_Equations[m_DistanceEqTwo].eq,
										  m_DistanceOneX,
										  m_DistanceTwoX,
										  m_BackgroundClr,
										  CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space),
										  m_GraphDestination,
										  m_Style,
										  m_Calculator,
										  pDC); 
			
			break;
		}
	case POLAR:
		{
			m_PolarGraph.DrawDistance(m_Distance, 
										  m_Equations[m_DistanceEqOne].eq,
										  m_Equations[m_DistanceEqTwo].eq,
										  m_BackgroundClr,
										  CRect(h_space, v_space, m_graph_width + h_space, m_graph_height + v_space),
										  m_GraphDestination,
										  m_Style,
										  m_Calculator,
										  pDC); 
			break;
		}
	case PARAMETRIC:
		{
			;
			break;
		}
	}
	m_Calculator->m_base = old_base;
}

CString CGraphView::GetDistanceStr()
{
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;
	switch(m_Mode){
	case EUCLIDEAN:
		{
			return m_EuclideanGraph.GetDistanceStr(m_Equations[m_DistanceEqOne].eq,
									  m_Equations[m_DistanceEqTwo].eq,
										  m_DistanceOneX,
										  m_DistanceTwoX,
										  m_Calculator); 
			
			break;
		}
	case POLAR:
		{
			return m_PolarGraph.GetDistanceStr(m_Equations[m_DistanceEqOne].eq,
									  m_Equations[m_DistanceEqTwo].eq,
									  m_Calculator); 
			break;
		}
	case PARAMETRIC:
		{
			;
			break;
		}
	}
	m_Calculator->m_base = old_base;
	return "";
}

/*********************************************************/
// CGraphView::DrawDyDx(long double x)
// Return Value: none
// Intent: to determine the slope at the current point
/*********************************************************/
CString CGraphView::GetDyDxStr(UINT nEq, long double x)
{
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	g_Calculator->SetErrorMode(ERROR_MODE_SILENT);

	switch(m_Mode){
	case EUCLIDEAN: 	return m_EuclideanGraph.GetDyDxStr(m_Equations[nEq].eq, x);
	case POLAR: 		return m_PolarGraph.GetDyDxStr(m_Equations[nEq].eq, x, m_Calculator); // x is really theta here
	case PARAMETRIC: 	return m_ParametricGraph.GetDyDxStr(nEq, x); // x is really t here
	}

	g_Calculator->SetErrorMode(ERROR_MODE_COMPLETE);
	g_Calculator->m_base = old_base;
	return "";
}

CString CGraphView::GetTraceCoordsStr()
{
	int old_base = m_Calculator->m_base;
	m_Calculator->m_base = 10;

	switch(m_Mode){
	case EUCLIDEAN: 	return m_EuclideanGraph.GetTraceCoordsStr(m_Equations[m_TraceEq].eq, m_Calculator);
	case POLAR: 		return m_PolarGraph.GetTraceCoordsStr(m_Equations[m_TraceEq].eq, m_Calculator);
	case PARAMETRIC: 	return m_ParametricGraph.GetTraceCoordsStr(m_TraceEq);
	}

	m_Calculator->m_base = old_base;
	return "";
}
