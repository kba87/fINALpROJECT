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

    arduino = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "";
    QSerialPort serial;

    qDebug() <<"Number of available points" << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() <<"Has vendor ID"<<serialPortInfo.hasVendorIdentifier();
        if (serialPortInfo.hasVendorIdentifier()){
            qDebug()<<"Vendor ID: "<<serialPortInfo.vendorIdentifier();
        }
        qDebug() <<"Has product ID"<<serialPortInfo.hasProductIdentifier();
        if (serialPortInfo.hasProductIdentifier()){
            qDebug()<<"Product ID: "<<serialPortInfo.productIdentifier();
        }
    }

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }}}}
    if(arduino_is_available){
        // konfig i otwarcie portu tutaj
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);

        if (serial.isOpen() && serial.isWritable())
              {
              qDebug() << "Serial is open";

              QByteArray output;
              QByteArray input;

                while(true)
                {
                output = "GET HUM";
                serial.write(output);
               serial.flush();

                serial.waitForBytesWritten(1000);
                serial.waitForReadyRead(1000);

                input = serial.readAll();
                qDebug()<<input;

                }
              }
         //  return a.exec();
       }


       //----------


         //----------
        //QSerialPort::setPortName("COM3")
        qDebug()<<"o panie";
   //-----------
        qDebug() << QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");

/*
    //----------
        QObject::connect(arduino, SIGNAL(readyRead()),this,SLOT(readSerial()));
    }else{
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }

  //  QSerialPort::write()
  //  QSerialPort::readLine()
*/
}
Sensor::~Sensor()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}


void Sensor::readSerial()
{
    qDebug()<<"Serial port works";
    QByteArray serialData= arduino->readAll();
    QString temp = QString::fromStdString(serialData.toStdString());
    qDebug()<<temp;

}

void Sensor::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->TextEdit->append(currentDateTime+ "\t" + message);
}

void Sensor::updateMeasure(QString command)
{
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    }else {
    qDebug()<<"Couldnt write to serial";
    }

}
//serial.write(envoi.toStdString.c_str() );
//Send defined commands to get current temperature and humidity ("GET TEMP" and "GET HUM") using
//QSerialPort::write() function and read response using for example QSerialPort::readLine() function
