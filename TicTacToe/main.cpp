#include "mainwindow.h"
#include <QApplication>
#include <thread>

void thread() {
    ros::spin();
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "uiNode");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::thread t(thread);

    return a.exec();
}
