#include "controltab.h"


ControlTab::ControlTab(QWidget *parent) : QWidget(parent) {

    QVBoxLayout* all = new QVBoxLayout;
    QHBoxLayout* main = new QHBoxLayout;

    QVBoxLayout* valvesLayouts[VALVE_COUNT];

    for (int i = 0; i < VALVE_COUNT; i++) {
        valveLabels[i] = new QLabel("None");
        valves[i] = new QPushButton("Off");
        valves[i]->setObjectName(QString("%1").arg(i));
        valvesLayouts[i] = new QVBoxLayout;
        valvesLayouts[i]->addWidget(valveLabels[i], 0, Qt::AlignCenter);
        valvesLayouts[i]->addWidget(valves[i], 0, Qt::AlignCenter);
        valvesValues[i] = false;
        main->addWidget(getVLine());
        main->addLayout(valvesLayouts[i]);
        main->addWidget(getVLine());
    }
    valveLabels[0]->setText("Battery"  );
    valveLabels[1]->setText("LCD" );
    valveLabels[2]->setText("Debug");

    QVBoxLayout* scroll = new QVBoxLayout;
    QLabel* t[TIME_COUNT];
    QHBoxLayout* hb[TIME_COUNT];
    for (int i = 0; i < TIME_COUNT; i++) {
        t[i] = new QLabel(QString("Freq (khz.)"));
        scrollBars[i] = new QScrollBar(Qt::Horizontal);
        scrollBars[i]->setObjectName(QString("%1").arg(i));
        scrollBars[i]->setMaximum(1000);

        hb[i] = new QHBoxLayout;
        timeSpins[i] = new QSpinBox();
        timeSpins[i]->setObjectName(QString("%1").arg(i));
        timeSpins[i]->setMinimum(0);
        timeSpins[i]->setMaximum(1000);
        timeSpins[i]->setValue(scrollBars[i]->value());
        scroll->addLayout(hb[i]);
        hb[i]->addWidget(t[i]);
        hb[i]->addWidget(scrollBars[i]);
        hb[i]->addWidget(timeSpins[i]);
    }

    auto sendlay = new QVBoxLayout;
    sendBuffer = new QLineEdit();
    morse = new QLabel("MORSE:\n");
    sendlay->addWidget(sendBuffer);
    sendlay->addWidget(morse);


    QHBoxLayout* btns = new QHBoxLayout;
    def = new QPushButton("Reset");
    send = new QPushButton("Send!");
    btns->addWidget(def);
    btns->addWidget(send);

    QLabel* header = new QLabel("Micro Processor V0.2", this);
    all->addWidget(header, 0, Qt::AlignCenter);
    all->addWidget(getHLine());
    all->addLayout(main);
    all->addWidget(getHLine());
    all->addLayout(scroll);
    all->addWidget(getHLine());
    all->addLayout(sendlay);
    all->addWidget(getHLine());
    all->addLayout(btns);
    setLayout(all);

    for (auto& v : valves) {
        connect(v, SIGNAL(clicked(bool)), this, SLOT(toggleBtn(bool)));
    }

    for (auto& s : scrollBars) {
        connect(s, SIGNAL(valueChanged(int)), this, SLOT(changeValueSpin(int)));
    }

    for (auto& s : timeSpins) {
        connect(s, SIGNAL(valueChanged(int)), this, SLOT(changeValueScroll(int)));
    }

    connect(def, SIGNAL(clicked(bool)), this, SLOT(defaultValue(bool)));
    connect(send, SIGNAL(clicked(bool)), this, SLOT(sendData(bool)));
    connect(sendBuffer, SIGNAL(textChanged(QString)), this, SLOT(morseIt(QString)));
}

void ControlTab::toggleBtn(bool) {
    QPushButton* btn = qobject_cast<QPushButton*> (QObject::sender());
    if (btn->text() == "On") btn->setText("Off");
    else btn->setText("On");
    int index = btn->objectName().toInt();
    valvesValues[index] = !valvesValues[index];

}

void ControlTab::changeValueSpin(int value) {
    QScrollBar* scroll = qobject_cast<QScrollBar*> (QObject::sender());
    int index = scroll->objectName().toInt();
    timeSpins[index]->setValue(value);
    timeValues[index] = value;

}

void ControlTab::changeValueScroll(int value) {
    QSpinBox* spin = qobject_cast<QSpinBox*> (QObject::sender());
    int index = spin->objectName().toInt();
    scrollBars[index]->setValue(value);
    timeValues[index] = value;
}

void ControlTab::encode(bool *_valves, int *_times) {
    output[0] = 0x99;
    for (int i = 0; i < TIME_COUNT; i++) output[i + 1] = static_cast<unsigned char>(_times[i] >> 2);
    for (int i = 0; i < VALVE_COUNT; i++) output[i + TIME_COUNT + 1] = static_cast<unsigned char>(_valves[i]);
}

void ControlTab::defaultValue(bool) {

    for (int i = 0; i < VALVE_COUNT; i++) {
        valvesValues[i] = false;
        valves[i]->setText("Off");
    }

    for (int i = 0; i < TIME_COUNT; i++) {
        timeSpins[i]->setValue(0);
        scrollBars[i]->setValue(0);
    }

    sendBuffer->clear();
    morse->setText("MORSE:\n");

}

void ControlTab::sendData(bool) {
    QString btn;
    btn.append(QString("%1X%2").arg(static_cast<unsigned char>(timeSpins[0]->value() >> 2)).arg(VALVE_COUNT));
    for (int i = 0; i < VALVE_COUNT; i++) {
        if (valves[i]->text() == QString("On")) btn.append("T");
        else btn.append("F");
    }
    emit write((char*)(btn + sendBuffer->text()).toStdString().c_str());
}

QString ControlTab::morseCode(QChar b) {
    switch (b.toLatin1()) {
    case 'A': return ".-  ";
    case 'B': return "-...  ";
    case 'C': return "-.-.  ";
    case 'D': return "-..  ";
    case 'E': return ".  ";
    case 'F': return "..-.  ";
    case 'G': return "--.  ";
    case 'H': return "....  ";
    case 'I': return "..  ";
    case 'J': return ".---  ";
    case 'K': return "-.-  ";
    case 'L': return ".-..  ";
    case 'M': return "--  ";
    case 'N': return "-.  ";
    case 'O': return "---  ";
    case 'P': return ".--.  ";
    case 'Q': return "--.-  ";
    case 'R': return ".-.  ";
    case 'S': return "...  ";
    case 'T': return "-  ";
    case 'U': return "..-  ";
    case 'V': return "...-  ";
    case 'W': return ".--  ";
    case 'X': return "-..-  ";
    case 'Y': return "-.--  ";
    case 'Z': return "--..  ";
    case '0': return "-----  ";
    case '1': return ".----  ";
    case '2': return "..---  ";
    case '3': return "...--  ";
    case '4': return "....-  ";
    case '5': return ".....  ";
    case '6': return "-....  ";
    case '7': return "--...  ";
    case '8': return "---..  ";
    case '9': return "----.  ";
    case ' ': return "     ";
    default:
        break;
    }
    return "Something goes wrong :( ";
}

void ControlTab::morseIt(QString b) {
    QString m = "MORSE\n";
    for (int i = 0; i < b.size(); i++) {
        m.append(morseCode(b[i].toUpper()));
    }
    morse->setText(m);
    morse->setFont(QFont("mono"));
}
