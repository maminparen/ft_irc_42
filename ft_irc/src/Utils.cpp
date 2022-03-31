#include "../include/Utils.hpp"

bool isComma(char sym){
	if (sym == ',')
		return true;
	return false;
}

bool isNotComma(char sym){
	if (sym != ',')
		return true;
	return false;
}

bool isStar(char sym){
	if (sym == '*')
		return true;
	return false;
}

bool isNotStar(char sym){
	if (sym != '*')
		return true;
	return false;
}

bool isEnter(char sym){
	if (sym == '\n')
		return true;
	return false;
}

bool isNotEnter(char sym){
	if (sym != '\n')
		return true;
	return false;
}

bool ismySpace(char sym){
	if (sym == ' ')
		return true;
	return false;
}

bool isNotSpace(char sym){
	if (sym != ' ')
		return true;
	return false;
}
bool ismySpace2(char sym1, char sym2){
	if (sym1 == sym2 && sym1 == ' ')
		return  true;
	return false;
}

std::vector<std::string> split(std::string msg, char sym) {
	std::vector<std::string> ret;
	std::string::iterator i = msg.begin();
	std::string::iterator j = msg.begin();
	while (i != msg.end()){
		if (sym == ' '){
			i = std::find_if(i, msg.end(), isNotSpace);
			j = std::find_if(i, msg.end(), ismySpace);
		}
		else if (sym == '*'){
			i = std::find_if(i, msg.end(), isNotStar);
			j = std::find_if(i, msg.end(), isStar);
		}
		else if (sym == ','){
			i = std::find_if(i, msg.end(), isNotComma);
			j = std::find_if(i, msg.end(), isComma);
		}
		else{
			i = std::find_if(i, msg.end(), isNotEnter);
			j = std::find_if(i, msg.end(), isEnter);
		}
		if (i != msg.end()){
			ret.push_back(std::string(i, j));
			i = j;
		}
	}
	return ret;
}

std::vector<std::string>	splitMessage(std::string msg){
	std::vector<std::string> args;
	std::string::iterator new_end = unique(msg.begin(), msg.end(), ismySpace2);
	msg.erase(new_end, msg.end());

	if (msg.size() && msg[0] == ' ')
		msg.erase(msg.begin());
	if (msg.size() - 1 > 0 && msg[msg.size() - 1] == ' ')
		msg.erase(msg.end() - 1);

	size_t i = msg.find(' ');
	size_t j = msg.find(':');
	//std::cout << "i  ?  j : " << i << "    "  << j << std::endl;
	while (i != std::string::npos && i < j){
		args.push_back(msg.substr(0, i));
		msg.erase(0, i + 1);
		i = msg.find(' ');
		j = msg.find(':');
	}
	args.push_back(msg);

	// std::string msg2;
	// for (int c = 0; c < args.size(); c++)
	// 						msg2 += args[c];
	// 					std::cout << "msg: " + msg2  << std::endl;

	for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++){
		if ((*it).front() == ':'){
			(*it).erase(0, 1);
		}
	}
	return args;
}

