#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "controltab.h"
#include "infotab.h"
#include "configtab.h"
#include "serialwriter.h"
#include "serialreader.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void write(char* data);
    void slt_connect(int);
    void slt_disconnect();
private:

    ControlTab* control;
    InfoTab* info;
    ConfigTab* config;

    QTabWidget* tabs;

//    SerialWriter* writer;
    SerialReader* reader;

};

#endif // MAINWINDOW_H
