//g++ Uinterface.cpp UIMain.cpp `wx-config --cxxflags --libs std` -lmariadbclient -o program
#include "includes/UIinterface.h"

wxIMPLEMENT_APP(Uinterface);

Uinterface::Uinterface(){

}

Uinterface::~Uinterface(){

}

bool Uinterface::OnInit(){
    m_frame1 = new UIMain();
    m_frame1->Show();
    return true;
}