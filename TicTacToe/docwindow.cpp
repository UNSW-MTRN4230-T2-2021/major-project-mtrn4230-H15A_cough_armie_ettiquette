#include "docwindow.h"
#include "ui_docwindow.h"

docWindow::docWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::docWindow)
{
  ui->setupUi(this);

  text = "<b>How to Play Tic-Tac-Toe Against Ur5e:</b><br><br>"
            "The following documentation explains components"
            " of the User Interface and how to play Tic-Tac-Toe"
            " against the Ur5e robot once the simulation is launched."
            "<br><br>"
            "<img src=\"images/AnnotatedUI.png\" width=\"800\" height=\"600\">"
            "<br><br>"
            "<b>1.1</b> – Select this ‘Help’ tab or ‘?’ to open this"
            " documentation containing all relevant information and"
            " instructions regarding this project’s system.<br><br>"
            "<b>1.2</b> – Select this button to turn the Robot’s power off.<br><br>"
            "<b>1.3</b> – Select this button to start a new game.<br><br>"
            "<b>1.4</b> – Select ‘Menu’ tab for a list with the options for"
            " starting a new game or powering off the Robot.<br><br>"
            "<b>2</b> – Displays whether it is the player or robot’s turn.<br><br>"
            "<b>3</b> – Displays the selected difficulty level (easy or hard).<br><br>"
            "<b>4</b> – A timer that indicates how long is left in this"
            " turn. Player’s turn automatically ends once the timer reaches 0. <br><br>"
            "<b>5</b> – The game board, select the button where you wish"
            " to place the game piece during your turn.<br><br>"
            "<b>6</b> – End your turn after placing a piece on the"
            " board for that turn.<br><br>"
            "<b>7</b> – Each game consists of 3 matches; this indicates which of"
            " the matches is currently taking place 1,2 or 3.<br><br>"
            "<b>8</b> – Displays whether the match is a win, lose or a"
            " draw for the Robot or Player.<br><br>";

  ui->textEdit->setText(text);

}

docWindow::~docWindow()
{
  delete ui;
}
