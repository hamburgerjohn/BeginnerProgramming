#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <cstdint>
#include <cmath>
#include <unistd.h>
#include <memory>
#include <map>
#include <cctype>
#include <algorithm>
#include "WAVData.h"


/*#####################################
Memory leaks galore
A ._    I ..    Q __._  Y _.__
B _...  J .___  R ._.   Z __..
C _._.  K _._   S ...
D _..   L ._..  T _
E .     M __    U .._
F .._.  N _.    V ..._
G __.   O ___   W .__  
H ....  P .__.  X _.._

##################################### */

namespace Morse{


#define SAMPLE_RATE 44100
#define BIT_DEPTH 16

std::map<int, const char*> m_map{
        {65 , ".- "}, {66, "-... "}, {67, "-.-. "}, {68, "-.. "}, {69, ". "}, {70 , "..-. "},
        {71, "--. "}, {72, ".... "}, {73, ".. "}, {74, ".--- "}, {75, "-.- "},
        {76 , ".-.. "}, {77, "-- "}, {78, "-. "}, {79, "--- "}, {80, ".--. "}, {81, "--.- "},
        {82 , ".-. "}, {83, "... "}, {84, "- "}, {85, "..- "}, {86, "....- "}, {87, ".-- "},
        {88 , "-..- "}, {89, "-.-- "}, {90, "--.. "}, {32, "  "},
    };


class WaveMaker{

protected:
    
    float freq, amp, angle = 0.0f, offset = 0.0;

    WaveMaker(float freq, float amp) : freq(freq), amp(amp) {
        offset = 2 * M_PI * freq / SAMPLE_RATE;
    }
    ~WaveMaker(){

    }

    float process(){
        auto sample = amp * sin(angle);
        angle += offset;
        return sample;
    }
    
};

class WriteMorseCode : public WaveMaker{

private: 
        std::ofstream audioFile;
        double max_amp;
        std::string filename;
        int preAudioPos, postAudioPos;

protected:
    WriteMorseCode() : WaveMaker(440, 0.5){ }

    ~WriteMorseCode(){}

    void Space(double duration){
        writeAudio(duration, 0);
    }

    void Dot(){
        writeAudio(.1, max_amp);
        Space(.05);
    }

    void Dash(){
        writeAudio(.2, max_amp);
        Space(.05);
    }

    void SetPos(){
        preAudioPos = audioFile.tellp();
    }

    void FinalizeWAVE(){
        audioFile.seekp(preAudioPos - 4);
        writeToFile(audioFile, postAudioPos - preAudioPos, 4);
        audioFile.seekp(4, std::ios::beg);
        writeToFile(audioFile, postAudioPos - 8, 4);
        audioFile.close();
    }

private:

    void writeAudio(double duration, double l_max_amp){
        
        for(int i = 0; i < SAMPLE_RATE * duration; i++)
            {
                
                auto sample = process();
                int intSample = static_cast<int>(sample * l_max_amp);
                
                audioFile.write(reinterpret_cast<char*>(&intSample), 2);
                writeToFile(audioFile, intSample, 2);
                
            }
    }

    void writeToFile(std::ofstream &file, int value, int size){
        file.write(reinterpret_cast<const char*>(&value), size);
    }

public:

    void InitWAVE(const char* filename){
        audioFile.open(filename, std::ios::binary);
        //Header chunk
        audioFile << "RIFF";
        audioFile << "----";
        audioFile << "WAVE";

        //fORMAT chunk
        audioFile << "fmt ";
        writeToFile(audioFile, 16, 4);  //size
        writeToFile(audioFile, 1, 2); //Compression code
        writeToFile(audioFile, 2, 2);   //Number of channels
        writeToFile(audioFile, SAMPLE_RATE, 4); //sample rate
        writeToFile(audioFile, SAMPLE_RATE * BIT_DEPTH /8, 4); //byte rate
        writeToFile(audioFile, BIT_DEPTH/8, 2); //BLOCK aligin
        writeToFile(audioFile, BIT_DEPTH, 2); //bit depth

        audioFile << "data";
        audioFile << "----";

        max_amp = pow(2,BIT_DEPTH -1) -1;
    }
    

};

class MorseCodePlayer : public WriteMorseCode{

private:
    std::string code;
    

public: 
    MorseCodePlayer(const char* code) : WriteMorseCode(){ this->code = code;}
    MorseCodePlayer() : WriteMorseCode(){}

    ~MorseCodePlayer(){/*std::cout << "deleted MorseCodePlater\n";*/}

    void SetCode(const char* code){
        this->code = code;
    }

    const std::string& GetCode() const{
        return code;
    }

    void PlayMorse(){
        
        formatCode();
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

    std::string& ConvertToMorse(std::string& phrase) {
        
        code = "";

        for(auto i=0; i < phrase.length(); i++){
            code += m_map.find(toupper(phrase[i]))->second;
            
        }

        return code;
    }
    

private:

    void formatCode(){
        for(auto i = 0; i < code.length(); i++){
            if(code[i] == '_' || code[i] == '-'){
                code[i] = '-';
            }
        }
    }

};


class MorseCodeDecipher
{
    std::string filename;
    std::string code;
    wav::WAVData wave;

public:
    MorseCodeDecipher(const char* filename) : filename(filename)
    {
        wave.ParseFile(filename);
    }
    MorseCodeDecipher(){}

    ~MorseCodeDecipher(){
        wave.~WAVData();
    }

    void SetFilename(const char* filename){
        this->filename = filename;
        wave.ParseFile(filename);
    }

    const char * GetDecipheredCode() const{
        return this->code.c_str();
    }

    void Decipher(){
        
        int32_t* samples = wave.GetSamples();
        code = "";

        int on=0, off=0;

        for(uint32_t i=0; i<wave.GetNumberOfSamples();i += 1000){
		
            if(*(samples + i) != 0)
            {
                if(off > 35)
                    code += "   ";
                else if(off > 25)
                    code += " "; 
                on++;
                off = 0;
            }
                    
            else
            {
                if(on > 0 && on < 10)
                    code += ".";
                else if(on > 10)
                    code += "-";

                off++;
                on = 0;
            }
			
	    }

    }

    std::string ConvertToEnglish(const std::string& phrase){
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

private:

    void helper(std::string& english, std::string& temp, int space_count){
        
        auto findResult = std::find_if(std::begin(m_map), std::end(m_map), [&](const std::pair<int, const char*> &pair)
                {
                    return pair.second == temp + " ";
                });

        if(findResult->first != 27)
            english += findResult->first;
            
        else english += 32;
    }

};

}



int main(int argc, char* argv[])
{
        
    std::string code;
    Morse::MorseCodePlayer* morse_code = new Morse::MorseCodePlayer();
    
    morse_code->InitWAVE(argv[1]);
        

    std::cout << "\nEnter Englisjh: ";      
    std::getline(std::cin, code);

    morse_code->ConvertToMorse(code);
    morse_code->PlayMorse();

    delete morse_code;

    Morse::MorseCodeDecipher* decipher = new Morse::MorseCodeDecipher();
        
    decipher->SetFilename(argv[1]);
    decipher->Decipher();
    std::cout << decipher->ConvertToEnglish(decipher->GetDecipheredCode());
    delete decipher;


    return 0;
}

