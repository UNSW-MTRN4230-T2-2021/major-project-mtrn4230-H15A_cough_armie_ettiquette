#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ros/ros.h"
//#include "std_msgs/String.h"
#include "std_msgs/Int32.h"
#include "lib/ControllerMessage.h"

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum uiStatusNo{
       noInfo = 0,
       newGameEasy = 1,
       newGameHard = 2,
       endUserTurn = 3,
       timerExp = 4,
       pauseGame = 5,
       powerOff = 6,
       violationRes = 7
    };

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveValues(project::ControllerMessage controllerStatus);
    // Subscriber Callback Function
    void msgsToUserCallback(const project::ControllerMessage& _controllerStatus);

    // Getters and Setters


    // Tic Tac Toe Functions
    void startUserTurn();

public slots:
   void timerExpired();
   void timerControl();

private slots:
   void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    ros::NodeHandle nh;
    ros::Publisher msgsToController_pub;
    ros::Subscriber sub;

    std_msgs::Int32 msg;
    project::ControllerMessage controllerStatus;

    QTimer *timer;
    QTimer *secTimer;
};

#endif // MAINWINDOW_H
