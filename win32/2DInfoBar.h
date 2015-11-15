#define IDC_TRACE_T IDC_TRACE_THETA // use one control for the both of them

#define GRAPH2D_INFOBAR_SPACE_H 3
#define GRAPH2D_INFOBAR_SPACE_V 1
#define GRAPH2D_INFOBAR_GROUP_SPACE_V 3
#define GRAPH2D_INFOBAR_EDIT_HEIGHT		18
#define GRAPH2D_INFOBAR_INDENT	7
#define GRAPH2D_INFOBAR_INDENT_MIDBAR \
	GRAPH2D_INFOBAR_SPACE_H + (GRAPH2D_INFOBAR_WIDTH/2)
	
#define GRAPH2D_INFOBAR_ROW(nRow) \
	((nRow-1) * (GRAPH2D_INFOBAR_SPACE_V+GRAPH2D_INFOBAR_EDIT_HEIGHT))


//************************************************************************/
// Cursor Position InfoBar

#define GRAPH2D_INFOBAR_CURSOR_POSITION_HEIGHT		61
#define GRAPH2D_INFOBAR_CURSOR_POSITION_EDIT_WIDTH		\
	(GRAPH2D_INFOBAR_WIDTH - (GRAPH2D_INFOBAR_INDENT*2) -GRAPH2D_INFOBAR_SPACE_H) / 2

InfoBarCtrl	g_InfoBarCursorPositionCtrls[] = {
		{IDC_CURSOR_POSITION,	0,
								GRAPH2D_INFOBAR_ROW(1),
								GRAPH2D_INFOBAR_WIDTH,
								GRAPH2D_INFOBAR_CURSOR_POSITION_HEIGHT},
		{IDC_CURSOR_X,	GRAPH2D_INFOBAR_INDENT,
						GRAPH2D_INFOBAR_ROW(2),
						GRAPH2D_INFOBAR_CURSOR_POSITION_EDIT_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_CURSOR_Y,	GRAPH2D_INFOBAR_INDENT,
						GRAPH2D_INFOBAR_ROW(3),
						GRAPH2D_INFOBAR_CURSOR_POSITION_EDIT_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_CURSOR_THETA,	GRAPH2D_INFOBAR_INDENT_MIDBAR,
							GRAPH2D_INFOBAR_ROW(2),
							GRAPH2D_INFOBAR_CURSOR_POSITION_EDIT_WIDTH - GRAPH2D_INFOBAR_SPACE_H,
							GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_CURSOR_R,		GRAPH2D_INFOBAR_INDENT_MIDBAR,
							GRAPH2D_INFOBAR_ROW(3),
							GRAPH2D_INFOBAR_CURSOR_POSITION_EDIT_WIDTH - GRAPH2D_INFOBAR_SPACE_H,
							GRAPH2D_INFOBAR_EDIT_HEIGHT},		
		{0,0,0,0,0}
};

//************************************************************************/

//************************************************************************/
// Equation Update InfoBar

#define GRAPH2D_INFOBAR_EQUATION_UPDATE_HEIGHT	21
#define GRAPH2D_INFOBAR_EQUPDATE_HEIGHT		21
#define GRAPH2D_INFOBAR_EQDROPDOWN_WIDTH		38
#define GRAPH2D_INFOBAR_UPDATE_WIDTH		48

InfoBarCtrl	g_InfoBarEquationUpdateCtrls[] = {
		{IDC_EQ,		0,
						0,
						GRAPH2D_INFOBAR_EQDROPDOWN_WIDTH,
						GRAPH2D_INFOBAR_EQUPDATE_HEIGHT},
		{IDC_EQ_EDIT,	GRAPH2D_INFOBAR_EQDROPDOWN_WIDTH + GRAPH2D_INFOBAR_SPACE_H,
						0, 
						(((GRAPH2D_INFOBAR_WIDTH - GRAPH2D_INFOBAR_EQDROPDOWN_WIDTH) - GRAPH2D_INFOBAR_UPDATE_WIDTH) - (GRAPH2D_INFOBAR_SPACE_H*2)), 
						GRAPH2D_INFOBAR_EQUPDATE_HEIGHT},
		{IDC_UPDATE_EQ,GRAPH2D_INFOBAR_WIDTH -GRAPH2D_INFOBAR_UPDATE_WIDTH,
						0,
						GRAPH2D_INFOBAR_UPDATE_WIDTH,
						GRAPH2D_INFOBAR_EQUPDATE_HEIGHT},		
		{0,0,0,0,0}
};

//************************************************************************/

//************************************************************************/
// Area InfoBar

#define GRAPH2D_INFOBAR_AREA_HEIGHT		40
#define GRAPH2D_INFOBAR_AREA_EDIT_WIDTH		\
	(GRAPH2D_INFOBAR_WIDTH - (GRAPH2D_INFOBAR_INDENT*2))

