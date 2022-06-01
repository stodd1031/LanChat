#include "host.h"

Host::Host(void (MainWindow::* updateTextBox)(QString), MainWindow* mw)
{
    this->updateTextBox = updateTextBox;
    this->mw = mw;
    openSocket();
    bindSocket();
    networkThread = std::thread(&Host::loop, this);
    strcpy(myUserName, "server");

    QString ipAndPort;
    ipAndPort += "ip: ";
    ipAndPort += QString::fromStdString(myIP);
    ipAndPort += "\nport: ";
    ipAndPort += QString::number(PORT);

    (mw->*updateTextBox)(ipAndPort);
}

Host::~Host()
{
    loopBool = false;
    networkThread.join();
}

void Host::bindSocket() {
#ifdef WIN32
    // Prepare the sockaddr_in structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(myIP.c_str());
    // servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind
    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) ==
        SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

#else
    // Filling server MessageInformation
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr(myIP.c_str());
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
#endif
}

void Host::send(QString string)
{
    ReceivedInfo si;
    si.type = SERVER_MESSAGE;
    char cliaddrChar[sizeof(cliaddr)];
    memcpy(cliaddrChar, &cliaddr, sizeof(cliaddr));
    strcpy(si.serverMessageInfo.userName, myUserName);
    memcpy(si.serverMessageInfo.message, string.toStdString().c_str(), MAX_MESSAGE_LEN);

    for (int index = 0; index < clients.size(); index++)
    {
        Network::send(si, clients[index]);
    }
    QString name = "me: ";
    (mw->*updateTextBox)(name + si.serverMessageInfo.message);
}

void Host::loop()
{
    ReceivedInfo ri;
    loopBool = true;
    while (loopBool)
    {
        ri = recieve(cliaddr);
        switch (ri.type)
        {
        case JOIN: {
            clients.push_back(cliaddr);
            char cliaddrChar[sizeof(cliaddr)];
            memcpy(cliaddrChar, &cliaddr, sizeof(cliaddr));

                std::array<char, sizeof(cliaddr)> &A = reinterpret_cast<std::array<char, sizeof(cliaddr)>&>(cliaddrChar);




            cliaddrToUsername[A] = ri.joinInfo.username;
            ReceivedInfo si;
            si.type = ACCEPT_JOIN;
            Network::send(si, cliaddr);
            break;}
        case LEAVE: {
            int found = -1;
            for (int index = 0; index < clients.size(); index++)
            {
                if (memcmp(&cliaddr, &clients[index], sizeof(sockaddr_in)) == 0)
                {
                    found = index;
                    break;
                }
            }
            if (found > -1)
            {
                clients.erase(clients.begin() + found);
            }
            break;}
        case USER_MESSAGE: {
            int found = -1;
            for (int index = 0; index < clients.size(); index++)
            {
                if (memcmp(&cliaddr, &clients[index], sizeof(sockaddr_in)) == 0)
                {
                    found = index;
                    break;
                }
            }
            ReceivedInfo si;
            char cliaddrChar[sizeof(cliaddr)];
            memcpy(cliaddrChar, &cliaddr, sizeof(cliaddr));

            std::array<char, sizeof(cliaddr)> &A = reinterpret_cast<std::array<char, sizeof(cliaddr)>&>(cliaddrChar);

            strcpy(si.serverMessageInfo.userName, cliaddrToUsername[A].toStdString().c_str());
            memcpy(si.serverMessageInfo.message, ri.userMessageInfo.message, MAX_MESSAGE_LEN);
            if (found > -1)
            {
                for (int index = 0; index < clients.size(); index++)
                {
                    Network::send(si, clients[index]);
                }
                std::array<char, sizeof(cliaddr)> &A = reinterpret_cast<std::array<char, sizeof(cliaddr)>&>(cliaddrChar);
                (mw->*updateTextBox)(cliaddrToUsername[A] + ": " + si.serverMessageInfo.message);
            }
            break;}
        } // end switch (ri.type)

    }
}

