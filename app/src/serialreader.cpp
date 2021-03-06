#include "serialreader.h"

SerialReader::SerialReader(QSerialPort *serialPort, QObject *parent)
    : BaseSerial(serialPort, parent)
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialReader::handleReadyRead);
//    m_timer.start(5000);

}

SerialReader::~SerialReader() {
}

void SerialReader::handleReadyRead() {
    emit ready(QString(m_serialPort->readAll()));
    qApp->processEvents();
    // You should decode data here.
//    if (!m_timer.isActive())
//        m_timer.start(5000);
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

void SerialReader::reset(QSerialPort *serialPort) {
    m_timer.stop();
    m_timer.setSingleShot(true);
    disconnect(m_serialPort, SIGNAL(bytesWritten(qint64)), this, SLOT(handleBytesWritten(qint64)));
    m_serialPort = serialPort;
    connect(m_serialPort, SIGNAL(bytesWritten(qint64)), this, SLOT(handleBytesWritten(qint64)));

}
