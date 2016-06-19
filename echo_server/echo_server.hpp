#pragma once
#include <asio.hpp>
#include <asio/steady_timer.hpp>
#include <unordered_set>
#include <mutex>
#include <boost/circular_buffer.hpp>
#include "connection.hpp"

namespace shibing {
class echo_server {
public:
    echo_server();
    void run();
    void on_message(connection_ptr conn);

private:
    void do_accept();
    void on_new_connection();
    void do_timer();
    void on_timeout();

private:
    asio::io_service _service;
    asio::ip::tcp::acceptor _acceptor;
    connection_ptr _new_connection;
    typedef std::unordered_set<connection_ptr> bucket;
    boost::circular_buffer<bucket> _timing_wheel;
    std::mutex _mutex;
    asio::steady_timer _timer;
};
}
