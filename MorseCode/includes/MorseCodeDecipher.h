#pragma once
#include "MorseCodePlayer.h"

namespace Morse{


class MorseCodeDecipher{
    
    long long eof, start;
    std::ifstream fd;
    std::string filename;
    std::string code;

public:
    MorseCodeDecipher(const char*);
    MorseCodeDecipher();
    ~MorseCodeDecipher();

    void SetFilename(const char*);

    const char* GetDecipheredCode() const;

    void Decipher();

    std::string ConvertToEnglish(const std::string&);

private:
    int32_t BytesToLE16(uint8_t*);
    int32_t BytesToBE16(uint8_t*);
    void helper(std::string&, std::string&, int);

};

}