#include "includes/net_message.h"


enum class CustomMsgTypes : uint32_t
{
    FireBulet, MovePlayer
};


int main()
{
    olc::net::message<CustomMsgTypes> msg;

    msg.header.id = CustomMsgTypes::MovePlayer;

    int a = 1;
    bool b = true;
    float c = 3.14159f;

    struct{
        float x, y;
    }d[5];

    msg << a << b << c << d;

    a = 99;
    b = false;
    c = 99.0f;

    msg >> d >> c >> b >> a;

    std::cout << msg;
}