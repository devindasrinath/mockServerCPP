
#include <boost/asio.hpp>
#include <iostream>
#include "boostMocksyncServer.h"


int main() {
    try {
        boost::asio::io_context io_context;
        MockSyncServer mockSyncServer(io_context, 5001);

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}