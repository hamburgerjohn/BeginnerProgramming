#include "includes/Cell.h"

Cell::Cell(wxWindow *parent, wxPoint pos, const wxString& title, std::string pass, int id) 
    : wxButton(parent, id, title, pos, wxSize(300, 100))

{
    filterString(title);
   
    this->pass = pass;
    this->parent = parent;
    Connect(id, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Cell::editCell));
}

Cell::~Cell()
{

}

void Cell::editCell(wxCommandEvent& event){
    CellForm* cellForm = new CellForm(parent, domain, user, pass); 
}

void Cell::filterString(const wxString& title){
    bool checked = false;
    for(int i = 0; i < title.length(); i++){
        
        if(title[i] == '\n'){
            checked = true;
            continue;
        } 

        if(checked) user.append(title[i]);
        else domain.append(title[i]);


    }
}

