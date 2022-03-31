#pragma once

# include <algorithm>
# include <sys/time.h>
# include "../include/Server.hpp"

std::vector<std::string>			splitMessage(std::string);
std::vector<std::string> 			split(std::string msg, char sym);
std::string 						compileError(int index, User &user, std::string arg1, std::string arg2);
std::string 						compileReply(int index, User &user, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::string arg5, std::string arg6, std::string arg7, std::string arg8);
uint64_t 							timer();
void 								*ping_request(void *req_res);