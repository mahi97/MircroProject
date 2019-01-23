#include "serialwriter.h"

SerialWriter::SerialWriter(QSerialPort *serialPort, QObject *parent)
    : BaseSerial(serialPort, parent) {
    m_timer.setSingleShot(true);
    connect(m_serialPort, SIGNAL(bytesWritten(qint64)), this, SLOT(handleBytesWritten(qint64)));
}

SerialWriter::~SerialWriter() {
}

void SerialWriter::handleBytesWritten(qint64 bytes) {
    m_bytesWritten += bytes;
    if (m_bytesWritten == m_data.size()) {
        m_bytesWritten = 0;
        m_standardOutput << QObject::tr("Data successfully sent to port %1").arg(m_serialPort->portName()) << endl;
    }
}

void SerialWriter::handleTimeout() {
    m_standardOutput << QObject::tr("Operation timed out for port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
}

void SerialWriter::handleError(QSerialPort::SerialPortError serialPortError) {
    if (serialPortError == QSerialPort::WriteError) {
        m_standardOutput << QObject::tr("An I/O error occurred while writing the data to port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
    }
}

void SerialWriter::write(const QByteArray &writeData)
{
    m_data = writeData;

    qint64 bytesWritten = m_serialPort->write(writeData);

    if (bytesWritten == -1) {
        m_standardOutput << QObject::tr("Failed to write the data to port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
    } else if (bytesWritten != m_data.size()) {
        m_standardOutput << QObject::tr("Failed to write all the data to port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
    }

    m_timer.start(5000);

}
