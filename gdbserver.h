#ifndef GDBSERVER_H
#define GDBSERVER_H

#include <QObject>
#include <QLocalServer>
#include <QTcpServer>
#include <inttypes.h>

class QStLink;
class GdbServer : public QObject
{
    Q_OBJECT
public:
    explicit GdbServer(QObject *parent);
    
signals:
    
public slots:
    
private slots:
    void newConnection();
    void ReadyRead(void);
    void CoreHalted(uint32_t addr);

    void Erasing(int perc);
    void Flashing(int perc);

private:
    QStLink * stlink;
    QTcpServer * server;
    int port;

    typedef QVector<QByteArray> params_t;

    static void MakePacket(QByteArray & data, QByteArray * binary = NULL);
    static bool DecodePacket(QByteArray & data);
    params_t ParseParams(const QByteArray & data);

    void processPacket(QTcpSocket * soc,const QByteArray & rawdata);
    QByteArray processQueryPacket(const QByteArray & rawdata);
    QByteArray processBreakpointPacket(const QByteArray & rawdata);

    QByteArray ans;
    QByteArray input;
    QTcpSocket * soc;
    QByteArray FlashProgram;
};

#endif // GDBSERVER_H
