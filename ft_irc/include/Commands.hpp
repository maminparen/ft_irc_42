#pragma once

# include "../include/Server.hpp"
# include <fstream>

class User;
class Chanel;
class Server;
class Files;

class Commands {
private:

public:
	static int			cmd_pass(std::vector<std::string> args, std::vector<User *>::iterator it, Server *data);
	static int			cmd_user(std::vector<std::string> args, std::vector<User *>::iterator it);
	static void			cmd_nick(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> users);
	static void			cmd_motd(std::vector<User *>::iterator it);
	static int			cmd_ping(std::vector<std::string> args, std::vector<User *>::iterator it);
	static int			cmd_pong(std::vector<std::string> args, std::vector<User *>::iterator it);
	static void			cmd_privmsg(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels, bool notice);

	static void			cmd_away(std::vector<std::string> args, std::vector<User *>::iterator it);
	static void			cmd_ison(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users);
	static void			cmd_admin(std::vector<std::string> args, std::vector<User *>::iterator it);
	static void			cmd_info(std::vector<std::string> args, std::vector<User *>::iterator it);

	static void			cmd_join(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels);
	static void			cmd_invite(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels);
	static void			cmd_who(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels);
	static std::string	chanel_who(std::vector<User *>::iterator &user, std::vector<Chanel *> &chanels);
	static void			cmd_part(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels);
	static void			cmd_whois(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels);

	static void			cmd_topic(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels);
	static void			cmd_kick(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels);
	static void			cmd_mode(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels);
};
