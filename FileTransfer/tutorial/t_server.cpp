#include "../headers/common.h"

using namespace boost::asio;

int main()
{
    unsigned short port_num = 3333;

    //create special object of asio::ip::address class
    //that specifies all IP_adresses available on host

    ip::address ip_address = ip::address_v4::any();

    ip::tcp::endpoint ep(ip_address, port_num);

    //the endpoint is created and cane be used to specify the 
    //IP addresses and a port number on which the server
    //application wants to listen for incoming connections

    return 0;
}