#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/IMG/Survival_menual.ico"));

    MainWindow w;
    //QRect screenrect = a.primaryScreen()->geometry();


    //w.setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    QSharedMemory shared("very-very-unique-key");

    if (!shared.create(512, QSharedMemory::ReadWrite))
    {
        exit(0);
    }
    w.show();
    return a.exec();
}
