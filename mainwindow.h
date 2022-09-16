#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <thread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void connectTo();

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  QByteArray Data;
  quint16 nextBlockSize;

public slots:
  // void slotReadyRead();
  // void SendToServer(QString str);
  void toLog(QString str);
};

#endif // MAINWINDOW_H
