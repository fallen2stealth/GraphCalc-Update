#ifndef _CDEBUG_H_
#define _CDEBUG_H_

#include <string>

class CDebug {

  public:
    CDebug();
    CDebug(bool db);
    void setFlag(bool db);
    void display(string str);
    bool Flagged();

  private:

    bool flag;
};

#endif   _CDEBUG_H_ is defined
