/*********************************************************/
// CGrphCalcDlg::OnContextMenuSubmit(int i, int j, CPoint point)
// Pre: none none
// Post: none
// Return Value: none
// Intent: when a context menu is called, this function
//		   loads the correct menu and displays it
/*********************************************************/
void CGrphCalcDlg::OnContextMenuSubmit(int i, int j, CPoint point)
{	
	CRect Window;
	GetWindowRect(Window);	//Get Window Coords to subtract from Screen coords.
							//41y and 4x is the difference between the window and client areas
	point.x += Window.left + 4;
	point.y += Window.top + 41;

	CMenu graph;
	bool valid(0);

	int row = i;

	switch (row){
	case 0:
		switch (j){
		case 0:	graph.LoadMenu(IDR_PALETE); valid = true; break;
		case 1: graph.LoadMenu(IDR_BASE); valid = true; break;
		case 2: 
			{
				m_Buttons[j][row].state = BUTTON_STATE_DOWN;
				DrawButton(row, j);

				// Add user entered Constans to Menu
				int num_entries = m_Calculator.m_VarList.GetCount();
				CMenu pSub;
				pSub.CreatePopupMenu();
				int pos = m_UserStart;
				
				for(int i = 0; i < num_entries; ++i){	
					VarListEntryT entry = m_Calculator.m_VarList.GetAt(m_Calculator.m_VarList.FindIndex(i));
					pSub.AppendMenu(MF_STRING, pos, entry.name);
					++pos;
				}
				
				if(num_entries > 0){
					m_MenuConstant.AppendMenu(MF_STRING | MF_POPUP | MF_ENABLED, (UINT)pSub.m_hMenu, "User Entered");
					pSub.Detach();
				}
				
				// END Adding User Entered Constants

				m_MenuConstant.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
										point.x, point.y, this); 
				
				m_Buttons[j][row].state = BUTTON_STATE_UP;
				DrawButton(row, j);

				// remove user entered menu iten now
				m_MenuConstant.RemoveMenu(m_Calculator.m_Constants.GetSize(), MF_BYPOSITION);
				pSub.DestroyMenu();
				// end of removing
				break;
			}
		case 3: 
			{
				m_Buttons[j][row].state = BUTTON_STATE_DOWN;
				DrawButton(row, j);

				m_MenuConvert.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
										point.x, point.y, this); 
				
				m_Buttons[j][row].state = BUTTON_STATE_UP;
				DrawButton(row, j);
				break;
			}
		case 4: graph.LoadMenu(IDR_CLEAR); valid = true; break;			
		}
		break;
	case 1:
		switch (j){
		case 0: graph.LoadMenu(IDR_LOG); valid = true; break;
		case 1: graph.LoadMenu(IDR_SIN); valid = true; break;
		case 2: graph.LoadMenu(IDR_COS); valid = true; break;
		case 3: graph.LoadMenu(IDR_TAN); valid = true; break;
		}
		break;
	case 2:
		switch (j){
		case 0: graph.LoadMenu(IDR_LN); valid = true; break;
		case 1: graph.LoadMenu(IDR_EE); valid = true; break;
		}
		break;
	case 3:
		switch (j){
		case 0:	graph.LoadMenu(IDR_POWERS); valid = true; break;
		}
		break;
	case 4:
		switch (j){
		case 0: graph.LoadMenu(IDR_ROOTS); valid = true; break;
		}
		break;
	case 5:
		switch (j){
		case 0: graph.LoadMenu(IDR_VAR); valid = true; break;
		}
		break;
	case 6:
		switch (j){
		case 0:
			{
				m_Buttons[j][row].state = BUTTON_STATE_DOWN;
				DrawButton(row, j);
				
				CMenu MenuAnswerHistory;
				MenuAnswerHistory.CreatePopupMenu();
				
				for(int i = 0; i < g_Calculator->GetHistoryCount(); ++i){
					MenuAnswerHistory.AppendMenu(MF_STRING, ans_history_start + i, 
												g_Calculator->GetHistoryStrByIndex(i));
				}
				if(g_Calculator->GetHistoryCount() == 0)
					MenuAnswerHistory.AppendMenu(MF_STRING | MF_DISABLED | MF_GRAYED, 
												ans_history_start, "No History");
				
				MenuAnswerHistory.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
												point.x, point.y, this); 

				MenuAnswerHistory.DestroyMenu();
				
				m_Buttons[j][row].state = BUTTON_STATE_UP;
				DrawButton(row, j);				
				break;
			}
		}
		break;
	}

	if(valid){
		m_Buttons[j][row].state = BUTTON_STATE_DOWN;
		DrawButton(row, j);
		graph.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
										point.x, point.y, this);
		m_Buttons[j][row].state = BUTTON_STATE_UP;
		DrawButton(row, j);
	}
}
/*********************************************************/
// CGrphCalcDlg::NaturalLN(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from LN menu
/*********************************************************/
void CGrphCalcDlg::NaturalLN(UINT nID)
{
	CString insert;

	switch(nID){
	case ID_LN_1: insert = "ln "; break;
	case ID_LN_2: insert = "e^"; 	break;
	}
	
	FormulaInsertion(insert);
}
/*********************************************************/
// CGrphCalcDlg::EE(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from EE menu 
/*********************************************************/
void CGrphCalcDlg::EE(UINT nID)
{
	UpdateData(true);
	
	CString insert;

	if(m_Formula.IsEmpty())
		insert = "ans";

	switch(nID){
	case ID_EE_1: insert = "*10^"; break;
	case ID_EE_2: insert = "*10^-"; break;
	}

	UpdateData(false);
	FormulaInsertion(insert);
}
/*********************************************************/
// CGrphCalcDlg::Sin(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from sin menu
/*********************************************************/
void CGrphCalcDlg::Sin(UINT nID)
{
	CString insert;

	switch(nID){
	case ID_SIN_1: insert = "sin "; break;
	case ID_SIN_2: insert = "arcsin "; break;
	case ID_SIN_3: insert = "hypsin "; break;
	case ID_SIN_4: insert = "hyparcsin "; break;
	}
	
	FormulaInsertion(insert);
}
/*********************************************************/
// CGrphCalcDlg::Cos(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from cos menu
/*********************************************************/
void CGrphCalcDlg::Cos(UINT nID)
{
	CString insert;

	switch(nID){
	case ID_COS_1: insert = "cos "; break;
	case ID_COS_2: insert = "arccos "; break;
	case ID_COS_3: insert = "hypcos "; break;
	case ID_COS_4: insert = "hyparccos "; break;
	}
	
	FormulaInsertion(insert);
}
/*********************************************************/
// CGrphCalcDlg::Tan(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from tan menu
/*********************************************************/
void CGrphCalcDlg::Tan(UINT nID)
{
	CString insert;

	switch(nID){
	case ID_TAN_1: insert = "tan "; break;
	case ID_TAN_2: insert = "arctan "; break;
	case ID_TAN_3: insert = "hyptan "; break;
	case ID_TAN_4: insert = "hyparctan "; break;
	}

	FormulaInsertion(insert);
}
/*********************************************************/
// CGrphCalcDlg::Clear(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from clear menu
/*********************************************************/
void CGrphCalcDlg::Clear(UINT nID)
{
	UpdateData(true);
	
	if(nID == ID_CLEAR_1){
		int pos_start, pos_end;
		DWORD span = m_FormulaCtrl.GetEditSel();
		pos_start = span & 0xFF;
		pos_end = (span & 0xFFFF0000)>>10;
		
		m_Formula = m_Formula.Left(pos_start - 1) + m_Formula.Right(m_Formula.GetLength() - pos_start);
		UpdateData(false);
		m_FormulaCtrl.SetEditSel(pos_start-1, pos_start-1);
	}
	
	if(nID == ID_CLEAR_2 || nID == ID_CLEAR_ALL){ m_Formula.Empty(); UpdateData(false); }
	
	if(nID == ID_CLEAR_3){
		int tab = GetActiveGraphTabIndex();
			
		if(tab != -1)
			m_GraphViewList[tab].GraphOff(); 
#ifndef GRAPHCALC_LIGHT
		else if(Is3DGraphActive())
			m_3DGraphView->AllEquationsOff();
#endif
		
		UpdateData(false);
	}
	if(nID == ID_CLEAR_ALL){	
		for(int i(0); i < MAXTABS; ++i)
			m_GraphViewList[i].GraphOff(); 

#ifndef GRAPHCALC_LIGHT
		m_3DGraphView->AllEquationsOff();
#endif

		// update active tab if any
		int tab = GetActiveGraphTabIndex();
		if(tab != -1)
			m_GraphViewList[tab].PaintNow(); 
#ifndef GRAPHCALC_LIGHT
		else if(Is3DGraphActive())
			m_3DGraphView->Invalidate();
#endif
		
		UpdateData(false);
	}
	if(nID == ID_CLEAR_4 || nID == ID_CLEAR_ALL){ m_OutputV.ClearOutput(); UpdateData(false); }
	
	if(nID == ID_CLEAR_5 || nID == ID_CLEAR_ALL){ m_FormulaCtrl.ResetContent(); UpdateData(false); }
	
	UpdateData(false);
}

