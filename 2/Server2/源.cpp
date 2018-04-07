#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/function.hpp>

using boost::asio::ip::tcp;

void func(boost::asio::ip::tcp::socket peer)
{
	std::string sendMessage = peer.local_endpoint().address().to_string() + "->" + peer.remote_endpoint().address().to_string();
	peer.send(boost::asio::buffer(sendMessage));
}

int main()
{
	try
	{
		boost::asio::io_service _ioserverce;
		tcp::acceptor _accapter(_ioserverce, tcp::endpoint(tcp::v4(), 4567));
		std::list<std::thread> threads;
		while (true)
		{
			tcp::socket _socket(_ioserverce);
			_accapter.accept(_socket);

			threads.push_back(std::thread(&func, std::move(_socket)));
		}
		for (auto & _ele : threads)
			if (_ele.joinable())
				_ele.join();

		_ioserverce.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}