InfoBarCtrl	g_InfoBarAreaCtrls[] = {
		{IDC_AREA,	0,
					GRAPH2D_INFOBAR_ROW(1),
					GRAPH2D_INFOBAR_WIDTH,
					GRAPH2D_INFOBAR_AREA_HEIGHT},
		{IDC_AREA_VALUE,	GRAPH2D_INFOBAR_INDENT,
						GRAPH2D_INFOBAR_ROW(2),
						GRAPH2D_INFOBAR_AREA_EDIT_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},	
		{0,0,0,0,0}
};

//************************************************************************/


//************************************************************************/
// Distance InfoBar

#define GRAPH2D_INFOBAR_DISTANCE_HEIGHT		40
#define GRAPH2D_INFOBAR_DISTANCE_EDIT_WIDTH		\
	(GRAPH2D_INFOBAR_WIDTH - (GRAPH2D_INFOBAR_INDENT*2))

InfoBarCtrl	g_InfoBarDistanceCtrls[] = {
		{IDC_DISTANCE,	0,
					GRAPH2D_INFOBAR_ROW(1),
					GRAPH2D_INFOBAR_WIDTH,
					GRAPH2D_INFOBAR_DISTANCE_HEIGHT},
		{IDC_DISTANCE_VALUE,	GRAPH2D_INFOBAR_INDENT,
						GRAPH2D_INFOBAR_ROW(2),
						GRAPH2D_INFOBAR_DISTANCE_EDIT_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},	
		{0,0,0,0,0}
};

//************************************************************************/

//************************************************************************/
// Equations InfoBar

#define GRAPH2D_INFOBAR_EQUATIONS_HEIGHT GRAPH2D_INFOBAR_ROW(11) - GRAPH2D_INFOBAR_SPACE_V
#define GRAPH2D_INFOBAR_EQ_COLOR_WIDTH GRAPH2D_INFOBAR_EDIT_HEIGHT
#define GRAPH2D_INFOBAR_EQ_ON_WIDTH			38
#define GRAPH2D_INFOBAR_EQ_LEFT		\
	(GRAPH2D_INFOBAR_EQ_ON_WIDTH + \
	GRAPH2D_INFOBAR_SPACE_H)
#define GRAPH2D_INFOBAR_EQ_WIDTH	\
	(GRAPH2D_INFOBAR_WIDTH - \
	GRAPH2D_INFOBAR_EQ_LEFT - \
	GRAPH2D_INFOBAR_EQ_COLOR_WIDTH - 7)

InfoBarCtrl	g_InfoBarEquationCtrls[] = {
		{IDC_EQ_ON_1,	0,
						GRAPH2D_INFOBAR_ROW(1),
						GRAPH2D_INFOBAR_EQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_1,		GRAPH2D_INFOBAR_EQ_LEFT,
						GRAPH2D_INFOBAR_ROW(1),
						GRAPH2D_INFOBAR_EQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_ON_2,	0,
						GRAPH2D_INFOBAR_ROW(2),
						GRAPH2D_INFOBAR_EQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_2,		GRAPH2D_INFOBAR_EQ_LEFT,
						GRAPH2D_INFOBAR_ROW(2),
						GRAPH2D_INFOBAR_EQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_ON_3,	0,
						GRAPH2D_INFOBAR_ROW(3),
						GRAPH2D_INFOBAR_EQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_3,		GRAPH2D_INFOBAR_EQ_LEFT,
						GRAPH2D_INFOBAR_ROW(3),
						GRAPH2D_INFOBAR_EQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_ON_4,	0,
						GRAPH2D_INFOBAR_ROW(4),
						GRAPH2D_INFOBAR_EQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_4,		GRAPH2D_INFOBAR_EQ_LEFT,
						GRAPH2D_INFOBAR_ROW(4),
						GRAPH2D_INFOBAR_EQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_ON_5,	0,
						GRAPH2D_INFOBAR_ROW(5),
						GRAPH2D_INFOBAR_EQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_5,		GRAPH2D_INFOBAR_EQ_LEFT,
						GRAPH2D_INFOBAR_ROW(5),
						GRAPH2D_INFOBAR_EQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_ON_6,	0,
						GRAPH2D_INFOBAR_ROW(6),
						GRAPH2D_INFOBAR_EQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_6,		GRAPH2D_INFOBAR_EQ_LEFT,
						GRAPH2D_INFOBAR_ROW(6),
						GRAPH2D_INFOBAR_EQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_ON_7,	0,
						GRAPH2D_INFOBAR_ROW(7),
						GRAPH2D_INFOBAR_EQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_7,		GRAPH2D_INFOBAR_EQ_LEFT,
						GRAPH2D_INFOBAR_ROW(7),
						GRAPH2D_INFOBAR_EQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_ON_8,	0,
						GRAPH2D_INFOBAR_ROW(8),
						GRAPH2D_INFOBAR_EQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_8,		GRAPH2D_INFOBAR_EQ_LEFT,
						GRAPH2D_INFOBAR_ROW(8),
						GRAPH2D_INFOBAR_EQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_ON_9,	0,
						GRAPH2D_INFOBAR_ROW(9),
						GRAPH2D_INFOBAR_EQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_9,		GRAPH2D_INFOBAR_EQ_LEFT,
						GRAPH2D_INFOBAR_ROW(9),
						GRAPH2D_INFOBAR_EQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_ON_10,	0,
						GRAPH2D_INFOBAR_ROW(10),
						GRAPH2D_INFOBAR_EQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_10,		GRAPH2D_INFOBAR_EQ_LEFT,
						GRAPH2D_INFOBAR_ROW(10),
						GRAPH2D_INFOBAR_EQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},		
		{0,0,0,0,0}
};

