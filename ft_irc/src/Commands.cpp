# include "../include/Commands.hpp"

int	Commands::cmd_pass(std::vector<std::string> args, std::vector<User *>::iterator it, Server *data){
	std::string msg;
	User *user = *it;
	if (args.size() < 2){
		msg = compileError(461, *user, args[0], "");
		Server::sendMsg(user->getSd(), msg);
		return 0;
	}
	if (user->getAccess()){
		msg = compileError(462, *user, "", "");
		data->sendMsg(user->getSd(), msg);
		return 0;
	}
	if (args[1] != data->getPassword()){
		msg = compileError(464, *user, "", "");
		data->sendMsg(user->getSd(), msg);
		data->disconnect(it);
		return 1;
	}
	else
		user->setAccess(1);
	return (0);
}

void	Commands::cmd_motd(std::vector<User *>::iterator it){
	std::ifstream file("motd/daily.msg");
	std::string msg;
	User *user = *it;
	if (file){
		std::string line;
		msg = compileReply(375, *user, SERVERNAME, "", "", "", "", "", "", "");
		Server::sendMsg(user->getSd(), msg);
		while(std::getline(file, line)){
			msg = compileReply(372, *user, line, "", "", "", "", "", "", "");
			Server::sendMsg(user->getSd(), msg);
		}
		msg = compileReply(376, *user, "", "", "", "", "", "", "", "");
		Server::sendMsg(user->getSd(), msg);
	}
	else{
		msg = compileError(422, *user, "", "");
		Server::sendMsg(user->getSd(), msg);
	}
}

