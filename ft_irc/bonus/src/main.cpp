#include "../include/Socket.hpp"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(){
    int port = IRC_SPORT;

    Socket *ircSocket = new Socket();
    ircSocket->tryToConnect();
    fcntl(ircSocket->getFd(), F_SETFL, O_NONBLOCK);

    std::string msg = "PASS " + (std::string)IRC_SPASS + "\n";
	msg += "USER " + (std::string)IRC_USER + " " + (std::string)IRC_HOST + " " + (std::string)IRC_SNAME + " " + (std::string)IRC_RNAME  + "\n";
	msg += "NICK " + (std::string)IRC_NICK + "\r\n";
	
	ircSocket->tryToSend(msg);
    bool exit = 0;
    while(!exit){
        msg = "";
        msg = ircSocket->tryToRecv();
        if (msg != ""){
            std::cout << msg;
            if (msg.find("PRIVMSG") != std::string::npos){
                std::string target = msg.substr(1, msg.find('!') - 1);
                msg = "./rush-02 " + msg.substr(msg.rfind(':') + 1, msg.size() - msg.rfind(':'));
                msg.pop_back();
                msg.pop_back();
                msg = exec(msg.c_str());
                msg = "PRIVMSG " + target + " " + msg;
                ircSocket->tryToSend(msg);
            }
            else if (msg.find("PING") != std::string::npos){
                 msg = msg.substr(msg.rfind(':') + 1, msg.size() - msg.rfind(':'));
                  std::cout << msg;
                 msg = "PONG " + msg;
                  std::cout << msg; 
                 ircSocket->tryToSend(msg);
            }
        }
    }
    return 0;
}