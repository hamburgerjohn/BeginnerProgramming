#pragma once
#include "wx/wx.h"
#include "wx/menu.h"
#include "wx/list.h"
#include <random>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "tinyxml2.h"


class CellForm : public wxFrame{

public:
    CellForm(wxWindow* parent, const wxString& domain, const wxString& user, std::string pass);
    ~CellForm();

    wxStaticText* t_domain;
    wxStaticText* t_user;
    wxStaticText* t_pass;
    wxStaticText* p_special_chars_l;
    wxStaticText* p_numbers_l;
    wxStaticText* p_length_l;

    wxTextCtrl* p_length;
    wxTextCtrl* p_special_chars;
    wxTextCtrl* p_numbers;
    wxTextCtrl* p_prev;

    wxButton* t_password;
    wxButton* t_password_submit;

    std::string p;
    std::string special_char;

    std::string domain;
    std::string user;

    wxList special_list;

    const char* pass_num;
 

    void CreatePassword(wxCommandEvent& event);
    void SubmitPassword(wxCommandEvent& event);
    void CreateCheckBoxes();
    void OutputToXml(const char*);

    wxDECLARE_EVENT_TABLE();
    



};