void CGraphView::HandPan(int x_dpixels, int y_dpixels)
{
	StoreCurrentRange();

	double x_change = x_dpixels*GetXPixelIncrement();
	double y_change = y_dpixels*GetYPixelIncrement();

	switch(m_Mode){
	case EUCLIDEAN:
		{	
		m_EuclideanGraph.m_EuclideanRange.Xmin += x_change;
		m_EuclideanGraph.m_EuclideanRange.Xmax += x_change;
		m_EuclideanGraph.m_EuclideanRange.Ymin += y_change;
		m_EuclideanGraph.m_EuclideanRange.Ymax += y_change;
		break;
		}
	case POLAR:
		{
		m_PolarGraph.m_PolarRange.Xmin += x_change;
		m_PolarGraph.m_PolarRange.Xmax += x_change;
		m_PolarGraph.m_PolarRange.Ymin += y_change;
		m_PolarGraph.m_PolarRange.Ymax += y_change;
		break;
		}
	case PARAMETRIC:
		{
		m_ParametricGraph.m_Xmin += x_change;
		m_ParametricGraph.m_Xmax += x_change;
		m_ParametricGraph.m_Ymin += y_change;
		m_ParametricGraph.m_Ymax += y_change;
		break;
		}
		}
	RePaintNow();
}


