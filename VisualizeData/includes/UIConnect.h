#pragma once
#include "wx/wx.h"
#include <string>

class UIConnect : public wxFrame{

public:
    UIConnect(const char*, wxPoint, wxSize);
    ~UIConnect();

private:
    const wxButton * createButton();
    UIConnect * c_frame;

private:
    wxDECLARE_EVENT_TABLE();
};