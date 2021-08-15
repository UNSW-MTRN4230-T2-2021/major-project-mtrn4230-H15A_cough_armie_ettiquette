#ifndef DOCWINDOW_H
#define DOCWINDOW_H

#include <QDialog>

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
};

#endif // DOCWINDOW_H
