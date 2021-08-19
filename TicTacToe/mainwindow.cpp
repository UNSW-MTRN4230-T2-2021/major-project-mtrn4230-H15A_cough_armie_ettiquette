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
    ui->whoseTurnLabel->setText("Turn: --");
}

MainWindow::~MainWindow()
{
    delete buttonGroup;
    delete secTimer;
    delete timer;
    delete qThreadMain;
    delete qThreadSub;
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
         recordRobotMove();           // SEGMENTATION FAULT X3
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
  if (msgSend.data != timerExp){
    QCoreApplication::postEvent(this, new QEvent(StopTimerEventType));
    ui->pBEndTurn->setVisible(false);
    msgSend.data = timerExp;
    msgsToController_pub.publish(msgSend);

    QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::warning, "Timer Expired", "Time is up! Robot wins by default." ));
  }
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
   timer->start(120000); // 2 minutes (120 seconds) // SEGMENTATION FAULT

   //QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information, "STARTUSERTURN", "FUNCTION IS CALLED");
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

bool MainWindow::event(QEvent *event)
{

  if(event->type() == CreateInformationEventType){
    PopUpEvent* wEvent = dynamic_cast<PopUpEvent*>(event);
    switch(wEvent->type){
    case PopUpEvent::PopUpType::information:
      QMessageBox::information(this, wEvent->title, wEvent->text);
      break;
    case PopUpEvent::PopUpType::warning:
      QMessageBox::warning(this,  wEvent->title, wEvent->text);
      break;
    }
  }

  if(event->type() == StartTimerEventType){
    timer->start(120000);
    //timer->start(5000);
  }
  else if(event->type() == StopTimerEventType){
    timer->stop();
  }

  return QMainWindow::event(event);
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
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information,  "Robot Power On", "Robot has been powered on!"));
        break;
      case gameStart:
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information,  "Start Game", "Game starts now!"));
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
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information,  "Robot Turn", "It is the robot's turn!"));
        break;
      case startPlayerTurn:
        ui->whoseTurnLabel->setText("Player's Turn");
        ui->pBEndTurn->setVisible(true);
        toggleCheckableBoxes(true);
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information, "Player Turn", "It is your turn!"));
        // start timer
        QCoreApplication::postEvent(this, new QEvent(StartTimerEventType));
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
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information, "Robot Wins", "Robot wins this game!"));
        break;
      case playerWinOnce:
        gameWinner = 'P';
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information, "Player Wins", "You win this game!"));
        break;
      case drawOnce:
        gameWinner = 'D';
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information, "Draw", "This game is a draw!"));
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

  // It is no-one's turn.
  ui->whoseTurnLabel->setText("Turn: --");
  // Set new match number
  matchNoControl();

  // reset member variables
  resetVariables();
  // reset game board
  resetGameBoard();

}

void MainWindow::winAllFunction()
{
  // TEST GAME THOROUGHLY
  // PLAY THROUGH ENTIRE GAME AS IF A PROPER GAME IS PLAYED.
  // WINALL FUNCTION SHOULD RESET ALL TEXT ON MAINWINDOW
  switch(winAll){
      case robotWinAll:
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information, "Robot Wins Overall", "Robot is the overall winner!"));
        break;
      case playerWinAll:
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information, "Player Wins Overall", "You are the overall winner!"));
        break;
      case drawAll:
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::information, "Overall Draw", " There is a draw overall!"));
        break;
  }
  // Reset member variables
  winCount = noInfoCont;
  resetVariables();

  // reset game board
  resetGameBoard();

  // Reset labels on user interface
  ui->scoreLabel->setText("Wins: --");
  ui->matchnoLabel->setText("Match No: --");
  ui->difficultyLabel->setText("Difficulty: --");
  ui->whoseTurnLabel->setText("Turn: --");
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
        QCoreApplication::postEvent(this, new PopUpEvent(PopUpEvent::PopUpType::warning, "No Move Selected", "Please select a tile for your next move!" ));
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
        QCoreApplication::postEvent(this, new QEvent(StopTimerEventType));
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
    QAbstractButton* pButtonEasy = chooseDifficulty.addButton("Easy", QMessageBox::RejectRole);
    QAbstractButton* pButtonHard = chooseDifficulty.addButton("Hard", QMessageBox::AcceptRole);
    QAbstractButton* pButtonExit = chooseDifficulty.addButton("Exit", QMessageBox::DestructiveRole);
    chooseDifficulty.exec();

    if(chooseDifficulty.clickedButton() == pButtonEasy){
       ui->difficultyLabel->setText("Difficulty: Easy");
       msgSend.data = newGameEasy; // Prepare to send controller easy difficulty signal
    }
    else if(chooseDifficulty.clickedButton() == pButtonHard) {
       ui->difficultyLabel->setText("Difficulty: Hard");
       msgSend.data = newGameHard; // Prepare to send controller hard difficulty signal
    }

    if(chooseDifficulty.clickedButton() == pButtonEasy ||
       chooseDifficulty.clickedButton() == pButtonHard){
       // Clear UI and board data
      ui->scoreLabel->setText("Wins: --");
      ui->whoseTurnLabel->setText("Turn: --");
      winCount = noInfoCont;
      resetVariables();
      matchNoControl();
      resetGameBoard();
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
void MainWindow::on_actionDocumentation_triggered()
{
    docWindow docwindow;

// Open documentation window when "help" is selected
    docwindow.setModal(true);
    docwindow.exec();

}

/*--------------------------
 TTT BOARD PUSHBUTTON FUNCTIONS
---------------------------*/
void MainWindow::on_pBR1C1_clicked()
{
}

// Things to Fix or Implement:
// fix bug with end turn button disappearing without tile being chosen
// Fix up timer (timer tim.X?)
// make timer: 0 be timer: --
// fix up new game - reject role is the x in the corner - easy is default value
// take updated screenshot of UI mid game for nethmini
// FIX ALL SEGMENTATION FAULTS - tagged in code using comments 
