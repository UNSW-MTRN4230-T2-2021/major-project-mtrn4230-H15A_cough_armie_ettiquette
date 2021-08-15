#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ros/ros.h"
//#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // CHECK THIS AGAINST DOCUMENT
    enum uiStatusNo{
       noInfoUI = 0,
       newGameEasy = 10,
       newGameHard = 11,

       // Piece Locations on Board
       boardR1C1 = 1,
       boardR1C2 = 2,
       boardR1C3 = 3,
       boardR2C1 = 4,
       boardR2C2 = 5,
       boardR2C3 = 6,
       boardR3C1 = 7,
       boardR3C2 = 8,
       boardR3C3 = 9,

       timerExp = 12,
       pauseGame = 13,
       powerOff = 14,
       violationRes = 15
    };

    enum contStatusNo {
      noInfoCont= 0,
      powerOn = 1,
      gameStart = 2,
      startRobotTurn = 3,
      startPlayerTurn = 4,
      robotWinOnce = 10,
      playerWinOnce = 11,
      drawOnce = 12,
      robotWinAll = 20,
      playerWinAll = 21,
      drawAll = 22
    };

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Subscriber Callback Function
    void msgsToUserCallback(const std_msgs::Int32& _msgRcv);

    // Getters and Setters


    // Tic Tac Toe Functions
    void startUserTurn();
    void matchNoControl();

    // Directly called by callback function 'interrupt'
    void basicInfoFunction();
    void whoseTurnFunction();
    void winOnceFunction();
    void winAllFunction();

public slots:
   void timerExpired();
   void timerControl();

private slots:
   void on_pushButton_clicked();

   void on_actionNew_Game_triggered();
   void on_actionPower_Off_triggered();
   void on_actionDocumentation_triggered();
   void on_pushButton_8_clicked();



private:
    Ui::MainWindow *ui;

    ros::NodeHandle nh;
    ros::Publisher msgsToController_pub;
    ros::Subscriber sub;

    std_msgs::Int32 msgSend;
    std_msgs::Int32 msgRcv;

    int basicInfo = 0;
    int whoseTurn = 0;
    int winOnce = 0;
    int winAll = 0;

    int winCount = 0;

    QTimer *timer;
    QTimer *secTimer;
};

#endif // MAINWINDOW_H
