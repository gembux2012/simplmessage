#include "mainwindow.h"
#include "mesendger.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  ui->textBrowser->resize(300, 500);
  Client *client = new Client();
  connect(this, &MainWindow::cnt, client, &Client::connectTo);
  connect(this, &MainWindow::send, client, &Client::SendTo);
  // connect(client, &Client::Logger, this, &MainWindow::toLog);

  th_server *thserver = new th_server();
  QThread *thread = new QThread();
  thserver->moveToThread(thread);
  // При запуске потока запускаем выполнение метода Worker::process()
  connect(thread, &QThread::started, thserver, &th_server::process);
  // При излучении сигнала finished получаем флаг успешности и выводим в консоль
  // соответствующее сообщение
  connect(thserver, &th_server::finished, this, [this](bool state) {
    if (state)
      toLog("server stop");
    else
      toLog("server error");
  });

  // Также, по сигналу finished отправляем команду на завершение потока
  connect(thserver, &th_server::finished, thread, &QThread::quit);
  // А потом удаляем экземпляр обработчика
  connect(thserver, &th_server::finished, thserver, &QObject::deleteLater);
  // И наконец, когда закончит работу поток, удаляем и его
  connect(thread, &QThread::finished, thread, &QObject::deleteLater);
  // connect(thserver, &Server::Logger, this, &MainWindow::toLog);
  thread->start();

  // delete client;
  // delete server;
  // delete thread;
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::toLog(QString str) { ui->textEdit->append(str); }

void MainWindow::on_pushButton_clicked() { emit cnt(); }

void MainWindow::on_pushButton_3_clicked() {
  emit send(ui->textEdit->toPlainText());
}
