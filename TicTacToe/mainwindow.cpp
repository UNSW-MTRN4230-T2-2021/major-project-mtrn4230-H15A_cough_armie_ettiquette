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

    // Button Group Setup-----------------------------------------------------------
    buttonGroup = new QButtonGroup(this);

    // Add buttons to buttonGroup
    buttonGroup->addButton(ui->pBR1C1, 1);
    buttonGroup->addButton(ui->pBR1C2, 2);
    buttonGroup->addButton(ui->pBR1C3, 3);
    buttonGroup->addButton(ui->pBR2C1, 4);
    buttonGroup->addButton(ui->pBR2C2, 5);
    buttonGroup->addButton(ui->pBR2C3, 6);
    buttonGroup->addButton(ui->pBR3C1, 7);
    buttonGroup->addButton(ui->pBR3C2, 8);
    buttonGroup->addButton(ui->pBR3C3, 9);
    buttonGroup->addButton(ui->pBEndTurn, 10);

    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(buttonSelected(int)));

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
    ui->whoseTurnLabel->setText("--");
//    Qt::HANDLE threadNo = QThread::currentThreadId();
//    qDebug() << threadNo;
//    qThread->moveToThread(qThread);

    // Testing
//    buttonGroup->button(1)->setText("X");
//    buttonGroup->button(4)->setText("X");
//    buttonGroup->button(2)->setText("O");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::msgsToUserCallback(const std_msgs::Int32& _msgRcv)
{
  msgRcv = _msgRcv;
  qDebug() << "statusNumber: " << msgRcv.data;

  switch(msgRcv.data) {
     case noInfoCont:
         // do nothing
         break;
     case boardR1C1:
     case boardR1C2:
     case boardR1C3:
     case boardR2C1:
     case boardR2C2:
     case boardR2C3:
     case boardR3C1:
     case boardR3C2:
     case boardR3C3:
         robotMoveId = msgRcv.data;
         recordRobotMove();
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
         qDebug() << "Warning! Invalid Status Number" << msgRcv.data;
         break;
  }

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
//   Qt::HANDLE threadNo = QThread::currentThreadId();
//   qDebug() << threadNo;
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
      default:
        ui->matchnoLabel->setText("Match No: --");
        break;
  }
}

void MainWindow::buttonSelected(int buttonId) {

    if((prevButtonId != -1) && (buttonGroup->button(prevButtonId)->isCheckable()) &&
       (buttonGroup->button(buttonId)->isCheckable())) {
        buttonGroup->button(prevButtonId)->setText("");
    }

    // add if button text is not already O
    if((buttonGroup->button(buttonId)->text() == "") && (buttonGroup->button(buttonId)->isCheckable())) {
        buttonGroup->button(buttonId)->setText("O");
        msgSend.data = buttonId;
        prevButtonId = buttonId;
    }

}

void MainWindow::toggleCheckableBoxes(bool _checkable){

  if (_checkable) {
    for(int i = 1; i < 11; i++)
    {
      if((buttonGroup->button(i)->text() == ""))
        buttonGroup->button(i)->setCheckable(true);
      else{
        buttonGroup->button(i)->setCheckable(false);
      }
    }
  }
  else {
    for(int i = 1; i < 11; i++)
    {
        buttonGroup->button(i)->setCheckable(false);
    }
  }
}

void MainWindow::resetVariables(){
  basicInfo = noInfoCont;
  whoseTurn = noInfoCont;
  winOnce = noInfoCont;
  winAll = noInfoCont;
  robotMoveId = noInfoUI;
  prevButtonId = -1;
  robotMoveId = -1;
  selectedButton = -1;
}

void MainWindow::resetGameBoard(){
  for(int i = 1; i < 10; i++) {
     buttonGroup->button(i)->setText("");
     buttonGroup->button(i)->setCheckable(false);
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
        QMessageBox::information(this, "Start Game", "Game starts now!");
        // Set match number
        matchNoControl();
        break;
  }
}

