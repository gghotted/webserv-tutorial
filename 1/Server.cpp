/* browser로 부터 request 받기 */
/* https://www.notion.so/browser-request-7ba30cd7e7474c6680be83577f55ee09 */
/* 참고 https://github.com/zappala/socket-programming-examples-c */

#include "Server.hpp"

Server::Server(int port)
{
    port_ = port;
    buflen_ = 1024;
    buf_ = new char[buflen_ + 1];
}

Server::~Server()
{
    delete buf_;
}

void Server::run()
{
    create();
    serve();
}

void Server::create()
{
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    server_ = socket(PF_INET, SOCK_STREAM, 0);
    if (!server_)
    {
        perror("socket");
        exit(-1);
    }

    int reuse = 1;
    if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        perror("setsockopt");
        exit(-1);
    }

    if (bind(server_,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(-1);
    }

    if (listen(server_,SOMAXCONN) < 0)
    {
        perror("listen");
        exit(-1);
    }
}

void Server::closeSocket()
{
    close(server_);
}

void Server::serve()
{
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

    while ((client = accept(server_, (struct sockaddr*)&client_addr, &clientlen)) > 0)
    {
        handle(client);
    }
    closeSocket();
}

void Server::handle(int client)
{
    while (1)
    {
        std::string request = getRequest(client);
        if (request.empty())
            break ;
        std::cout << request;
    }
    close(client);
}

std::string Server::getRequest(int client)
{
    std::string request = "";
    while (request.find("\n") == std::string::npos)
    {
        int nread = recv(client, buf_, 1024, 0);
        if (nread < 0)
        {
            if (errno == EINTR)
                continue ;
            else
                return "";
        }
        else if (nread == 0)
            return "";
        request.append(buf_, nread);
    }
    return request;
}
