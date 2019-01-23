#ifndef BASESERIAL_H
#define BASESERIAL_H

#include <QtSerialPort/QSerialPort>
#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QObject>

class BaseSerial : public QObject
{
    Q_OBJECT
public:
    BaseSerial(QSerialPort* serialPort, QObject *parent = 0);
    virtual ~BaseSerial();
protected slots:
    virtual void handleTimeout() = 0;
    virtual void handleError(QSerialPort::SerialPortError error) = 0;
protected:
    QSerialPort     *m_serialPort;
    QByteArray      m_data;
    QTextStream     m_standardOutput;
    QTimer          m_timer;
};

#endif // BASESERIAL_H
