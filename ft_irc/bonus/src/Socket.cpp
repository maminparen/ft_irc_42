#include "../include/Socket.hpp"

Socket::Socket() : _fd(0), _host(IRC_SERVER), _port(IRC_SPORT){
	
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd < 0)
	{
		std::cerr << "Cannot create socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	set();
}

Socket::~Socket() {
	close(_fd);
}

void Socket::set(void) {
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	_addr.sin_addr.s_addr = inet_addr(_host.c_str());

	if (_addr.sin_addr.s_addr == static_cast<in_addr_t>(-1)) {
		std::cerr << "Cannot transform socket address" << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Socket::tryToConnect(void) {
		
	if (connect(_fd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0) {
		std::cerr << "Cannot connect with this socket" << std::endl;
		exit(EXIT_FAILURE);
	}

}

int Socket::tryToSend(const std::string &msg) {

	if (send(_fd, msg.c_str(), msg.length(), SO_NOSIGPIPE) < 0) {
		std::cerr << "Cannot send data" << std::endl;
		return 1;
	}
	return 0;
}

std::string Socket::tryToRecv( void ) {
	const int _SOCK_BUFFER_SIZE = 1024;
	
	char buf[_SOCK_BUFFER_SIZE] = {0};
	
	std::string _res;
	int rd = 0;
	while ((rd = recv(_fd, buf, _SOCK_BUFFER_SIZE - 1, 0)) > 0) {
		buf[rd] = 0;
		_res += buf;
	}
	
	return _res;
}

int Socket::getFd(void) {
	return _fd;
}

void Socket::bind(void) {}
Socket::Socket(const Socket &other) { *this = other; }
Socket &Socket::operator=(const Socket &other) {
	if (this != &other) {}
	return *this;
}
