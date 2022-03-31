#pragma once

# include "../include/Server.hpp"


class	User{
private:
	int			_id;
    std::string _nick;
    std::string _user;
    std::string _host;
    std::string _serverName;
    std::string _realName;
    std::string _buff;
    int         _sd;
    bool        _access;
    bool        _autorization;
    bool        _disconnect;
    bool        _oper;
    bool        _invis;
    struct sockaddr_in  _address;
    bool        _away;
    std::string _away_msg;
public:
    User(int id, int sd, sockaddr_in address);
	int			getSd();
	sockaddr_in	getAddr();
    
	int			getId();

    bool        getAccess();
    void        setAccess(bool status);

    bool        getRegistred();
    void        setRegistration(bool status);

	std::string	getNickname();
    void        setNickname(std::string nick);

	std::string getUsername();
    void        setUsername(std::string user);

    std::string getHost();
    void        setHost(std::string host);

    std::string getServerName();
    void        setServerName(std::string srv_name);

    std::string getRealName();
    void        setRealName(std::string real_name);

    std::string getBuff();
    void        clearBuff();
    bool        createBuff(int read_b, char *buff);

    std::string getAwayMessage();
    void        setAwayMessage(std::string away_msg);

    bool    	getAway();
    void        setAway(bool status);

    bool        getInvis();
    void        setInvis(bool status);

    bool        getOper();
    void        setOper(bool status);
};