//************************************************************************/


//************************************************************************/
// Parametric Equations InfoBar

#define GRAPH2D_INFOBAR_PARAMETRIC_ON_ROW(n) \
	(GRAPH2D_INFOBAR_ROW(n) + GRAPH2D_INFOBAR_ROW(n+1)) /2

#define GRAPH2D_INFOBAR_PARAMETRICEQ_ON_WIDTH			45
#define GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH			15
#define GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT		\
	(GRAPH2D_INFOBAR_PARAMETRICEQ_ON_WIDTH + \
	GRAPH2D_INFOBAR_SPACE_H)
#define GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT		\
	(GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT + \
	(GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH + \
	GRAPH2D_INFOBAR_SPACE_H))
#define GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH	\
	(GRAPH2D_INFOBAR_WIDTH - \
	GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT - \
	GRAPH2D_INFOBAR_EQ_COLOR_WIDTH - 7)

InfoBarCtrl	g_InfoBarParametricEquationCtrls[] = {
		{IDC_PARAMETRIC_EQ_1,	0,
						GRAPH2D_INFOBAR_PARAMETRIC_ON_ROW(1),
						GRAPH2D_INFOBAR_PARAMETRICEQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_PARAMETRIC_EQ_2,	0,
						GRAPH2D_INFOBAR_PARAMETRIC_ON_ROW(3),
						GRAPH2D_INFOBAR_PARAMETRICEQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_PARAMETRIC_EQ_3,	0,
						GRAPH2D_INFOBAR_PARAMETRIC_ON_ROW(5),
						GRAPH2D_INFOBAR_PARAMETRICEQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_PARAMETRIC_EQ_4,	0,
						GRAPH2D_INFOBAR_PARAMETRIC_ON_ROW(7),
						GRAPH2D_INFOBAR_PARAMETRICEQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_PARAMETRIC_EQ_5,	0,
						GRAPH2D_INFOBAR_PARAMETRIC_ON_ROW(9),
						GRAPH2D_INFOBAR_PARAMETRICEQ_ON_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_X_EQLABEL_1,	GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT,
						GRAPH2D_INFOBAR_ROW(1),
						GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_X1,		GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT,
						GRAPH2D_INFOBAR_ROW(1),
						GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_Y_EQLABEL_1,	GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT,
						GRAPH2D_INFOBAR_ROW(2),
						GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_Y1,		GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT,
						GRAPH2D_INFOBAR_ROW(2),
						GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_X_EQLABEL_2,	GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT,
						GRAPH2D_INFOBAR_ROW(3),
						GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_X2,		GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT,
						GRAPH2D_INFOBAR_ROW(3),
						GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_Y_EQLABEL_2,	GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT,
						GRAPH2D_INFOBAR_ROW(4),
						GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_Y2,		GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT,
						GRAPH2D_INFOBAR_ROW(4),
						GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_X_EQLABEL_3,	GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT,
						GRAPH2D_INFOBAR_ROW(5),
						GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_X3,		GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT,
						GRAPH2D_INFOBAR_ROW(5),
						GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_Y_EQLABEL_3,	GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT,
						GRAPH2D_INFOBAR_ROW(6),
						GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_Y3,		GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT,
						GRAPH2D_INFOBAR_ROW(6),
						GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_X_EQLABEL_4,	GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT,
						GRAPH2D_INFOBAR_ROW(7),
						GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_X4,		GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT,
						GRAPH2D_INFOBAR_ROW(7),
						GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_Y_EQLABEL_4,	GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT,
						GRAPH2D_INFOBAR_ROW(8),
						GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_Y4,		GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT,
						GRAPH2D_INFOBAR_ROW(8),
						GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_X_EQLABEL_5,	GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT,
						GRAPH2D_INFOBAR_ROW(9),
						GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_EQ_X5,		GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT,
						GRAPH2D_INFOBAR_ROW(9),
						GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
						
		{IDC_Y_EQLABEL_5,	GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_LEFT,
						GRAPH2D_INFOBAR_ROW(10),
						GRAPH2D_INFOBAR_PARAMETRICEQ_LABEL_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
												
		{IDC_EQ_Y5,		GRAPH2D_INFOBAR_PARAMETRICEQ_LEFT,
						GRAPH2D_INFOBAR_ROW(10),
						GRAPH2D_INFOBAR_PARAMETRICEQ_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},		
		{0,0,0,0,0}
};

//************************************************************************/

//************************************************************************/
// Trace InfoBar

#define GRAPH2D_INFOBAR_TRACE_HEIGHT		82
#define GRAPH2D_INFOBAR_TRACE_EDIT_WIDTH		\
	GRAPH2D_INFOBAR_CURSOR_POSITION_EDIT_WIDTH
	
InfoBarCtrl	g_InfoBarTraceCtrls[] = {
		{IDC_TRACE,		0,
						GRAPH2D_INFOBAR_ROW(1),
						GRAPH2D_INFOBAR_WIDTH,
						GRAPH2D_INFOBAR_TRACE_HEIGHT},
		{IDC_TRACE_X,	GRAPH2D_INFOBAR_INDENT,
						GRAPH2D_INFOBAR_ROW(2),
						GRAPH2D_INFOBAR_TRACE_EDIT_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_TRACE_Y,	GRAPH2D_INFOBAR_INDENT,
						GRAPH2D_INFOBAR_ROW(3),
						GRAPH2D_INFOBAR_TRACE_EDIT_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_TRACE_DYDX,GRAPH2D_INFOBAR_INDENT,
						GRAPH2D_INFOBAR_ROW(4),
						GRAPH2D_INFOBAR_TRACE_EDIT_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_TRACE_THETA,	GRAPH2D_INFOBAR_INDENT_MIDBAR,
						GRAPH2D_INFOBAR_ROW(2),
						GRAPH2D_INFOBAR_TRACE_EDIT_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_TRACE_R,	GRAPH2D_INFOBAR_INDENT_MIDBAR,
						GRAPH2D_INFOBAR_ROW(3),
						GRAPH2D_INFOBAR_TRACE_EDIT_WIDTH,
						GRAPH2D_INFOBAR_EDIT_HEIGHT},
		{IDC_TRACE_DRDTHETA,	GRAPH2D_INFOBAR_INDENT_MIDBAR,
							  	GRAPH2D_INFOBAR_ROW(4),
							  	GRAPH2D_INFOBAR_TRACE_EDIT_WIDTH,
								GRAPH2D_INFOBAR_EDIT_HEIGHT},		
		{0,0,0,0,0}
};

void CGraphView::InitializeInfoBarCtrlGroups()
{
	g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATION_UPDATE].height = GRAPH2D_INFOBAR_EQUATION_UPDATE_HEIGHT;
	g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATION_UPDATE].bOn  = false;
	g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATION_UPDATE].pCtrls = g_InfoBarEquationUpdateCtrls;
	g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATION_UPDATE].start_y = 0;
	g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATIONS].height = GRAPH2D_INFOBAR_EQUATIONS_HEIGHT;
	g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATIONS].bOn  = true;
	g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATIONS].pCtrls = g_InfoBarEquationCtrls;
	g_InfoBarGroups[GRAPH2D_INFOBAR_CURSOR_POSITION].height = GRAPH2D_INFOBAR_CURSOR_POSITION_HEIGHT;
	g_InfoBarGroups[GRAPH2D_INFOBAR_CURSOR_POSITION].bOn  = false;
	g_InfoBarGroups[GRAPH2D_INFOBAR_CURSOR_POSITION].pCtrls = g_InfoBarCursorPositionCtrls;
	g_InfoBarGroups[GRAPH2D_INFOBAR_TRACE].height = GRAPH2D_INFOBAR_TRACE_HEIGHT;
	g_InfoBarGroups[GRAPH2D_INFOBAR_TRACE].bOn  = false;
	g_InfoBarGroups[GRAPH2D_INFOBAR_TRACE].pCtrls = g_InfoBarTraceCtrls;
	g_InfoBarGroups[GRAPH2D_INFOBAR_AREA].height = GRAPH2D_INFOBAR_AREA_HEIGHT;
	g_InfoBarGroups[GRAPH2D_INFOBAR_AREA].bOn  = false;
	g_InfoBarGroups[GRAPH2D_INFOBAR_AREA].pCtrls = g_InfoBarAreaCtrls;
	g_InfoBarGroups[GRAPH2D_INFOBAR_DISTANCE].height = GRAPH2D_INFOBAR_DISTANCE_HEIGHT;
	g_InfoBarGroups[GRAPH2D_INFOBAR_DISTANCE].bOn  = false;
	g_InfoBarGroups[GRAPH2D_INFOBAR_DISTANCE].pCtrls = g_InfoBarDistanceCtrls;
	g_InfoBarGroups[GRAPH2D_INFOBAR_PARAMETRIC_EQS].height = GRAPH2D_INFOBAR_EQUATIONS_HEIGHT;
	g_InfoBarGroups[GRAPH2D_INFOBAR_PARAMETRIC_EQS].bOn  = false;
	g_InfoBarGroups[GRAPH2D_INFOBAR_PARAMETRIC_EQS].pCtrls = g_InfoBarParametricEquationCtrls;

	for(int i=1; GRAPH2D_INFOBAR_GROUPS > i; ++i)
		g_InfoBarGroups[i].start_y = g_InfoBarGroups[i-1].start_y + g_InfoBarGroups[i-1].height + GRAPH2D_INFOBAR_GROUP_SPACE_V;

	// initialize polar & euclidean edit ctrls;
	for(i=0; i < 10; ++i)
		{
		m_aEquationEditCtrls[i].m_nEq = i;
		m_aEquationEditCtrls[i].m_pwndParent = this;
		
		m_aParametricEquationEditCtrls[i].m_nEq = i;
		m_aParametricEquationEditCtrls[i].m_pwndParent = this;
		}	

	
	// initialize parametric edit ctrls;
	// yes this is fucked up, it doesn't just look like it, it is.
	for(i=0; i < 5; ++i)
		{
		int x=i*2;
		int y=x+1;
		int eq=i;
		
		m_aParametricEquationEditCtrls[x].m_nEq = eq;
		m_aParametricEquationEditCtrls[x].m_uParametricEq = PARAMETRIC_EQ_X;
		m_aParametricEquationEditCtrls[x].m_pwndParent = this;
		
		m_aParametricEquationEditCtrls[y].m_nEq = eq;
		m_aParametricEquationEditCtrls[y].m_uParametricEq = PARAMETRIC_EQ_Y;
		m_aParametricEquationEditCtrls[y].m_pwndParent = this;
		}	
	
}

