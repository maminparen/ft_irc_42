#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netinet/tcp.h>
#include <sys/types.h>
#include <netdb.h>

#define IRC_SERVER "127.0.0.1"
#define IRC_SPORT 4242
#define IRC_SPASS "4242"
#define IRC_SNAME "IrcServ"
#define IRC_USER "Botinok"
#define IRC_HOST "127.0.0.1"
#define IRC_RNAME "Botik"
#define IRC_NICK "ircbot"


class Socket
{
	private:
		int _fd;
		std::string _host;
		in_port_t _port;
		sockaddr_in _addr;

		Socket(const Socket & other);
		Socket & operator=(const Socket & other);
		void bind(void);
		void set(void);

	public:
		Socket();
		~Socket(void);

		int getFd(void);
		void tryToConnect(void);
		int tryToSend(const std::string &msg);
		std::string tryToRecv( void );
};
