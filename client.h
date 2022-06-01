#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"

class Client : public Network
{
public:
    Client(void (MainWindow::* updateTextBox)(QString), MainWindow *mw, QString ip, QString port, QString username);
    ~Client();
    void send(QString string);

    bool getConnected();
    
private:
    void connect(QString ip, QString port);
    void loop();
    bool connected;
};

#endif // CLIENT_H
