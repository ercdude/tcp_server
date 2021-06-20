/*
 * MIT License
 *
 * Copyright (c) 2021 ercdude
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "server.h"

#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost::asio;

typedef struct TcpConnection
{
    // The socket of each connection
    ip::tcp::socket socket;
    // Callback handler for each connection
    TcpHandler handler = nullptr;

    TcpConnection(io_service& service, TcpHandler handler)
        : socket(service)
        , handler(handler)
        {}
} TcpConnection;

typedef struct TcpServerImpl
{
    io_service service;
    // The endpoint listener
    ip::tcp::acceptor acceptor;
    TcpConnection* connection = nullptr;

    TcpServerImpl(const std::string& address, uint16_t port)
        : service()
        , acceptor(service,
                   ip::tcp::endpoint(ip::address::from_string(address.c_str()),
                                     port))
        , connection(nullptr)
        {}
} TcpServerImpl;

TcpServer::TcpServer(const std::string& address, uint16_t port)
    : address( address ),
      port( port ),
      _impl(new TcpServerImpl (address, port))
{}

TcpServer::~TcpServer()
{
    delete _impl;
}

void TcpServer::handle_accept(TcpConnection* connection)
{
    connection->handler(connection);

    add_handler( connection->handler );
}

void TcpServer::add_handler(TcpHandler callback)
{
    if(_impl->connection) delete _impl->connection;

    _impl->connection = new TcpConnection( _impl->service, callback );

    // _impl->acceptor->async_accept(*(_impl->connection->socket.get()),
    //                               boost::bind(&TcpServer::handle_accept, this,
    //                                           _impl->connection.get()));
}

std::string TcpServer::read_string(TcpConnection* conn,
                                          uint32_t size)
{
    boost::asio::streambuf buf;
    boost::asio::read_until( conn->socket, buf, "\n" );
    std::string data = boost::asio::buffer_cast<const char*>(buf.data());
    return data;
}

void TcpServer::write_string(TcpConnection* conn,
                                    const std::string& message)
{
    const std::string msg = message + "\n";
    boost::asio::write( conn->socket, boost::asio::buffer(msg) );
}

bool TcpServer::listen()
{
    try
    {
        //_impl->service->run();
        _impl->acceptor.accept(_impl->connection->socket);
        _impl->connection->handler(_impl->connection);
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

