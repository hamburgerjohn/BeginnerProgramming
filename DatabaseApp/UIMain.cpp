#include "includes/UIMain.h"


wxBEGIN_EVENT_TABLE(UIMain, wxFrame)
///////Database Control Center////////////////////
    EVT_BUTTON(10, UIMain::OnRetButtonClicked)
    EVT_BUTTON(11, UIMain::OnSqlButtonClicked)
    EVT_LISTBOX(30, UIMain::OnListBoxClicked)

///////Connect To Database/////////////////////////

    EVT_BUTTON(12, UIMain::OnConnectButtonClicked)
wxEND_EVENT_TABLE()


UIMain::UIMain(const char* s, const char* u, const char* p, const char* d) : wxFrame(nullptr, wxID_ANY, "Database Control Center", wxPoint(30, 30), wxSize(800, 600)) //construct Control Center
{
    d_btn1 = new wxButton(this, 10, "Retrieve Data", wxPoint(10,10), wxSize(150, 50)); //submit query
    d_btn2 = new wxButton(this, 11, "Enter Query", wxPoint(440,10), wxSize(150, 50)); //confirm query
    d_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10,70), wxSize(350,30)); //selection from ListBox field
    d_txt2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(440,70), wxSize(350,30));//enter query field
    d_txt3 = new wxStaticText(this, wxID_ANY, "", wxPoint(440,110), wxSize(350,300)); //error console
    d_list1 = new wxListBox(this, 30, wxPoint(10, 110), wxSize(350,300));//rows returned from database
    db1 = new Database(s,u,p,d);
}

UIMain::UIMain() : wxFrame(nullptr, wxID_ANY, "Connect to Database", wxPoint(30, 30), wxSize(600, 400)){ //construct connect page

    l_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20,75), wxSize(125,50));
    l_txt2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(165,75), wxSize(125,50));
    l_txt3 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(310,75), wxSize(125,50));
    l_txt4 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(455,75), wxSize(125,50));
    l_btn1 = new wxButton(this, 12, "Connect", wxPoint(225,250), wxSize(150, 50)); 
}

UIMain::~UIMain()
{
    delete db1;
}

void UIMain::OnListBoxClicked(wxCommandEvent &evt){
    d_txt1->Clear();
    d_txt1->WriteText(evt.GetString());
    evt.Skip();
}

void UIMain::OnRetButtonClicked(wxCommandEvent &evt){

    MYSQL_ROW row;
    MYSQL_RES* res = db1->retrieveData();
    std::string result = "";

    while((row = mysql_fetch_row(res))!= NULL){
        for(int i = 0; i < mysql_num_fields(res); i++){
            
            if(row[i] == NULL){
                result.append("null").append(" | "); 
            }
            else{
               result.append(row[i]).append(" | ");  
            }
            
           
            
        }
        d_list1->AppendString(result);
        result.clear();
    }
    
    evt.Skip();
}

void UIMain::OnSqlButtonClicked(wxCommandEvent& evt){
    d_txt3->SetLabel(db1->setQuery(d_txt2->GetValue()));
    d_list1->Clear();
    d_txt2->Clear();
    evt.Skip();
}


void UIMain::OnConnectButtonClicked(wxCommandEvent& evt){

    if(Database::validate_database(l_txt1->GetValue(),l_txt2->GetValue(),l_txt3->GetValue(),l_txt4->GetValue())){
        frame_2 = new UIMain(l_txt1->GetValue(),l_txt2->GetValue(),l_txt3->GetValue(),l_txt4->GetValue());
        frame_2->Show();
    }
    
    evt.Skip();
}