void CGraphView::ShowInfoBar(bool fShow)
{	
	#ifndef GRAPH2D_INFOBAR
		fShow = false;
	#endif
	
	m_fInfoBar = fShow;

	Trace("toggling infobar state\n");

	int i=0;
	CWnd *pWnd;

	for(int j=0; j < GRAPH2D_INFOBAR_GROUPS; ++j)
		{
		i=0;
		while(g_InfoBarGroups[j].pCtrls[i].nID)
			{
			pWnd = GetDlgItem(g_InfoBarGroups[j].pCtrls[i].nID);

			if(pWnd)
				pWnd->ShowWindow((g_InfoBarGroups[j].bOn && fShow) ? SW_SHOW : SW_HIDE);
			++i;
			}
		}

	GraphInfoBar(PositionInfoBar());
}

#ifdef GRAPH2D_INFOBAR

void CGraphView::SetInfoBarRedraw(bool fRedraw)
{	
	int i=0;
	CWnd *pWnd;

	for(int j=0; j < GRAPH2D_INFOBAR_GROUPS; ++j)
		{
		i=0;
		while(g_InfoBarGroups[j].pCtrls[i].nID)
			{
			pWnd = GetDlgItem(g_InfoBarGroups[j].pCtrls[i].nID);

			if(pWnd)
				pWnd->SetRedraw(fRedraw);
			++i;
			}
		}
}

