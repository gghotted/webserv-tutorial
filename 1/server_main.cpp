#include "Server.hpp"

int main()
{
    int port = 3000;
    Server server(port);
    server.run();
    // 이 프로그램을 실행하고 브라우저에서 localhost:port로 요청하세요.
}
