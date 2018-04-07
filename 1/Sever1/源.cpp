#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/function.hpp>

using boost::asio::ip::tcp;

int main()
{
	try
	{
		boost::asio::io_service _ioserverce;
		tcp::acceptor _accapter(_ioserverce, tcp::endpoint(tcp::v4(), 4567));

		while (true)
		{
			tcp::socket _socket(_ioserverce);
			_accapter.accept(_socket);
			_socket.send(boost::asio::buffer("hello world"));
		}

		_ioserverce.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}