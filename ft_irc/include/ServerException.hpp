#pragma once
#include "../include/Server.hpp"

void error(std::string error);

class ServerException{
public:
    	class pass_mismatch : public std::exception{
		const char *what() const throw(){
			return ":Server error 464 pass :Password incorrect\r\n";
		}
	};

	class pass_param : public std::exception{
		const char *what() const throw(){
			return ":Server error 461 <PASS> :Not enough parameters\r\n";
		}
	};

	class create_newsc : public std::exception{
		const char *what() const throw(){
			return "Error create new user socket.\n";
		}
	};
};