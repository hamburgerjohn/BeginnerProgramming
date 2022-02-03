#include "includes/MorseCodeDecipher.h"


using namespace Morse;

MorseCodeDecipher::MorseCodeDecipher(const char* filename) : filename(filename){}
MorseCodeDecipher::MorseCodeDecipher(){}
MorseCodeDecipher::~MorseCodeDecipher(){}

void MorseCodeDecipher::SetFilename(const char* filename){
    this->filename = filename;
        
}

const char * MorseCodeDecipher::GetDecipheredCode() const{
    return this->code.c_str();
}

void MorseCodeDecipher::Decipher(){
        
    fd.open(filename, std::ios::in|std::ios::binary|std::ios::ate);
    code = "";

    fd.seekg(0, std::ios::end);
    eof = fd.tellg();

    fd.seekg(44);
    start = fd.tellg();

    int on=0, off=0;

    char * signal = new char[2];

    for(int32_t i=start; i<eof; i += 120){
		
        fd.read(signal, 2);
        uint32_t decoded = BytesToLE16((uint8_t*)signal);
            
        if(decoded != 0)
        {
            if(off > 500)
                code += "   ";
            else if(off > 200)
                code += " "; 
            on++;
            off = 0;
        }
                    
        else
        {
            if(on > 200)
                code += "-";
            else if(on > 100)
                code += ".";

            off++;
            on = 0;
        }

        fd.seekg(i);
			
	}

    fd.close();
    delete[] signal;

}

std::string MorseCodeDecipher::ConvertToEnglish(const std::string& phrase){
    std::string english = "";
    std::string temp = "";
    int space_count=0;

    for(auto i=0; i < phrase.length(); i++){

        if(phrase[i] != 32){
            temp += phrase[i];
            space_count = 0;
        }
        else{
            space_count++;
            helper(english, temp, space_count);
                    
            temp = "";
        }

    }
    helper(english, temp, space_count);
    return english;
}



int32_t MorseCodeDecipher::BytesToLE16(uint8_t byte[2]){
 	return byte[0] | byte[1] << 8;
}

int32_t MorseCodeDecipher::BytesToBE16(uint8_t byte[2]){
 	return byte[1] | byte[0] << 8;
}

void MorseCodeDecipher::helper(std::string& english, std::string& temp, int space_count){
        
    auto findResult = std::find_if(std::begin(m_map), std::end(m_map), [&](const std::pair<int, const char*> &pair)
            {
                return pair.second == temp + " ";
            });

    if(findResult->first != 27)
        english += findResult->first;
            
    else english += 32;
}

