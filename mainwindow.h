#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "host.h"
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateTextBox(QString);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    Network *network;
};
#endif // MAINWINDOW_H
