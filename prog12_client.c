// udp_client_windows.c

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in server;
    char *message = "Hello from the client!";
    char buffer[BUFFER_SIZE] = {0};
    int serverLen = sizeof(server);

    // Step 1: Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Step 2: Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Step 3: Define server details
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Step 4: Send message to server
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&server, serverLen);
    printf("Message sent to server: %s\n", message);

    // Step 5: Receive server response
    recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server, &serverLen);
    printf("Server response: %s\n", buffer);

    // Step 6: Cleanup
    closesocket(sockfd);
    WSACleanup();

    return 0;
}