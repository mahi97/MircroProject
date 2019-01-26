#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "controltab.h"
#include "infotab.h"
#include "configtab.h"
#include "serialwriter.h"
#include "serialreader.h"
#include "replwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void write(char* data);
    void parse(QString data);
signals:
    void ready(QString);
private:

    ControlTab* control;
    InfoTab* info;
    ConfigTab* config;
    ReplWidget* repl;


    QTabWidget* tabs;

    SerialWriter* writer;
    SerialReader* reader;

};

#endif // MAINWINDOW_H
