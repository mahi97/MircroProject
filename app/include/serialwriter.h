#ifndef SerialWriter_H
#define SerialWriter_H

#include "baseserial.h"

class SerialWriter : public BaseSerial
{
    Q_OBJECT

public:
    SerialWriter(QSerialPort *serialPort, QObject *parent = 0);
    virtual ~SerialWriter();

    void write(const QByteArray &writeData);

private slots:
    void handleBytesWritten(qint64 bytes);
    virtual void handleTimeout();
    virtual void handleError(QSerialPort::SerialPortError error);

private:
    qint64          m_bytesWritten;
};

#endif // SerialWriter_H
