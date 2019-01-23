#include "baseserial.h"

BaseSerial::BaseSerial(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_standardOutput(stdout)
{
    connect(m_serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &BaseSerial::handleError);
    connect(&m_timer, &QTimer::timeout, this, &BaseSerial::handleTimeout);

}

BaseSerial::~BaseSerial()
{

}

