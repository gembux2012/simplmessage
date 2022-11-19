#include "mainwindow.h"
#include "mesendger.h"
#include "ui_mainwindow.h"
// now
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);
  ui->textBrowser->resize(300, 500);
  Messendger *client = new Messendger();
  connect(this, &MainWindow::cnt, client, &Messendger::connectTo);
  connect(this, &MainWindow::send, client, &Messendger::SendTo);
  // connect(client, &Client::Logger, this, &MainWindow::toLog);

  Worker *worker = new Worker();
  QThread *thread = new QThread();
  worker->moveToThread(thread);
  // При запуске потока запускаем выполнение метода Worker::process()
  connect(thread, &QThread::started, worker, &Worker::process);
  // При излучении сигнала finished получаем флаг успешности и выводим в консоль
  // соответствующее сообщение
  connect(worker, &Worker::finished, this, [this](bool state) {
    if (state)
      toLog("server start");
    else
      toLog("server error");
  });

  // Также, по сигналу finished отправляем команду на завершение потока
  connect(worker, &Worker::finished, thread, &QThread::quit);
  // А потом удаляем экземпляр обработчика
  connect(worker, &Worker::finished, worker, &QObject::deleteLater);
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
