#pragma once

# include <iostream>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <fcntl.h>
# include <vector>
# include <fstream>
# include <iterator>
# include <unistd.h>

# include "../include/Ping.hpp"
# include "../include/User.hpp"
# include "../include/Chanel.hpp"
# include "../include/Commands.hpp"
# include "../include/ServerException.hpp"
# include "../include/Utils.hpp"

#define	MAX_CLIENT	1000
#define	MAX_CHANEL	100
#define	REQTIME	100
#define	RESTIME	200
#define SERVERNAME "IrcServ"
#define OPERATOR "hzona"


class Ping;
class User;
class Chanel;
class Commands;
class Files;

class Server {
private:
	int							_port;
	int							_socket;
	int							_user_conection;
	std::string					_password;
	fd_set						_readsc;
	fd_set						_writesc;
	fd_set						_acceptsc;
	timeval						_time;
	Ping						req_res[MAX_CLIENT];
	struct sockaddr_in  		_address;
	std::vector <User *>		users;
	std::vector <User *>		history;
	std::vector <Chanel *>		chanels;

public:
	Server();
	Server(char **argv);
	std::string		getPassword();

	void			start_irc();
	void			new_user_connect();
	void			start_read();
	void			disconnect(std::vector<User *>::iterator it);
	void			start_timer(std::vector<User *>::iterator it);

	int				parseMessage(std::vector<User *>::iterator it);
	static void		compileMsg(User &sender, User& recipient, std::string arg1, std::string arg2, std::string arg3);
	static bool		sendMsg(int sd, std::string &msg);
};