#pragma once
#include "Main.h"

class interface : public wxApp{

public:
    interface();
    ~interface();

    UIMain* m_frame1 = nullptr;



public:
    virtual bool OnInit();
    bool fileExists(const char* file_name);
    
};