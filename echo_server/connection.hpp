#pragma once
#include <asio.hpp>
#include <memory>

namespace shibing {
class echo_server;
class connection : public std::enable_shared_from_this<connection> {
public:
    connection(echo_server& server, asio::io_service& service);
    ~connection();
    asio::ip::tcp::socket& socket();
    void start();

private:
    void do_read();
    void do_write();

private:
    echo_server& _server;
    asio::io_service& _service;
    asio::ip::tcp::socket _sock;
    enum { BUF_SIZE = 1024 };
    char _buf[BUF_SIZE];
    std::size_t _size;
};
typedef std::shared_ptr<connection> connection_ptr;
typedef std::weak_ptr<connection> weak_connection_ptr;
}
