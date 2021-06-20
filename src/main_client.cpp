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

#include <iostream>
#include <boost/asio.hpp>

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;


int main() {
        boost::asio::io_service io_service;
//socket creation
        tcp::socket socket(io_service);
//connection
        socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 666 ));
// request/message from client
        const string msg = "Hello from Client!\n";
        boost::system::error_code error;
        boost::asio::write( socket, boost::asio::buffer(msg), error );
        if( !error ) {
                cout << "Client sent hello message!" << endl;
        }
        else {
                cout << "send failed: " << error.message() << endl;
        }
        // getting response from server
        boost::asio::streambuf receive_buffer;
        boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
        if( error && error != boost::asio::error::eof ) {
                cout << "receive failed: " << error.message() << endl;
        }
        else {
                const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
                cout << data << endl;
        }
        return 0;
}