void CGraphView::ZoomRect()
{
	StoreCurrentRange();
	
	switch(m_Mode){
	case EUCLIDEAN:
		{			
			double x_increment = (m_EuclideanGraph.m_EuclideanRange.Xmax - m_EuclideanGraph.m_EuclideanRange.Xmin) / double(m_graph_width);
			double y_increment = (m_EuclideanGraph.m_EuclideanRange.Ymax - m_EuclideanGraph.m_EuclideanRange.Ymin) / double(m_graph_height);
			
			long double Ymax, Ymin, Xmax, Xmin;
			
			if(m_ZoomPt.x > m_ZoomPrevPt.x){
				if((m_ZoomPt.x - m_ZoomPrevPt.x) < 10)
					return;
				Xmax = ((m_ZoomPt.x - h_space) * x_increment) + m_EuclideanGraph.m_EuclideanRange.Xmin;
				Xmin = ((m_ZoomPrevPt.x - h_space) * x_increment) + m_EuclideanGraph.m_EuclideanRange.Xmin;
			}
			else{
				if((m_ZoomPrevPt.x - m_ZoomPt.x) < 10)
					return;
				Xmax = ((m_ZoomPrevPt.x - h_space) * x_increment) + m_EuclideanGraph.m_EuclideanRange.Xmin;
				Xmin = ((m_ZoomPt.x - h_space) * x_increment) + m_EuclideanGraph.m_EuclideanRange.Xmin;
			}
			if(m_ZoomPt.y < m_ZoomPrevPt.y){
				if((m_ZoomPrevPt.y - m_ZoomPt.y) < 10)
					return;
				Ymax = -(((m_ZoomPt.y - v_space) * y_increment) - m_EuclideanGraph.m_EuclideanRange.Ymax);
				Ymin = -(((m_ZoomPrevPt.y - v_space) * y_increment) - m_EuclideanGraph.m_EuclideanRange.Ymax);
			}
			else{
				if((m_ZoomPt.y - m_ZoomPrevPt.y) < 10)
					return;
				Ymax = -(((m_ZoomPrevPt.y - v_space) * y_increment) - m_EuclideanGraph.m_EuclideanRange.Ymax);
				Ymin = -(((m_ZoomPt.y - v_space) * y_increment) - m_EuclideanGraph.m_EuclideanRange.Ymax);
			}
			
			if(!ValidateIncrement(Xmin, Xmax, Ymin, Ymax))
				return;
			
			m_EuclideanGraph.m_EuclideanRange.Xmin = Xmin;
			m_EuclideanGraph.m_EuclideanRange.Xmax = Xmax;
			m_EuclideanGraph.m_EuclideanRange.Ymin = Ymin;
			m_EuclideanGraph.m_EuclideanRange.Ymax = Ymax;
			
			if(!m_FixedGrid){
				m_EuclideanGraph.m_EuclideanRange.Yscl = (m_EuclideanGraph.m_EuclideanRange.Ymax - m_EuclideanGraph.m_EuclideanRange.Ymin) / 10.0;
				m_EuclideanGraph.m_EuclideanRange.Xscl = (m_EuclideanGraph.m_EuclideanRange.Xmax - m_EuclideanGraph.m_EuclideanRange.Xmin) / 10.0;
			}
			break;
		}
	case POLAR:
		{
			double x_increment = (m_PolarGraph.m_PolarRange.Xmax - m_PolarGraph.m_PolarRange.Xmin) / double(m_graph_width);
			double y_increment = (m_PolarGraph.m_PolarRange.Ymax - m_PolarGraph.m_PolarRange.Ymin) / double(m_graph_height);
			
			long double Ymax, Ymin, Xmax, Xmin;
			
			if(m_ZoomPt.x > m_ZoomPrevPt.x){
				if((m_ZoomPt.x - m_ZoomPrevPt.x) < 10)
					return;
				Xmax = ((m_ZoomPt.x - h_space) * x_increment) + m_PolarGraph.m_PolarRange.Xmin;
				Xmin = ((m_ZoomPrevPt.x - h_space) * x_increment) + m_PolarGraph.m_PolarRange.Xmin;
			}
			else{
				if((m_ZoomPrevPt.x - m_ZoomPt.x) < 10)
					return;
				Xmax = ((m_ZoomPrevPt.x - h_space) * x_increment) + m_PolarGraph.m_PolarRange.Xmin;
				Xmin = ((m_ZoomPt.x - h_space) * x_increment) + m_PolarGraph.m_PolarRange.Xmin;
			}
			if(m_ZoomPt.y < m_ZoomPrevPt.y){
				if((m_ZoomPrevPt.y - m_ZoomPt.y) < 10)
					return;
				Ymax = -(((m_ZoomPt.y - v_space) * y_increment) - m_PolarGraph.m_PolarRange.Ymax);
				Ymin = -(((m_ZoomPrevPt.y - v_space) * y_increment) - m_PolarGraph.m_PolarRange.Ymax);
			}
			else{
				if((m_ZoomPt.y - m_ZoomPrevPt.y) < 10)
					return;
				Ymax = -(((m_ZoomPrevPt.y - v_space) * y_increment) - m_PolarGraph.m_PolarRange.Ymax);
				Ymin = -(((m_ZoomPt.y - v_space) * y_increment) - m_PolarGraph.m_PolarRange.Ymax);
			}
			
			if(!ValidateIncrement(Xmin, Xmax, Ymin, Ymax))
				return;
			
			m_PolarGraph.m_PolarRange.Xmin = Xmin;
			m_PolarGraph.m_PolarRange.Xmax = Xmax;
			m_PolarGraph.m_PolarRange.Ymin = Ymin;
			m_PolarGraph.m_PolarRange.Ymax = Ymax;

			break;
		}
	case PARAMETRIC:
		{			
			double x_increment = (m_ParametricGraph.m_Xmax - m_ParametricGraph.m_Xmin) / double(m_graph_width);
			double y_increment = (m_ParametricGraph.m_Ymax - m_ParametricGraph.m_Ymin) / double(m_graph_height);
			
			long double Ymax, Ymin, Xmax, Xmin;
			
			if(m_ZoomPt.x > m_ZoomPrevPt.x){
				if((m_ZoomPt.x - m_ZoomPrevPt.x) < 10)
					return;
				Xmax = ((m_ZoomPt.x - h_space) * x_increment) + m_ParametricGraph.m_Xmin;
				Xmin = ((m_ZoomPrevPt.x - h_space) * x_increment) + m_ParametricGraph.m_Xmin;
			}
			else{
				if((m_ZoomPrevPt.x - m_ZoomPt.x) < 10)
					return;
				Xmax = ((m_ZoomPrevPt.x - h_space) * x_increment) + m_ParametricGraph.m_Xmin;
				Xmin = ((m_ZoomPt.x - h_space) * x_increment) + m_ParametricGraph.m_Xmin;
			}
			if(m_ZoomPt.y < m_ZoomPrevPt.y){
				if((m_ZoomPrevPt.y - m_ZoomPt.y) < 10)
					return;
				Ymax = -(((m_ZoomPt.y - v_space) * y_increment) - m_ParametricGraph.m_Ymax);
				Ymin = -(((m_ZoomPrevPt.y - v_space) * y_increment) - m_ParametricGraph.m_Ymax);
			}
			else{
				if((m_ZoomPt.y - m_ZoomPrevPt.y) < 10)
					return;
				Ymax = -(((m_ZoomPrevPt.y - v_space) * y_increment) - m_ParametricGraph.m_Ymax);
				Ymin = -(((m_ZoomPt.y - v_space) * y_increment) - m_ParametricGraph.m_Ymax);
			}
			
			if(!ValidateIncrement(Xmin, Xmax, Ymin, Ymax))
				return;
			
			m_ParametricGraph.m_Xmin = Xmin;
			m_ParametricGraph.m_Xmax = Xmax;
			m_ParametricGraph.m_Ymin = Ymin;
			m_ParametricGraph.m_Ymax = Ymax;
			
			if(!m_FixedGrid){
				m_ParametricGraph.m_Yscl = (m_ParametricGraph.m_Ymax - m_ParametricGraph.m_Ymin) / 10.0;
				m_ParametricGraph.m_Xscl = (m_ParametricGraph.m_Xmax - m_ParametricGraph.m_Xmin) / 10.0;
			}
			break;
		}
	}

	RePaintNow();
}

