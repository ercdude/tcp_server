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

// The function signature for handling a connection
typedef void (*TcpHandler)(TcpConnection*);

/**
 *
 */
class TcpServer
{
public:
    std::string address;
    uint16_t port;

    TcpServer(const std::string& address, uint16_t port);
    ~TcpServer();

    void handle_accept(TcpConnection* connection);

    void add_handler(TcpHandler callback);

    bool listen();

    static std::string read_string(TcpConnection* conn, uint32_t size = 0);

    static void write_string(TcpConnection* conn, const std::string& message);

private:
    //std::unique_ptr<TcpServerImplData> _impl;
    TcpServerImpl *_impl;
};
