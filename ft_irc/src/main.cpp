#include "../include/Server.hpp"

void error(std::string error){
    std::cerr << error << std::endl;
    exit(1);
}

int main(int argc, char **argv){
	system("clear");
    if (argc != 3)
        error("Error: Arguments incorrect.\nTo start the server, you must enter the port and password.\n" + (std::string)argv[0] + " <PORT> <PASSWORD>");
    Server data(argv);
    data.start_irc();
    return (0);
}