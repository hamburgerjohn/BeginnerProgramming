#pragma once
#include "common.h"
#include "packet.h"

namespace interwebs{

    using namespace boost::asio;
    using ip::tcp;
    using std::cout;

    class Connection : public boost::enable_shared_from_this<Connection>
    {
    private:
        tcp::socket sock;
        std::string message="hello from server";

        enum{max_length = 1024};
        char data[max_length];

    public:
        typedef boost::shared_ptr<Connection> pointer;

        Connection(boost::asio::io_service& io_service) : sock(io_service){}

        static pointer create(boost::asio::io_service& io_service)
        {
            return pointer(new Connection(io_service));
        }

        tcp::socket& socket()
        {
            return sock;
        }

        void start()
        {
            sock.async_read_some(
                boost::asio::buffer(data, max_length), boost::bind(&Connection::HandleWrite,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
  
            sock.async_write_some(
                boost::asio::buffer(message, max_length), boost::bind(&Connection::HandleWrite,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

        }

        void HandleWrite(const boost::system::error_code& err, size_t bytes_transferred)
        {
            if(!err){
                std::cout << "Server sent hello message\n";
            }else{
                std::cerr << "error: " << err.message() << '\n';
                sock.close();
            }
        }
    };
}