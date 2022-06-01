#include "client.h"

Client::Client(void (MainWindow::* updateTextBox)(QString), MainWindow *mw, QString ip, QString port, QString username)
{
    this->updateTextBox = updateTextBox;
    this->mw = mw;

    openSocket();
    connect(ip, port);
    ReceivedInfo si;
    si.type = JOIN;
    memcpy(&si.joinInfo.username, username.toStdString().c_str(), std::min(MAX_USERNAME_LEN, (int)(username.length())));
    Network::send (si, servaddr);

    ReceivedInfo ri;
    for (int index = 0; index < 5; index++)
    {
        ri = recieve(servaddr);
        if (ri.type == ACCEPT_JOIN)
        {
            break;
        }
    }
    if (ri.type == ACCEPT_JOIN)
    {
        connected = true;
        networkThread = std::thread(&Client::loop, this);
    }
}

void Client::connect(QString ip, QString port)
{
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr(ip.toStdString().c_str());
    servaddr.sin_port = htons(port.toInt());
}

Client::~Client()
{
    close(sockfd);
}

void Client::loop()
{
    ReceivedInfo ri;
    loopBool = true;
    while(loopBool)
    {
        memset(&ri, 0, sizeof(ReceivedInfo));
        ri = recieve(servaddr);
        if(ri.type)
        {
            QString displayedMessage;
            displayedMessage += ri.serverMessageInfo.userName;
            displayedMessage += ": ";
            displayedMessage += ri.serverMessageInfo.message;
            (mw->*updateTextBox)(displayedMessage);
        }
    }
}

void Client::send(QString string)
{
    ReceivedInfo si;
    si.type = USER_MESSAGE;
    memcpy(si.userMessageInfo.message, string.toStdString().c_str(), MAX_MESSAGE_LEN);
    Network::send(si, servaddr);

    QString name = "me: ";
    (mw->*updateTextBox)(name + si.userMessageInfo.message);
}

bool Client::getConnected()
{
    return connected;
}