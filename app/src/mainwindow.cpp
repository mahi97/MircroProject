#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    tabs = new QTabWidget(this);
    setCentralWidget(tabs);

    control = new ControlTab(tabs);
    info  = new InfoTab(tabs);
    config = new ConfigTab(tabs);

    tabs->addTab(control, "Control");
    tabs->addTab(config, "Config");
    tabs->addTab(info, "Info");

    setFocus();

    connect(control, SIGNAL(write(char*)), this, SLOT(write(char*)));
    connect(config, SIGNAL(con(int)), this, SLOT(slt_connect(int)));
    connect(config, SIGNAL(disconnected()), this, SLOT(slt_disconnect()));
}


MainWindow::~MainWindow() {
}

void MainWindow::write(char *data) {
    if (config->serialPort->isOpen()) {
//        writer->write(QByteArray(data, 8));
    }
}

void MainWindow::slt_connect(int) {
    qDebug() << "Updated!!";
//    writer = new SerialWriter(config->serialPort, this);
    reader = new SerialReader(config->serialPort, this);
}

void MainWindow::slt_disconnect() {
//    delete writer;
//    delete reader;
//    writer = nullptr;
//    reader = nullptr;
}