/*********************************************************/
// CGrphCalcDlg::Var(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from clear menu
/*********************************************************/
void CGrphCalcDlg::Var(UINT nID)
{
	CString insert;

	switch(nID){
	case ID_VAR_X:	insert = "x";	break;
	case ID_VAR_Y:	insert = "y";	break;
	case ID_VAR_T:	insert = "t";	break;
	case ID_VAR_R:	insert = "r";	break;
	}
	FormulaInsertion(insert);
}

/*********************************************************/
// CGrphCalcDlg::Log(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls form log menu
/*********************************************************/
void CGrphCalcDlg::Log(UINT nID)
{
	CString insert;

	switch(nID){
	case ID_LOG_1: insert = "log "; break;
	case ID_LOG_2: insert = "10^"; break;
	case ID_LOG_3: break;
	}
	
	FormulaInsertion(insert);
}
/*********************************************************/
// CGrphCalcDlg::Power(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from power menu
/*********************************************************/
void CGrphCalcDlg::Power(UINT nID)
{
	UpdateData(true);
	
	CString insert;

	if(m_Formula.IsEmpty())
		insert = "ans";

	switch(nID){
	case ID_POWER_1: insert = "^2"; break;
	case ID_POWER_2: insert = "^3"; break;
	case ID_POWER_3: insert = "^4"; break;
	case ID_POWER_4: insert = "^5"; break;
	case ID_POWER_5: insert = "^-1"; break;
	case ID_POWER_6: insert = "^-2"; break;
	case ID_POWER_7: insert = "^-3"; break;
	case ID_POWER_8: insert = "^-4"; break;
	case ID_POWER_9: insert = "^-5"; break;
	}

	UpdateData(false);
	FormulaInsertion(insert);
}
/*********************************************************/
// CGrphCalcDlg::Base(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from base menu
/*********************************************************/
void CGrphCalcDlg::Base(UINT nID)
{
	switch(nID){
	case ID_BASE_2:  m_Calculator.m_base = 2; break;
	case ID_BASE_3:  m_Calculator.m_base = 3; break;
	case ID_BASE_4:  m_Calculator.m_base = 4; break;
	case ID_BASE_5:  m_Calculator.m_base = 5; break;
	case ID_BASE_6:  m_Calculator.m_base = 6; break;
	case ID_BASE_7:  m_Calculator.m_base = 7; break;
	case ID_BASE_8:  m_Calculator.m_base = 8; break;
	case ID_BASE_9:  m_Calculator.m_base = 9; break;
	case ID_BASE_10:  m_Calculator.m_base = 10; break;
	case ID_BASE_11:  m_Calculator.m_base = 11; break;

	case ID_BASE_12:  m_Calculator.m_base = 12; break;
	case ID_BASE_13:  m_Calculator.m_base = 13; break;
	case ID_BASE_14:  m_Calculator.m_base = 14; break;
	case ID_BASE_15:  m_Calculator.m_base = 15; break;
	case ID_BASE_16:  m_Calculator.m_base = 16; break;
	case ID_BASE_17:  m_Calculator.m_base = 17; break;
	case ID_BASE_18:  m_Calculator.m_base = 18; break;
	case ID_BASE_19:  m_Calculator.m_base = 19; break;
	case ID_BASE_20:  m_Calculator.m_base = 20; break;
	case ID_BASE_21:  m_Calculator.m_base = 21; break;

	case ID_BASE_22:  m_Calculator.m_base = 22; break;
	case ID_BASE_23:  m_Calculator.m_base = 23; break;
	case ID_BASE_24:  m_Calculator.m_base = 24; break;
	case ID_BASE_25:  m_Calculator.m_base = 25; break;
	case ID_BASE_26:  m_Calculator.m_base = 26; break;
	case ID_BASE_27:  m_Calculator.m_base = 27; break;
	case ID_BASE_28:  m_Calculator.m_base = 28; break;
	case ID_BASE_29:  m_Calculator.m_base = 29; break;
	case ID_BASE_30:  m_Calculator.m_base = 30; break;
	case ID_BASE_31:  m_Calculator.m_base = 31; break;

	case ID_BASE_32:  m_Calculator.m_base = 32; break;
	case ID_BASE_33:  m_Calculator.m_base = 33; break;
	case ID_BASE_34:  m_Calculator.m_base = 34; break;
	case ID_BASE_35:  m_Calculator.m_base = 35; break;
	case ID_BASE_36:  m_Calculator.m_base = 36; break;
	case ID_BASE_HELP: 	LoadHelpFile(HELP_PAGE_BASES); break;
	}
}
/*********************************************************/
// CGrphCalcDlg::OnConvertBaseMenu(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from base conversion menu
/*********************************************************/
void CGrphCalcDlg::OnConvertBaseMenu(UINT nID)
{
	UpdateData(true);

	CString insert(" convbase ");
	if(m_Formula.IsEmpty())
		insert = "ans convbase";

	switch(nID){
	case ID_CONVER_BASE_2: insert += "2"; break;
	case ID_CONVER_BASE_3: insert += "3"; break;
	case ID_CONVER_BASE_4: insert += "4"; break;
	case ID_CONVER_BASE_5: insert += "5"; break;
	case ID_CONVER_BASE_6: insert += "6"; break;
	case ID_CONVER_BASE_7: insert += "7"; break;
	case ID_CONVER_BASE_8: insert += "8"; break;
	case ID_CONVER_BASE_9: insert += "9"; break;
	case ID_CONVER_BASE_10: insert += "10"; break;
	case ID_CONVER_BASE_11: insert += "11"; break;

	case ID_CONVER_BASE_12: insert += "12"; break;
	case ID_CONVER_BASE_13: insert += "13"; break;
	case ID_CONVER_BASE_14: insert += "14"; break;
	case ID_CONVER_BASE_15: insert += "15"; break;
	case ID_CONVER_BASE_16: insert += "16"; break;
	case ID_CONVER_BASE_17: insert += "17"; break;
	case ID_CONVER_BASE_18: insert += "18"; break;
	case ID_CONVER_BASE_19: insert += "19"; break;
	case ID_CONVER_BASE_20: insert += "20"; break;
	case ID_CONVER_BASE_21: insert += "21"; break;

	case ID_CONVER_BASE_22: insert += "22"; break;
	case ID_CONVER_BASE_23: insert += "23"; break;
	case ID_CONVER_BASE_24: insert += "24"; break;
	case ID_CONVER_BASE_25: insert += "25"; break;
	case ID_CONVER_BASE_26: insert += "26"; break;
	case ID_CONVER_BASE_27: insert += "27"; break;
	case ID_CONVER_BASE_28: insert += "28"; break;
	case ID_CONVER_BASE_29: insert += "29"; break;
	case ID_CONVER_BASE_30: insert += "30"; break;
	case ID_CONVER_BASE_31: insert += "31"; break;

	case ID_CONVER_BASE_32: insert += "32"; break;
	case ID_CONVER_BASE_33: insert += "33"; break;
	case ID_CONVER_BASE_34: insert += "34"; break;
	case ID_CONVER_BASE_35: insert += "35"; break;
	case ID_CONVER_BASE_36: insert += "36"; break;
	}

	UpdateData(false);
	FormulaInsertion(insert);
}
/*********************************************************/
// CGrphCalcDlg::RootsMenu(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from roots menu
/*********************************************************/
void CGrphCalcDlg::RootsMenu(UINT nID)
{	
	UpdateData(true);

	CString insert;
	if(m_Formula.IsEmpty())
		insert = "ans";
	
	switch(nID){
	case ID_R_1: insert = "^(1/2)"; break;	
	case ID_R_2: insert = "^(1/3)"; break;
	case ID_R_3: insert = "^(1/4)"; break;
	case ID_R_4: insert = "^(1/5)"; break;
	case ID_R_5: insert = "^(-1/2)"; break;
	case ID_R_6: insert = "^(-1/3)"; break;
	case ID_R_7: insert = "^(-1/4)"; break;
	case ID_R_8: insert = "^(-1/5)"; break;
	}

	UpdateData(false);
	FormulaInsertion(insert);
}
/*********************************************************/
// CGrphCalcDlg::OnAltMenu(UINT nID)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls from Alt menu
/*********************************************************/
void CGrphCalcDlg::OnAltMenu(UINT nID)
{
	switch(nID){
	case ID_PALETES_PROB: m_CurrentPalete = PROB; m_Buttons[0][0].state = BUTTON_STATE_DOWN; break;
	case ID_PALETES_MATH: m_CurrentPalete = MATH; m_Buttons[0][0].state = BUTTON_STATE_DOWN; break;
	case ID_PALETES_TEST: m_CurrentPalete = TEST; m_Buttons[0][0].state = BUTTON_STATE_DOWN; break;
	case ID_PALETES_STATS: m_CurrentPalete = STATS; m_Buttons[0][0].state = BUTTON_STATE_DOWN; break;
	case ID_PALETES_LETTERS: m_CurrentPalete = LETTERS; m_Buttons[0][0].state = BUTTON_STATE_DOWN; break;
	case ID_PALETES_NONE: m_CurrentPalete = NONE; m_Buttons[0][0].state = BUTTON_STATE_UP; break;
	}
	Invalidate(true);
}

