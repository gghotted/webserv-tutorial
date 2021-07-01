#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <cerrno>
#include <iostream>

class Server
{
public:
    Server(int port);
    ~Server();

    void run();

private:
    void create();
    void closeSocket();
    void serve();
    void handle(int);
    std::string getRequest(int);

    int port_;
    int server_;
    int buflen_;
    char* buf_;
};

#endif // SERVER_HPP
