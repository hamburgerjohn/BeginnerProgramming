#include "../includes/MorseCodeDecipher.h"

//-----------------------------__________________________________________________--------------------------------------

int main(int argc, char** argv){
    std::string code;
    Morse::MorseCodePlayer* morse_code = new Morse::MorseCodePlayer();
    
 

    Morse::MorseCodeDecipher* decipher = new Morse::MorseCodeDecipher();

    int choice;
    std::cout << "1: Morse to English 2: English to Morse \n3: Morse from audio 4: English from audio \n5: Morse to audio   6: English to audio";
    std::cin >> choice;
    std::getchar();
    switch(choice){
        case 1:
            std::cout << "Enter Morse: ";
            std::getline(std::cin, code);
            std::cout << decipher->ConvertToEnglish(code) << '\n';
            break;

        case 2:
            std::cout << "Enter English: ";
            std::getline(std::cin, code);
            std::cout << morse_code->ConvertToMorse(code) << '\n';
            break;
        
        case 3:
            std::cout << "Enter filename: ";
            std::getline(std::cin, code);
            decipher->SetFilename(code.c_str());
            decipher->Decipher();
            std::cout << decipher->GetDecipheredCode() << '\n';
            break;

        case 4:
            std::cout << "Enter filename: ";
            std::getline(std::cin, code);
            decipher->SetFilename(code.c_str());
            decipher->Decipher();
            std::cout << decipher->ConvertToEnglish(decipher->GetDecipheredCode()) << '\n';
            break;

        case 5:
            std::cout << "Enter Filename: ";
            std::getline(std::cin, code);
            std::getchar();
            morse_code->InitWAVE(code.c_str());
            std::cout << "Enter Morse: ";
            std::getline(std::cin, code);
            morse_code->SetCode(code.c_str());
            morse_code->PlayMorse();
            break;

        case 6:
            std::cout << "Enter Filename: ";
            std::getline(std::cin, code);
            std::getchar();
            morse_code->InitWAVE(code.c_str());
            std::cout << "Enter Englisg: ";
            std::getline(std::cin, code);
            morse_code->ConvertToMorse(code);
            morse_code->PlayMorse();
            break;

        default:
            std::cout << "retard\n";
            break;
    }


    delete decipher;
    delete morse_code;

    return 0;
}