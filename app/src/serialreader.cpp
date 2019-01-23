#include "serialreader.h"

SerialReader::SerialReader(QSerialPort *serialPort, QObject *parent)
    : BaseSerial(serialPort, parent)
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialReader::handleReadyRead);
    m_timer.start(5000);

}

SerialReader::~SerialReader() {
}

void SerialReader::handleReadyRead() {
    m_data.append(m_serialPort->readAll());
    // You should decode data here.
    if (!m_timer.isActive())
        m_timer.start(5000);
}

void SerialReader::handleTimeout() {
    if (m_data.isEmpty()) {
        m_standardOutput << QObject::tr("No data was currently available for reading from port %1").arg(m_serialPort->portName()) << endl;
    } else {
        m_standardOutput << QObject::tr("Data successfully received from port %1").arg(m_serialPort->portName()) << endl;
        m_standardOutput << m_data << endl;
    }
}

void SerialReader::handleError(QSerialPort::SerialPortError serialPortError) {
    if (serialPortError == QSerialPort::ReadError) {
        m_standardOutput << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
    }
}