void CGraphView::InvalidateInfoBarCtrls()
{	
	int i=0;
	CWnd *pWnd;

	for(int j=0; j < GRAPH2D_INFOBAR_GROUPS; ++j)
		{
		i=0;
		while(g_InfoBarGroups[j].pCtrls[i].nID)
			{
			pWnd = GetDlgItem(g_InfoBarGroups[j].pCtrls[i].nID);

			if(pWnd)
				pWnd->Invalidate();
			++i;
			}
		}
}

void CGraphView::SetInfoBarCtrlSet(UINT setID, bool fOn)
{
	g_InfoBarGroups[setID].bOn = fOn;
	
	int i=0;
	CWnd *pWnd;
	while(g_InfoBarGroups[setID].pCtrls[i].nID)
		{
		pWnd = GetDlgItem(g_InfoBarGroups[setID].pCtrls[i].nID);

		if(pWnd)
			pWnd->ShowWindow((g_InfoBarGroups[setID].bOn && m_fInfoBar) ? SW_SHOW : SW_HIDE);
		++i;
		}
	PositionInfoBar();
}


void CGraphView::PositionInfoBar()
{
	CRect client;
	GetClientRect(client);

	RePositionInfoBar(CPoint(client.right - GRAPH2D_INFOBAR_WIDTH, m_fToolbarOn ? ToolbarHeight() : 0));
}

void CGraphView::RePositionInfoBar(CPoint ptStart)
{	
	//SetInfoBarRedraw(false);
	if(!m_fInfoBar)
		return;

	Trace("Positioning infobar\n");
	
	int i=0;
	UINT next_y= ptStart.y;
	CWnd *pWnd;

	for(int j=0; j < GRAPH2D_INFOBAR_GROUPS; ++j)
		{
		if(!g_InfoBarGroups[j].bOn)
			continue;

		Trace("Positioning infobar control set\n");
		
		i=0;
		g_InfoBarGroups[j].start_y = next_y;
		next_y += g_InfoBarGroups[j].height + GRAPH2D_INFOBAR_GROUP_SPACE_V;
		
		while(g_InfoBarGroups[j].pCtrls[i].nID)
			{
			CPoint ptCtrlStart;
			ptCtrlStart.x = ptStart.x + g_InfoBarGroups[j].pCtrls[i].left;
			ptCtrlStart.y = g_InfoBarGroups[j].start_y + g_InfoBarGroups[j].pCtrls[i].top;
			
			pWnd = GetDlgItem(g_InfoBarGroups[j].pCtrls[i].nID);

			if(pWnd)
				{
				//HaltRedrawWnd(pWnd);
				pWnd->MoveWindow(CRect(ptCtrlStart.x, 
								 		ptCtrlStart.y, 
									 	ptCtrlStart.x + g_InfoBarGroups[j].pCtrls[i].width, 
								 		ptCtrlStart.y + g_InfoBarGroups[j].pCtrls[i].height), 
					true);
				//InvalidateRedrawWnd(pWnd)				
				}
			++i;
			}
		}

	//SetInfoBarRedraw(true);
	//InvalidateInfoBarCtrls();
	
	//UpdateInfoBarEquationColors();

}



