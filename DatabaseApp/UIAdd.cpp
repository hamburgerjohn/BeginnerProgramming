#include "includes/UIAdd.h"

wxBEGIN_EVENT_TABLE(UIAdd, wxFrame)

wxEND_EVENT_TABLE()

UIAdd::UIAdd(std::string& title, wxPoint& point, wxSize& size) : wxFrame(nullptr, wxID_ANY, title, point, size){

}

UIAdd::~UIAdd(){

}