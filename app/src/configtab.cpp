#include "configtab.h"

ConfigTab::ConfigTab(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout;

    QHBoxLayout* portLay = new QHBoxLayout;
    QLabel* port = new QLabel("Port: ");
    comboPort = new QComboBox(this);
    const auto infos = QSerialPortInfo::availablePorts();
    for (const auto& info : infos) {
      comboPort->addItem(info.portName(), QVariant(info.systemLocation()));
    }
    portLay->addWidget(port);
    portLay->addWidget(comboPort);

    QHBoxLayout* baudLay = new QHBoxLayout;
    QLabel* baud = new QLabel("Baud Rate: ");
    comboBaud = new QComboBox(this);
    comboBaud->addItem(QString("1200")  , QVariant(1200));
    comboBaud->addItem(QString("2400")  , QVariant(2400));
    comboBaud->addItem(QString("4800")  , QVariant(4800));
    comboBaud->addItem(QString("9600")  , QVariant(9600));
    comboBaud->addItem(QString("19200") , QVariant(19200));
    comboBaud->addItem(QString("38400") , QVariant(38400));
    comboBaud->addItem(QString("57600") , QVariant(57600));
    comboBaud->addItem(QString("115200"), QVariant(115200));
    baudLay->addWidget(baud);
    baudLay->addWidget(comboBaud);

    QHBoxLayout* stopLay = new QHBoxLayout;
    QLabel* stop = new QLabel("Stop Bits: ");
    comboStop = new QComboBox(this);
    comboStop->addItem(QString("OneStop")         , QVariant(QSerialPort::OneStop));
    comboStop->addItem(QString("OneAndHalfStop")  , QVariant(QSerialPort::OneAndHalfStop));
    comboStop->addItem(QString("TwoStop")         , QVariant(QSerialPort::TwoStop));
    comboStop->addItem(QString("UnknownStopBits") , QVariant(QSerialPort::UnknownStopBits));
    stopLay->addWidget(stop);
    stopLay->addWidget(comboStop);

    QHBoxLayout* parityLay = new QHBoxLayout;
    QLabel* parity = new QLabel("Parity: ");
    comboParity = new QComboBox(this);
    comboParity->addItem(QString("NoParity")  , QVariant(QSerialPort::NoParity));
    comboParity->addItem(QString("EvenParity")  , QVariant(QSerialPort::EvenParity));
    comboParity->addItem(QString("OddParity")  , QVariant(QSerialPort::OddParity));
    comboParity->addItem(QString("SpaceParity")  , QVariant(QSerialPort::SpaceParity));
    comboParity->addItem(QString("MarkParity")  , QVariant(QSerialPort::MarkParity));
    comboParity->addItem(QString("UnknownParity")  , QVariant(QSerialPort::UnknownParity));
    parityLay->addWidget(parity);
    parityLay->addWidget(comboParity);

    QHBoxLayout* dataLay = new QHBoxLayout;
    QLabel* data = new QLabel("Baud Rate: ");
    comboDataBits = new QComboBox(this);
    comboDataBits->addItem(QString("Data5")  , QVariant(QSerialPort::Data5));
    comboDataBits->addItem(QString("Data6")  , QVariant(QSerialPort::Data6));
    comboDataBits->addItem(QString("Data7")  , QVariant(QSerialPort::Data7));
    comboDataBits->addItem(QString("Data8")  , QVariant(QSerialPort::Data8));
    comboDataBits->addItem(QString("UnknownDataBits")  , QVariant(QSerialPort::UnknownDataBits));
    dataLay->addWidget(data);
    dataLay->addWidget(comboDataBits);

    check = new QPushButton("Check");


    layout->addLayout(portLay);
    layout->addLayout(baudLay);
    layout->addLayout(stopLay);
    layout->addLayout(parityLay);
    layout->addLayout(dataLay);
    layout->addWidget(check);
    setLayout(layout);

    connect(check, SIGNAL(clicked(bool)), this, SLOT(checkPort(bool)));

    connect(comboPort, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePort(int)));
    connect(comboBaud, SIGNAL(currentIndexChanged(int)), this, SLOT(updateBaud(int)));
    connect(comboParity, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePari(int)));
    connect(comboStop, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStop(int)));
    connect(comboDataBits, SIGNAL(currentIndexChanged(int)), this, SLOT(updateData(int)));

    serial_open = false;
    serialPort = nullptr;
    connectSerial();
}

ConfigTab::~ConfigTab() {
    closeSerial();
}

void ConfigTab::connectSerial() {
    closeSerial();

    serialPort = new QSerialPort(this);
    serialPort->setBaudRate(comboBaud->currentData().toInt());
    serialPort->setPortName(comboPort->currentData().toString());
    serialPort->setParity(QSerialPort::Parity(comboParity->currentData().toInt()));
    serialPort->setStopBits(QSerialPort::StopBits(comboStop->currentData().toInt()));
    serialPort->setDataBits(QSerialPort::DataBits(comboDataBits->currentData().toInt()));

    if (serialPort->open(QIODevice::WriteOnly)) {
        serial_open = true;
        qInfo() << "Device is Connected";
    } else {
        serial_open = false;
        qWarning() << "Cannot Open Device";
    }
    emit con(3);
}

void ConfigTab::closeSerial() {
//    emit disconnect();
    if (serialPort == nullptr) {
        return;
    }
    serialPort->close();
    delete serialPort;
    serialPort = nullptr;
    serial_open = false;
    qInfo() << "Disconnected";
}

void ConfigTab::checkPort(bool) {
    connectSerial();
}


void ConfigTab::updatePort(int) {
    connectSerial();
    qInfo() << "Port Updated To: " << serialPort->portName();
}

void ConfigTab::updateBaud(int) {
    connectSerial();
    qInfo() << "Baud Updated To: " << serialPort->baudRate();
}

void ConfigTab::updateStop(int) {
    connectSerial();
    qInfo() << "Stop Bits Updated To: " << serialPort->stopBits();
}

void ConfigTab::updatePari(int) {
    connectSerial();
    qInfo() << "Parity Updated To: " << serialPort->parity();
}

void ConfigTab::updateData(int) {
    connectSerial();
    qInfo() << "DataBits Updated To: " << serialPort->dataBits();
}
