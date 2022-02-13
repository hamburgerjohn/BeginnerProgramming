#pragma once
#include "common.h"

namespace interwebs{

    template<typename T>
    struct PacketHeader{
        T id{}; //type of packect being sent/received
        uint32_t size = 0; //size of packet 
    };

    template<typename T>
    struct PacketContent{ //packet structure
        PacketHeader<T> header{}; //packet header
        std::vector<uint8_t> body; //packet payload

        size_t size() const{ //get size of packet
            return body.size();
        }

        friend std::ostream& operator <<(std::ostream& stream, const PacketContent& packet)
        {
            stream << "ID: " << int(packet.header.id) << " Size: " << packet.header.size << " bytes\n";
            return stream;
        }

        template<typename DataType>
        friend PacketContent<T>& operator<<(PacketContent<T>& packet, const DataType& data){
            
            static_assert(std::is_standard_layout<DataType>::value, "Only normal data types allowed pl0x");

            //store inital szie of packet
            size_t size = packet.body.size(); 

            //resize to accomodate for new DataType
            packet.body.resize(packet.body.size() + sizeof(DataType)); 

            //copy data to vector
            std::memcpy(packet.body.data() + size, &data, sizeof(DataType));

            //update header size
            packet.header.size = packet.size();

            return packet;
        }

        template<typename DataType>
        friend PacketContent<T>& operator>>(PacketContent<T>& packet, DataType& data)
        {

            static_assert(std::is_standard_layout<DataType>::value, "Only normal data types allowed pl0x");

            size_t size = packet.body.size() - sizeof(DataType); 
 
            std::memcpy(&data, packet.body.data() + size, sizeof(DataType));

            packet.body.resize(size);

            packet.header.size = packet.size();

            return packet;


        }

    };
}