UINT g_PolarCtrls [] = {
	IDC_CURSOR_THETA,
	IDC_CURSOR_R
	};

void CGraphView::UpdateInfoBar(bool fAll /*=false*/)
{
	UpdateInfoBarCursorPosition();

	if(fAll)
		{
		UpdateInfoBarTrace();
		UpdateInfoBarEquations();
		UpdateInfoBarEquationColors();
		}
}

void CGraphView::UpdateInfoBarCtrls(bool fAll /*=false*/)
{
	UpdateInfoBarPolarCtrls();
	UpdateInfoBarTraceCtrls();

	if(fAll)
		{
		;
		}
}

void CGraphView::UpdateInfoBarPolarCtrls()
{
	int i=0;
	CWnd *pWnd;
	while(g_PolarCtrls[i])
		{
		pWnd = GetDlgItem(g_PolarCtrls[i]);

		if(pWnd)
			pWnd->ShowWindow(m_Mode == POLAR && g_InfoBarGroups[GRAPH2D_INFOBAR_CURSOR_POSITION].bOn ? SW_SHOW : SW_HIDE);
		++i;
		}
}

void CGraphView::UpdateInfoBarTraceCtrls()
{
	if(!m_fInfoBar)
		return;

	int i=0;
	CWnd *pWnd;
	while(g_InfoBarTraceCtrls[i].nID)
		{
		pWnd = GetDlgItem(g_InfoBarTraceCtrls[i].nID);

		if(pWnd)
			pWnd->ShowWindow((m_Trace && g_InfoBarGroups[GRAPH2D_INFOBAR_TRACE].bOn) ? SW_SHOW : SW_HIDE);
		++i;
		}
}

///////////////////////////////////////////////////
// EQUATION UPDATING

InforBarEq g_InfoBarEqs [] = {
		{IDC_EQ_ON_1, IDC_EQ_1},
		{IDC_EQ_ON_2, IDC_EQ_2},
		{IDC_EQ_ON_3, IDC_EQ_3},
		{IDC_EQ_ON_4, IDC_EQ_4},
		{IDC_EQ_ON_5, IDC_EQ_5},
		{IDC_EQ_ON_6, IDC_EQ_6},
		{IDC_EQ_ON_7, IDC_EQ_7},
		{IDC_EQ_ON_8, IDC_EQ_8},
		{IDC_EQ_ON_9, IDC_EQ_9},
		{IDC_EQ_ON_10, IDC_EQ_10},
		{0,0}
};
		
InforBarParametricEq g_InfoBarParametricEqs [] = {
		{IDC_PARAMETRIC_EQ_1, IDC_EQ_X1, IDC_EQ_Y1, IDC_X_EQLABEL_1, IDC_Y_EQLABEL_1},
		{IDC_PARAMETRIC_EQ_2, IDC_EQ_X2, IDC_EQ_Y2, IDC_X_EQLABEL_2, IDC_Y_EQLABEL_2},
		{IDC_PARAMETRIC_EQ_3, IDC_EQ_X3, IDC_EQ_Y3, IDC_X_EQLABEL_3, IDC_Y_EQLABEL_3},
		{IDC_PARAMETRIC_EQ_4, IDC_EQ_X4, IDC_EQ_Y4, IDC_X_EQLABEL_4, IDC_Y_EQLABEL_4},
		{IDC_PARAMETRIC_EQ_5, IDC_EQ_X5, IDC_EQ_Y5, IDC_X_EQLABEL_5, IDC_Y_EQLABEL_5},
		{0,0}
};

void CGraphView::OnInfoBarEqOn()
{
	switch(m_Mode){
		case EUCLIDEAN:  	
		case POLAR:		
			{
			int i=0;
			while(g_InfoBarEqs[i].nIDEqOn)
				{	
				Assert(i < MAX_EQUATIONS);
				if(BST_CHECKED == IsDlgButtonChecked(g_InfoBarEqs[i].nIDEqOn))
					{
					if(m_Equations[i].eq != "" && g_Calculator->IsValid(m_Equations[i].eq))
						m_Equations[i].disp = true;
					}
				else
					m_Equations[i].disp = false;
				++i;
				}
			break;
			}
		case PARAMETRIC:
			{
			int i=0;
			while(g_InfoBarParametricEqs[i].nIDEqOn)
				{	
				Assert(i < MAX_PARAMETRIC_EQUATIONS);
				if(BST_CHECKED == IsDlgButtonChecked(g_InfoBarParametricEqs[i].nIDEqOn))
					{
					if(m_ParametricGraph.m_Equations[i].xt != "" && m_ParametricGraph.m_Equations[i].yt != "" && 
						g_Calculator->IsValid(m_ParametricGraph.m_Equations[i].xt) && 
						g_Calculator->IsValid(m_ParametricGraph.m_Equations[i].yt))
						m_ParametricGraph.m_Equations[i].disp = true;
					}
				else
					m_ParametricGraph.m_Equations[i].disp = false;
				++i;
				}

			break;
			}
		}
		
	RePaintNow();
}

