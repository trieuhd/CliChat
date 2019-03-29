#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_addr.s_addr = inet_addr("192.168.1.1"); // replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1080);

    connect(server, (SOCKADDR *)&addr, sizeof(addr));
    cout << "ket noi toi server!" << endl;

    char buffer[1024]={'h', 'e', 'l', 'l', 'o', '.'};
    send(server, buffer, sizeof(buffer), 0);
    cout << "Gui Tin nhan Basic!" << endl;

    closesocket(server);
    WSACleanup();
    cout << "Dong socket." << endl << endl;
}
