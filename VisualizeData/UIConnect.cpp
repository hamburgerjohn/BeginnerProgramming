#include "includes/UIConnect.h"

wxBEGIN_EVENT_TABLE(UIConnect, wxFrame)
    EVT_BUTTON(12, UIMain::OnConnect)
wxEND_EVENT_TABLE()

UIConnect::UIConnect(const char * title, wxPoint point, wxSize size) : wxFrame(nullptr, wxID_ANY, title, point, size){
    
}

UIConnect::~UIConnect(){

}