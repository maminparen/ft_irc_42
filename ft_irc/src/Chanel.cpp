#include "../include/Chanel.hpp"

bool	Chanel::isBanned(User *user){
	for (int i = 0; i < _banned.size(); i++){
		if (user->getId() == _banned[i].getId())
			return true;
	}
	return false;
}

bool	Chanel::isInvisble(User *user){
	for (int i = 0; i < _members.size(); i++){
		if (user->getId() == _members[i].getId())
			return true;
	}
	return false;
}

bool	Chanel::isInvited(User *user){
	for (int i = 0; i < _invited.size(); i++){
		if (user->getId() == _invited[i].getId())
			return true;
	}
	return false;
}

bool	Chanel::isMember(User *user){
	for (int i = 0; i < _members.size(); i++){
		if (user->getId() == _members[i].getId())
			return true;
	}
	return false;
}

void	Chanel::removeMember(User *user){
	for (std::vector<User>::iterator it = _members.begin(); it != _members.end(); it++){
		if (user->getId() == it->getId()){
			_members.erase(it);
			break;
		}
	}
	sendAll(user, "QUIT", "Client exit chanel", "");
}

bool	Chanel::isOper(User *user){
	for (int i = 0; i < _operators.size(); i++){
		if (user->getId() == _operators[i].getId())
			return true;
	}
	return false;
}

void	Chanel::addOper(User *oper, User *user){
	std::cout << "addOper: " << std::endl;
	if (user == NULL){
		for(int i = 0; i < _members.size(); i++){
			if (_operators[0].getId() != _members[i].getId()){
				user = &_members[i];
				break;
			}
		}
	}
	sendAll(oper, "MODE " + _name + " +o " + user->getNickname(), "", "");
	if (isOper(user))
		return;
	_operators.push_back(*user);
}

void	Chanel::removeOper(User *user){
	for (std::vector<User>::iterator it = _operators.begin(); it != _operators.end(); it++){
		if (user->getId() == it->getId()){
			_operators.erase(it);
			return ;
		}
	}
}

int		Chanel::oper_size(){
	return _operators.size();
}

int		Chanel::member_size(){
	return _members.size();
}

int		Chanel::max_member(){
	return _max_member;
}

void	Chanel::set_max_member(int max){
	_max_member = max;
}

void	Chanel::sendAll(User *user, std::string arg1, std::string arg2, std::string arg3){
	for (int i = 0; i < _members.size(); i ++){
		Server::compileMsg(*user, _members[i], arg1, arg2, arg3);
	}
}

std::string	Chanel::getName(){
	return (_name);
}

std::string	Chanel::getPassword(){
	return (_password);
}

void		Chanel::setPassword(std::string password){
	_password = password;
}

std::string	Chanel::getTopic(){
	return (_topic);
}

void		Chanel::setTopic(std::string topic){
	_topic = topic;
}

void		Chanel::addUser(User *user){
	_members.push_back(*user);
}

void		Chanel::addBan(User *user){
	_banned.push_back(*user);
}

void	Chanel::removeBan(User *user){
	for (std::vector<User>::iterator it = _banned.begin(); it != _banned.end(); it++){
		if (user->getId() == it->getId()){
			_banned.erase(it);
			return ;
		}
	}
}

std::string	Chanel::getOperNames(){
	std::string ret = "";

	for (int i = 0; i < _operators.size(); i++){
		ret += "@";
		ret += _operators[i].getNickname();
		if (i + 1 != _operators.size())
				ret += " ";
	}
	return ret;
}

std::string	Chanel::getUserNames(){
	std::string ret = "";

	for (int i = 0; i < _members.size(); i++){
		bool add = 1;
		for (int j = 0; j < _operators.size(); j++){
			if (_members[i].getNickname() == _operators[j].getNickname()){
				add = 0;
			}
		}
		if (add == 1){
			ret += _members[i].getNickname();
			if (i + 1 != _members.size())
				ret += " ";
		}
	}
	return ret;
}

Chanel::Chanel(User *user, std::string name, std::string password){
	_name = name;
	_password = password;
	_max_member = 100;
	_invOnly = 0;
	_members.push_back(*user);
	_operators.push_back(*user);
}

bool		Chanel::getInvOnly(){
	return _invOnly;
}

void		Chanel::setInvOnly(bool status){
	_invOnly = status;
}

void		Chanel::addInviteUser(User *user){
	for (int i = 0; i < _invited.size(); i++){
		if (user->getNickname() == _invited[i].getNickname())
			return;
	}
	_invited.push_back(*user);
}
