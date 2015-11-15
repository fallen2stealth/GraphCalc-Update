#include "3DGraphOptions.h"


////////////////////////////////////////////////////////////////////////////////
// Draws the buttons for the Calculator
/*********************************************************/
// CGrphCalcDlg::DrawButtons()
// Pre: none
// Post: none
// Return Value: none
// Intent: draws all the buttons in the main pallete
/*********************************************************/
void CGrphCalcDlg::DrawButtons(CDC *pDC)
{
	Assert(pDC);
	
	// now draw each button
	for(int i(0); i < 7; ++i)
		for(int j(0); j < 5; ++j)
			DrawButton(i, j, pDC);
}

/*********************************************************/
// CGrphCalcDlg::DrawButton(int i, int j)
// Pre: none
// Post: none
// Return Value: none
// Intent: draws the specified button in the main pallete
/*********************************************************/
void CGrphCalcDlg::DrawButton(int i, int j, CDC* pDC)
{
	if(m_FullScreen)
		return;

	int x_start;

	if(pDC)
		x_start = RIGHT_BITMAP_INDENT;
	else
		{
		x_start = m_alt_button_start.x;
		pDC = GetDC();
		}

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap;

	int y = m_button_start.y + (i * button_height) + (i * button_spacing);
	int x = x_start + (j * button_width) + (j * button_spacing);

	if(m_Buttons[j][i].state == BUTTON_STATE_UP)
		pOldBitmap = dcMemory.SelectObject(&m_Buttons[j][i].up);
	else
		pOldBitmap = dcMemory.SelectObject(&m_Buttons[j][i].down);

	pDC->BitBlt(x, y, button_width, button_height, &dcMemory, 0, 0, SRCCOPY);
	dcMemory.SelectObject(pOldBitmap);

	if(x_start == m_alt_button_start.x)
		ReleaseDC(pDC);
}


/*********************************************************/
// CGrphCalcDlg::ButtonDetect(CPoint point, int &i, int &j)
// Pre: none
// Post: none
// Return Value: none
// Intent: detects which button, if any, point lies in
/*********************************************************/
bool CGrphCalcDlg::ButtonDetect(CPoint point, int &i, int &j)
{
	CRect button;

	for(i=0; i < 7; ++i){
		int y = m_button_start.y + (i * button_height) + (i * button_spacing);
		for(j=0; j < 5; ++j){
			int x = m_button_start.x + (j * button_width) + (j * button_spacing);
			
			button.SetRect(x, y, x+button_width, y+button_height);

			if(button.PtInRect(point))
				return true;
		}
	}
	return false;
}
/*********************************************************/
// CGrphCalcDlg::DrawPaleteButtons()
// Pre: none
// Post: none
// Return Value: none
// Intent: draws the current exteneded palete
/*********************************************************/
void CGrphCalcDlg::DrawPaleteButtons(CDC *pDC)
{
	int buttons=0;
	Assert(pDC);

	switch(m_CurrentPalete){
	case NONE:
		return;
	case PROB:
		buttons = m_ProbButtons.GetSize();
		break;
	case TEST:
		buttons = m_TestButtons.GetSize();
		break;
	case MATH:
		buttons = m_MathButtons.GetSize();
		break;
	case STATS:
		buttons = m_StatsButtons.GetSize();
		break;
	case LETTERS:
		buttons = m_LetterButtons.GetSize();
		break;
	}

	for(int i(0); i < buttons; ++i)
		DrawPaleteButton(i, pDC);
}