void CGraphView::ScrollZoom(short amount)
{
	long double zoom_amount;
	if(amount <= 0)
		zoom_amount = (m_ZoomPerc / 100.0);
	else
		zoom_amount = (100.0 / double(m_ZoomPerc));

	ZoomXY(zoom_amount);
	RePaintNow();
}

void CGraphView::OnGraphZoomInXY() 
{
	StoreCurrentRange();
	long double zoom_amount = (100.0 / double(m_ZoomPerc));
	ZoomXY(zoom_amount);
	
	RePaintNow();
}

void CGraphView::OnGraphZoomOutXY() 
{
	StoreCurrentRange();
	long double zoom_amount = (m_ZoomPerc / 100.0);
	ZoomXY(zoom_amount);
	RePaintNow();
}

void CGraphView::ZoomXY(long double zoom_amount)
{
	StoreCurrentRange();
	ZoomX(zoom_amount);
	ZoomY(zoom_amount);
	if(!m_FixedGrid && m_Mode == POLAR)
		m_PolarGraph.m_PolarRange.GridRadius = m_PolarGraph.m_PolarRange.GridRadius * zoom_amount;
}

void CGraphView::OnGraphZoomInX() 
{
	StoreCurrentRange();
	long double zoom_amount = (100.0 / double(m_ZoomPerc));
	ZoomX(zoom_amount);	
	RePaintNow();
}

void CGraphView::OnGraphZoomInY() 
{
	StoreCurrentRange();
	long double zoom_amount = (100.0 / double(m_ZoomPerc));
	ZoomY(zoom_amount);
	RePaintNow();
}

void CGraphView::OnGraphZoomOutX() 
{
	StoreCurrentRange();
	long double zoom_amount = (m_ZoomPerc / 100.0);
	ZoomX(zoom_amount);
	RePaintNow();
}

void CGraphView::OnGraphZoomOutY() 
{
	StoreCurrentRange();
	long double zoom_amount = (m_ZoomPerc / 100.0);
	ZoomY(zoom_amount);
	RePaintNow();
}

