#include <communication/multicast_receiver.h>

#include <boost/bind.hpp>

MulticastReceiver::MulticastReceiver(std::string multicast_ip, short multicast_port):
    _io(), _socket(_io)
{
    boost::asio::ip::udp::endpoint listen_endpoint(
                boost::asio::ip::address::from_string("0.0.0.0"),
                static_cast<unsigned short>(multicast_port));
    _socket.open(listen_endpoint.protocol());
    _socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    _socket.bind(listen_endpoint);
    _socket.set_option(boost::asio::ip::multicast::join_group(
                            boost::asio::ip::address::from_string(multicast_ip)));
    _socket.async_receive_from(
                boost::asio::buffer(_buffer, BUFFER_SIZE),
                _sender_endpoint,
                boost::bind(
                    &MulticastReceiver::_handle_receive_from,
                    this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
}

void MulticastReceiver::_handle_receive_from(const boost::system::error_code &ec, size_t bytes_rcvd)
{
    if (!ec) {
        received(_buffer, bytes_rcvd);
        _socket.async_receive_from(
                    boost::asio::buffer(_buffer, BUFFER_SIZE),
                    _sender_endpoint,
                    boost::bind(
                        &MulticastReceiver::_handle_receive_from,
                        this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }
}
