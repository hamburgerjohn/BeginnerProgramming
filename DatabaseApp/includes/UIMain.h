#pragma once 
#include "wx/wx.h"
#include "database.h"
#include <string>


class UIMain : public wxFrame{

public:
    UIMain(const char* s, const char* u, const char* p, const char* d);
    UIMain();
    ~UIMain();

private:

    //////////////database Control center attibutes/////////////
    wxButton* d_btn1 = nullptr;
    wxButton* d_btn2 = nullptr;

    wxTextCtrl* d_txt1 = nullptr;
    wxTextCtrl* d_txt2 = nullptr;
    wxStaticText* d_txt3 = nullptr;

    wxListBox* d_list1 = nullptr;

    void OnRetButtonClicked(wxCommandEvent& evt);

    void OnSqlButtonClicked(wxCommandEvent& evt);

    void OnListBoxClicked(wxCommandEvent& evt);

    ////////////////Connect to Database attributes///////////////

    Database* db1 = nullptr;
    UIMain* frame_2 = nullptr;

    wxTextCtrl* l_txt1 = nullptr;
    wxTextCtrl* l_txt2 = nullptr;
    wxTextCtrl* l_txt3 = nullptr;
    wxTextCtrl* l_txt4 = nullptr;
    wxButton* l_btn1 = nullptr;

    void OnConnectButtonClicked(wxCommandEvent& evt);
    
    wxDECLARE_EVENT_TABLE();

};