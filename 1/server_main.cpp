/* browser로 부터 request 받기 */
/* https://www.notion.so/browser-request-7ba30cd7e7474c6680be83577f55ee09 */
/* 참고 https://github.com/zappala/socket-programming-examples-c */

#include "Server.hpp"

int main()
{
    int port = 3000;
    Server server(port);
    server.run();
    // 이 프로그램을 실행하고 브라우저에서 localhost:port로 요청하세요.
}
