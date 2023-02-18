#include "mainwindow.h"

#include <QApplication>
#include <mongocxx/instance.hpp>






void test();
int main(int argc, char *argv[])
{
    mongocxx::instance ins{};

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