void CGraphView::ZoomX(long double zoom_amount) 
{
	switch(m_Mode){
	case EUCLIDEAN:
		{
			long double x_mid = (m_EuclideanGraph.m_EuclideanRange.Xmax +m_EuclideanGraph.m_EuclideanRange.Xmin)/2.0, 
					    y_mid = (m_EuclideanGraph.m_EuclideanRange.Ymax +m_EuclideanGraph.m_EuclideanRange.Ymin)/2.0;
			long double x_range(m_EuclideanGraph.m_EuclideanRange.Xmax-m_EuclideanGraph.m_EuclideanRange.Xmin), 
				        y_range(m_EuclideanGraph.m_EuclideanRange.Ymax-m_EuclideanGraph.m_EuclideanRange.Ymin);
			
			if(!ValidateIncrement(x_mid - (x_range * zoom_amount)/2.0, 
				x_mid + (x_range * zoom_amount)/2.0, 
				y_mid - (y_range * zoom_amount)/2.0, 
				y_mid + (y_range * zoom_amount)/2.0))
				return;
			
			if((m_EuclideanGraph.m_EuclideanRange.Xmax > 99999999999999999 || m_EuclideanGraph.m_EuclideanRange.Xmin < -99999999999999999) && zoom_amount > 1)
				return;
			
			m_EuclideanGraph.m_EuclideanRange.Xmax = x_mid + (x_range * zoom_amount)/2.0;
			m_EuclideanGraph.m_EuclideanRange.Xmin = x_mid - (x_range * zoom_amount)/2.0;
			
			if(!m_FixedGrid)
				m_EuclideanGraph.m_EuclideanRange.Xscl = m_EuclideanGraph.m_EuclideanRange.Xscl * zoom_amount;
			break;
		}
	case POLAR:
		{
			long double x_mid = (m_PolarGraph.m_PolarRange.Xmax +m_PolarGraph.m_PolarRange.Xmin)/2.0, 
				        y_mid = (m_PolarGraph.m_PolarRange.Ymax +m_PolarGraph.m_PolarRange.Ymin)/2.0;
			long double x_range(m_PolarGraph.m_PolarRange.Xmax-m_PolarGraph.m_PolarRange.Xmin), 
				        y_range(m_PolarGraph.m_PolarRange.Ymax-m_PolarGraph.m_PolarRange.Ymin);
			
			if((m_PolarGraph.m_PolarRange.Xmax > 99999999999999999 || m_PolarGraph.m_PolarRange.Xmin < -99999999999999999) && zoom_amount > 1)
				return;
			
			m_PolarGraph.m_PolarRange.Xmax = x_mid + (x_range * zoom_amount)/2.0;
			m_PolarGraph.m_PolarRange.Xmin = x_mid - (x_range * zoom_amount)/2.0;			
			break;
		}
	case PARAMETRIC:
		{
			long double x_mid = (m_ParametricGraph.m_Xmax +m_ParametricGraph.m_Xmin)/2.0, 
					    y_mid = (m_ParametricGraph.m_Ymax +m_ParametricGraph.m_Ymin)/2.0;
			long double x_range(m_ParametricGraph.m_Xmax-m_ParametricGraph.m_Xmin), 
				        y_range(m_ParametricGraph.m_Ymax-m_ParametricGraph.m_Ymin);
			
			if(!ValidateIncrement(x_mid - (x_range * zoom_amount)/2.0, 
				x_mid + (x_range * zoom_amount)/2.0, 
				y_mid - (y_range * zoom_amount)/2.0, 
				y_mid + (y_range * zoom_amount)/2.0))
				return;
			
			if((m_ParametricGraph.m_Xmax > 99999999999999999 || m_ParametricGraph.m_Xmin < -99999999999999999) && zoom_amount > 1)
				return;
			
			m_ParametricGraph.m_Xmax = x_mid + (x_range * zoom_amount)/2.0;
			m_ParametricGraph.m_Xmin = x_mid - (x_range * zoom_amount)/2.0;
			
			if(!m_FixedGrid)
				m_ParametricGraph.m_Xscl = m_ParametricGraph.m_Xscl * zoom_amount;
			break;
		}
	}
}

