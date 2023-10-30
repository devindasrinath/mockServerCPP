//
// Created by devinda on 10/30/23.
//

#ifndef MOCKSYNCSERVER_BOOSTMOCKSYNCSERVER_H
#define MOCKSYNCSERVER_BOOSTMOCKSYNCSERVER_H



#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;



class MockSyncServer {
public:
    MockSyncServer(boost::asio::io_context &io_context, short port)
            : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),io_context_(io_context)  {
        acceptRequests();
    }


private:

    void acceptRequests() {
        tcp::socket socket(io_context_);
        acceptor_.accept(socket);

        // Read the HTTP request
        boost::beast::flat_buffer buffer;
        http::request<http::string_body> request;
        boost::beast::http::read(socket, buffer, request);

        // Handle the request
        std::cout << "Request : " <<request.body()<<std::endl;
        handleRequest(request, socket);

        // Close the socket
        socket.shutdown(tcp::socket::shutdown_send);

        acceptRequests();
    }

    void handleRequest(http::request<http::string_body>& request, tcp::socket& socket) {
        // Prepare the response message
        http::response<http::string_body> response;
        response.version(request.version());
        response.result(http::status::ok);
        response.set(http::field::server, "My HTTP Server");
        response.set(http::field::content_type, "text/plain");
        response.body() = "Hello, World!";
        response.prepare_payload();

        // Send the response to the client
        boost::beast::http::write(socket, response);
    }

    tcp::acceptor acceptor_;
    boost::asio::io_context &io_context_;

};
















#endif //MOCKSYNCSERVER_BOOSTMOCKSYNCSERVER_H