void	Commands::cmd_nick(std::vector<std::string> args, std::vector<User *>::iterator it,  std::vector<User *> users){
	User *user = *it;
	std::string msg;
	int nick = 0;
	if (args.size() != 2){
		msg = compileError(461, *user, args[0], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	for (int i = 0; i < users.size(); i++){
		if (users[i]->getNickname() == args[1]){
			msg = compileError(433, *user, args[1], "");
			Server::sendMsg(user->getSd(), msg);
			return;
		}
	}
	for (int i = 0; i < args[1].length(); i++){
		if (args[1][i] <= 32 || args[1][i] > 126 || args[1][i] == ' ' || args[1][i] == ':' || args[1][i] == '#' || args[1][i] == '!' || args[1][i] == '@'){
            msg = compileError(432, *user, args[1], "");
			Server::sendMsg(user->getSd(), msg);
			return ;
        }
	}
	if ((*it)->getNickname().empty())
		nick = 1;

	(*it)->setNickname(args[1]);
	if (nick && (*it)->getRegistred())
		cmd_motd(it);
}

int	Commands::cmd_user(std::vector<std::string> args, std::vector<User *>::iterator it){
	User *user = *it;
	std::string msg;
	if (args.size() < 4){
		msg = compileError(461, *user, args[0], "");
		Server::sendMsg(user->getSd(), msg);
		return 0;
	}
	if (user->getRegistred()){
		msg = compileError(462, *user, "", "");
		Server::sendMsg(user->getSd(), msg);
		return 0;
	}
	user->setUsername(args[1]);
	user->setHost(args[2]);
	user->setServerName(args[3]);
	user->setRealName(args[4]);
	user->setRegistration(1);
	if (!user->getNickname().empty())
		cmd_motd(it);
	return 1;
}

int Commands::cmd_ping(std::vector<std::string> args, std::vector<User *>::iterator it) {
	User *user = *it;
	std::string msg;
	if (args.size() == 1){
		msg = compileError(409, *user, "", "");
		Server::sendMsg(user->getSd(), msg);
		return 0;
	}
	msg = ":" + (std::string)SERVERNAME + " PONG :" + args[1] + "\n";
	Server::sendMsg(user->getSd(), msg);
	return 1;
}

int Commands::cmd_pong(std::vector<std::string> args, std::vector<User *>::iterator it) {
	User *user = *it;
	std::string msg;
	if (args[1] == SERVERNAME)
		return 1;
	msg = compileError(402, *user, args[1], "");
		Server::sendMsg(user->getSd(), msg);
	return 0;
}

void	Commands::cmd_ison(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users){
	std::string msg;
	if (args.size() == 1){
		msg = compileError(461, *(*it), args[1], "");
		Server::sendMsg((*it)->getSd(), msg);
	}
	else{
		for (int i = 0; i < args.size(); i++){
			for (int j = 0; j < users.size(); j++){
				if (args[i] == users[j]->getNickname()){
					msg += args[i] + " ";
				}
			}
		}
		msg.pop_back();
		msg = compileReply(303, *(*it), msg, "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
	}
}

void	Commands::cmd_admin(std::vector<std::string> args, std::vector<User *>::iterator it){
	std::string msg;
	if (args.size() == 1 || (args.size() != 1 && args[1] == (std::string)SERVERNAME)){
		msg = compileReply(256, *(*it), " " + (std::string)SERVERNAME, "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
		msg = compileReply(257, *(*it), "hzona, cdarrell, bmohamme", "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
		msg = compileReply(258, *(*it), "Denis, Vitaliy, Dmitriy", "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
		msg = compileReply(259, *(*it), "hzona@student.21-school.ru, cdarrell@student.21-school.ru, bmohamme@student.21-school.ru", "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
	}
	else{
		msg = compileError(402, *(*it), args[1], "");
		Server::sendMsg((*it)->getSd(), msg);
	}
}

void	Commands::cmd_info(std::vector<std::string> args, std::vector<User *>::iterator it){
	std::string msg;
	if (args.size() == 1 || (args.size() != 1 && args[1] == (std::string)SERVERNAME)){
		msg = compileReply(371, *(*it), "==============SERVER INFORMATION==============", "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
		msg = compileReply(371, *(*it), "This is the best irc server project school 42!", "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
		msg = compileReply(371, *(*it), "==============================================", "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
		msg = compileReply(374, *(*it), "", "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
	}
	else{
		msg = compileError(402, *(*it), args[1], "");
		Server::sendMsg((*it)->getSd(), msg);
	}
}

void	Commands::cmd_away(std::vector<std::string> args, std::vector<User *>::iterator it){
	std::string msg;
	if (args.size() == 1){
		(*it)->setAway(0);
		msg = compileReply(305, *(*it), "", "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
	}
	if (args.size() > 1){
		(*it)->setAway(1);
		msg = "";
		for (int i = 1; i < args.size(); i++){
			msg += args[i];
			if (i + 1 != args.size())
				msg += " ";
		}
		(*it)->setAwayMessage(msg);
		msg = compileReply(306, *(*it), "", "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
	}
}

void	Commands::cmd_privmsg(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels, bool notice){
	User *user = *it;
	std::string msg;
	if (args.size() == 1){
		msg = compileError(411, *user, args[0], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	if (args.size() == 2){
		msg = compileError(412, *user, "", "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	std::vector<std::string> target = split(args[1], ',');
	for (int i = 0; i < target.size(); i++){
		if (target[i].front() != '#' && target[i].front() != '&'){
			for (int j = 0; j < users.size(); j++){
				if (target[i] == users[j]->getNickname()){
					msg.clear();
					for (int c = 2; c < args.size(); c++)
						msg += args[c] + " ";
					msg.pop_back();
					Server::compileMsg(*user, *users[j], args[0], users[j]->getNickname(), msg);
					if (users[j]->getAway() && !notice){
						msg = compileReply(301, *user, users[j]->getNickname(), users[j]->getAwayMessage(), "", "", "", "", "", "");
						Server::sendMsg(user->getSd(), msg);
					}
					break;
				}
				if (j + 1 == users.size()){
					msg = compileError(401, *user, "", "");
					Server::sendMsg(user->getSd(), msg);
				}
			}
		}
		else{
			bool send = 0;
			for(int j = 0; j < chanels.size(); j++){
				if (target[i] == chanels[j]->getName()){
					if (chanels[j]->isBanned(user) || !chanels[j]->isMember(user)){
						msg = compileError(404, *user, "", "");
						Server::sendMsg(user->getSd(), msg);
						continue ;
					}
					for (int n = 0; n < users.size(); n++){
						if (user->getNickname() != users[n]->getNickname() && chanels[j]->isMember(users[n])){
							msg.clear();
							for (int c = 2; c < args.size(); c++)
								msg += args[c] + " ";
							Server::compileMsg(*user, *users[n], args[0], args[1], msg);
						}
					}
					send = 1;
				}
				if (!send && j + 1 == chanels.size()){
					msg = compileError(401, *user, "", "");
					Server::sendMsg(user->getSd(), msg);
				}
			}
		}
	}
}

void Commands::cmd_join(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels){
	std::string						msg;
	User 							*user = *it;
	std::vector<std::string>		arr_channel;
	std::vector<std::string>		arr_password;

	if (args.size() == 1){
		msg = compileError(461, *user, args[0], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	arr_channel = split(args[1], ',');
	if (args.size() > 2)
		arr_password = split(args[2], ',');
	while (arr_password.size() < arr_channel.size())
		arr_password.push_back("");
	for (int i = 0; i < arr_channel.size(); i++){
		if (arr_channel[i][0] != '#'){
			msg = compileError(403, *user, arr_channel[i], "");
			Server::sendMsg(user->getSd(), msg);
			continue ;
		}
		for (int j = 0; j < arr_channel[i].length(); j++){
			if (arr_channel[i][j] <= 32 || arr_channel[i][j] > 126 || arr_channel[i][j] == ':' || arr_channel[i][j] == '!' || arr_channel[i][j] == ' ' || arr_channel[i][j] == '@'){
				msg = compileError(403, *user, arr_channel[i], "");
				Server::sendMsg(user->getSd(), msg);
				continue ;
			}
		}
		bool	new_chanel = 1;
		for (int j = 0; j < chanels.size(); j++){
			if (chanels[j]->getName() == arr_channel[i]){
				new_chanel = 0;
				if (chanels[j]->isBanned(user)){
					msg = compileError(474, *user, arr_channel[i], "");
					Server::sendMsg(user->getSd(), msg);
					continue ;
				}
				else if (chanels[j]->isMember(user)){
					msg = compileError(443, *user, arr_channel[i], "");
					Server::sendMsg(user->getSd(), msg);
					continue ;
				}
				else if (chanels[j]->isInvited(user)){
					msg = compileError(473, *user, arr_channel[i], "");
					Server::sendMsg(user->getSd(), msg);
					continue ;
				}
				else if (chanels[j]->member_size() >= chanels[j]->max_member()){
					msg = compileError(471, *user, arr_channel[i], "");
					Server::sendMsg(user->getSd(), msg);
					continue ;
				}
				else if (!chanels[j]->getPassword().empty() && chanels[j]->getPassword() != arr_password[i]){
					msg = compileError(475, *user, arr_channel[i], "");
					Server::sendMsg(user->getSd(), msg);
					continue ;
				}
				chanels[j]->addUser(user);
				chanels[j]->sendAll(user, args[0], arr_channel[i], "");
				if (!chanels[j]->getTopic().empty()){
					msg = compileReply(332, *(*it), arr_channel[i], chanels[j]->getTopic(), "", "", "", "", "", "");
					Server::sendMsg((*it)->getSd(), msg);
				}
				else{
					msg = compileReply(331, *(*it), arr_channel[i], "", "", "", "", "", "", "");
					Server::sendMsg((*it)->getSd(), msg);
				}
				msg = compileReply(353, *(*it), "= " +arr_channel[i], chanels[j]->getOperNames() + " " + chanels[j]->getUserNames(), "", "", "", "", "", "");
				Server::sendMsg((*it)->getSd(), msg);
				msg = compileReply(366, *(*it), arr_channel[i], "", "", "", "", "", "", "");
				Server::sendMsg((*it)->getSd(), msg);
			}
		}
		if (new_chanel){
			Chanel *tmp = new Chanel(user, arr_channel[i], arr_password[i]);
			chanels.push_back(tmp);
			tmp->sendAll(user, args[0], arr_channel[i], "");
			msg = compileReply(331, *(*it), arr_channel[i], "", "", "", "", "", "", "");
			Server::sendMsg((*it)->getSd(), msg);
			msg = compileReply(353, *(*it),  "= " + arr_channel[i], "@" + user->getNickname(), "", "", "", "", "", "");
			Server::sendMsg((*it)->getSd(), msg);
			msg = compileReply(366, *(*it), arr_channel[i], "", "", "", "", "", "", "");
			Server::sendMsg((*it)->getSd(), msg);
		}
	}
}

void Commands::cmd_invite(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels){
	std::string						msg;
	User 							*user = *it;

	if (args.size() != 3){
		msg = compileError(461, *user, args[0], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	User *target = NULL;
	for (int i = 0; i < users.size(); i++){
		if (users[i]->getNickname() == args[1])
			target = users[i];
	}
	if (!target){
		msg = compileError(401, *user, args[1], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	Chanel *target_c = NULL;
	for (int i = 0; i < chanels.size(); i++){
		std::cout << chanels[i]->getName() << "        " << args[2] << std::endl;
		if (chanels[i]->getName() == args[2])
			target_c = chanels[i];
	}
	if (!target_c){
		msg = compileError(442, *user, args[2], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	if (target_c->isMember(target)){
		msg = compileError(443, *user, args[1], args[2]);
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	if (target_c->getInvOnly() && !target_c->isOper(user)){
		msg = compileError(482, *user, args[2], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	if (!target->getAway()){
		if (target_c->isInvited(target))
			target_c->addInviteUser(target);
		msg = compileReply(341, *target, args[2], args[1], "", "", "", "", "", "");
		Server::sendMsg(user->getSd(), msg);
		Server::compileMsg(*user, *target, args[0] + " " + target->getNickname() + " " + args[2], "", "");
	}
	else{
		msg = compileReply(301, *(*it), args[1], target->getAwayMessage(), "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
	}
}

std::string Commands::chanel_who(std::vector<User *>::iterator &user, std::vector<Chanel *> &chanels){
	std::string msg = "";

	for (int i = 0; i < chanels.size(); i++){
		if (chanels[i]->isMember(*user)){
			if (chanels[i]->getInvOnly())
				msg += "Prv,";
			else
				msg += chanels[i]->getName() + ",";
		}
	}
	if (!msg.empty())
		msg.pop_back();
	else
		msg = "*no joined channels*";
	return msg;
}

void Commands::cmd_who(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels){
	std::string						msg;
	User 							*user = *it;
	bool							oper = 0;
	std::cout << "WHO args.size() " << args.size() << std::endl;

	if ((args.size() > 2 && args[2] == "o") || (args.size() == 2 && args[1] == "o"))
		oper = 1;
	if (args.size() > 1 && args[1] != "0"){
		bool status = 0;
		for (int i  = 0; i < chanels.size(); i++){
			if (chanels[i]->getName() == args[1]){
				status = 1;
				for (std::vector<User *>::iterator target = users.begin(); target < users.end(); target++){
					if (chanels[i]->isMember(*target)){
						msg = chanel_who(target, chanels);
						msg = compileReply(352, *user, msg, (*target)->getUsername(), (*target)->getHost(), (*target)->getServerName(), (*target)->getNickname(), "H", "", (*target)->getRealName());
						Server::sendMsg(user->getSd(), msg);
					}
				}
			}
		}
		if (!status){
			msg = compileError(403, *user, args[0], "");
			Server::sendMsg(user->getSd(), msg);
		}
		else{
			msg = compileReply(315, *user, args[1], "", "", "", "", "", "", "");
			Server::sendMsg((*it)->getSd(), msg);
		}
	}
	else{
		for (std::vector<User *>::iterator target = users.begin(); target < users.end(); target++){
			if ((!(*target)->getInvis() && (!oper || (oper && (*target)->getOper())))
			|| ((*target)->getInvis() && (*target)->getNickname() == user->getNickname() && (!oper || (oper && (*target)->getOper())))){
				msg = chanel_who(target, chanels);
				msg = compileReply(352, *user, msg, (*target)->getUsername(), (*target)->getHost(), (*target)->getServerName(), (*target)->getNickname(), "H", "", (*target)->getRealName());
				Server::sendMsg(user->getSd(), msg);
			}
		}
		msg = compileReply(315, *user, "", "", "", "", "", "", "", "");
		Server::sendMsg((*it)->getSd(), msg);
	}
}

void Commands::cmd_part(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels){
	std::string						msg;
	User 							*user = *it;

	if (args.size() < 2){
		msg = compileError(461, *user, args[0], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	bool exit = 0;
	for (std::vector<Chanel *>::iterator it2 = chanels.begin(); it2 != chanels.end(); it2++){
		if ((*it2)->getName() == args[1]){
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
				exit = 1;
									
					for (int i = 0; i < users.size(); i++){
						if ((*it2)->isMember(users[i])){
							msg = chanel_who(it, chanels);
							msg = compileReply(353, *users[i], "= " + args[1], (*it2)->getOperNames() + " " + (*it2)->getUserNames(), "", "", "", "", "", "");
							Server::sendMsg(users[i]->getSd(), msg);
							msg = compileReply(366, *users[i], args[1], "", "", "", "", "", "", "");
							Server::sendMsg(users[i]->getSd(), msg);
						}
					}
				break;
			}
			else{
				msg = compileError(442, *user, args[1], "");
				Server::sendMsg(user->getSd(), msg);
			}
		}
	}
	if (!exit){
		msg = compileError(403, *user, args[1], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
}

void Commands::cmd_whois(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels){
	std::string						msg;
	User 							*user = *it;
	
	if (args.size() < 2){
		msg = compileError(431, *user, "", "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}

	std::vector<std::string>	user_list = split(args[1], ',');
	for (int i = 0; i < user_list.size(); i++){
		for (int j = 0; j < users.size(); j++){
			if (users[j]->getNickname() == user_list[i]){
				msg = compileReply(311, *user, users[j]->getNickname(), users[j]->getUsername(), users[j]->getHost(), users[j]->getRealName(), "", "", "", "");
				Server::sendMsg(user->getSd(), msg);
				msg = compileReply(317, *user, users[j]->getNickname(), "AFK MODE", "", "", "", "", "", "");
				Server::sendMsg(user->getSd(), msg);
				if (users[j]->getAway()){
					msg = compileReply(301, *user, users[j]->getNickname(), users[j]->getAwayMessage(), "", "", "", "", "", "");
					Server::sendMsg(user->getSd(), msg);
				}
				if (users[j]->getOper()){
					msg = compileReply(313, *user, users[j]->getNickname(), "", "", "", "", "", "", "");
					Server::sendMsg(user->getSd(), msg);
				}
				msg = "";
				for (int n = 0; n < chanels.size(); n++){
					if (chanels[n]->isMember(users[j]))
						msg += chanels[n]->getName() + " ";
				}
				if (!msg.empty()){
					msg.pop_back();
					msg = compileReply(319, *user, users[j]->getNickname(), msg, "", "", "", "", "", "");
					Server::sendMsg(user->getSd(), msg);
				}
				msg = compileReply(318, *user, users[j]->getNickname(), "", "", "", "", "", "", "");
				Server::sendMsg(user->getSd(), msg);
			}
		}
	}
}

void Commands::cmd_topic(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels){
	std::string						msg;
	User 							*user = *it;
	
	if (args.size() < 2){
		msg = compileError(431, *user, args[0], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	for (int i = 0; i < chanels.size(); i++){
		if (chanels[i]->getName() == args[1]){
				if (args.size() == 2){
					if (!chanels[i]->getTopic().empty()){
						msg = compileReply(332, *user, args[1], chanels[i]->getTopic(), "", "", "", "", "", "");
						Server::sendMsg(user->getSd(), msg);
					}
					else{
						msg = compileReply(331, *user, args[1], "", "", "", "", "", "", "");
						Server::sendMsg(user->getSd(), msg);
					}
				}
				else{
					msg = "";
					for (int n = 2; n < args.size(); n++){
						msg += args[n] + " ";
					}
					chanels[i]->setTopic(msg);
					for (int j = 0; j < users.size(); j++){
						Server::compileMsg(*user, *users[j], args[0], args[1], msg);
					}
				}
		}
	}
}

void Commands::cmd_kick(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels){
	std::string						msg;
	User 							*user = *it;

	if (args.size() < 3){
		msg = compileError(461, *user, args[0], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}

	std::vector<std::string> target_chanel = split(args[1], ',');
	std::vector<std::string> target_user = split(args[2], ',');
	bool chanel = 0;
	bool userb = 0;
	bool kick = 0;
	std::vector<User *> del_user;
	for (int i = 0; i < target_chanel.size(); i++){
		for (std::vector<Chanel *>::iterator it_c = chanels.begin(); it_c < chanels.end(); it_c++){
			if (target_chanel[i] == (*it_c)->getName()){
				chanel = 1;
				for (int j = 0; j < target_user.size(); j++){
					for (std::vector<User *>::iterator it_u = users.begin(); it_u < users.end(); it_u++){
						if (target_user[j] != (*it_u)->getNickname()){
							userb = 1;
						}
						if (target_user[j] == (*it_u)->getNickname() && (*it_c)->isMember(*it_u)){
							userb = 1;
							kick = 1;
							if ((*it_c)->isOper(*it_u) || !(*it_c)->isOper(user)){
								msg = compileError(482, *user, target_chanel[i], "");
								Server::sendMsg(user->getSd(), msg);
								continue;
							}
							del_user.push_back(*it_u);
						}
						if (!userb){
							msg = compileError(442, *user, target_chanel[i], "");
							Server::sendMsg(user->getSd(), msg);
						}
						userb = 0;
					}
					if (!kick){
						msg = compileError(401, *user, target_user[j], "");
						Server::sendMsg(user->getSd(), msg);
						}
					kick = 0;
				}
			}
			if (!chanel){
				msg = compileError(403, *user, target_chanel[i], "");
				Server::sendMsg(user->getSd(), msg);
			}
		chanel = 0;
		}
	}
	if (args.size() > 3){
	 	msg = "";
		for (int i = 0; i < args.size(); i++){
			msg += args[i] + " ";
		}
	}
	else
	 	msg = user->getNickname();
	while (del_user.size()){
		for (int i = 0; i < chanels.size(); i++){
			if (chanels[i]->isMember(del_user[0])){
				std::vector<User *>::iterator it_u;
				for (std::vector<User *>::iterator it = del_user.begin(); it != del_user.end(); it ++){
					if ((*it)->getNickname() == del_user[0]->getNickname())
					it_u = it;
				}
				std::cout << "Kick user: " + (*it_u)->getNickname() + "   in chanel: " + chanels[i]->getName() << std::endl;
				chanels[i]->sendAll(user, args[0], chanels[i]->getName() + " " + (*it_u)->getNickname(), msg);
				chanels[i]->removeMember(del_user[0]);
				del_user.erase(it_u);
				break;
			}
		}
	}
}

void Commands::cmd_mode(std::vector<std::string> args, std::vector<User *>::iterator it, std::vector<User *> &users, std::vector<Chanel *> &chanels){
	std::string						msg;
	User 							*user = *it;

	if (args.size() < 3){
		msg = compileError(461, *user, args[0], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	if (args[2][0] != '+' && args[2][0] != '-'){
		msg = compileError(472, *user, args[2], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	std::string		flags_c= "opsitnmlbvk";
    std::string     flags_u= "iswo";
	if (args[2].size() > 2 && (args[2].find('o') != std::string::npos || args[2].find('l') != std::string::npos || args[2].find('v') != std::string::npos)){
		msg = compileError(472, *user, args[2], "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
	int		flags[255];
	for (int i = 1; i < args[2].length(); i++){
		if ((args[1][0] == '#' && flags_c.find(args[2][i]) != std::string::npos)  || (args[1][0] != '#' && flags_u.find(args[2][i]) != std::string::npos )){
			if (flags[args[2][i]] == 100500){
				msg = compileError(501, *user, args[2], "");
				Server::sendMsg(user->getSd(), msg);
				return ;
			}
			flags[args[2][i]] = 100500;
		}
		else{
			msg = compileError(472, *user, args[2], "");
			Server::sendMsg(user->getSd(), msg);
			return ;
		}
	}
	if (args[1][0] == '#'){
		if (args.size() < 4){
			msg = compileError(461, *user, args[0], "");
			Server::sendMsg(user->getSd(), msg);
			return ;
		}
		bool chanel_b = 0;
		User *target_user;
		for (int i = 0; i < users.size(); i ++){
			if (users[i]->getNickname() == args[3])
				target_user = users[i];
			}
		if (args[3].find("*!") != std::string::npos){
			for (int i = 0; i < users.size(); i ++){
				if (args[3].find(users[i]->getUsername()) != std::string::npos)
					target_user = users[i];
			}
		}
		for (int i = 0; i < chanels.size(); i++){
			if (chanels[i]->getName() == args[1]){
				chanel_b = 1;
				if (!chanels[i]->isOper(user)){
					msg = compileError(482, *user, args[1], "");
					Server::sendMsg(user->getSd(), msg);
					return ;
				}
				for (int j = 1; j < args[2].length(); j++){
					if (args[2][j] == 'o' && args[2][0] == '+'){
						chanels[i]->addOper(user, target_user);
					}
					if (args[2][j] == 'o' && args[2][0] == '-'){
						if (chanels[i]->member_size() == 1){
							return ;
						}
						chanels[i]->removeOper(target_user);
						if (chanels[i]->oper_size() == 0)
							chanels[i]->addOper(user, NULL);
						chanels[i]->sendAll(user, "MODE " + args[1] + " -o " + target_user->getNickname(), "", "");
					}
					if (args[2][j] == 'v' && args[2][0] == '+'){
						chanels[i]->sendAll(user, "MODE " + args[1] + " +v " + target_user->getNickname(), "", "");
					}
					if (args[2][j] == 'v' && args[2][0] == '-'){
						chanels[i]->sendAll(user, "MODE " + args[1] + " -v " + target_user->getNickname(), "", "");
					}
					if (args[2][j] == 'b' && args[2][0] == '+'){
						chanels[i]->sendAll(user, "MODE " + args[1] + " +b " + target_user->getNickname(), "", "");
						chanels[i]->addBan(target_user);
					}
					if (args[2][j] == 'b' && args[2][0] == '-'){
						chanels[i]->sendAll(user, "MODE " + args[1] + " -b " + target_user->getNickname(), "", "");
						chanels[i]->removeBan(target_user);
					}
				}
			}
		}
		if (!chanel_b){
			msg = compileError(403, *user, args[1], "");
			Server::sendMsg(user->getSd(), msg);
			return ;
		}
	}
	else if (user->getNickname() == args[1]){
		for (int i = 1; i < args[2].length(); i++){
			if (args[2][i] == 'i' && args[2][0] == '+')
				user->setInvis(1);
			if (args[2][i] == 'i' && args[2][0] == '-')
				user->setInvis(0);
			if (args[2][i] == 's' && args[2][0] == '+')
				user->setInvis(1);
			if (args[2][i] == 'w' && args[2][0] == '+')
				user->setInvis(1);
			if (args[2][i] == 'o' && args[2][0] == '+')
				user->setInvis(1);
		}
	}
	else{
		msg = compileError(502, *user, "", "");
		Server::sendMsg(user->getSd(), msg);
		return ;
	}
}