//g++ Uinterface.cpp UIMain.cpp `wx-config --cxxflags --libs std` -lmariadbclient -o program
#include "includes/Interface.h"

wxIMPLEMENT_APP(interface);

interface::interface(){

}

interface::~interface(){

}

bool interface::fileExists(const char* file_name){
    if(FILE* file = fopen(file_name, "r")){
        fclose(file);
        return true;
    }
    else return false;
}

bool interface::OnInit(){

    using namespace tinyxml2;

    if(!fileExists("wow.xml")){

        XMLDocument doc;

        XMLElement* root = doc.NewElement("PasswordSavor");
        root->SetAttribute("Version", "");
        root->SetAttribute("Platform", "");
        doc.InsertFirstChild(root);

        doc.SaveFile("wow.xml");

    }

    m_frame1 = new UIMain("Password Savor");
    m_frame1->Show();
    return true;
}


