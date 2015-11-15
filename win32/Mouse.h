/*********************************************************/
// CGrphCalcDlg::OnLButtonDown(UINT nFlags, CPoint point)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles the buttons.  checks to see if the user 
//		   pressed on a button.  If it has it changes the
//		   button image accordingly
/*********************************************************/
void CGrphCalcDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonDown(nFlags, point);

	if(m_FullScreen)
		return;

	int i, j;

	if(ButtonDetect(point, i, j)){
		m_button_down = true;

		if(m_SndEffects){
			m_BDwave.Load("ButtonDown.wav");
			m_BDwave.PlayFromDisk("ButtonDown.wav");
		}
		m_Buttons[j][i].state = BUTTON_STATE_DOWN;
		DrawButton(i, j);
		m_down_i = i;
		m_down_j = j;
	}
	// Check exteneded palete for button click
	else if(PaleteButtonDetect(point, j)){
		m_button_down = true;

		if(m_SndEffects){
			m_BDwave.Load("ButtonDown.wav");
			m_BDwave.PlayFromDisk("ButtonDown.wav");
		}

		switch(m_CurrentPalete){
		case PROB:
			if(m_ProbButtons[j].state == BUTTON_STATE_DOWN){
				m_button_down = false;
				m_ProbButtons[j].state = BUTTON_STATE_UP;
			}else{
				m_down_i = -1;
				m_down_j = j;
				m_ProbButtons[j].state = BUTTON_STATE_DOWN;
			}
			break;
		case TEST:
			if(m_TestButtons[j].state == BUTTON_STATE_DOWN){
				m_button_down = false;
				m_TestButtons[j].state = BUTTON_STATE_UP;
			}else{
				m_down_i = -1;
				m_down_j = j;
				m_TestButtons[j].state = BUTTON_STATE_DOWN;
			}
			break;
		case MATH:
			if(m_MathButtons[j].state == BUTTON_STATE_DOWN){
				m_button_down = false;
				m_MathButtons[j].state = BUTTON_STATE_UP;
			}else{
				m_down_i = -1;
				m_down_j = j;
				m_MathButtons[j].state = BUTTON_STATE_DOWN;
			}
			break;
		case STATS:
			if(m_StatsButtons[j].state == BUTTON_STATE_DOWN){
				m_button_down = false;
				m_StatsButtons[j].state = BUTTON_STATE_UP;
			}else{
				m_down_i = -1;
				m_down_j = j;
				m_StatsButtons[j].state = BUTTON_STATE_DOWN;
			}
			break;
		case LETTERS:
			if(m_LetterButtons[j].state == BUTTON_STATE_DOWN){
				m_button_down = false;
				m_LetterButtons[j].state = BUTTON_STATE_UP;
			}else{
				m_down_i = -1;
				m_down_j = j;
				m_LetterButtons[j].state = BUTTON_STATE_DOWN;
			}
			break;
		}

		DrawPaleteButton(j);
	}
}
/*********************************************************/
// CGrphCalcDlg::OnLButtonUp(UINT nFlags, CPoint point) 
// Pre: none
// Post: none
// Return Value: none
// Intent: to handle a button click.
//		   if a button was down and th emouse is still
//		   over the button handle accordingly
/*********************************************************/
void CGrphCalcDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CDialog::OnLButtonUp(nFlags, point);
	int x(-1), y(-1);

	if(!m_button_down && !ButtonDetect(point, x, y) && !PaleteButtonDetect(point, y))
		return;
	else if(0 == x && 0 == y)
		OnButtonSubmit(0, 0, point);
	else if(ButtonDetect(point, x, y) || PaleteButtonDetect(point, y)){
		if((x == m_down_i && y == m_down_j) || (-1 == m_down_i && y == m_down_j)){
			if(m_SndEffects){
				m_BDwave.Load("ButtonUp.wav");
				m_BDwave.PlayFromDisk("ButtonUp.wav");
			}
			OnButtonSubmit(m_down_i, m_down_j, point);
		}
	}
		
	if(m_button_down){
		m_button_down = false;

		if(m_down_i != -1){
			if(!(m_down_i == 0 && m_down_j == 0))
				m_Buttons[m_down_j][m_down_i].state = BUTTON_STATE_UP;

			DrawButton(m_down_i, m_down_j);
		}
		else{
			switch(m_CurrentPalete){
			case PROB:
				m_ProbButtons[m_down_j].state = BUTTON_STATE_UP;
				break;
			case TEST:
				m_TestButtons[m_down_j].state = BUTTON_STATE_UP;
				break;
			case MATH:
				m_MathButtons[m_down_j].state = BUTTON_STATE_UP;
				break;			
			case STATS:
				m_StatsButtons[m_down_j].state = BUTTON_STATE_UP;
				break;
			case LETTERS:
				m_LetterButtons[m_down_j].state = BUTTON_STATE_UP;
				break;
			}

			DrawPaleteButton(m_down_j);
		}
	}
}
/*********************************************************/
// CGrphCalcDlg::OnMouseMove(UINT nFlags, CPoint point) 
// Pre: none
// Post: none
// Return Value: none
// Intent: tracks the mouse cursor if a button is down
/*********************************************************/
void CGrphCalcDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDialog::OnMouseMove(nFlags, point);
	CRect button;

	ShowToolTips(point);

	//if(m_down_i == 0 && m_down_j == 0 && m_CurrentPalete != NONE)
	if(m_down_i == 0 && m_down_j == 0){
		
		if(nFlags != MK_LBUTTON)
			return;

		int y = m_button_start.y + (m_down_i * button_height) + (m_down_i * button_spacing);
		int x = m_button_start.x + (m_down_j * button_width) + (m_down_j * button_spacing);	
		
		button.SetRect(x, y, x+button_width, y+button_height);
		
		if((!button.PtInRect(point) && m_CurrentPalete == NONE) 
			|| (button.PtInRect(point) && m_CurrentPalete != NONE) )
			m_Buttons[m_down_j][m_down_i].state = BUTTON_STATE_UP;
		else
			m_Buttons[m_down_j][m_down_i].state = BUTTON_STATE_DOWN;

		DrawButton(m_down_i, m_down_j);
		
		return;
	}

	if(m_down_i != -1 && m_button_down){
		
		int y = m_button_start.y + (m_down_i * button_height) + (m_down_i * button_spacing);
		int x = m_button_start.x + (m_down_j * button_width) + (m_down_j * button_spacing);	
		
		button.SetRect(x, y, x+button_width, y+button_height);
		
		if(!button.PtInRect(point) || nFlags != MK_LBUTTON)
			m_Buttons[m_down_j][m_down_i].state = BUTTON_STATE_UP;
		else
			m_Buttons[m_down_j][m_down_i].state = BUTTON_STATE_DOWN;

		DrawButton(m_down_i, m_down_j);
	}
	else if(m_button_down){
		int y = m_alt_button_start.y - ((m_down_j/5) * button_height) - ((m_down_j/5) * button_spacing);
		int x = m_alt_button_start.x + ((m_down_j%5) * button_width) + ((m_down_j%5) * button_spacing);

		button.SetRect(x, y, x+button_width, y+button_height);

		if(!button.PtInRect(point) || nFlags != MK_LBUTTON){
			switch(m_CurrentPalete){
			case NONE:
				return;
			case PROB:
				m_ProbButtons[m_down_j].state = BUTTON_STATE_UP;
				break;
			case TEST:
				m_TestButtons[m_down_j].state = BUTTON_STATE_UP;
				break;
			case MATH:
				m_MathButtons[m_down_j].state = BUTTON_STATE_UP;
				break;
			case STATS:
				m_StatsButtons[m_down_j].state = BUTTON_STATE_UP;
				break;
			case LETTERS:
				m_LetterButtons[m_down_j].state = BUTTON_STATE_UP;
				break;
			}
		}else{
			switch(m_CurrentPalete){
			case NONE:
				return;
			case PROB:
				m_ProbButtons[m_down_j].state = BUTTON_STATE_DOWN;
				break;
			case TEST:
				m_TestButtons[m_down_j].state = BUTTON_STATE_DOWN;
				break;
			case MATH:
				m_MathButtons[m_down_j].state = BUTTON_STATE_DOWN;
				break;
			case STATS:
				m_StatsButtons[m_down_j].state = BUTTON_STATE_DOWN;
				break;
			case LETTERS:
				m_LetterButtons[m_down_j].state = BUTTON_STATE_DOWN;
				break;
			}
		}
		DrawPaleteButton(m_down_j);
	}
}
/*********************************************************/
// CGrphCalcDlg::ShowToolTips(CPoint point)
// Pre: none
// Post: none
// Return Value: none
// Intent: to select appropriate tooltip and display it
/*********************************************************/
void CGrphCalcDlg::ShowToolTips(CPoint point)
{
	int i(-1), j(-1);

	if(!ButtonDetect(point, i, j)){
		i = -1;
		if(!PaleteButtonDetect(point, j))
			return;
	}

	CString msg;

	switch(i){
	case -1:
		{
			switch(m_CurrentPalete){
				case PROB:
					switch(j){
					case 0:	msg = "! - Factorial"; break;
					case 1:	msg = "a nCr b"; break;
					case 2:	msg = "a nPr b"; break;
					case 3: msg = "frand(a:b) - get a random floating point number between a and b"; break;
					case 4: msg = "irand(a:b) - get a random integer between a and b"; break;
					}
					break;
				case TEST:
					switch(j){
					case 0:	msg = "== - Test for equality"; break;
					case 1:	msg = "> - Greater than"; break;
					case 2:	msg = "< - Less than"; break;
					case 3: msg = ">= - Greater than or equal"; break;
					case 4: msg = "<= - Less than or equal"; break;
					case 5: msg = "!= - Not equal"; break;
					}
					break;
				case MATH:
					switch(j){
					case 0: msg = "abs(a) - returns the absolute value of a"; break;
					case 1:	msg = "fpart(a) - returns the fractional part of a"; break;
					//case 2:	msg = "ipart(a) - returns the integer part of a"; break;
					case 2: msg = "int(a) - returns the integer part of a"; break;
					case 3: msg = "round(a) - rounds a to the nerest whole number"; break;
					case 4: msg = "% - precent"; break;
					case 5: msg = "min(a:b) - returns the lower of the two values"; break;
					case 6: msg = "max(a:b) - returns the larger of the two values"; break;
					case 7: msg = "gcd(a:b) - returns the greatest common divisor of a and b"; break;
					case 8: msg = "lcm(a:b) - returns the least common multiple of a and b"; break;
					case 9: msg = "a mod b - returns the remainder of b/a"; break;
					case 10: msg = "floor(a) - returns a rounded to the next lowest integer"; break;
					case 11: msg = "ceil(a) - returns a rounded to the next highest integer"; break;
					case 12: msg = "fib(a) - returns the ath value in the fibonacci sequence"; break;
					}
					break;
				case STATS:
					switch(j){
					case 0: msg = "mean(a:b:c:d) - returns the mean of a,b,c, and d"; break;
					case 1: msg = "med(a:b:c:d) - returns the median of a,b,c, and d"; break;
					case 2: msg = "mode(a:b:c:d) - returns the mode of a,b,c, and d"; break;
					case 3: msg = "stdev(a:b:c:d) - returns the standard deviation of a,b,c, and d"; break;
					case 4: msg = "variance(a:b:c:d) - returns the variance of a,b,c, and d"; break;
					}
					break;
				case LETTERS:
					switch(j){
					case 0: msg = "A"; break;
					case 1: msg = "B"; break;
					case 2: msg = "C"; break;
					case 3: msg = "D"; break;
					case 4: msg = "E"; break;
					case 5: msg = "F"; break;
					}
					break;
			}
			break;
		}
	case 0:
		{
			switch(j){
			case 0: msg = "Changes the current button palette"; break;
			case 1: msg = "Displays the base options"; break;
			case 2: msg = "Displays the constants menu"; break;
			case 3: msg = "Displays the convert menu"; break;
			case 4: msg = "Erases the character to the left of the cursor. Right click for more options"; break;
			}
			break;
		}
	case 1:
		{
			switch(j){
			case 0:	msg = "log -  right click for more options"; break;
			case 1:	msg = "sin - right click for more options"; break;
			case 2:	msg = "cos - right click for more options"; break;
			case 3:	msg = "tan - right click for more options"; break;
			case 4: msg = "^ - exponent"; break;
			}
			break;
		}
	case 2:
		{
			switch(j){
			case 0: msg = "ln - right click for more options"; break;
			case 1: msg = "*10^ - right click for more options"; break;
			}
			break;
		}
	case 3:
		{
			switch(j){
			case 0: msg = "^2 - right click for more options"; break;
			}
			break;
		}
	case 4:
		{
			switch(j){
			case 0: msg = "^(1/2) - square root, right click for more options"; break;
			}
			break;
	}
	case 6:
		{
			switch(j){
			case 0: msg = "ans - previous answer, right click for last 20 answers";	break;
			case 3: msg = ": - colon"; break;
			}
			break;
		}
	}

	if(!msg.IsEmpty())
		m_ToolTips.Set(point, msg);
}
