#include "includes/CellForm.h"

WX_DECLARE_LIST(wxCheckBox, special_list);

wxBEGIN_EVENT_TABLE(CellForm, wxFrame)
   EVT_BUTTON(203, CellForm::CreatePassword)
   EVT_BUTTON(204, CellForm::SubmitPassword) 

wxEND_EVENT_TABLE()

CellForm::CellForm(wxWindow* parent, const wxString& domain, const wxString& user, std::string pass)
    : wxFrame(parent, wxID_ANY, "", wxDefaultPosition, wxSize(600, 270),wxCAPTION | wxCLOSE_BOX | wxSTAY_ON_TOP)

{

    this->CenterOnParent();
    this->Show();
    this->domain = domain.ToStdString();
    this->user = user.ToStdString();

    special_char = "!@#$%^&*";
    t_domain = new wxStaticText(this, wxID_ANY, "Domain:      " + domain, wxPoint(20, 10), wxSize(400, 20));
    t_user = new wxStaticText(this, wxID_ANY, "Username: " + user, wxPoint(20, 30), wxSize(400, 20));
    t_pass = new wxStaticText(this, wxID_ANY, "Passwrd:  " + pass, wxPoint(20, 50), wxSize(400, 20));
    p_length_l = new wxStaticText(this, wxID_ANY, "Length of password:  ", wxPoint(20, 85), wxSize(250, 20));
    p_special_chars_l = new wxStaticText(this, wxID_ANY, "How many Special Chars:  ", wxPoint(20, 120), wxSize(250, 20));
    p_numbers_l = new wxStaticText(this, wxID_ANY, "How many numbers:  ", wxPoint(20, 155), wxSize(250, 20));

    t_password = new wxButton(this, 203, "Create Password", wxPoint(425, 125), wxSize(150, 50));
    t_password_submit = new wxButton(this, 204, "Submit", wxPoint(425, 185), wxSize(150, 25));

    p_length = new wxTextCtrl(this, 303, "16", wxPoint(200,80), wxSize(35,25));
    p_special_chars = new wxTextCtrl(this, 304, "4", wxPoint(200,115), wxSize(35,25));
    p_numbers = new wxTextCtrl(this, 306, "3", wxPoint(200,150), wxSize(35,25));
    p_prev = new wxTextCtrl(this, 307, "", wxPoint(20,185), wxSize(380,25));
    CreateCheckBoxes();
}

CellForm::~CellForm(){

}

void CellForm::CreateCheckBoxes(){
    
    for(int i = 0; i < 8; i++)
    {
        if(i < 4) special_list.Append(new wxCheckBox(this, 500 + i, special_char[i], wxPoint(250 + (i*40),129), wxSize(40,25)));
        
        else special_list.Append(new wxCheckBox(this, 500 + i, special_char[i], wxPoint(250 + ((i-4)*40),154), wxSize(40,25)));
    
    }
        
}

void CellForm::CreatePassword(wxCommandEvent& event){

    int special_char_length = std::stoi(p_special_chars->GetValue().ToStdString());
    int p_numbers_length = std::stoi(p_numbers->GetValue().ToStdString());
    int p_length_int = std::stoi(p_length->GetValue().ToStdString());
    special_char = "";
    
    if(p_numbers_length + special_char_length > p_length_int){
        wxMessageBox("num of special + num of nums < pass length");
        return;
    }

    for(int i = 0; i < 8; i ++)
        if(((wxCheckBox*)special_list[i])->GetValue())
            special_char += ((wxCheckBox*)special_list[i])->GetLabelText().ToStdString();

        
    

    std::random_device rd;
    std::mt19937 gen(rd());
    p = "";

    for(int i = 0; i < p_length_int; i++){
        
        std::uniform_int_distribution<> distr1(0, 1);
        int a = distr1(gen);

        if(a == 0){
            std::uniform_int_distribution<> distr2(97, 122);
            p += (char)distr2(gen);
        }

        else{
            std::uniform_int_distribution<> distr3(65, 90);
            p += (char)distr3(gen);
        }
    }


    for(int i = 0; i < special_char_length; i++){
        if(special_char == "") break;
        std::uniform_int_distribution<> distr1(0, p_length_int-1);

        int a = distr1(gen);

        if(special_char.find(p[a]) != std::string::npos){
            i--;
            continue;
        }

        std::uniform_int_distribution<> distr2(0, special_char.length()-1);

        int b = distr2(gen);

        
        p[a] = special_char[b];
    }

    for(int i = 0; i < p_numbers_length; i++){
        std::uniform_int_distribution<> distr1(0, p_length_int-1);

        int a = distr1(gen);

        if(!isalpha(p[a])){
            i--;
            continue;
        }

        std::uniform_int_distribution<> distr2(0, 9);
       
        p[a] = std::to_string(distr2(gen))[0];
    }
    
    p_prev->SetValue(p);
    
}

void CellForm::OutputToXml(const char* passwrd){

    std::string line;
    int num_of_lines = 0;
    std::ifstream myfile("wow.xml");
    while(std::getline(myfile, line)) ++num_of_lines;

    std::cout << num_of_lines << '\n';

    std::string p = std::to_string(((num_of_lines-2)/5));
    pass_num = p.c_str();


    using namespace tinyxml2;
    XMLDocument doc;
    doc.LoadFile("wow.xml");
   
    XMLElement* child = (XMLElement*)doc.FirstChildElement();

    XMLElement* subchild = doc.NewElement("Password");
    subchild->SetAttribute("pass_num", pass_num);
    subchild->SetText("\n");
    child->InsertEndChild(subchild);

    XMLElement* domain = doc.NewElement("domain");
    domain->SetText(this->domain.c_str());
    subchild->InsertEndChild(domain);

    XMLElement* user = doc.NewElement("username");
    user->SetText(this->user.c_str());
    subchild->InsertEndChild(user);

    XMLElement* password = doc.NewElement("password");
    password->SetText(passwrd);
    subchild->InsertEndChild(password);

    doc.SaveFile("wow.xml");
}

void CellForm::SubmitPassword(wxCommandEvent& event){
    t_pass->SetLabelText("Passwrd:    " + p_prev->GetValue());
    OutputToXml(p_prev->GetValue().ToStdString().c_str());
}