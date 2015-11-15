void CGrphCalcDlg::On3DCommand(UINT nID){
#ifndef GRAPHCALC_LIGHT
	m_3DGraphView->Message(nID);
#endif
}
