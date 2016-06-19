#include "connection.hpp"
#include "echo_server.hpp"
#include <iostream>

namespace shibing {
connection::connection(echo_server& server, asio::io_service& service)
    : _server(server),
      _service(service),
      _sock(_service)
{
}

connection::~connection()
{
}

asio::ip::tcp::socket& connection::socket()
{
    return _sock;
}

void connection::start()
{
    this->do_read();
}

void connection::do_read()
{
    weak_connection_ptr self = shared_from_this();
    _sock.async_read_some(asio::buffer(_buf, BUF_SIZE), [self, this](const asio::error_code& ec, std::size_t size) {
        if (!ec) {
            auto conn = self.lock();
            if (conn) {
                _server.on_message(conn);
                _size = size;
                do_write();
            }
        } 
    });
}
void connection::do_write()
{
    weak_connection_ptr self = shared_from_this();
    asio::async_write(_sock, asio::buffer(_buf, _size), [self, this](const asio::error_code& ec, std::size_t size) {
        (void)size;
        if (!ec) {
            auto conn = self.lock();
            if (conn) {
                do_read();
            }
        }
    });
}
}
