#include "../include/Server.hpp"

void error(std::string error);

Server::Server(char **argv){
	for (int i = 0; argv[1][i] != '\0'; i++){
		if (!isdigit(argv[1][i]))
			error("Error: port incorrect. Use only digit.");
	}

	_port = atoi(argv[1]);
	if (_port < 1024 || _port > 49151)
		error("Error: Wrong port. Use 1024 - 49151.");
	_password.assign(argv[2], strlen(argv[2]));
	_user_conection = 0;
	FD_ZERO(&_readsc);
	FD_ZERO(&_writesc);
	FD_ZERO(&_acceptsc);
	_time.tv_sec = 0;
	_time.tv_usec = 0;

	for (int i = 0; i < MAX_CLIENT; i++){
		pthread_mutex_init(&req_res[i].mutex, NULL);
		req_res[i].delay = -1;
		req_res[i].online = 1;
	}

	_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0)
        error("Error: create socket");
	
	int enable = 1;
	if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        error("Error: setsockopt(SO_REUSEADDR) failed");
	
	_address.sin_family = AF_INET;
    _address.sin_addr.s_addr = htonl(INADDR_ANY);
    _address.sin_port = htons(_port);

	if (bind(_socket, (struct sockaddr *)&_address, sizeof(_address)) < 0)
        error("Error: bind socket");
	if (listen(_socket, SOMAXCONN) < 0)
        error("Error: listen socket");
	fcntl(_socket, F_SETFL, O_NONBLOCK);
    std::cout << "IRC Server started. \nPort: " << _port << " Password: " + _password + "\nWaiting for connections ..."<< std::endl;
}

void	Server::new_user_connect(){
	int new_socket;
	int size_addr = sizeof(_address);

	if ((new_socket = accept(_socket, (struct sockaddr *)&_address, (socklen_t *)&size_addr)) < 0)
        throw ServerException::create_newsc();

	fcntl(new_socket, F_SETFL, O_NONBLOCK);
	FD_SET(new_socket, &_readsc);
	req_res[_user_conection].client_sc = new_socket;
	req_res[_user_conection].disconnect = 0;
	users.push_back(new User(_user_conection, new_socket, _address));
	_user_conection++;


	std::cout << "\nNew connection id[" << _user_conection - 1 << "], open socket: " << new_socket << std::endl;
    std::cout << "Ip adress: " << inet_ntoa(_address.sin_addr) << std::endl;
    std::cout << "Port: " << ntohs(_address.sin_port) << std::endl;
}

void	Server::disconnect(std::vector<User *>::iterator it){
	history.push_back(*it);
	for (std::vector<Chanel *>::iterator it2 = chanels.begin(); it2 != chanels.end(); it2++){
		if ((*it2)->isMember(*it)){
			if ((*it2)->isOper(*it) && (*it2)->member_size() > 1 && (*it2)->oper_size() == 1){
				(*it2)->addOper(*it, NULL);
			}
			else if ((*it2)->member_size() == 1){
				chanels.erase(it2);
				break;
			}
			(*it2)->removeOper(*it);
			(*it2)->removeMember(*it);
			(*it2)->sendAll(*it, "QUIT", "Client exit", "");
			break;
		}
	}
	std::cout << "\nUser disconnected, ip: " << inet_ntoa((*it)->getAddr().sin_addr) << " port: " << ntohs((*it)->getAddr().sin_port) << std::endl;
	req_res[(*it)->getId()].online = 0;
	close((*it)->getSd());
	users.erase(it);
}

