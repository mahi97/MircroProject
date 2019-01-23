#ifndef CONFIGTAB_H
#define CONFIGTAB_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QScrollBar>
#include <QDebug>
#include <QSpinBox>
#include <QTabWidget>
#include <QSerialPortInfo>
#include <QScrollArea>
#include <QComboBox>
#include <QSerialPort>
#include <QDebug>
#include "serialwriter.h"

class ConfigTab : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigTab(QWidget *parent = 0);
    ~ConfigTab();
    QSerialPort* serialPort;
private:
    void connectSerial();
    void closeSerial();
    bool serial_open;

    QComboBox* comboParity;
    QComboBox* comboStop;
    QComboBox* comboDataBits;
    QComboBox* comboBaud;
    QComboBox* comboPort;

//    SerialWriter* writer;

    QPushButton* check;

private slots:
    void checkPort(bool);
    void updatePort(int i);
    void updateBaud(int i);
    void updateStop(int i);
    void updatePari(int i);
    void updateData(int i);

signals:
    void con(int);
    void disconnected();
};

#endif // CONFIGTAB_H
