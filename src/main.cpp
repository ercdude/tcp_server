/*
 *
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

#include <stdio.h>
#include <stdlib.h>

#include "server.h"

/**
 * Handles a TcpConnection \c conn.
 *
 * It waits until something is read from \c conn, prints the message received and
 * sends a Hello text.
 */
void handle_connection(TcpConnection* conn)
{
        std::string msg = TcpServer::read_string(conn);

        printf("Message received from client: %s\n", msg.c_str());

        TcpServer::write_string(conn, "Hello from server");
}

int main(int argc, char *argv[])
{
        // TODO: adds argv handling and use a config file for reading these attributes.
        std::string address = "127.0.0.1";
        uint16_t port = 666;
        printf("Starting to serve...\n");

        try
        {
                TcpServer server(address, port);
                server.add_handler(&handle_connection);
                server.listen();
        }
        catch( std::exception& e )
        {
                printf("Error: %s", e.what());
                return 1;
        }

        printf("Done serving...\n");
        return 0;
}
