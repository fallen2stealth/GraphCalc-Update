#include <iostream>
#include <string>
#include "CDebug.h"

CDebug::CDebug() : flag(false) {}
CDebug::CDebug(bool db) : flag(db) {}

void CDebug::setFlag(bool db) { flag = db; }

bool CDebug::Flagged(){
    return flag;
}

void CDebug::display(string str)
{
  if (flag) cout << str << endl;
}