void CGraphView::ZoomY(long double zoom_amount) 
{
	switch(m_Mode){
	case EUCLIDEAN:
		{
			long double x_mid = (m_EuclideanGraph.m_EuclideanRange.Xmax +m_EuclideanGraph.m_EuclideanRange.Xmin)/2.0, y_mid = (m_EuclideanGraph.m_EuclideanRange.Ymax +m_EuclideanGraph.m_EuclideanRange.Ymin)/2.0;
			long double x_range(m_EuclideanGraph.m_EuclideanRange.Xmax-m_EuclideanGraph.m_EuclideanRange.Xmin), y_range(m_EuclideanGraph.m_EuclideanRange.Ymax-m_EuclideanGraph.m_EuclideanRange.Ymin);
			
			if((m_EuclideanGraph.m_EuclideanRange.Ymax > 99999999999999999 || m_EuclideanGraph.m_EuclideanRange.Ymin < -99999999999999999) && zoom_amount > 1)
				return;
			
			m_EuclideanGraph.m_EuclideanRange.Ymax = y_mid + (y_range * zoom_amount)/2.0;
			m_EuclideanGraph.m_EuclideanRange.Ymin = y_mid - (y_range * zoom_amount)/2.0;
			
			if(!m_FixedGrid)
				m_EuclideanGraph.m_EuclideanRange.Yscl = m_EuclideanGraph.m_EuclideanRange.Yscl * zoom_amount;
			break;
		}
	case POLAR:
		{
			long double x_mid = (m_PolarGraph.m_PolarRange.Xmax +m_PolarGraph.m_PolarRange.Xmin)/2.0, y_mid = (m_PolarGraph.m_PolarRange.Ymax +m_PolarGraph.m_PolarRange.Ymin)/2.0;
			long double x_range(m_PolarGraph.m_PolarRange.Xmax-m_PolarGraph.m_PolarRange.Xmin), y_range(m_PolarGraph.m_PolarRange.Ymax-m_PolarGraph.m_PolarRange.Ymin);
			
			if(!ValidateIncrement(x_mid - (x_range * zoom_amount)/2.0, 
				x_mid + (x_range * zoom_amount)/2.0, 
				y_mid - (y_range * zoom_amount)/2.0, 
				y_mid + (y_range * zoom_amount)/2.0))
				return;
			
			if((m_PolarGraph.m_PolarRange.Ymax > 99999999999999999 || m_PolarGraph.m_PolarRange.Ymin < -99999999999999999) && zoom_amount > 1)
				return;
			
			m_PolarGraph.m_PolarRange.Ymax = y_mid + (y_range * zoom_amount)/2.0;
			m_PolarGraph.m_PolarRange.Ymin = y_mid - (y_range * zoom_amount)/2.0;
			break;
		}
	case PARAMETRIC:
		{
			long double x_mid = (m_ParametricGraph.m_Xmax +m_ParametricGraph.m_Xmin)/2.0, y_mid = (m_ParametricGraph.m_Ymax +m_ParametricGraph.m_Ymin)/2.0;
			long double x_range(m_ParametricGraph.m_Xmax-m_ParametricGraph.m_Xmin), y_range(m_ParametricGraph.m_Ymax-m_ParametricGraph.m_Ymin);
			
			if((m_ParametricGraph.m_Ymax > 99999999999999999 || m_ParametricGraph.m_Ymin < -99999999999999999) && zoom_amount > 1)
				return;
			
			m_ParametricGraph.m_Ymax = y_mid + (y_range * zoom_amount)/2.0;
			m_ParametricGraph.m_Ymin = y_mid - (y_range * zoom_amount)/2.0;
			
			if(!m_FixedGrid)
				m_ParametricGraph.m_Yscl = m_ParametricGraph.m_Yscl * zoom_amount;
			break;
		}
	}
}

