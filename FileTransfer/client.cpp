#include <iostream>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <thread>


std::vector<char> vBuffer(20 * 1024);


//continuously read some data in chunks 
void RetrieveData(asio::ip::tcp::socket& socket){
    
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),[&](std::error_code ec, std::size_t length){

        if(!ec){
            std::cout << "\nRead " << length << " bytes\n\n";

            for(int i = 0; i < length; i++)
                std::cout << vBuffer[i];

            RetrieveData(socket);
        }
        else std::cout << ec.message();
    });
}

/*
Create context for where asio can do its work
and then prime it with jobs for asio to do, or else it would close prematurely
Allow the context to run in it's own thread so is does cause a block

connect to tcp server and when successful prime the asio context with 
an instruction to read some data if it is available

Once primed write data to server 

*/

int main()
{
    asio::error_code ec;

    // Create a context, platform specific interface
    asio::io_context context;

    //Give some fake tasks to asio so the context doesnt finish
    asio::io_context::work idleWork(context);

    //start context
    std::thread thrContext = std::thread([&](){context.run();});

    // Get the address of the host
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("72.53.118.107", ec), 3389);

    //Creat a socket, the contexrt will deliver the implementation
    asio::ip::tcp::socket socket(context);

    //tell socket to try and connect
    socket.connect(endpoint, ec);

    if(!ec){
        std::cout << "Connection Successful\n";
    }else{
        std::cout << "Failed to connect to address:\n" << ec.message() << '\n';
    }

    if(socket.is_open()){
    
        RetrieveData(socket);
        std::string h = "hello there";

        socket.write_some(asio::buffer(h.data(), h.size()), ec);
    }
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2000ms);
    context.stop();
    if(thrContext.joinable()) thrContext.join();

    


}
