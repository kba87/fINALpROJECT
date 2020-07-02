#ifndef SENSOR_H
#define SENSOR_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QMainWindow>
#include <QDialog>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class Sensor; }
QT_END_NAMESPACE

class Sensor : public QMainWindow
{
    Q_OBJECT

public:
    Sensor(QWidget *parent = nullptr);
    ~Sensor();


private slots:
    void updateMeasure(QString);
    void readSerial();
    void serialReceived();



private:
    Ui::Sensor *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id =9025;
    static const quint16 arduino_uno_product_id =67;
    QString arduino_port_name;
    bool arduino_is_available;
    void addToLogs(QString message);

};
#endif // SENSOR_H
