#pragma once 
#include "wx/wx.h"
#include "database.h"
#include <string>


class UIMain : public wxFrame{

public:
    UIMain();
    UIMain(const char*, wxPoint, wxSize);
    ~UIMain();

private:

    //////////////database Control center attibutes/////////////
    wxButton* d_btn1 = nullptr;
    wxButton* d_btn2 = nullptr;
    wxButton* d_btn3 = nullptr;
    wxTextCtrl* d_txt1 = nullptr;
    wxTextCtrl* d_txt2 = nullptr;
    wxStaticText* d_txt3 = nullptr;
    wxListBox* d_list1 = nullptr;

    UIMain * frame_1;

    void OnRetButtonClicked(wxCommandEvent& evt);

    void OnSqlButtonClicked(wxCommandEvent& evt);

    void OnListBoxClicked(wxCommandEvent& evt);

    ////////////////Connect to Database attributes///////////////

    Database* db1 = nullptr;
    
    wxDECLARE_EVENT_TABLE();

};