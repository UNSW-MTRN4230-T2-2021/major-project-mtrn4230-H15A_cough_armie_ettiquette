#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ros/ros.h"
//#include "std_msgs/String.h"
#include "std_msgs/Int32.h"

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QEvent>
#include <QThread>
#include <QButtonGroup>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum pieceLocations {
      boardR1C1 = 1,
      boardR1C2 = 2,
      boardR1C3 = 3,
      boardR2C1 = 4,
      boardR2C2 = 5,
      boardR2C3 = 6,
      boardR3C1 = 7,
      boardR3C2 = 8,
      boardR3C3 = 9
    };

    enum uiStatusNo{
       noInfoUI = 0,
       newGameEasy = 10,
       newGameHard = 11,
       timerExp = 12,
       pauseGame = 13,
       //unpauseGame = 14,
       powerOff = 14,
       violationRes = 15
    };

    enum contStatusNo {
      noInfoCont= 0,
      powerOn = 10,
      gameStart = 11,
      startPlayerTurn = 12,
      startRobotTurn = 13,
      robotWinOnce = 14,
      playerWinOnce = 15,
      drawOnce = 16,
      robotWinAll = 17,
      playerWinAll = 18,
      drawAll = 19,
    };

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Subscriber Callback Function
    void msgsToUserCallback(const std_msgs::Int32& _msgRcv);

    // Getters and Setters


    // Tic Tac Toe Functions
    void startUserTurn();
    void matchNoControl();
    void toggleCheckableBoxes(bool checkable);  // check the boxes are checked/unchecked properly
    void resetVariables();
    void resetGameBoard();
    // Directly called by callback function 'interrupt'
    void basicInfoFunction();
    void whoseTurnFunction();
    void winOnceFunction();
    void winAllFunction();
    void recordRobotMove();     // check the robot moves are recorded properly

    bool event(QEvent *);

public slots:
   void timerExpired();
   void timerControl();
   void buttonSelected(int buttonId);

private slots:
   // End Turn Button
   void on_pBEndTurn_clicked();

   void on_actionNew_Game_triggered();
   void on_actionPower_Off_triggered();
   void on_actionDocumentation_triggered();

   // Tic Tac Toe Board Buttons
   void on_pBR1C1_clicked();

private:
    static const QEvent::Type CreateInformationEventType = static_cast<QEvent::Type>(9999);
    Ui::MainWindow *ui;
    QButtonGroup *buttonGroup;

    QThread *qThreadMain;
    QThread *qThreadSub;

    int prevButtonId = -1;
    int robotMoveId = -1;
    int selectedButton = -1;

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
    class PopUpEvent : public QEvent {

    public:
      enum PopUpType{
        warning,
        information,
      };
      explicit PopUpEvent(PopUpType type, QString title, QString text) : QEvent(CreateInformationEventType), type(type), title(title), text(text) {}
      PopUpType type;
      QString title;
      QString text;

    };
};

#endif // MAINWINDOW_H
