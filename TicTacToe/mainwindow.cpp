#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "docwindow.h"

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
      //loop_rate.sleep();
      msgSend.data = 0;

      msgsToController_pub.publish(msgSend);
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

    // Initialise UI Label Data --------------------------------------------------------
    ui->scoreLabel->setText("Wins: --");
    ui->matchnoLabel->setText("Match No: --");
    ui->difficultyLabel->setText("Difficulty: --");
    ui->whoseturnLabel->setText("--");

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::msgsToUserCallback(const std_msgs::Int32& _msgRcv)
{
  msgRcv = _msgRcv;
  qDebug() << "statusNumber OK: " << msgRcv.data;

  switch(msgRcv.data) {
     case noInfoCont:
         // do nothing
         break;
     case powerOn:
     case gameStart:
         basicInfo = msgRcv.data;
         basicInfoFunction();
         break;
     case startRobotTurn:
     case startPlayerTurn:
         whoseTurn = msgRcv.data;
         whoseTurnFunction();
         break;
     case robotWinOnce:
     case playerWinOnce:
     case drawOnce:
         winOnce = msgRcv.data;
         winOnceFunction();
         break;
     case robotWinAll:
     case playerWinAll:
     case drawAll:
         winAll = msgRcv.data;
         winAllFunction();
         break;
     default:
         qDebug() << "Warning: statusNumber = " << msgRcv.data;
         break;
  }
  
/*--------------
 TIMER FUNCTIONS
---------------*/
// Publishes timerExp status and sends message to user that timer has expired
void MainWindow::timerExpired()
{
    msgSend.data = timerExp;
    msgsToController_pub.publish(msgSend);

    QMessageBox::warning(this, "Timer Expired", "Time is up! Robot wins by default.");
}

void MainWindow::timerControl()
{
    QString timerText = QString::number(timer->remainingTime()/1000);

    ui->timerLabel->setText("Time Left: " +timerText);
    // OPTIONAL: Convert to minutes and seconds
}

/*--------------
 TTT GAME FUNCTIONS
---------------*/
// Restarts timer and sends message to user that turn has started.
void MainWindow::startUserTurn(){
   timer->start(120000); // 2 minutes (120 seconds)

   QMessageBox::information(this, "STARTUSERTURN", "FUNCTION IS CALLED");
}

void MainWindow::matchNoControl()
{
  switch(winCount) {
      case 0:
        ui->matchnoLabel->setText("Match No: 1 of 3");
        break;
      case 1:
        ui->matchnoLabel->setText("Match No: 2 of 3");
        break;
      case 2:
        ui->matchnoLabel->setText("Match No: 3 of 3");
        break;
      case 3:
        ui->scoreLabel->setText("Match No: --");
        break;
  }
}

/*--------------------------
 CALLED DIRECTLY BY CALLBACK
---------------------------*/
void MainWindow::basicInfoFunction()
{
  switch(basicInfo){
      case powerOn:
        QMessageBox::information(this, "Robot Power On", "Robot has been powered on!");
        break;
      case gameStart:
        QMessageBox::information(this, "Start Game", "Robot has been powered on!");
        break;
  }
}

void MainWindow::whoseTurnFunction()
{
  // Signal whose turn it is
  switch(whoseTurn){
      case startRobotTurn:
        QMessageBox::information(this, "Robot Turn", "It is the robot's turn!");
        ui->whoseturnLabel->setText("Robot's Turn");
        break;
      case startPlayerTurn:
        QMessageBox::information(this, "Player Turn", "It is your turn!");
        ui->whoseturnLabel->setText("Player's Turn");
        startUserTurn();
        break;
  }

  // Set match number
  matchNoControl();

}

void MainWindow::winOnceFunction()
{
  winCount++;
  QString gameWinner;

  // Determine who has won and set value for gameWinner accordingly
  switch(winOnce){
      case robotWinOnce:
        gameWinner = 'R';
        break;
      case playerWinOnce:
        gameWinner = 'P';
        break;
      case drawOnce:
        gameWinner = 'D';
        break;
  }

  // Update text for scoreLabel
  switch(winCount){
      case 1:
        ui->scoreLabel->setText("Wins: " + gameWinner);
        break;
      case 2:
        ui->scoreLabel->setText(ui->scoreLabel->text() + " | " + gameWinner);
        break;
      case 3:
        ui->scoreLabel->setText(ui->scoreLabel->text() + " | " + gameWinner);
        break;
  }

}

void MainWindow::winAllFunction()
{
  switch(winAll){
      case robotWinAll:
        QMessageBox::information(this, "Robot Wins Overall", "Robot is the overall winner!");
        break;
      case playerWinAll:
        QMessageBox::information(this, "Player Wins Overall", "You are the overall winner!");
        break;
      case drawAll:
        QMessageBox::information(this, "Overall Draw", " There is a draw overall!");
        break;
  }

  // Reset member variables and game
  winCount = noInfoCont;

}

/*--------------------------
 UI INTERACTIVITY
---------------------------*/
// Ends the user turn and waits to start robot turn
void MainWindow::on_pushButton_clicked()
{
    timer->stop();

    // Tell controller that user has finished their turn
    msgSend.data = boardR1C1;
    msgsToController_pub.publish(msgSend);

    // Wait for signal that robot turn has started

   //while not robot turn, do nothing

   // if robot turn, send QMessageBox to user that it is the robot's turn

   // wait for signal that player turn has started

    //
}


// Pushbutton name : X and O
// Win Count: Set 1 Set 2 Set 3
// Add randomising function to choosing difficulty
// Send number from 1 to 9 for board when button is chosen.
// instead of sending endUserTurn, send a value from 1 to 9 to controller.

/*--------------------------
 TOOLBAR FUNCTIONS
---------------------------*/
void MainWindow::on_actionNew_Game_triggered()
{
    // Make custom message box dialog
    QMessageBox chooseDifficulty;
    chooseDifficulty.setWindowTitle("New Game");
    chooseDifficulty.setText("Choose Your Difficulty: Easy or Hard?");
    QAbstractButton* pButtonEasy = chooseDifficulty.addButton("Easy", QMessageBox::NoRole);
    QAbstractButton* pButtonHard = chooseDifficulty.addButton("Hard", QMessageBox::YesRole);

    chooseDifficulty.exec();

    if(chooseDifficulty.clickedButton() == pButtonEasy){
       ui->difficultyLabel->setText("Difficulty: Easy");
       msgSend.data = newGameEasy; // Prepare to send controller easy difficulty signal

    }
    else if(chooseDifficulty.clickedButton() == pButtonHard) {
       ui->difficultyLabel->setText("Difficulty: Hard");
       msgSend.data = newGameHard; // Prepare to send controller hard difficulty signal
    }

    msgsToController_pub.publish(msgSend);
}



void MainWindow::on_actionPower_Off_triggered()
{
  QMessageBox::StandardButton power =
      QMessageBox::question(this, "Power Off", "Would you like to end your game and power off?",
      QMessageBox::Yes | QMessageBox::No);

  // If user wants to quit, send power off message to controller and close main window
  if(power == QMessageBox::Yes) {
      msgSend.data = powerOff;
      msgsToController_pub.publish(msgSend);
      QApplication::quit();
  }

}

/*--------------------------
 TTT BOARD PUSHBUTTON FUNCTIONS
---------------------------*/
void MainWindow::on_pushButton_8_clicked()
{
    ui->pushButton_8->setText("O");
}

// Open documentation window when "help" is selected
void MainWindow::on_actionDocumentation_triggered()
{
    docWindow docwindow;
    docwindow.setModal(true);
    docwindow.exec();

}
