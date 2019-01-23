#ifndef SERIALREADER_H
#define SERIALREADER_H

#include "baseserial.h"

class SerialReader : public BaseSerial
{
    Q_OBJECT

public:
    SerialReader(QSerialPort *serialPort, QObject *parent = 0);
    virtual ~SerialReader();

private slots:
    void handleReadyRead();
    virtual void handleTimeout();
    virtual void handleError(QSerialPort::SerialPortError error);

};


#endif // SERIALREADER_H
