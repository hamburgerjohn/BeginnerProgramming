#pragma once
#include "Cell.h"
#include <string>
#include <map>

class UIMain : public wxFrame{

public:
	
	UIMain(const wxString& title);
	~UIMain();

	void CreateCell(std::string, std::string, std::string);
	void CreateDialog(wxCommandEvent& event);
	void SubmitDialog(wxCommandEvent& event);
	void LoadCells();


public:

	int id;
	int count;
	int num_of_lines = -1;

	wxMenuBar* m_menuBar;
    wxMenu* m_option;
	wxList b_list;
	wxPoint c_pos;
	wxFrame* m_frame;
	wxButton* button;
	wxTextCtrl* m_domain;
	wxTextCtrl* m_user;
	wxString c_domain;
	wxString c_user;

	std::map<std::string, std::string> cred;


};