void MainWindow::whoseTurnFunction()
{
  // Signal whose turn it is
  switch(whoseTurn){
      case startRobotTurn:
        ui->whoseTurnLabel->setText("Robot's Turn");
        // End Turn button is already set to false at end of player turn
        prevButtonId = -1;  // reset previous button tracker
        // Make boxes checkable
        toggleCheckableBoxes(false);
        QMessageBox::information(this, "Robot Turn", "It is the robot's turn!");
        break;
      case startPlayerTurn:
        ui->whoseTurnLabel->setText("Player's Turn");
        ui->pBEndTurn->setVisible(true);
        toggleCheckableBoxes(true);
        QMessageBox::information(this, "Player Turn", "It is your turn!");
        startUserTurn();
        break;
  }



}

void MainWindow::winOnceFunction()
{
  winCount++;
  QString gameWinner;

  // Determine who has won and set value for gameWinner accordingly
  switch(winOnce){
      case robotWinOnce:
        gameWinner = 'R';
        QMessageBox::information(this, "Robot Wins", "Robot wins this game!");
        break;
      case playerWinOnce:
        gameWinner = 'P';
        QMessageBox::information(this, "Player Wins", "You win this game!");
        break;
      case drawOnce:
        gameWinner = 'D';
        QMessageBox::information(this, "Draw", "This game is a draw!");
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

  // Set new match number
  matchNoControl();

  // reset member variables
  resetVariables();
  // reset game board
  resetGameBoard();

}

void MainWindow::winAllFunction()
{
  //TEST GAME THOROUGHLY
  // PLAY THROUGH ENTIRE GAME AS IF A PROPER GAME IS PLAYED.
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
  // Reset member variables
  winCount = noInfoCont;
  resetVariables();

  // reset game board
  resetGameBoard();

  // Prompt new game or power off


}

void MainWindow::recordRobotMove()
{
    buttonGroup->button(robotMoveId)->setText("X");
    buttonGroup->button(robotMoveId)->setCheckable(false);
}

/*--------------------------
 UI INTERACTIVITY
---------------------------*/
// Ends the user turn and waits to start robot turn
void MainWindow::on_pBEndTurn_clicked()
{
    selectedButton = buttonGroup->checkedId();
    if(whoseTurn == startPlayerTurn) {
      // if no button has been pressed

      if(selectedButton == -1) {
        QMessageBox::warning(this, "No Move Selected", "Please select a tile for your next move!");
      }
      // if a button has been pressed
      else {
        // Immediately hide button to prevent choosing more than one tile
        ui->pBEndTurn->setVisible(false);
        // Make boxes uncheckable
        toggleCheckableBoxes(false);
        // Tell controller what square user has chosen at end of their turn
        msgsToController_pub.publish(msgSend);
        // timer stops as end of turn is reached
        timer->stop();
      }
    }
}

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

// Open documentation window when "help" is selected
void MainWindow::on_actionDocumentation_triggered()
{
    docWindow docwindow;
    docwindow.setModal(true);
    docwindow.exec();

}

/*--------------------------
 TTT BOARD PUSHBUTTON FUNCTIONS
---------------------------*/
void MainWindow::on_pBR1C1_clicked()
{
//    ui->pBR1C1->toggle();
//     if(ui->pBR1C1->isChecked())
//        ui->pBR1C1->setText("O");
//     else
//      ui->pBR1C1->setText("EEE");
}


// Things to Fix or Implement:
// Function WinAllFunction : prompt user to start new game or power off
// fix bug with end turn button disappearing without tile being chosen
// reset board and all variables at end of each win, and at end of ultimate win
// Fix up timer (timer tim.X?)
// take screenshot of UI mid game for nethmini


// Questions for Team:
// How will the UI get the most recent board state? It just needs to know where to mark the X of the robot's turn
// What sort of test cases should I write for the UI?
// I feel like the test cases specified in our requirements doc could be improved. WHat sort of format are you guys using for your test cases?