void CGraphView::UpdateInfoBarEquations()
{
	TRACE0("Updating infobar equations\n");

	// first set the right view controls
	g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATIONS].bOn  = false;
	g_InfoBarGroups[GRAPH2D_INFOBAR_PARAMETRIC_EQS].bOn  = false;
	
	switch(m_Mode){
		case EUCLIDEAN:  	
		case POLAR:		
			g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATIONS].bOn  = true; 	
			break;
		case PARAMETRIC:
			g_InfoBarGroups[GRAPH2D_INFOBAR_PARAMETRIC_EQS].bOn  = true;
			break;
		}
	ShowInfoBar(m_fInfoBar);

	// now set each equation
	int i=0;
	while(g_InfoBarEqs[i].nIDEqOn)
		{
		UpdateInfoBarEquation(i);
		++i;
		}
}

void CGraphView::UpdateInfoBarEquation(UINT eq)
{
	switch(m_Mode){
		case EUCLIDEAN:
		case POLAR:	
			{
			CString strLabel;
			switch(m_Mode){
				case EUCLIDEAN:  	strLabel.Format("y%d:", eq+1); break;
				case POLAR:		 	strLabel.Format("r%d:", eq+1); break;
				}
			SetDlgItemText(g_InfoBarEqs[eq].nIDEqStr, m_astrEquationsRaw[eq]);
			SetDlgItemText(g_InfoBarEqs[eq].nIDEqOn, strLabel);
			CheckDlgButton(g_InfoBarEqs[eq].nIDEqOn, m_Equations[eq].disp);
			break;
			}
		case PARAMETRIC:
			{
			SetDlgItemText(g_InfoBarParametricEqs[eq].nIDEqX, m_ParametricGraph.m_Equations[eq].xt);
			SetDlgItemText(g_InfoBarParametricEqs[eq].nIDEqY, m_ParametricGraph.m_Equations[eq].yt);
			CheckDlgButton(g_InfoBarParametricEqs[eq].nIDEqOn, m_ParametricGraph.m_Equations[eq].disp);
			break;
			}
		}
}

void CGraphView::InvalidateEquationColors()
{
	CRect client;
	GetClientRect(client);

	CRect rect;
	rect.left = client.right - GRAPH2D_INFOBAR_EQ_COLOR_WIDTH;
	rect.top = g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATIONS].start_y;
	rect.right = client.right;
	rect.bottom = rect.top + GRAPH2D_INFOBAR_ROW(11);
	
	InvalidateRect(rect);
}

void CGraphView::UpdateInfoBarEquationColors()
{
	if(!(g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATIONS].bOn || g_InfoBarGroups[GRAPH2D_INFOBAR_PARAMETRIC_EQS].bOn)
		|| !m_fInfoBar)
		return;

	TRACE0("Updating infobar equation colors\n");

	CRect client;
	GetClientRect(client);	
	
	CDC *pDC = GetDC();
	int i=0;
	while((m_Mode==PARAMETRIC) ? g_InfoBarParametricEqs[i].nIDEqOn : g_InfoBarEqs[i].nIDEqOn)
		{
		switch(m_Mode){
			case EUCLIDEAN:
			case POLAR:
				{
				CBrush brush(m_Equations[i].color), *pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);	

				CRect rect;
				rect.left = client.right - GRAPH2D_INFOBAR_EQ_COLOR_WIDTH;
				rect.top = g_InfoBarGroups[GRAPH2D_INFOBAR_EQUATIONS].start_y + GRAPH2D_INFOBAR_ROW(i+1);
				rect.right = client.right;
				rect.bottom = rect.top + GRAPH2D_INFOBAR_EQ_COLOR_WIDTH;
				
				pDC->Rectangle(rect);
				pDC->SelectObject(pOldBrush);
				pOldBrush = 0;

				delete pOldBrush;
				break;
				}
			case PARAMETRIC:
				{
				CBrush brush(m_ParametricGraph.m_Equations[i].color), *pOldBrush;
				pOldBrush = pDC->SelectObject(&brush);	

				CRect rect;
				rect.left = client.right - GRAPH2D_INFOBAR_EQ_COLOR_WIDTH;
				rect.top = g_InfoBarGroups[GRAPH2D_INFOBAR_PARAMETRIC_EQS].start_y + GRAPH2D_INFOBAR_ROW((2*i)+1);
				rect.right = client.right;
				rect.bottom = rect.top + (2*GRAPH2D_INFOBAR_EQ_COLOR_WIDTH);
				
				pDC->Rectangle(rect);
				pDC->SelectObject(pOldBrush);
				pOldBrush = 0;

				delete pOldBrush;
				break;
				}
			}
		
		++i;
		}
	ReleaseDC(pDC);
}

