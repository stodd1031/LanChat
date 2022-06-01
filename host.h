#ifndef HOST_H
#define HOST_H
#include "network.h"
#include <QMap>



class Host : public Network
{
public:
    Host(void (MainWindow::* updateTextBox)(QString), MainWindow *mw);
    ~Host();
    void send(QString string);
private:
    void bindSocket();
    void loop();

    sockaddr_in cliaddr;
    std::vector<sockaddr_in> clients;
    QMap<std::array<char, 16>, QString> cliaddrToUsername;

    
};

#endif // HOST_H
