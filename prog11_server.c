
// Compile    gcc prog11_server.c -o prog11_server.exe -lws2_32
//  Compile    gcc prog11_client.c -o prog11_client.exe -lws2_32
//  Run server .\prog11_server.exe
//  Run client  .\prog11_client.exe

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in server, client;
    int c;
    char buffer[BUFFER_SIZE] = {0};

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
        printf("WSAStartup failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    listen(server_fd, 3);
    printf("Server listening on port %d...\n", PORT);

    c = sizeof(struct sockaddr_in);
    new_socket = accept(server_fd, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET) {
        printf("accept failed with error code : %d", WSAGetLastError());
        return 1;
    }

    recv(new_socket, buffer, BUFFER_SIZE, 0);
    printf("Received from client: %s\n", buffer);

    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
