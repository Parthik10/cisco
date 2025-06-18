// udp_server_windows.c

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET sockfd;
    struct sockaddr_in server, client;
    int clientLen = sizeof(client);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "Message received by server!";

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

    // Step 3: Bind the socket to port
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("UDP Server listening on port %d...\n", PORT);

    // Step 4: Receive message from client
    recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client, &clientLen);
    printf("Message from client: %s\n", buffer);

    // Step 5: Send response to client
    sendto(sockfd, response, strlen(response), 0, (struct sockaddr*)&client, clientLen);

    // Step 6: Cleanup
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