std::string compileError(int index, User &user, std::string arg1, std::string arg2) {
	std::string msg = ":" + (std::string)SERVERNAME + " " + std::to_string(index) + " " + user.getNickname();
	if (index == 401)
		msg += " " + arg1 + " :No such nick/channel\n";
	else if(index == 402)
		msg += " " + arg1 + " :No such server\n";
	else if(index == 403)
		msg += " " + arg1 + " :No such channel\n";
	else if(index == 404)
		msg += " " + arg1 + " :Cannot send to channel\n";
	else if(index == 405)
		msg += " " + arg1 + " :You have joined too many channels\n";
	else if(index == 406)
		msg += " " + arg1 + " :There was no such nickname\n";
	else if(index == 407)
		msg += " " + arg1 + " :Duplicate recipients. No arg1 delivered\n";
	else if(index == 409)
		msg += " :No origin specified\n";
	else if(index == 411)
		msg += " :No recipient given (" + arg1 + ")\n";
	else if(index == 412)
		msg += " :No text to send\n";
	else if(index == 413)
		msg += " " + arg1 + " :No toplevel domain specified\n";
	else if(index == 414)
		msg += " " + arg1 + " :Wildcard in toplevel domain\n";
	else if(index == 421)
		msg += " " + arg1 + " :Unknown command\n";
	else if(index == 422)
		msg += " :MOTD File is missing\n";
	else if(index == 423)
		msg += " " + arg1 + " :No administrative info available\n";
	else if(index == 424)
		msg += " :File error doing \n" + arg1 + " on " + arg2 + "\n";
	else if(index == 431)
		msg += " :No nickname given\n";
	else if(index == 432)
		msg += " " + arg1 + " :Erroneus nickname\n";
	else if(index == 433)
		msg += " " + arg1 + " :Nickname is already in use\n";
	else if(index == 436)
		msg += " " + arg1 + " :Nickname collision KILL\n";
	else if(index == 441)
		msg += " " + arg1 + " " + arg2 + " :They aren't on that channel\n";
	else if(index == 442)
		msg += " " + arg1 + " :You're not on that channel\n";
	else if(index == 443)
		msg += " " + arg1 + " " + arg2 + " :is already on channel\n";
	else if(index == 444)
		msg += " " + arg1 + " :User not logged in\n";
	else if(index == 445)
		msg += " :SUMMON has been disabled\n";
	else if(index == 446)
		msg += " :USERS has been disabled\n";
	else if(index == 451)
		msg += " :You have not registered\n";
	else if(index == 461)
		msg += " " + arg1 + " :Not enough parameters\n";
	else if(index == 462)
		msg += " :You may not reregister\n";
	else if(index == 463)
		msg += " :Your host isn't among the privileged\n";
	else if(index == 464)
		msg += " :Password incorrect\n";
	else if(index == 465)
		msg += " :You are banned from this server\n";
	else if(index == 467)
		msg += " " + arg1 + " :Channel key already set\n";
	else if(index == 471)
		msg += " " + arg1 + " :Cannot join channel (+l)\n";
	else if(index == 472)
		msg += " " + arg1 + " :is unknown mode char to me\n";
	else if(index == 473)
		msg += " " + arg1 + " :Cannot join channel (+i)\n";
	else if(index == 474)
		msg += " " + arg1 + " :Cannot join channel (+b)\n";
	else if(index == 475)
		msg += " " + arg1 + " :Cannot join channel (+k)\n";
	else if(index == 481)
		msg += " :Permission Denied- You're not an IRC operator\n";
	else if(index == 482)
		msg += " " + arg1 + " :You're not channel operator\n";
	else if(index == 483)
		msg += " :You cant kill a server!\n";
	else if(index == 491)
		msg += " :No O-lines for your host\n";
	else if(index == 501)
		msg += " :Unknown MODE flag\n";
	else if(index == 502)
		msg += " :Cant change mode for other users\n";
	else
		msg += "UNKNOWN ERROR\n";
	return msg;
}

