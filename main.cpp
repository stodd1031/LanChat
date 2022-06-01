#include "mainwindow.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
