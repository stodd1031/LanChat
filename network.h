#ifndef NETWORK_H
#define NETWORK_H

#ifdef WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #define MSG_CONFIRM 0
    #define MSG_WAITALL 0
#else
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <sys/param.h>
    #include <sys/socket.h>
#endif

#include <thread>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>

#include <QString>



#define ADDRESS "127.0.0.1"
#define PORT 8080
#define MAX_MESSAGE_LEN 512
#define MAX_USERNAME_LEN 16

#define JOIN 1
#define ACCEPT_JOIN 2
#define LEAVE 3
#define USER_MESSAGE 4
#define SERVER_MESSAGE 5

struct UserMessageInfo
{
    char type;
    char message[MAX_MESSAGE_LEN];
};

struct ServerMessageInfo
{
    char type;
    char userName[16];
    char message[MAX_MESSAGE_LEN];
};

struct JoinInfo
{
    char type;
    char username[MAX_USERNAME_LEN];
};

struct AcceptInfo
{
    char type;
};

struct LeaveInfo
{
    char type;
};

union ReceivedInfo
{
    ReceivedInfo()
    {
        memset(this, 0, sizeof(ReceivedInfo));
    }
    char type;
    UserMessageInfo userMessageInfo;
    ServerMessageInfo serverMessageInfo;
    JoinInfo joinInfo;
    AcceptInfo acceptInfo;
    LeaveInfo leaveInfo;
};

class MainWindow;

class Network
{
public:
    Network();
    virtual void send(QString string){}
    virtual bool getConnected(){}
protected:
    void loop();
    void openSocket();
    void send(ReceivedInfo& mi, struct sockaddr_in& addr);
    ReceivedInfo recieve(struct sockaddr_in& addr);
    char myUserName[16];

#ifdef WIN32
    WSADATA wsa;
    int len;
    SOCKET sockfd;
#else
    socklen_t len;
    int sockfd;
#endif

    struct sockaddr_in servaddr;
    std::string myIP;
    int receiveSize;
    bool loopBool;
    std::thread networkThread;

    MainWindow *mw;
    void (MainWindow::* updateTextBox)(QString);

};

#endif // NETWORK_H
