#include "docwindow.h"
#include "ui_docwindow.h"

docWindow::docWindow(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::docWindow)
{
  ui->setupUi(this);
}

docWindow::~docWindow()
{
  delete ui;
}
