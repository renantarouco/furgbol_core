#ifndef MULTICAST_RECEIVER_H
#define MULTICAST_RECEIVER_H

#include <boost/asio.hpp>
#include <boost/signals2.hpp>

#include <string>

#define BUFFER_SIZE 8192

class MulticastReceiver
{
public:
    MulticastReceiver(std::string, short);
    boost::signals2::signal<void(char*, size_t)> received;
    inline void run() { _io.run(); }
private:
    boost::asio::io_service _io;
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _sender_endpoint;
    char _buffer[BUFFER_SIZE];
    void handle_receive_from(const boost::system::error_code &, size_t);
};

#endif
