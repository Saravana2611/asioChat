#pragma once
#include <boost/asio.hpp>


bool isServerRunning(boost::asio::io_context &io_context, boost::asio::ip::tcp::endpoint endpoint);
void write_handler(const boost::system::error_code &error,
                   std::size_t bytes_transferred);