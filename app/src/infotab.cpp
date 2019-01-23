#include "infotab.h"

InfoTab::InfoTab(QWidget *parent) : QWidget(parent){
    QVBoxLayout *main = new QVBoxLayout;
    QVBoxLayout *layout = new QVBoxLayout;
    label = new QLabel;
    updateInfo();
    layout->addWidget(label);
    QPushButton* update = new QPushButton("Update!");

    QWidget *workPage = new QWidget;
    workPage->setLayout(layout);
    QScrollArea* area = new QScrollArea(this);
    area->setWindowTitle(QObject::tr("Info about all available serial ports."));
    area->setWidget(workPage);
    main->addWidget(area);
    main->addWidget(update);
    setLayout(main);

    connect(update, SIGNAL(clicked(bool)), this, SLOT(updateInfo(bool)));
}

void InfoTab::updateInfo(bool) {
    const auto infos = QSerialPortInfo::availablePorts();
    QString s;
    for (const auto& info : infos) {
       s += QObject::tr("Port: ") + info.portName() + "\n"
          + QObject::tr("Location: ") + info.systemLocation() + "\n"
          + QObject::tr("Description: ") + info.description() + "\n"
          + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
          + QObject::tr("Serial number: ") + info.serialNumber() + "\n"
          + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
          + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
          + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n"
          + "--------------------------------------------------------\n";
    }
    label->setText(s);
    qInfo() << "Information Updated!";
}
