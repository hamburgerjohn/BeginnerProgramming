#pragma once
#include "UIMain.h"

class UIAdd : public wxFrame{

public:
    UIAdd(std::string&, wxPoint&, wxSize&);
    ~UIAdd();

private:
    const wxButton * createButton();

private:
    wxDECLARE_EVENT_TABLE();
};