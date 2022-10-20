#ifndef MESENDGER_H
#define MESENDGER_H

#include <QDataStream>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QVector>

class Logable : public QObject {
  Q_OBJECT;
signals:
  QString Logger(QString str);
public slots:
  void toLog(QString str);
};

class th_server : public Logable {
  Q_OBJECT;
signals:
  void finished(bool);
public slots:
  void process();
};

class Messendger : public QObject {
  Q_OBJECT;

public:
  QTcpSocket *socket;

private:
  QByteArray Data;
  quint16 nextBlockSize;
public slots:
  void slotReadyRead();
  void SendTo(QString str);
};

class Server : public Messendger {
  Q_OBJECT;

public:
  Server();
  QTcpServer *tsps;
public slots:
  void in_conection();
  void toLog(QString str);

private:
  QVector<QTcpSocket *> socets;
};

class Client : public Messendger {
  Q_OBJECT;
public slots:
  void connectTo();
};

#endif // MESENDGER_H
