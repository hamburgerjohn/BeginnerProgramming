#include "headers/common.h"
#include "headers/packet.h"


enum class CustomMsgTypes : uint32_t
{
    File, CMD
};

int main()
{
    interwebs::PacketContent<CustomMsgTypes> packet;
    packet.header.id = CustomMsgTypes::CMD;

    



   
    


}
