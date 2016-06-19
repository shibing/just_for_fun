#include "echo_server.hpp"
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

namespace shibing {
echo_server::echo_server() : _acceptor(_service), _timer(_service)
{
    asio::ip::tcp::endpoint endpoint{asio::ip::address::from_string("127.0.0.1"), 8080};
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen(128);
    _timing_wheel.resize(5);
}

void echo_server::run()
{
    do_accept();
    do_timer();
    std::thread t1{[this]() { _service.run(); }};
    std::thread t2{[this]() { _service.run(); }};
    t1.join();
    t2.join();
}

void echo_server::on_message(connection_ptr conn)
{
    {
        std::lock_guard<std::mutex> lock{_mutex};
        _timing_wheel.back().insert(conn);
    }
}

void echo_server::do_accept()
{
    _new_connection.reset(new connection{*this, _service});
    _acceptor.async_accept(_new_connection->socket(), [this](const asio::error_code& ec) {
        if (!ec) {
            on_new_connection();
        }
        do_accept();
    });
}

void echo_server::on_new_connection()
{
    {
        std::lock_guard<std::mutex> lock{_mutex};
        _timing_wheel.back().insert(_new_connection);
    }
    _new_connection->start();
}

void echo_server::do_timer()
{
    _timer.expires_from_now(std::chrono::seconds{1});
    _timer.async_wait([this](const asio::error_code& ec) {
        (void)ec;
        on_timeout();
        do_timer();
    });
}

void echo_server::on_timeout()
{
    {
        std::lock_guard<std::mutex> lock{_mutex};
        _timing_wheel.push_back(bucket{});
    }
}
}