void CGraphView::OnGraphZoomDecimal() 
{
	int num_points = int((double(m_EuclideanGraph.GetLinePrec())/100.0)*m_graph_width);
	double range = m_ZoomDecPrec * double(num_points);
	
	StoreCurrentRange();
	
	switch(m_Mode){
	case EUCLIDEAN:
		{
			m_EuclideanGraph.m_EuclideanRange.Xmax = range / 2.0;
			m_EuclideanGraph.m_EuclideanRange.Xmin = -m_EuclideanGraph.m_EuclideanRange.Xmax;
			m_EuclideanGraph.m_EuclideanRange.Ymax = m_EuclideanGraph.m_EuclideanRange.Xmax;
			m_EuclideanGraph.m_EuclideanRange.Ymin = m_EuclideanGraph.m_EuclideanRange.Xmin;
			m_EuclideanGraph.m_EuclideanRange.Xscl = m_EuclideanGraph.m_EuclideanRange.Yscl = range / 10.0;
			break;
		}
	case POLAR:
		{
			m_PolarGraph.m_PolarRange.Xmax = range / 2.0;
			m_PolarGraph.m_PolarRange.Xmin = -m_PolarGraph.m_PolarRange.Xmax;
			m_PolarGraph.m_PolarRange.Ymax = m_PolarGraph.m_PolarRange.Xmax;
			m_PolarGraph.m_PolarRange.Ymin = m_PolarGraph.m_PolarRange.Xmin;
			m_PolarGraph.m_PolarRange.GridRadius = (m_PolarGraph.m_PolarRange.Xmax - m_PolarGraph.m_PolarRange.Xmin)/10;
			m_PolarGraph.m_PolarRange.GridAngle = (m_Calculator->m_trig_state == RADIAN) ? PI/6 : 30;
			break;
		}
	case PARAMETRIC:
		{
			m_ParametricGraph.m_Xmax = range / 2.0;
			m_ParametricGraph.m_Xmin = -m_ParametricGraph.m_Xmax;
			m_ParametricGraph.m_Ymax = m_ParametricGraph.m_Xmax;
			m_ParametricGraph.m_Ymin = m_ParametricGraph.m_Xmin;
			m_ParametricGraph.m_Xscl = m_ParametricGraph.m_Yscl = range / 10.0;
			break;
		}
	}
	
	RePaintNow();
}

void CGraphView::OnGraphZoomStandard() 
{
	StoreCurrentRange();
	
	switch(m_Mode){
	case EUCLIDEAN:
		{
			m_EuclideanGraph.m_EuclideanRange.Xmin = -10;
			m_EuclideanGraph.m_EuclideanRange.Xmax = 10;
			m_EuclideanGraph.m_EuclideanRange.Xscl = 2;
			m_EuclideanGraph.m_EuclideanRange.Ymin = -10;
			m_EuclideanGraph.m_EuclideanRange.Ymax = 10;
			m_EuclideanGraph.m_EuclideanRange.Yscl = 2;
			break;
		}
	case POLAR:
		{
			m_PolarGraph.m_PolarRange.Xmin = -10;
			m_PolarGraph.m_PolarRange.Xmax = 10;
			m_PolarGraph.m_PolarRange.Ymin = -10;
			m_PolarGraph.m_PolarRange.Ymax = 10;
			m_PolarGraph.m_PolarRange.GridRadius = 2;
			m_PolarGraph.m_PolarRange.GridAngle = (m_Calculator->m_trig_state == RADIAN) ? PI/6 : 30;
			break;
		}
	case PARAMETRIC:
		{
			m_ParametricGraph.m_Xmin = -10;
			m_ParametricGraph.m_Xmax = 10;
			m_ParametricGraph.m_Xscl = 2;
			m_ParametricGraph.m_Ymin = -10;
			m_ParametricGraph.m_Ymax = 10;
			m_ParametricGraph.m_Yscl = 2;
			break;
		}
	}
		
	RePaintNow();
}