// END EQUATION UPDATING
///////////////////////////////////////////////////

void CGraphView::UpdateInfoBarCursorPosition()
{
	if(m_cursor_pos.x > m_graph_width
		|| m_cursor_pos.x < 0
		|| m_cursor_pos.y < 0
		|| m_cursor_pos.y > m_graph_height)
		{
		SetDlgItemText(IDC_CURSOR_X, "");
		SetDlgItemText(IDC_CURSOR_Y, "");
		SetDlgItemText(IDC_CURSOR_THETA, "");
		SetDlgItemText(IDC_CURSOR_R, "");
		return;
		}
	
	SetDlgItemText(IDC_CURSOR_X, "x: " + GetCursorXStr());
	SetDlgItemText(IDC_CURSOR_Y, "y: " + GetCursorYStr());
	
	if(m_Mode == POLAR)
		{
		SetDlgItemText(IDC_CURSOR_THETA, 	"theta: " + GetCursorThetaStr());
		SetDlgItemText(IDC_CURSOR_R, 	 	"r:        " + GetCursorRStr());
		}
}

	
void CGraphView::UpdateInfoBarTrace()
{
	if(!m_Trace) return;
	
	switch(m_Mode){
		case EUCLIDEAN:
			{
			SetDlgItemText(IDC_TRACE_X, "x: " + m_EuclideanGraph.GetTraceXStr());
			SetDlgItemText(IDC_TRACE_Y, "y: " + m_EuclideanGraph.GetTraceYStr(m_Equations[m_TraceEq].eq));
			SetDlgItemText(IDC_TRACE_DYDX, "dy/dx: " + m_EuclideanGraph.GetTraceDyDxStr(m_Equations[m_TraceEq].eq));
			break;
			}
		case POLAR:
			{
			SetDlgItemText(IDC_TRACE_X, "x: " + m_PolarGraph.GetTraceXStr(m_Equations[m_TraceEq].eq));
			SetDlgItemText(IDC_TRACE_Y, "y: " + m_PolarGraph.GetTraceYStr(m_Equations[m_TraceEq].eq));
			SetDlgItemText(IDC_TRACE_DYDX, "dy/dx: " + m_PolarGraph.GetTraceDyDxStr(m_Equations[m_TraceEq].eq));
			SetDlgItemText(IDC_TRACE_THETA, "theta: " + m_PolarGraph.GetTraceThetaStr());
			SetDlgItemText(IDC_TRACE_R, "r: " + m_PolarGraph.GetTraceRStr(m_Equations[m_TraceEq].eq));
			SetDlgItemText(IDC_TRACE_DRDTHETA, "dr/dtheta: " + m_PolarGraph.GetTraceDrDthetaStr(m_Equations[m_TraceEq].eq));
			break;
			}
		case PARAMETRIC:
			{
			SetDlgItemText(IDC_TRACE_X, "x: " + m_ParametricGraph.GetTraceXStr(m_ParametricGraph.m_Equations[m_TraceEq].xt));
			SetDlgItemText(IDC_TRACE_Y, "y: " + m_ParametricGraph.GetTraceYStr(m_ParametricGraph.m_Equations[m_TraceEq].yt));
			SetDlgItemText(IDC_TRACE_DYDX, "dy/dx: " + m_ParametricGraph.GetDyDxStr(m_TraceEq, m_ParametricGraph.m_TraceT));
			SetDlgItemText(IDC_TRACE_T, "t: " + m_ParametricGraph.GetTraceTStr());
			// TODO: also display the value of t
			
			break;
			}
		}

}

CString CGraphView::GetCursorXStr()
{
	CString str;
	//str.Format("%.15f", ScreenToGraphX(m_cursor_pos.x, 100));
	g_Calculator->DecimalToStringSci(str, ScreenToGraphX(m_cursor_pos.x, 100), 10);
	return str;
}

CString CGraphView::GetCursorYStr()
{
	CString str;
	//str.Format("%.15f", ScreenToGraphY(m_cursor_pos.y));
	g_Calculator->DecimalToStringSci(str, ScreenToGraphY(m_cursor_pos.y), 10);
	return str;
}

CString CGraphView::GetCursorThetaStr()
{
	long double theta=0;
	long double x(ScreenToGraphX(m_cursor_pos.x, 100)), y(ScreenToGraphY(m_cursor_pos.y));
		
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

	CString str;
	g_Calculator->DecimalToStringSci(str, theta, 10);
	return str;	
}

CString CGraphView::GetCursorRStr()
{
	long double x(ScreenToGraphX(m_cursor_pos.x, 100)), y(ScreenToGraphY(m_cursor_pos.y));
	long double r = sqrt(powf(x, 2.0) + powf(y,2.0));
	CString str;
	g_Calculator->DecimalToStringSci(str, r, 10);
	return str;	
}

#endif