/*********************************************************/
// CGrphCalcDlg::CreateConvertMenus()
// Pre: none
// Post: none
// Return Value: none
// Intent: creats the convert menu
/*********************************************************/
void CGrphCalcDlg::CreateConvertMenus()
{
	m_MenuConvert.CreatePopupMenu();
	int pos = conv_start;
	
	for(int i = 0; i < m_Calculator.m_Categories.GetSize(); ++i){

		int num_entries = m_Calculator.m_Categories[i].entries.GetSize();

		CMenu pSub;
		pSub.CreatePopupMenu();

		for(int j = 0; j < num_entries; ++j){
			////////////
			CMenu pSubSub;
			pSubSub.CreatePopupMenu();

			for(int k = 0; k < num_entries; ++k){
				if(k != j){
					pSubSub.AppendMenu(MF_STRING, pos, m_Calculator.m_Categories[i].entries[k].unit);
					++pos;
				}
			}

			if(num_entries > 0){
				pSub.AppendMenu(MF_STRING | MF_POPUP | MF_ENABLED, (UINT)pSubSub.m_hMenu, m_Calculator.m_Categories[i].entries[j].unit + " ->");
				pSubSub.Detach();
			}
			/////////////
		}

		if(num_entries > 0){
			m_MenuConvert.AppendMenu(MF_STRING | MF_POPUP | MF_ENABLED, (UINT)pSub.m_hMenu, m_Calculator.m_Categories[i].name);
			pSub.Detach();
		}
	}
}
/*********************************************************/
// CGrphCalcDlg::CreateConstantMenus()
// Pre: none
// Post: none
// Return Value: none
// Intent: creates the constants menu
/*********************************************************/
void CGrphCalcDlg::CreateConstantMenus()
{
	m_MenuConstant.CreatePopupMenu();
	int pos = cons_start;

	CreateSubConstantMenu(pos, m_MenuConstant, m_Calculator.m_Constants);
	m_UserStart = pos;
}
/*********************************************************/
// CGrphCalcDlg::CreateSubConstantMenu(int &pos, CMenu &menu, CArray<ConstCatT, ConstCatT> &cons)
// Pre: none
// Post: none
// Return Value: none
// Intent: creates constants submenu items
/*********************************************************/
void CGrphCalcDlg::CreateSubConstantMenu(int &pos, CMenu &menu, CArray<ConstCatT, ConstCatT> &cons)
{	
	for(int i = 0; i < cons.GetSize(); ++i){

		int num_entries(0);
		bool sub_menu(false);
		CMenu pSub;
		pSub.CreatePopupMenu();

		// check for sub menus
		if(cons[i].sub_menu.GetSize() > 0){
			sub_menu = true;
			CreateSubConstantMenu(pos, pSub, cons[i].sub_menu);
		}
		
		// check for constants in this level
		num_entries = cons[i].entries.GetSize();
		
		for(int j = 0; j < num_entries; ++j){
			pSub.AppendMenu(MF_STRING, pos, cons[i].entries[j].name);
			++pos;
		}
	
		if(num_entries > 0 || sub_menu){
			menu.AppendMenu(MF_STRING | MF_POPUP | MF_ENABLED, (UINT)pSub.m_hMenu, cons[i].name);
			pSub.Detach();
		}
	}
}
/*********************************************************/
// CGrphCalcDlg::OnConvertMenu(UINT id)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles calls to convert menu
/*********************************************************/
void CGrphCalcDlg::OnConvertMenu(UINT id)
{
	int i, j(0), k(0);
	UINT start = conv_start;

	bool done(false);

	for(i = 0; i < m_Calculator.m_Categories.GetSize() && !done; ++i){

		int num_entries = m_Calculator.m_Categories[i].entries.GetSize();

		for(j = 0; j < num_entries && !done; ++j){
			for(k = 0; k < num_entries && !done; ++k){
				if(k != j){
					if(start == id)
						done = true;
					++start;
				}
			}

		}
	}

	CString insert;
	if(m_Formula.IsEmpty())
		insert = "ans";

	--i;
	--j;
	--k;

	insert = insert + "(" + m_Calculator.m_Categories[i].entries[j].unit + "->" + m_Calculator.m_Categories[i].entries[k].unit + ")";
	FormulaInsertion(insert);
}