void CGraphView::OnGraphZoomTrig() 
{
	if(m_Calculator->m_trig_state == RADIAN){
		int num_points = int((double(m_EuclideanGraph.GetLinePrec())/100.0)*m_graph_width);
		double range = PI/48.0 * double(num_points);
		
		StoreCurrentRange();
		
		switch(m_Mode){
		case EUCLIDEAN:
			{
				m_EuclideanGraph.m_EuclideanRange.Xmax = range / 2.0;
				m_EuclideanGraph.m_EuclideanRange.Xmin = -m_EuclideanGraph.m_EuclideanRange.Xmax;
				m_EuclideanGraph.m_EuclideanRange.Ymax = 3;
				m_EuclideanGraph.m_EuclideanRange.Ymin = -3;
				m_EuclideanGraph.m_EuclideanRange.Xscl = (m_Calculator->m_trig_state == RADIAN) ? PI/2 : 45;
				m_EuclideanGraph.m_EuclideanRange.Yscl = 1;	
				break;
			}
		case POLAR:
			{
				m_PolarGraph.m_PolarRange.Xmax = range / 2.0;
				m_PolarGraph.m_PolarRange.Xmin = -m_PolarGraph.m_PolarRange.Xmax;
				m_PolarGraph.m_PolarRange.Ymax = 3;
				m_PolarGraph.m_PolarRange.Ymin = -3;
				m_PolarGraph.m_PolarRange.GridRadius = 2;
				m_PolarGraph.m_PolarRange.GridAngle = (m_Calculator->m_trig_state == RADIAN) ? PI/6 : 30;
				break;
			}
		case PARAMETRIC:
			{
				m_ParametricGraph.m_Xmax = range / 2.0;
				m_ParametricGraph.m_Xmin = -m_ParametricGraph.m_Xmax;
				m_ParametricGraph.m_Ymax = 3;
				m_ParametricGraph.m_Ymin = -3;
				m_ParametricGraph.m_Xscl = (m_Calculator->m_trig_state == RADIAN) ? PI/2 : 45;
				m_ParametricGraph.m_Yscl = 1;	
				break;
			}
		}
	}
	else{
		int num_points = int((double(m_EuclideanGraph.GetLinePrec())/100.0)*m_graph_width);
		double range = 360/48.0 * double(num_points);
		
		StoreCurrentRange();
		
		switch(m_Mode){
		case EUCLIDEAN:
			{
				m_EuclideanGraph.m_EuclideanRange.Xmax = range / 2.0;
				m_EuclideanGraph.m_EuclideanRange.Xmin = -m_EuclideanGraph.m_EuclideanRange.Xmax;
				m_EuclideanGraph.m_EuclideanRange.Ymax = 3;
				m_EuclideanGraph.m_EuclideanRange.Ymin = -3;
				m_EuclideanGraph.m_EuclideanRange.Xscl = 180;
				m_EuclideanGraph.m_EuclideanRange.Yscl = 1;	
				break;
			}
		case POLAR:
			{
				m_PolarGraph.m_PolarRange.Xmax = range / 2.0;
				m_PolarGraph.m_PolarRange.Xmin = -m_PolarGraph.m_PolarRange.Xmax;
				m_PolarGraph.m_PolarRange.Ymax = 3;
				m_PolarGraph.m_PolarRange.Ymin = -3;
				m_PolarGraph.m_PolarRange.GridRadius = 2;
				m_PolarGraph.m_PolarRange.GridAngle = (m_Calculator->m_trig_state == RADIAN) ? PI/6 : 30;
				break;
			}
		case PARAMETRIC:
			{
				m_ParametricGraph.m_Xmax = range / 2.0;
				m_ParametricGraph.m_Xmin = -m_ParametricGraph.m_Xmax;
				m_ParametricGraph.m_Ymax = 3;
				m_ParametricGraph.m_Ymin = -3;
				m_ParametricGraph.m_Xscl = 180;
				m_ParametricGraph.m_Yscl = 1;	
				break;
			}
		}
	}
	RePaintNow();
}

