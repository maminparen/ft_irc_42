#pragma once

#include "../include/Server.hpp"

class Ping{
public:
	int				client_sc;
	std::time_t		delay;
	pthread_mutex_t	mutex;
	bool			online;
	bool			disconnect;
	bool			res_wait;
	bool			res_req;
	bool			res_res;
};