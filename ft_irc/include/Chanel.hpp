#pragma once

#include "../include/Server.hpp"

class User;
class Server;

class Chanel{
private:
	std::string				_name;
	std::string				_password;
	int						_max_member;
	bool					_invOnly;
	std::vector<User>		_members;
	std::vector<User>		_operators;
    std::vector<User>		_invited;
   	std::vector<User>		_invisibles;
    std::vector<User>		_banned;
	std::string				_topic;
public:
	Chanel(User *user, std::string name, std::string password);
	std::string		getName();
	std::string		getPassword();
	std::string		getTopic();
	std::string		getOperNames();
	std::string		getUserNames();

	void		setTopic(std::string topic);
	void		setPassword(std::string password);
	bool		isMember(User *user);
	void		removeMember(User *user);
	void		removeBan(User *user);
	bool		isOper(User *user);
	int			oper_size();
	void		addOper(User *oper, User *user);
	void		addUser(User *user);
	void		addBan(User *user);
	void		addInviteUser(User *user);
	void		removeOper(User *user);
	bool		isInvited(User *user);
	bool		isInvisble(User *user);
	bool		isBanned(User *user);
	int			member_size();
	int			max_member();
	void		set_max_member(int max);
	void		sendAll(User *user, std::string arg1, std::string arg2, std::string arg3);
	void		setInvOnly(bool status);
	bool		getInvOnly();
};