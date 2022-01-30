#pragma once
#include "wx/wx.h"
#include "UIMain.h"



class Uinterface : public wxApp{


public:
    Uinterface();
    ~Uinterface();

    UIMain* m_frame1 = nullptr;
    

public:
    virtual bool OnInit();
};