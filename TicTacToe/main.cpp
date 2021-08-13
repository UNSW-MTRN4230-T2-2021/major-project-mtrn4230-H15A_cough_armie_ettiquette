#include "ros/ros.h"
#include "std_msgs/String.h"

#include <thread>

#include "mainwindow.h"
#include <QApplication>

int pubThread(int argc, char **argv)
{
  ros::init(argc, argv, "publisher");
  ros::NodeHandle nh;

  ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    std_msgs::String msg;
    msg.data = "hello world";

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}


void subThreadCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int subThread(int argc, char **argv)
{
  ros::init(argc, argv, "subscriber");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("chatter", 1000, subThreadCallback);

  ros::spin();

  return 0;
}


int main(int argc, char *argv[])
{
    std::thread firstthread(pubThread, argc, argv);
    std::thread secondthread(subThread, argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
