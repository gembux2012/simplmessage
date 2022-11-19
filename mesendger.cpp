#include "mesendger.h"
#include <QDataStream>

// void Server::Server() { tsps = new QTcpServer(); }

void Worker::process() {
  Server *server = new Server();
  server->listen(QHostAddress::Any, 2323);
  if (server != nullptr || server->isListening()) {

    // toLog("Server start");
    emit finished(false);
  } else {
    // toLog("server error");
    emit finished(true);
  }
}
// void Messendger::toLog(QString str) { emit Logger(str); }

void Server::incomingConnection(qintptr socketDescriptor) {
  socket = new QTcpSocket;
  socket->setSocketDescriptor(socketDescriptor);
  QObject::connect(socket, &QTcpSocket::readyRead, this,
                   &Server::slotReadyRead);
  QObject::connect(socket, &QTcpSocket::disconnected, socket,
                   &QTcpSocket::deleteLater);
  socets.push_back(socket);
  toLog("client connectid " + socketDescriptor);
}

// void Server::toLog(QString str) { emit th_server::Logger(str); }

void Messendger::slotReadyRead() {
  socket = (QTcpSocket *)sender();
  QDataStream in(socket);
  in.setVersion(QDataStream::Qt_5_9);
  if (in.status() == QDataStream ::Ok) {
    toLog("read..");
    // QString str;
    // in >> str;
    for (;;) {
      if (nextBlockSize == 0) {
        if (socket->bytesAvailable() < 2) {
          break;
        }
        in >> nextBlockSize;
      }
      if (socket->bytesAvailable() < nextBlockSize) {
        break;
      }
      QString str;
      in >> str;
      nextBlockSize = 0;
      toLog(str);
      SendTo(str);
    }
  } else {
    toLog("data stream error");
  }
}

void Messendger::SendTo(QString str) {
  Data.clear();
  QDataStream out(&Data, QIODevice::WriteOnly);
  out.setVersion(QDataStream ::Qt_5_9);
  out << quint16(0) << str;
  out.device()->seek(0);
  out << quint16(Data.size() - sizeof(quint16));
  out << str;
  socket->write(Data);
}

void Server::connectTo() {
  socket = new QTcpSocket();
  connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
  socket->connectToHost("127.0.0.1", 2323);
  if (socket->waitForConnected())
    toLog("Connected");
  else
    toLog("client no connect");
}