int	Server::parseMessage(std::vector<User *>::iterator it){
	std::vector<std::string> msg_n = split((*it)->getBuff(), '\n');
	for (size_t i = 0; i < msg_n.size(); i++){

		if (msg_n[i] == "\n")
			continue ;
		std::vector<std::string> args = splitMessage(msg_n[i]);
		std::string msg;

		if (args[0] == "QUIT"){
			disconnect(it);
			return 1;
		}
		else if (args[0] == "PASS" && Commands::cmd_pass(args, it, this))
			return 1;
		else if (args[0] == "USER" && Commands::cmd_user(args,it) && req_res[(*it)->getId()].delay == -1)
			start_timer(it);
		else if (args[0] == "NICK")
			Commands::cmd_nick(args, it, users);
		else if ((args[0] == "PING" && Commands::cmd_ping(args,it)) || (args[0] == "PONG" && Commands::cmd_pong(args,it))){
			if (!req_res[(*it)->getId()].res_wait)
				req_res[(*it)->getId()].res_req = 1;
			else{
				req_res[(*it)->getId()].res_res = 1;
				start_timer(it);
			}
		}
		else if (args[0] == "ADMIN"){
			Commands::cmd_admin(args, it);
		}
		else if (!(*it)->getRegistred() && args[0] != "PASS"){
			User *user = *it;
			std::string msg = compileError(451, *user, args[0], "");
			Server::sendMsg(user->getSd(), msg);
		}
		else if (args[0] == "AWAY"){
			Commands::cmd_away(args, it);
		}
		else if (args[0] == "ISON"){
			Commands::cmd_ison(args, it, users);
		}
		else if (args[0] == "PRIVMSG"){
			Commands::cmd_privmsg(args, it, users, chanels, 0);
		}
		else if (args[0] == "NOTICE"){
			Commands::cmd_privmsg(args, it, users, chanels, 1);
		}
		else if (args[0] == "INFO"){
			Commands::cmd_info(args, it);
		}
		else if (args[0] == "JOIN"){
			Commands::cmd_join(args, it, users, chanels);
		}
		else if (args[0] == "INVITE"){
			Commands::cmd_invite(args, it, users, chanels);
		}
		else if (args[0] == "WHO"){
			Commands::cmd_who(args, it, users, chanels);
		}
		else if (args[0] == "WHOIS"){
			Commands::cmd_whois(args, it, users, chanels);
		}
		else if (args[0] == "PART"){
			Commands::cmd_part(args, it, users, chanels);
		}
		else if (args[0] == "TOPIC"){
			Commands::cmd_topic(args, it, users, chanels);
		}
		else if (args[0] == "KICK"){
			Commands::cmd_kick(args, it, users, chanels);
		}
		else if (args[0] == "MODE"){
			Commands::cmd_mode(args, it, users, chanels);
		}
		else if (args[0] != "PASS"){
			User *user = *it;
			std::string msg = compileError(421, *user, args[0], "");
			Server::sendMsg(user->getSd(), msg);
		}
	}
	(*it)->clearBuff();
	return 0;
}

void	Server::start_read(){
	int read_b;
    int size_adress;
    char buff[1025];

	size_adress = sizeof(_address);
	for (std::vector<User *>::iterator it = users.begin(); it != users.end(); it++){
		int sd = (*it)->getSd();
		if (req_res[(*it)->getId()].disconnect == 1){
				std::cout << "TTTTTTYYYYTTT" << std::endl;
				disconnect(it);
				return;
		}
		if (FD_ISSET(sd, &_readsc)){
			read_b = read(sd, &buff, 1024);
			if (read_b < 0){
				std::cerr << "Error: reading from socket[" << sd << "]" << std::endl;
				return ;
			}
			else if (read_b == 0){
				disconnect(it);
				return;
			}
			else{
				if (!(*it)->createBuff(read_b, buff))
					return ;
					std::cout << "New Buff :" << (*it)->getBuff() << std::endl;
				if ((*it)->getRegistred() && !req_res[(*it)->getId()].res_wait)
					req_res[(*it)->getId()].res_req = 1;
				if (parseMessage(it))
					return;
			}
		}
		(*it)->clearBuff();
	}
}



void	Server::start_irc(){
	int		max_sd;
	int		activity;
	pthread_t check_ping;

	while(1){
		FD_ZERO(&_readsc);
		FD_SET(_socket, &_readsc);
		max_sd = _socket;

		for (int i = 0; i < users.size(); i++){
			if (users[i]->getSd() > 0)
				FD_SET(users[i]->getSd(), &_readsc);
			if (users[i]->getSd() > max_sd)
				max_sd = users[i]->getSd();
		}
		activity = select(max_sd + 1, &_readsc, NULL, NULL, NULL);
        if ((activity < 0) && (errno!=EINTR))
				std::cerr << "timeout select" << std::endl;
		if (FD_ISSET(_socket, &_readsc))
        {
            try {
                 new_user_connect();
            }
            catch (const std::exception& e){
                std::cerr << e.what() << std::endl;
            }
        }
		else
			start_read();
	}
}

void	Server::compileMsg(User &sender, User& recipient, std::string arg1, std::string arg2, std::string arg3){
	std::string msg = ":" + sender.getNickname() + "!" + sender.getUsername() + "@" + std::string(inet_ntoa(sender.getAddr().sin_addr)) + " ";
	if (arg2.empty()){
		msg = msg + arg1 + "\r\n";
	}
	else if (arg3.empty()){
		msg = msg + arg1 + " :" + arg2 + "\r\n";
	}
	else 
		msg = msg + arg1 + " " + arg2 + " :" + arg3 + "\r\n";

	std::cout << "SEND MSG SD: recipient.getSd()" << recipient.getSd() << "\n MSG: " << msg << std::endl;
	sendMsg(recipient.getSd(), msg);
}

bool	Server::sendMsg(int sd, std::string &msg){
	int ret = send(sd, msg.c_str(), msg.length(), 0);
	if (ret >= 0)
		return true;
	std::cerr << "Error occurred while writing to socket" << std::endl; 
	return false;
}

std::string Server::getPassword(){
	return _password;
}

void	Server::start_timer(std::vector<User *>::iterator it){
	pthread_t timer_th;
	req_res[(*it)->getId()].delay = time(0);
	pthread_create(&timer_th, NULL, &ping_request, &req_res[(*it)->getId()]);
	pthread_detach(timer_th);
}
