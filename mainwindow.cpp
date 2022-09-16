#include "mainwindow.h"
#include "mesendger.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  Server server;
  connect(&server, &Server::Logger, this, &MainWindow::toLog);

  if (server.isListening()) {
    ui->textEdit->append("server start");
  } else {
    ui->textEdit->append("server error");
  }
  QThread *s_thread = new QThread();
  server.moveToThread(s_thread);
  s_thread->start();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::toLog(QString str) { ui->textEdit->append(str); }
