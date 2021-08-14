#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Publisher and Subscriber Setup-----------------------------------------------

    msgsToController_pub = nh.advertise<std_msgs::Int32>("msgsToController", 1000);
    ros::Rate loop_rate(10);
    if(ros::ok())
    {
      loop_rate.sleep();
      std_msgs::Int32 msg;
      msg.data = 0;

      msgsToController_pub.publish(msg);
      ros::spinOnce();
    }

    sub = nh.subscribe("controller_message", 1000, &MainWindow::msgsToUserCallback, this);
    sleep(3); // Messages are only sent to the topic every 3 seconds
    ros::spinOnce();



    // Timer Setup------------------------------------------------------------------
    secTimer = new QTimer(this);
    connect(secTimer, SIGNAL(timeout()), this, SLOT(timerControl()));
    secTimer->start(1000);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerExpired()));
    //timer->start(5000);
    timer->start(120000); // 2 minutes (120 seconds)

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::msgsToUserCallback(const project::ControllerMessage& _controllerStatus)
{
  saveValues(_controllerStatus);

  switch(controllerStatus.playerId) {
    case 0:  // NA

      break;
    case -1: // AI

      break;
    case 1:  // OP

      break;
    case 2:  // DR

      break;
  }


  qDebug() << "playerId: " << controllerStatus.playerId;
  qDebug() << "gameWinner: " << controllerStatus.gameWinner;

}

void MainWindow::saveValues(project::ControllerMessage _controllerStatus){
    controllerStatus.playerId = _controllerStatus.playerId;
    controllerStatus.gameWinner = _controllerStatus.gameWinner;
    controllerStatus.setWinners = _controllerStatus.setWinners;
}


// Publishes timerExp status and sends message to user that timer has expired
void MainWindow::timerExpired()
{
    msg.data = timerExp;
    msgsToController_pub.publish(msg);

    QMessageBox::warning(this, "Timer Expired", "Time is up! Robot wins by default.");
}

void MainWindow::timerControl()
{
    QString timerText = QString::number(timer->remainingTime()/1000);
    ui->timerLabel->setText("Time Left: " +timerText);
    // OPTIONAL: Convert to minutes and seconds
}

// Restarts timer and sends message to user that turn has started.
void MainWindow::startUserTurn(){
   timer->start(120000); // 2 minutes (120 seconds)

   QMessageBox::information(this, "Player Turn", "Your turn starts!");
}


// Define Event - then set status values back to 0 to avoid duplicate events

// Ends the user turn and waits to start robot turn
void MainWindow::on_pushButton_clicked()
{
    timer->stop();

    // Tell controller that user has finished their turn
    msg.data = endUserTurn;
    msgsToController_pub.publish(msg);

    // Wait for signal that robot turn has started

   //while not robot turn, do nothing

   // if robot turn, send QMessageBox to user that it is the robot's turn

   // wait for signal that player turn has started

    //
}
