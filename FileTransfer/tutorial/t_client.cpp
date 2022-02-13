#include "../headers/common.h"
#include <iostream>



int main()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port_num = 3333;

    //used to store information about error that happens
    //while parsing the raw IP-address
    boost::system::error_code ec;

    //using ip protocol version indenpendent 
    //address representation
    boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(raw_ip_address, ec);

    if(ec.value() != 0){
        //Provided IP address is invalid. Breaking execution
        std::cout << "Failed to parse the IP address. Error code: "
        << ec.value() << ". Message: " << ec.message();
        return ec.value();
    }

    boost::asio::ip::tcp::endpoint ep(ip_address, port_num);
    //endpoint is ready and can be used to specify server in the network
    //the client wants to communivate with

    return 0;


}