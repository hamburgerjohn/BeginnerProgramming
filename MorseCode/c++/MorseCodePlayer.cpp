#include "../includes/MorseCodePlayer.h"

using namespace Morse;

MorseCodePlayer::MorseCodePlayer(const char* code) : WriteMorseCode(){ this->code = code;}
MorseCodePlayer::MorseCodePlayer() : WriteMorseCode(){}
MorseCodePlayer::~MorseCodePlayer(){}


void MorseCodePlayer::SetCode(const char* code){
    this->code = code;
}

const std::string&  MorseCodePlayer::GetCode() const{
    return code;
}

void MorseCodePlayer::PlayMorse(){
        
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

