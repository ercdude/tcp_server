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

#pragma once

#include <string>
#include <memory>

// incomplete types
struct TcpConnection;
struct TcpServerImpl;

/**
 * The function signature for handling a connection.
 *
 * \sa TcpServer::add_handler
 */
typedef void (*TcpHandler)(TcpConnection*);

/**
 * The \c TcpServer class abstracts a listening TCP connection.
 * It opens a socket with a handler registered to act as a callback once a
 * package reaches to the listening address.
 *
 * To start listening, there is the function \sa TcpServer::listen which
 * remains locked while waiting a connection and running the handler function,
 * which should effectively read and/or write to the socket.
 */
class TcpServer
{
public:
    /** The ip address to be used. E.g: '127.0.0.1', '0.0.0.0'...*/
    std::string address;
    /** The port number to listen.*/
    uint16_t port;

    /** Creates a TcpServer object and initializes \c _impl. */
    TcpServer(const std::string& address, uint16_t port);
    ~TcpServer();

    /** Add a handler which will be called once a connection is stabilised.*/
    void add_handler(TcpHandler callback);

    /**
     * Starts to listen.
     * This function accepts a connection in the configured address and port
     * and calls the registered handler to deal with the connection.
     */
    bool listen();

    /**
     * Reads a string from the connection \c conn until reaches a \n.
     */
    static std::string read_string(TcpConnection* conn, uint32_t size = 0);

    /**
     * Writes the string \c message to the connection \c conn
     * appending a \n at the end.
     */
    static void write_string(TcpConnection* conn, const std::string& message);

private:
    /**
     * Handles the incoming connection by calling the registered handlers.
     * TODO: this function is still not used and therefore may be errors.
     *       This would be used as a callback for async connections.
     */
    void handle_accept(TcpConnection* connection);

    //std::unique_ptr<TcpServerImplData> _impl;
    TcpServerImpl *_impl;
};
