#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using boost::asio::generic::raw_protocol;

int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_service io_service;
		raw_protocol _raw(AF_INET, IPPROTO_IPV4);
		raw_protocol::endpoint _endPoint(tcp::v4(), 4567);
		raw_protocol::socket socket(io_service);
		boost::asio::connect(socket, _endPoint);

		boost::array<char, 128> buf;
		boost::system::error_code error;

		size_t len = socket.read_some(boost::asio::buffer(buf), error);

		if (error)
			throw boost::system::system_error(error); // Some other error.

		std::cout.write(buf.data(), len);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}