#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    auto ww = new QWidget(this);
    QVBoxLayout* v = new QVBoxLayout(ww);
    ww->setLayout(v);
    setCentralWidget(ww);

    tabs = new QTabWidget(ww);
    v->addWidget(tabs);
    control = new ControlTab(tabs);
    info  = new InfoTab(tabs);
    config = new ConfigTab(tabs);

    tabs->addTab(control, "Control");
    tabs->addTab(config, "Config");
    tabs->addTab(info, "Info");

    repl = new ReplWidget(ww);
    v->addWidget(repl);

    setFocus();

    writer = new SerialWriter(config->serialPort, this);
    reader = new SerialReader(config->serialPort, this);

    connect(control, SIGNAL(write(char*)), this, SLOT(write(char*)));

}


MainWindow::~MainWindow() {
}

void MainWindow::write(char *data) {
    qDebug() << config->serialPort->portName();
    qDebug() << data;
    if (config->serialPort->isOpen()) {
        writer->write(QByteArray(data, 8));
    }
}
