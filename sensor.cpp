#include "sensor.h"
#include "ui_sensor.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <string>
#include <QtWidgets>
#include <QDateTime>
#include <QList>
#include <QTextEdit>

Sensor::Sensor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sensor)
{
     ui->setupUi(this);
     timer = new QTimer(this);
     arduino = new QSerialPort();

     for (auto serialPort: QSerialPortInfo::availablePorts())
     {
         ui->portsComboBox-> addItem(serialPort.portName());
     }

     ui->portsComboBox->model()->sort(0);

     connect(ui->connectionButton, &QPushButton::clicked,this, &Sensor::connectArduino);

//--------------------
}
void Sensor::connectArduino()
{

    if(!arduino->isOpen())
    {
        arduino->setPortName(ui->portsComboBox->currentText());
        if(!arduino->open(QSerialPort::ReadWrite))
        {
            QMessageBox::critical(this, "Error", "Could not open serial port!");
            return;
        }

        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);

        ui->connectionButton->setText("Disconnect");
        ui->connectionStatusLabel->setText("Connected");

        ui->dialgroupBox->setEnabled(true);

         connect(timer,SIGNAL(timeout()),this,SLOT(MyFunction()));
         timer->start(2000);
         
      //  QTimer::start()

        if(!arduino->isWritable())
        {
            QMessageBox::critical(this, "Error", "Could not write to serial port!");
              qDebug()<<"IsWritable";
            return;
        }



    }
    else
    {
        arduino->close();

        ui->connectionButton->setText("Connect");
        ui->connectionStatusLabel->setText("Disconnected");

        ui->dialgroupBox->setDisabled(true);
    }
}
void Sensor::MyTimer()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MySlot()));
    timer->start(2000);
    qDebug()<<"2000";
    connect(this->arduino, SIGNAL(readyRead()), this, SLOT(readFromPort()));

}

void Sensor::MyFunction()
{
     qDebug()<<"update";
     qDebug()<<"GET HUM";
     arduino->write("GET HUM\n");

     arduino->waitForBytesWritten(2000);
     arduino->readLine();
     //-------------
     QSerialPort serial;
     if (serial.isOpen() && serial.isWritable())
     {
     qDebug() << "Serial is open";

     QByteArray output;
     QByteArray input;

       while(true)
       {
       output = "GET TEMP";
       serial.write(output);
      serial.flush();

       serial.waitForBytesWritten(2000);
       serial.waitForReadyRead(2000);

       input = serial.readAll();
       qDebug()<<input;

       }
     }
//  return a.exec();
}




void Sensor::MySlot()
{
    qDebug()<<"Timer executed";
    qDebug()<<"GET HUM";

}


Sensor::~Sensor()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}

//serial.write(envoi.toStdString.c_str() );
//Send defined commands to get current temperature and humidity ("GET TEMP" and "GET HUM") using
//QSerialPort::write() function and read response using for example QSerialPort::readLine() function