/*********************************************************/
// CGrphCalcDlg::DrawPaleteButton(int j)
// Pre: none
// Post: none
// Return Value: none
// Intent: draws a button in the current extended palete
/*********************************************************/
void CGrphCalcDlg::DrawPaleteButton(int j, CDC *pDC)
{
	if(m_FullScreen)
		return;

	int x_start;

	if(pDC)
		x_start = RIGHT_BITMAP_INDENT;
	else
		{
		x_start = m_alt_button_start.x;
		pDC = GetDC();
		}

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap=0;

	int y = m_alt_button_start.y - ((j/5) * button_height) - ((j/5) * button_spacing);
	int x = x_start + ((j%5) * button_width) + ((j%5) * button_spacing);

	switch(m_CurrentPalete){
	case NONE:
		return;
	case PROB:
		if(m_ProbButtons[j].state == BUTTON_STATE_UP)
			pOldBitmap = dcMemory.SelectObject(&m_ProbButtons[j].up);
		else
			pOldBitmap = dcMemory.SelectObject(&m_ProbButtons[j].down);
		
		break;
	case TEST:
		if(m_TestButtons[j].state == BUTTON_STATE_UP)
			pOldBitmap = dcMemory.SelectObject(&m_TestButtons[j].up);
		else
			pOldBitmap = dcMemory.SelectObject(&m_TestButtons[j].down);
		break;
	case MATH:
		if(m_MathButtons[j].state == BUTTON_STATE_UP)
			pOldBitmap = dcMemory.SelectObject(&m_MathButtons[j].up);
		else
			pOldBitmap = dcMemory.SelectObject(&m_MathButtons[j].down);
		break;
	case STATS:
		if(m_StatsButtons[j].state == BUTTON_STATE_UP)
			pOldBitmap = dcMemory.SelectObject(&m_StatsButtons[j].up);
		else
			pOldBitmap = dcMemory.SelectObject(&m_StatsButtons[j].down);
		break;
	case LETTERS:
		if(m_LetterButtons[j].state == BUTTON_STATE_UP)
			pOldBitmap = dcMemory.SelectObject(&m_LetterButtons[j].up);
		else
			pOldBitmap = dcMemory.SelectObject(&m_LetterButtons[j].down);
		break;
	}
	
	if(m_CurrentPalete != NONE){
		pDC->BitBlt(x, y, button_width, button_height, &dcMemory, 0, 0, SRCCOPY);
		if(pOldBitmap)
			dcMemory.SelectObject(pOldBitmap);
	}

	if(x_start == m_alt_button_start.x)
		ReleaseDC(pDC);
}