void CGraphView::OnGraphZoomInteger() 
{
	int num_points = int((double(m_EuclideanGraph.GetLinePrec())/100.0)*m_graph_width);
	double range = 1.0 * double(num_points);

	StoreCurrentRange();
	
	switch(m_Mode){
	case EUCLIDEAN:
		{
			m_EuclideanGraph.m_EuclideanRange.Xmax = range / 2.0;
			m_EuclideanGraph.m_EuclideanRange.Xmin = -m_EuclideanGraph.m_EuclideanRange.Xmax;
			m_EuclideanGraph.m_EuclideanRange.Ymax = m_EuclideanGraph.m_EuclideanRange.Xmax;
			m_EuclideanGraph.m_EuclideanRange.Ymin = m_EuclideanGraph.m_EuclideanRange.Xmin;
			m_EuclideanGraph.m_EuclideanRange.Xscl = m_EuclideanGraph.m_EuclideanRange.Yscl = range / 10.0;
			break;
		}
	case POLAR:
		{
			m_PolarGraph.m_PolarRange.Xmax = range / 2.0;
			m_PolarGraph.m_PolarRange.Xmin = -m_PolarGraph.m_PolarRange.Xmax;
			m_PolarGraph.m_PolarRange.Ymax = m_PolarGraph.m_PolarRange.Xmax;
			m_PolarGraph.m_PolarRange.Ymin = m_PolarGraph.m_PolarRange.Xmin;
			m_PolarGraph.m_PolarRange.GridRadius = (m_PolarGraph.m_PolarRange.Xmax - m_PolarGraph.m_PolarRange.Xmin)/10;
			m_PolarGraph.m_PolarRange.GridAngle = (m_Calculator->m_trig_state == RADIAN) ? PI/6 : 30;
			break;
		}
	case PARAMETRIC:
		{
			m_ParametricGraph.m_Xmax = range / 2.0;
			m_ParametricGraph.m_Xmin = -m_ParametricGraph.m_Xmax;
			m_ParametricGraph.m_Ymax = m_ParametricGraph.m_Xmax;
			m_ParametricGraph.m_Ymin = m_ParametricGraph.m_Xmin;
			m_ParametricGraph.m_Xscl = m_ParametricGraph.m_Yscl = range / 10.0;
			break;
		}
	}
	RePaintNow();
}

void CGraphView::OnGraphZoomPreviousRange() 
{
	SwapPrevCurRanges();
	RePaintNow();
}

void CGraphView::OnGraphZoomFit() 
{
	StoreCurrentRange();
	
	switch(m_Mode){
	case EUCLIDEAN:
		{
			m_EuclideanGraph.m_EuclideanRange.Ymin = m_EuclideanGraph.m_EuclideanRange.Xmin;
			m_EuclideanGraph.m_EuclideanRange.Ymax = m_EuclideanGraph.m_EuclideanRange.Xmax;
			m_EuclideanGraph.m_EuclideanRange.Yscl = m_EuclideanGraph.m_EuclideanRange.Xscl;
			break;
		}
	case POLAR:
		{
			m_PolarGraph.m_PolarRange.Ymin = m_PolarGraph.m_PolarRange.Xmin;
			m_PolarGraph.m_PolarRange.Ymax = m_PolarGraph.m_PolarRange.Xmax;
			break;
		}
	case PARAMETRIC:
		{
			m_ParametricGraph.m_Ymin = m_ParametricGraph.m_Xmin;
			m_ParametricGraph.m_Ymax = m_ParametricGraph.m_Xmax;
			m_ParametricGraph.m_Yscl = m_ParametricGraph.m_Xscl;
			break;
		}
	}

	RePaintNow();
}
