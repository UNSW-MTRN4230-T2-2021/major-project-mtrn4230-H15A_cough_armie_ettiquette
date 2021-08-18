#ifndef DOCWINDOW_H
#define DOCWINDOW_H

#include <QDialog>
#include <QTextEdit>
#include <QScrollArea>

namespace Ui {
class docWindow;
}

class docWindow : public QDialog
{
  Q_OBJECT

public:
  explicit docWindow(QWidget *parent = nullptr);
  ~docWindow();

private:
  Ui::docWindow *ui;
  QScrollArea *scrollArea;

  QString text;
};

#endif // DOCWINDOW_H
