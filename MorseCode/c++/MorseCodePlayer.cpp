#include "../includes/MorseCodePlayer.h"

using namespace Morse;

MorseCodePlayer::MorseCodePlayer(std::string code) : WriteMorseCode(){ this->code = code;}
MorseCodePlayer::MorseCodePlayer() : WriteMorseCode(){}
MorseCodePlayer::~MorseCodePlayer(){}


void MorseCodePlayer::SetCode(std::string code){
    this->code = code;
}

const std::string&  MorseCodePlayer::GetCode() const{
    return code;
}

void MorseCodePlayer::RecordMorse(){
        
    FormatCode();
    SetPos();

    for(auto i = 0; i < code.length(); i++){
            
        if(code[i] == '.') Dot(); 

        else if(code[i] == '-') Dash();

        else{
            Space(.25);
        } 
    }
    FinalizeWAVE();
}

void MorseCodePlayer::PlayMorse(const char* filename){
    std::string a = filename;
    
    std::thread th(&MorseCodePlayer::Execute,this,"cvlc --play-and-exit " + a);

    th.join();
}

std::string& MorseCodePlayer::ConvertToMorse(std::string& phrase) {
        
    code = "";

    for(auto i=0; i < phrase.length(); i++){
        code += m_map.find(toupper(phrase[i]))->second;
            
    }

    return code;
}
    
void MorseCodePlayer::FormatCode(){
    
    for(auto i = 0; i < code.length(); i++){
        if(code[i] == '_' || code[i] == '-'){
            code[i] = '-';
        }
    }
}

void MorseCodePlayer::Execute(std::string cmd){
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
}