/*********************************************************/
// CGrphCalcDlg::OnConstantMenu(UINT id)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles cals to constant menu
/*********************************************************/
void CGrphCalcDlg::OnConstantMenu(UINT id)
{		
	// look for builting constants
	int pos(cons_start);
	FindConstantMenu(pos, id, m_Calculator.m_Constants, "");

	// look for user entered constants
	int j;
	UINT start = m_UserStart;

	bool done(false);
	int num_entries = m_Calculator.m_VarList.GetCount();

	for(j = 0; j < num_entries && !done; ++j){
		if(start == id){
			done = true;
			VarListEntryT entry = m_Calculator.m_VarList.GetAt(m_Calculator.m_VarList.FindIndex(j));
			FormulaInsertion(entry.name);
		}
		++start;
	}
}

/*********************************************************/
// CGrphCalcDlg::OnAnswerHistoryMenu(UINT id)
// Pre: none
// Post: none
// Return Value: none
// Intent: handles cals to answer history menu
/*********************************************************/
void CGrphCalcDlg::OnAnswerHistoryMenu(UINT id)
{		
	FormulaInsertion(g_Calculator->GetHistoryStrByIndex(id-ans_history_start));
}

/*********************************************************/
// CGrphCalcDlg::FindConstantMenu(int &pos, UINT id, 
//								  CArray<ConstCatT, ConstCatT> &cons, 
//							      CString menu_name)
// Pre: none
// Post: none
// Return Value: none
// Intent: finds the constant that was clicked on
/*********************************************************/
void CGrphCalcDlg::FindConstantMenu(int &pos, UINT id, CArray<ConstCatT, ConstCatT> &cons, CString menu_name)
{	
	bool done(false);

	for(int i = 0; i < cons.GetSize() && !done; ++i){

		if(cons[i].sub_menu.GetSize() > 0)
			FindConstantMenu(pos, id, cons[i].sub_menu, menu_name + cons[i].name + "|");
			
		int num_entries = cons[i].entries.GetSize();
			
		for(int j = 0; j < num_entries && !done; ++j){
			if(pos == id){
				done = true;
				FormulaInsertion("(" + menu_name + cons[i].name + "|" + cons[i].entries[j].name + ")");
			}
			++pos;
		}
	}
}


void CGrphCalcDlg::OnScriptLibraryMenu(UINT id)
{		
	// look for builting constants
	int pos(script_start);
	FindScriptLibraryMenu(pos, id, m_aScripts);
}

// return true if done
bool CGrphCalcDlg::FindScriptLibraryMenu(int &pos, UINT id, ScriptsT &scripts)
{	
	bool done(false);

	for(int i = 0; i < scripts.sub_menu.GetSize() && !done; ++i)
		done = FindScriptLibraryMenu(pos, id, scripts.sub_menu[i]);
						
	for(int j = 0; j < scripts.entries.GetSize() && !done; ++j)
		{
		if(pos == id)
			{
			RunScript(scripts.name + "\\" + scripts.entries[j]);
			return true;
			}
		++pos;
		}

	return false;
}
