#ifndef MESENDGER_H
#define MESENDGER_H

#include <QDataStream>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QVector>

class Logable : private QObject {
  Q_OBJECT;
signals:
  QString Logger(QString str);
public slots:
  void toLog(QString str);
};

class Worker : public QObject {
  Q_OBJECT;
signals:
  void finished(bool);
public slots:
  void process();
};

class Messendger : private QObject {
  Q_OBJECT;

signals:
  QString Logger(QString str);

public:
  QTcpSocket *socket;

private:
  QByteArray Data;
  quint16 nextBlockSize;
public slots:
  void slotReadyRead();
  void SendTo(QString str);
  void connectTo();
  void toLog(QString str);
};

class Server : public Messendger, public QTcpServer {
  Q_OBJECT;

private:
  void incomingConnection(qintptr socketDescriptor);

public:
  // Server();
  // QTcpServer *tsps;
public slots:
  void in_conection();
  void toLog(QString str);

private:
  QVector<QTcpSocket *> socets;
};

#endif // MESENDGER_H
