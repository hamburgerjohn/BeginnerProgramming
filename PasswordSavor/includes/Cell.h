#pragma once 
#include "CellForm.h"

class Cell : public wxButton{

public:

    Cell(wxWindow *parent, wxPoint pos, const wxString& title, std::string, int id);
    ~Cell();

    void editCell(wxCommandEvent& event);
    void filterString(const wxString&);

    CellForm* cellForm;
    wxWindow *parent;
    wxString user;
    wxString domain;
    std::string pass;
};