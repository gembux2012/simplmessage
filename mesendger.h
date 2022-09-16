#ifndef MESENDGER_H
#define MESENDGER_H

#include <QDataStream>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Messendger : public QTcpServer {

  Q_OBJECT;
signals:
  void Logger(QString str);

public:
  QTcpSocket *socket;

private:
  QByteArray Data;
  quint16 nextBlockSize;
  void SendTo(QString str);

public slots:
  void toLog(QString str);
  void slotReadyRead();
};

class Server : public Messendger {
  Q_OBJECT;

public:
  Server();
public slots:
  void incomingConnection(qintptr socketDescriptor);

private:
  QVector<QTcpSocket *> socets;
};

class Client : public Messendger {
public:
  void connectTo();
};

#endif // MESENDGER_H