std::string compileReply(int index, User &user, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5, std::string arg6, std::string arg7, std::string arg8) {
	std::string msg = ":" + (std::string)SERVERNAME + " " + std::to_string(index) + " " + user.getNickname() + " " ;
	if(index == 302)
		msg += ":" + arg1 + "\n";
	else if(index == 303)
		msg += ":" + arg1 + "\n";
	else if(index == 301)
		msg += arg1 + " :" + arg2 + "\n";
	else if(index == 305)
		msg += ":You are no longer marked as being away\n";
	else if(index == 306)
		msg += ":You have been marked as being away\n";
	else if(index == 311)
		msg += arg1 + " " + arg2 + " " + arg3 + " * :" + arg4 + "\n";
	else if(index == 312)
		msg += arg1 + " " + arg2 + " :" + arg3 + "\n";
	else if(index == 313)
		msg += arg1 + " :is an IRC operator\n";
	else if(index == 317)
		msg += arg1 + " " + arg2 + " " + arg3 + " :seconds idle\n";
	else if(index == 318)
		msg += arg1 + " :End of /WHOIS list\n";
	else if(index == 319)
		msg += arg1 + " :" + arg2 + "\n";
	else if(index == 314)
		msg += arg1 + " " + arg2 + " " + arg3 + " * :" + arg4 + "\n";
	else if(index == 369)
		msg += arg1 + " :End of WHOWAS\n";
	else if(index == 321)
		msg += "Channel :Users  Name\n";
	else if(index == 322)
		msg += arg1 + " " + arg2 + " :" + arg3 + "\n";
	else if(index == 323)
		msg += ":End of /LIST\n";
	else if(index == 324)
		msg += arg1 + " +" + arg2 + "\n";
	else if(index == 331)
		msg += arg1 + " :No topic is set\n";
	else if(index == 332)
		msg += arg1 + " :" + arg2 + "\n";
	else if(index == 341)
		msg += arg1 + " " + arg2 + "\n";
	else if(index == 342)
		msg += arg1 + " :Summoning user to IRC\n";
	else if(index == 351)
		msg += arg1 + "." + arg2 + " " + arg3 + " :" + arg4 + "\n";
	else if(index == 352)
		msg += arg1 + " " + arg2 + " " + arg3 + " " + arg4 + " " + arg5 + " " + arg6 + " :" + arg7 + " " + arg8 + "\n";
	else if(index == 315)
		msg += arg1 + " :End of /WHO list\n";
	else if(index == 353)
		msg += arg1 + " :" + arg2 + "\n";
	else if(index == 366)
		msg += arg1 + " :End of /NAMES list\n";
	else if(index == 364)
		msg += arg1 + " " + arg2 + ": " + arg3 + " " + arg4 + "\n";
	else if(index == 365)
		msg += arg1 + " :End of /LINKS list\n";
	else if(index == 367)
		msg += arg1 + " " + arg2 + "\n";
	else if(index == 368)
		msg += arg1 + " :End of channel ban list\n";
	else if(index == 371)
		msg += ":" + arg1 + "\n";
	else if(index == 374)
		msg += ":End of /INFO list\n";
	else if(index == 375)
		msg += ":- " + arg1 + " Message of the day - \n";
	else if(index == 372)
		msg += ":- " + arg1 + "\n";
	else if(index == 376)
		msg += ":End of /MOTD command\n";
	else if(index == 381)
		msg += ":You are now an IRC operator\n";
	else if(index == 382)
		msg += arg1 + " :Rehashing\n";
	else if(index == 391)
		msg += arg1 + " :" + arg2 + "\n";
	else if(index == 392)
		msg += ":UserID   Terminal  Host\n";
	else if(index == 393)
		msg += ":%-8s %-9s %-8s\n";
	else if(index == 394)
		msg += ":End of users\n";
	else if(index == 395)
		msg += ":Nobody logged in\n";
	else if(index == 200)
		msg += "Link " + arg1 + " " + arg2 + " " + arg3 + "\n";
	else if(index == 201)
		msg += "Try. " + arg1 + " " + arg2 + "\n";
	else if(index == 202)
		msg += "H.S. " + arg1 + " " + arg2 + "\n";
	else if(index == 203)
		msg += "???? " + arg1 + " " + arg2 + "\n";
	else if(index == 204)
		msg += "Oper " + arg1 + " " + arg2 + "\n";
	else if(index == 205)
		msg += "User " + arg1 + " " + arg2 + "\n";
	else if(index == 206)
		msg += "Serv " + arg1 + " " + arg2 + "S " + arg3 + "C " + arg4 + " " + arg5 + "@" + arg6 + "\n";
	else if(index == 208)
		msg += arg1 + " 0 " + arg2 + "\n";
	else if(index == 261)
		msg += "File " + arg1 + " " + arg2 + "\n";
	else if(index == 211)
		msg += arg1 + " " + arg2 + " " + arg3 + " " + arg4 + " " + arg5 + " " + arg6 + " " + arg7 + "\n";
	else if(index == 212)
		msg += arg1 + " " + arg2 + "\n";
	else if(index == 213)
		msg += "C " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n";
	else if(index == 214)
		msg += "N " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n";
	else if(index == 215)
		msg += "I " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n";
	else if(index == 216)
		msg += "K " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n";
	else if(index == 218)
		msg += "Y " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n";
	else if(index == 219)
		msg += arg1 + " :End of /STATS report\n";
	else if(index == 241)
		msg += "L " + arg1 + " * " + arg2 + " " + arg3 + "\n";
	else if(index == 242)
		msg += ":Server Up %d days %d:%02d:%02d\n";
	else if(index == 243)
		msg += "O " + arg1 + " * " + arg2 + "\n";
	else if(index == 244)
		msg += "H " + arg1 + " * " + arg2 + "\n";
	else if(index == 221)
		msg += arg1 + "\n";
	else if(index == 251)
		msg += ":There are " + arg1 + " users and " + arg2 + " invisible on " + arg3 + " servers\n";
	else if(index == 252)
		msg += arg1 + " :operator(s) online\n";
	else if(index == 253)
		msg += arg1 + " :unknown connection(s)\n";
	else if(index == 254)
		msg += arg1 + " :channels formed\n";
	else if(index == 255)
		msg += ":I have " + arg1 + " clients and " + arg2 + " servers\n";
	else if(index == 256)
		msg += arg1 + " :Administrative info\n";
	else if(index == 257)
		msg += ":Name     " + arg1 + "\n";
	else if(index == 258)
		msg += ":Nickname " + arg1 + "\n";
	else if(index == 259)
		msg += ":E-Mail   " + arg1 + "\n";
	else
		msg += "UNKNOWN REPLY\n";
	return msg;
}

void	*ping_request(void *req_res){
	Ping *ping = (Ping *)req_res;
	ping->res_res = 0;
	while (time(0) - ping->delay < REQTIME){
		if (!ping->online)
			return NULL;
		if (ping->res_req){
			ping->res_req = 0;
			ping->delay = time(0);
		}
		//sleep(1);
		//std::cout << "time stamp: " << time(0) << std::endl;
	}
	pthread_mutex_lock(&ping->mutex);
	std::string msg = ":" + (std::string)SERVERNAME + " PING :" + (std::string)SERVERNAME + "\n";
	if (!Server::sendMsg(ping->client_sc, msg))
		return NULL;
	pthread_mutex_unlock(&ping->mutex);
	ping->res_wait = 1;
	std:: time_t res_time = time(0);
	while ((time(0) - res_time < RESTIME) && !ping->res_res) {
		if (!ping->online)
			return NULL;
		//sleep(1);
	}
	if (!ping->res_res) {
		pthread_mutex_lock(&ping->mutex);
		ping->disconnect = 1;
		pthread_mutex_unlock(&ping->mutex);
	}
	ping->res_wait = 0;
	return NULL;
}