/*********************************************************/
// CGrphCalcDlg::PaleteButtonDetect(CPoint point, int &j)
// Pre: none
// Post: none
// Return Value: none
// Intent: detects which button, if any, point lies in
/*********************************************************/
bool CGrphCalcDlg::PaleteButtonDetect(CPoint point, int &j)
{	
	int buttons;
	CRect button=0;

	switch(m_CurrentPalete){
	case NONE:
		return false;
	case PROB:
		buttons = m_ProbButtons.GetSize();
		break;
	case TEST:
		buttons = m_TestButtons.GetSize();
		break;
	case MATH:
		buttons = m_MathButtons.GetSize();
		break;
	case STATS:
		buttons = m_StatsButtons.GetSize();
		break;
	case LETTERS:
		buttons = m_LetterButtons.GetSize();
		break;
	}
	
	for(j=0; j < buttons; ++j){
		int y = m_alt_button_start.y - ((j/5) * button_height) - ((j/5) * button_spacing);
		int x = m_alt_button_start.x + ((j%5) * button_width) + ((j%5) * button_spacing);
			
		button.SetRect(x, y, x+button_width, y+button_height);
	
		if(button.PtInRect(point))
			return true;
	}
	return false;
}
/*********************************************************/
// CGrphCalcDlg::OnButtonSubmit(int i, int j, CPoint point)
// Pre: none
// Post: none
// Return Value: none
// Intent: when a button is pressed, this function is called
//		   to perform the action associated wiht that button
/*********************************************************/
void CGrphCalcDlg::OnButtonSubmit(int i, int j, CPoint point)
{
	CString insert;
	insert.Empty();

	UpdateData(true);

	switch(i){
	case -1:
		{
			switch(m_CurrentPalete){
				case PROB:
					switch(j){
					case 0:	if(m_Formula.IsEmpty()) insert = "ans!";
							else insert = "!";
							break;
					case 1:	if(m_Formula.IsEmpty()) insert = "ans ncr";
							else insert = "ncr";
							break;
					case 2:	if(m_Formula.IsEmpty()) insert = "ans npr";
							else insert = "npr";
							break;
					case 3: insert = "frand(a:b)"; break;
					case 4: insert = "irand(a:b)"; break;
					}
					break;
				case TEST:
					if(m_Formula.IsEmpty()) insert = "ans ";

					switch(j){
					case 0:	insert += "=="; break;
					case 1:	insert += ">"; break;
					case 2:	insert += "<"; break;
					case 3: insert += ">="; break;
					case 4: insert += "<="; break;
					case 5: insert += "!="; break;
					}
					break;
				case MATH:
					switch(j){
					case 0: insert = "abs(a)"; break;
					case 1:	insert = "fpart(a)"; break;
					case 2: insert = "int(a)"; break;
					case 3: insert = "round(a)"; break;
					case 4: if(m_Formula.IsEmpty()) insert = "ans%";
							else insert = "%";
							break;
					case 5: insert = "min(a:b)"; break;
					case 6: insert = "max(a:b)"; break;
					case 7: insert = "gcd(a:b)"; break;
					case 8: insert = "lcm(a:b)"; break;
					case 9: insert = "mod"; break;
					case 10: insert = "floor(a)"; break;
					case 11: insert = "ceil(a)"; break;
					case 12: insert = "fib(a)"; break;
					}
					break;
				case STATS:
					switch(j){
					case 0: insert = "mean(a:b:c:d)"; break;
					case 1:	insert = "median(a:b:c:d)"; break;
					case 2:	insert = "mode(a:b:c:d)"; break;
					case 3: insert = "stdev(a:b:c:d)"; break;
					case 4: insert = "variance(a:b:c:d)"; break;
					}
					break;
				case LETTERS:
					switch(j){
					case 0: insert = "A"; break;
					case 1: insert = "B"; break;
					case 2: insert = "C"; break;
					case 3: insert = "D"; break;
					case 4: insert = "E"; break;
					case 5: insert = "F"; break;
					}
					break;
			}
			break;
		}
	case 0:
		{
			switch(j){
			case 0: 
					m_CurrentPalete = PaleteE((m_CurrentPalete + 1) % 6);
					if(m_CurrentPalete == NONE)
						m_Buttons[0][0].state = BUTTON_STATE_UP;
					else
						m_Buttons[0][0].state = BUTTON_STATE_DOWN;
					Invalidate(true); 
					break;
			case 1: OnContextMenuSubmit(i, j, point); break;
			case 2: OnContextMenuSubmit(i, j, point); break;
			case 3: OnContextMenuSubmit(i, j, point); break;
			case 4:
				{
					int pos_start, pos_end;
					DWORD span = m_FormulaCtrl.GetEditSel();
					pos_start = span & 0xFF;
					pos_end = (span & 0xFFFF0000)>>10;
					
					m_Formula = m_Formula.Left(pos_start - 1) + m_Formula.Right(m_Formula.GetLength() - pos_start);
					UpdateData(false);
					m_FormulaCtrl.SetEditSel(pos_start-1, pos_start-1);
					break;
				}
			}
			break;
		}
	case 1:
		{
			switch(j){
			case 0:	insert = "log "; break;
			case 1:	insert = "sin "; break;
			case 2:	insert = "cos "; break;
			case 3:	insert = "tan "; break;
			case 4: m_Formula.IsEmpty() ? insert = "ans^" : insert =  "^"; break;
			}
			break;
		}
	case 2:
		{
			switch(j){
			case 0: insert = "ln "; break;
			case 1: if(m_Formula.IsEmpty())
						insert = "ans*10^";
					else
						insert = "*10^"; 
					break;
			case 2: insert = '('; break;
			case 3: insert = ')'; break;
			case 4: if(m_Formula.IsEmpty())
						insert = "ans/";
					else
						insert = "/"; 
					break;
			}
			break;
		}
	case 3:
		{
			switch(j){
			case 0: if(m_Formula.IsEmpty())
						insert = "ans^2";
					else
						insert = "^2"; 
					break;
			case 1: insert = '7'; break;
			case 2: insert = '8'; break;
			case 3: insert = '9'; break;
			case 4: if(m_Formula.IsEmpty())
						insert = "ans*";
					else
						insert = "*"; 
					break;
			}
			break;
		}
	case 4:
		{
			switch(j){
			case 0: insert = "sqrt "; break;
			case 1: insert = '4'; break;
			case 2: insert = '5'; break;
			case 3: insert = '6'; break;
			case 4: if(m_Formula.IsEmpty())
						insert = "ans-";
					else
						insert = "-"; 
					break;
			}
			break;
	}
	case 5:
		{
			switch(j){
			case 0: 
				{
					insert = 'x'; 
					break;
				}
			case 1: insert = '1'; break;
			case 2: insert = '2'; break;
			case 3: insert = '3'; break;
			case 4: if(m_Formula.IsEmpty())
						insert = "ans+";
					else
						insert = "+"; 
					break;
			}
			break;
		}
	case 6:
		{
			switch(j){
			case 0: insert = "ans"; break;
			case 1: insert = '0'; break;
			case 2: if(m_Calculator.m_IntlMode == US)
						insert = '.'; 
					else if(m_Calculator.m_IntlMode == EUROPEAN)
						insert = ','; 
					break;
			case 3: 
				{
					insert = ':'; 
					break;
				}
			case 4: UpdateData(false); OnEnter(); UpdateData(true);
					break;
			}
			break;
		}
	}

	UpdateData(false);
	FormulaInsertion(insert);
}
/*********************************************************/
// CGrphCalcDlg::InitButtons()
// Pre: none
// Post: all buttons are initialzed
// Return Value: none
// Intent: this function loads all the buttons into their
//		   respective member variables
/*********************************************************/
void CGrphCalcDlg::InitButtons()
{
	for(int i(0); i < 7; ++i)
		for(int j(0); j < 5; ++j)
			m_Buttons[j][i].state = BUTTON_STATE_UP;

	m_Buttons[0][0].up.LoadBitmap(IDB_0U);
	m_Buttons[0][0].down.LoadBitmap(IDB_0D);
	m_Buttons[1][0].up.LoadBitmap(IDB_1U);
	m_Buttons[1][0].down.LoadBitmap(IDB_1D);
	m_Buttons[2][0].up.LoadBitmap(IDB_2U);
	m_Buttons[2][0].down.LoadBitmap(IDB_2D);
	m_Buttons[3][0].up.LoadBitmap(IDB_3U);
	m_Buttons[3][0].down.LoadBitmap(IDB_3D);
	m_Buttons[4][0].up.LoadBitmap(IDB_4U);
	m_Buttons[4][0].down.LoadBitmap(IDB_4D);
	m_Buttons[0][1].up.LoadBitmap(IDB_5U);
	m_Buttons[0][1].down.LoadBitmap(IDB_5D);
	m_Buttons[1][1].up.LoadBitmap(IDB_6U);
	m_Buttons[1][1].down.LoadBitmap(IDB_6D);
	m_Buttons[2][1].up.LoadBitmap(IDB_7U);
	m_Buttons[2][1].down.LoadBitmap(IDB_7D);
	m_Buttons[3][1].up.LoadBitmap(IDB_8U);
	m_Buttons[3][1].down.LoadBitmap(IDB_8D);
	m_Buttons[4][1].up.LoadBitmap(IDB_9U);
	m_Buttons[4][1].down.LoadBitmap(IDB_9D);
	m_Buttons[0][2].up.LoadBitmap(IDB_10U);
	m_Buttons[0][2].down.LoadBitmap(IDB_10D);
	m_Buttons[1][2].up.LoadBitmap(IDB_11U);
	m_Buttons[1][2].down.LoadBitmap(IDB_11D);
	m_Buttons[2][2].up.LoadBitmap(IDB_12U);
	m_Buttons[2][2].down.LoadBitmap(IDB_12D);
	m_Buttons[3][2].up.LoadBitmap(IDB_13U);
	m_Buttons[3][2].down.LoadBitmap(IDB_13D);
	m_Buttons[4][2].up.LoadBitmap(IDB_14U);
	m_Buttons[4][2].down.LoadBitmap(IDB_14D);
	m_Buttons[0][3].up.LoadBitmap(IDB_15U);
	m_Buttons[0][3].down.LoadBitmap(IDB_15D);
	m_Buttons[1][3].up.LoadBitmap(IDB_16U);
	m_Buttons[1][3].down.LoadBitmap(IDB_16D);
	m_Buttons[2][3].up.LoadBitmap(IDB_17U);
	m_Buttons[2][3].down.LoadBitmap(IDB_17D);
	m_Buttons[3][3].up.LoadBitmap(IDB_18U);
	m_Buttons[3][3].down.LoadBitmap(IDB_18D);
	m_Buttons[4][3].up.LoadBitmap(IDB_19U);
	m_Buttons[4][3].down.LoadBitmap(IDB_19D);
	m_Buttons[0][4].up.LoadBitmap(IDB_20U);
	m_Buttons[0][4].down.LoadBitmap(IDB_20D);
	m_Buttons[1][4].up.LoadBitmap(IDB_21U);
	m_Buttons[1][4].down.LoadBitmap(IDB_21D);
	m_Buttons[2][4].up.LoadBitmap(IDB_22U);
	m_Buttons[2][4].down.LoadBitmap(IDB_22D);
	m_Buttons[3][4].up.LoadBitmap(IDB_23U);
	m_Buttons[3][4].down.LoadBitmap(IDB_23D);
	m_Buttons[4][4].up.LoadBitmap(IDB_24U);
	m_Buttons[4][4].down.LoadBitmap(IDB_24D);
	m_Buttons[0][5].up.LoadBitmap(IDB_25U);
	m_Buttons[0][5].down.LoadBitmap(IDB_25D);
	m_Buttons[1][5].up.LoadBitmap(IDB_26U);
	m_Buttons[1][5].down.LoadBitmap(IDB_26D);
	m_Buttons[2][5].up.LoadBitmap(IDB_27U);
	m_Buttons[2][5].down.LoadBitmap(IDB_27D);
	m_Buttons[3][5].up.LoadBitmap(IDB_28U);
	m_Buttons[3][5].down.LoadBitmap(IDB_28D);
	m_Buttons[4][5].up.LoadBitmap(IDB_29U);
	m_Buttons[4][5].down.LoadBitmap(IDB_29D);
	m_Buttons[0][6].up.LoadBitmap(IDB_30U);
	m_Buttons[0][6].down.LoadBitmap(IDB_30D);
	m_Buttons[1][6].up.LoadBitmap(IDB_31U);
	m_Buttons[1][6].down.LoadBitmap(IDB_31D);

	if(m_Calculator.m_IntlMode == US){
		m_Buttons[2][6].up.LoadBitmap(IDB_32U);
		m_Buttons[2][6].down.LoadBitmap(IDB_32D);
	}
	else if(m_Calculator.m_IntlMode == EUROPEAN){
		m_Buttons[2][6].up.LoadBitmap(IDB_32U_2);
		m_Buttons[2][6].down.LoadBitmap(IDB_32D_2);
	}

	m_Buttons[3][6].up.LoadBitmap(IDB_33U);
	m_Buttons[3][6].down.LoadBitmap(IDB_33D);
	m_Buttons[4][6].up.LoadBitmap(IDB_34U);
	m_Buttons[4][6].down.LoadBitmap(IDB_34D);

	m_ProbButtons.SetSize(5);
	for(int p(0); p < 5; ++p)
		m_ProbButtons[p].state = BUTTON_STATE_UP;
			
	m_ProbButtons[0].up.LoadBitmap(IDB_PROB_FACT_U);
	m_ProbButtons[0].down.LoadBitmap(IDB_PROB_FACT_D);
	m_ProbButtons[1].up.LoadBitmap(IDB_PROB_NCR_U);
	m_ProbButtons[1].down.LoadBitmap(IDB_PROB_NCR_D);
	m_ProbButtons[2].up.LoadBitmap(IDB_PROB_NPR_U);
	m_ProbButtons[2].down.LoadBitmap(IDB_PROB_NPR_D);
	m_ProbButtons[3].up.LoadBitmap(IDB_PROB_FRAND_U);
	m_ProbButtons[3].down.LoadBitmap(IDB_PROB_FRAND_D);
	m_ProbButtons[4].up.LoadBitmap(IDB_PROB_IRAND_U);
	m_ProbButtons[4].down.LoadBitmap(IDB_PROB_IRAND_D);

	m_TestButtons.SetSize(6);
	for(int t(0); t < 6; ++t)
		m_TestButtons[t].state = BUTTON_STATE_UP;
			
	m_TestButtons[0].up.LoadBitmap(IDB_TEST_EQ_U);
	m_TestButtons[0].down.LoadBitmap(IDB_TEST_EQ_D);
	m_TestButtons[1].up.LoadBitmap(IDB_TEST_GT_U);
	m_TestButtons[1].down.LoadBitmap(IDB_TEST_GT_D);
	m_TestButtons[2].up.LoadBitmap(IDB_TEST_LT_U);
	m_TestButtons[2].down.LoadBitmap(IDB_TEST_LT_D);
	m_TestButtons[3].up.LoadBitmap(IDB_TEST_GTE_U);
	m_TestButtons[3].down.LoadBitmap(IDB_TEST_GTE_D);
	m_TestButtons[4].up.LoadBitmap(IDB_TEST_LTE_U);
	m_TestButtons[4].down.LoadBitmap(IDB_TEST_LTE_D);
	m_TestButtons[5].up.LoadBitmap(IDB_TEST_NE_U);
	m_TestButtons[5].down.LoadBitmap(IDB_TEST_NE_D);

	m_MathButtons.SetSize(13);
	for(int m(0); m < 13; ++m)
		m_MathButtons[m].state = BUTTON_STATE_UP;
			
	m_MathButtons[0].up.LoadBitmap(IDB_MATH_ABS_U);
	m_MathButtons[0].down.LoadBitmap(IDB_MATH_ABS_D);
	m_MathButtons[1].up.LoadBitmap(IDB_MATH_FPART_U);
	m_MathButtons[1].down.LoadBitmap(IDB_MATH_FPART_D);
	//m_MathButtons[2].up.LoadBitmap(IDB_MATH_IPART_U);
	//m_MathButtons[2].down.LoadBitmap(IDB_MATH_IPART_D);
	m_MathButtons[2].up.LoadBitmap(IDB_MATH_INT_U);
	m_MathButtons[2].down.LoadBitmap(IDB_MATH_INT_D);
	m_MathButtons[3].up.LoadBitmap(IDB_MATH_ROUND_U);
	m_MathButtons[3].down.LoadBitmap(IDB_MATH_ROUND_D);
	m_MathButtons[4].up.LoadBitmap(IDB_MATH_PERCENT_U);
	m_MathButtons[4].down.LoadBitmap(IDB_MATH_PERCENT_D);
	m_MathButtons[5].up.LoadBitmap(IDB_MATH_MIN_U);
	m_MathButtons[5].down.LoadBitmap(IDB_MATH_MIN_D);
	m_MathButtons[6].up.LoadBitmap(IDB_MATH_MAX_U);
	m_MathButtons[6].down.LoadBitmap(IDB_MATH_MAX_D);
	m_MathButtons[7].up.LoadBitmap(IDB_MATH_GCD_U);
	m_MathButtons[7].down.LoadBitmap(IDB_MATH_GCD_D);
	m_MathButtons[8].up.LoadBitmap(IDB_MATH_LCM_U);
	m_MathButtons[8].down.LoadBitmap(IDB_MATH_LCM_D);
	m_MathButtons[9].up.LoadBitmap(IDB_MATH_MOD_U);
	m_MathButtons[9].down.LoadBitmap(IDB_MATH_MOD_D);
	m_MathButtons[10].up.LoadBitmap(IDB_MATH_FLOOR_U);
	m_MathButtons[10].down.LoadBitmap(IDB_MATH_FLOOR_D);
	m_MathButtons[11].up.LoadBitmap(IDB_MATH_CEIL_U);
	m_MathButtons[11].down.LoadBitmap(IDB_MATH_CEIL_D);	
	m_MathButtons[12].up.LoadBitmap(IDB_MATH_FIB_U);
	m_MathButtons[12].down.LoadBitmap(IDB_MATH_FIB_D);	

	m_StatsButtons.SetSize(5);
	for(int s(0); s < 5; ++s)
		m_StatsButtons[s].state = BUTTON_STATE_UP;

	m_StatsButtons[0].up.LoadBitmap(IDB_STATS_MEAN_U);
	m_StatsButtons[0].down.LoadBitmap(IDB_STATS_MEAN_D);
	m_StatsButtons[1].up.LoadBitmap(IDB_STATS_MEDIAN_U);
	m_StatsButtons[1].down.LoadBitmap(IDB_STATS_MEDIAN_D);
	m_StatsButtons[2].up.LoadBitmap(IDB_STATS_MODE_U);
	m_StatsButtons[2].down.LoadBitmap(IDB_STATS_MODE_D);
	m_StatsButtons[3].up.LoadBitmap(IDB_STATS_STDEV_U);
	m_StatsButtons[3].down.LoadBitmap(IDB_STATS_STDEV_D);
	m_StatsButtons[4].up.LoadBitmap(IDB_STATS_VARIANCE_U);
	m_StatsButtons[4].down.LoadBitmap(IDB_STATS_VARIANCE_D);

	m_LetterButtons.SetSize(6);
	for(int l(0); l < 6; ++l)
		m_LetterButtons[l].state = BUTTON_STATE_UP;

	m_LetterButtons[0].up.LoadBitmap(IDB_AU);
	m_LetterButtons[0].down.LoadBitmap(IDB_AD);
	m_LetterButtons[1].up.LoadBitmap(IDB_BU);
	m_LetterButtons[1].down.LoadBitmap(IDB_BD);
	m_LetterButtons[2].up.LoadBitmap(IDB_CU);
	m_LetterButtons[2].down.LoadBitmap(IDB_CD);
	m_LetterButtons[3].up.LoadBitmap(IDB_DU);
	m_LetterButtons[3].down.LoadBitmap(IDB_DD);
	m_LetterButtons[4].up.LoadBitmap(IDB_EU);
	m_LetterButtons[4].down.LoadBitmap(IDB_ED);
	m_LetterButtons[5].up.LoadBitmap(IDB_FU);
	m_LetterButtons[5].down.LoadBitmap(IDB_FD);

}

