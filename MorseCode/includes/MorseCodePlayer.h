#pragma once
#include "WriteMorseCode.h"


namespace Morse{

    static std::map<int, const char*> m_map{
        {65 , ".- "}, {66, "-... "}, {67, "-.-. "}, {68, "-.. "}, {69, ". "}, {70 , "..-. "},
        {71, "--. "}, {72, ".... "}, {73, ".. "}, {74, ".--- "}, {75, "-.- "},
        {76 , ".-.. "}, {77, "-- "}, {78, "-. "}, {79, "--- "}, {80, ".--. "}, {81, "--.- "},
        {82 , ".-. "}, {83, "... "}, {84, "- "}, {85, "..- "}, {86, "...- "}, {87, ".-- "},
        {88 , "-..- "}, {89, "-.-- "}, {90, "--.. "}, {32, "  "},
    };

class MorseCodePlayer : public WriteMorseCode{

private:
    std::string code;

public:
    MorseCodePlayer(const char*);
    MorseCodePlayer();

    ~MorseCodePlayer();

    void SetCode(const char*);

    const std::string& GetCode() const;

    void PlayMorse();

    std::string& ConvertToMorse(std::string&);

private:
    void FormatCode();
};

}