#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "mesendger.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

signals:
  void cnt();
  void send(QString str);

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

public slots:
  // void slotReadyRead();
  // void SendToServer(QString str);
  void toLog(QString str);
private slots:
  void on_pushButton_clicked();
  void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
