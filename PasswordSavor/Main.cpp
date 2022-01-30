#include "includes/Main.h"

WX_DECLARE_LIST(wxButton, b_list);

UIMain::UIMain(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(940, 610), wxCAPTION | wxCLOSE_BOX)
{
    id = num_of_lines;
    count = -1;
    m_menuBar = new wxMenuBar;
    m_option = new wxMenu;
    m_option->Append(100, wxT("&Add Password"));
    m_menuBar->Append(m_option, wxT("&Options"));
    SetMenuBar(m_menuBar);


    //Connect(100, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(UIMain::CreateCell));
    Connect(100, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(UIMain::CreateDialog));
    Connect(202, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(UIMain::SubmitDialog));
    Centre();
    LoadCells();
    c_pos = wxPoint(0,0);
}

UIMain::~UIMain()
{

}

void UIMain::LoadCells(){
    using namespace tinyxml2;

    std::string line;
    int num_of_lines;
    std::ifstream myfile("wow.xml");
    while(std::getline(myfile, line)) ++num_of_lines;

    num_of_lines = (num_of_lines-2)/5;

    XMLDocument doc;
    doc.LoadFile("wow.xml");
    XMLElement* root = doc.FirstChildElement()->FirstChildElement("Password");
    XMLElement* child;
    std::string d, u, p;

    for(int i = 0; i < num_of_lines; i++){
        
        child = root->FirstChildElement();
        d = child->GetText();
        child = child->NextSiblingElement();
        u = child->GetText();
        child = child->NextSiblingElement();
        p = child->GetText();

        CreateCell(d,u,p);

        
        
        root = root->NextSiblingElement();

    }
    
}

void UIMain::CreateCell(std::string domain, std::string user, std::string pass)
{
    id++;
    count++;
    
    if(count == 0){
        c_pos.x = 10;
    }
    else if(count == 1){
        c_pos.x += 310;
    }
    else if(count == 2){
        c_pos.x += 310;
    }
    
    
    b_list.Append(new Cell(this, c_pos, domain + "\n" + user, pass, id));

    
    if(count == 2){
        c_pos.y += 110;
        count = -1;
    }
        
   
}

void UIMain::CreateDialog(wxCommandEvent& WXUNUSED(event)){
    m_frame = new wxFrame(this, 400, "Create Button", wxDefaultPosition, wxSize(300, 200), wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP);
    
    m_frame->CenterOnParent();
    m_frame->Show();
    button = new wxButton(m_frame, 202, "Submit", wxPoint(90,115), wxSize(120,25));
    m_domain = new wxTextCtrl(m_frame, 301, "amazon.com", wxPoint(50, 25), wxSize(200,35));
    m_user = new wxTextCtrl(m_frame, 302, "joebob2154@gmail.com", wxPoint(60, 70), wxSize(180,35));
  
}

void UIMain::SubmitDialog(wxCommandEvent& WXUNUSED(event)){

    c_domain = m_domain->GetValue();
    c_user = m_user->GetValue();
    m_frame->Close();

    CreateCell(c_domain.ToStdString(), c_user.ToStdString(), "");
  
}


