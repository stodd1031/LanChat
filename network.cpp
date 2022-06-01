#include "network.h"


Network::Network()
{

}

void Network::openSocket()
{
#ifdef WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    unsigned int tv = 1000;
        char tvchar[sizeof(tv)];
        memcpy(tvchar, &tv, sizeof(tv));
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));
#else
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0; ;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
#endif
    len = sizeof(sockaddr_in);

    char host[256];
    struct hostent* host_entry;
    int hostname;
    hostname = gethostname(host, sizeof(host)); // find the host name
    host_entry = gethostbyname(host);                                         // find host MessageInformation
    myIP = inet_ntoa(*(
        (struct in_addr*)host_entry->h_addr_list[0])); // Convert into IP string
}

void Network::send(ReceivedInfo& ri, struct sockaddr_in& addr)
{
#ifdef WIN32
    sendto(sockfd, (char*)&ri, sizeof(ReceivedInfo), 0,
        (struct sockaddr*)&addr, sizeof(addr));
#else
    sendto(sockfd, &ri, sizeof(ReceivedInfo), 0,
        (struct sockaddr*)&addr, sizeof(addr));
#endif
}

ReceivedInfo Network::recieve(struct sockaddr_in& addr)
{
    ReceivedInfo ri;
    memset(&ri, 0, sizeof(ReceivedInfo));
    recvfrom(sockfd, (char*)&ri, sizeof(ReceivedInfo), MSG_WAITALL,
        (struct sockaddr*)&addr, &len);
    return ri;
}
