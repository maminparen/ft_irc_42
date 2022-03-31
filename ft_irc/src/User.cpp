#include "../include/User.hpp"

User::User(int id ,int sd, sockaddr_in address){
	_id = id;
    _sd = sd;
    _address = address;
    _access = 0;
    _autorization = 0;
	_away = 0;
	_oper = 0;
	_invis = 0;
}

int	User::getSd(){
	return _sd;
}

int	User::getId(){
	return _id;
}

bool	User::getAccess(){
	return _access;
}

void	User::setAccess(bool status){
	_access = status;
}

bool	User::getRegistred(){
	return _autorization;
}

void	User::setRegistration(bool status){
	_autorization = status;
}

sockaddr_in	User::getAddr(){
	return _address;
}

std::string User::getNickname(){
	return _nick;
}

void User::setNickname(std::string name){
	_nick = name;
	if (_nick == OPERATOR)
		_oper = 1;
}

std::string User::getUsername(){
	return _user;
}

void User::setUsername(std::string user){
	_user = user;
}

std::string User::getHost(){
	return _host;
}

void User::setHost(std::string host){
	_host = host;
}

std::string User::getServerName(){
	return _serverName;
}

void User::setServerName(std::string srv_name){
	_serverName = srv_name;
}

std::string User::getRealName(){
	return _realName;
}

void User::setRealName(std::string real_name){
	_realName = real_name;
}

std::string User::getAwayMessage(){
	return _away_msg;
}

void User::setAwayMessage(std::string away_msg){
	_away_msg = away_msg;
}

bool	User::getAway(){
	return _away;
}

void	User::setAway(bool status){
	_away = status;
}

std::string User::getBuff(){
	return _buff;
}

void	User::clearBuff(){
	_buff = "";
	_buff.clear();
}

bool	User::createBuff(int read_b, char *buff){
	buff[read_b] = '\0';
	if (_buff.empty())
		_buff = buff;
	else
		_buff = _buff + buff;
	if (buff[read_b - 1] != '\n')
			return false;
	while (_buff.find("\r\n") != std::string::npos)
		_buff.replace(_buff.find("\r\n"), 2, "\n");
	return true;
}

bool	User::getInvis(){
	return _invis;
}

void	User::setInvis(bool status){
	_invis = status;
}

bool	User::getOper(){
	return _oper;
}

void	User::setOper(bool status){
	_oper = status;
}