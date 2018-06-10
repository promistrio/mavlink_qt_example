#ifndef MAVCOMMUNICATOR_H
#define MAVCOMMUNICATOR_H

#include <QObject>
#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <mavlink_v1/ardupilotmega/mavlink.h>
#include <QtMath>
#include <QTimer>

//#define MAVLINK_MSG_ID_OPT_RAW 187

class MavCommunicator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant pitch READ getPitch NOTIFY pitchChanged)
    Q_PROPERTY(QVariant roll READ getRoll NOTIFY rollChanged)
    Q_PROPERTY(QVariant yaw READ getYaw NOTIFY yawChanged)
    Q_PROPERTY(QVariant lat READ getLat NOTIFY latChanged)
    Q_PROPERTY(QVariant lon READ getLon NOTIFY lonChanged)
public:
    explicit MavCommunicator(QObject *parent = nullptr);

    QVariant getPitch();
    QVariant getRoll();
    QVariant getYaw();
    QVariant getLat();
    QVariant getLon();

signals:
    void pitchChanged();
    void rollChanged();
    void yawChanged();
    void latChanged();
    void lonChanged();

public slots:
    void readData();
    void missionRequestListPack();
    void missionRequestWP();
    void missionRequestHome();
    void send_opt_raw();
    //void missionAck();
private:
    QSerialPort serial;
    bool startWPread = false;
    uint8_t last_wp_id = -1;
    uint8_t wp_count = 0;

    QVariant m_pitch;
    QVariant m_roll;
    QVariant m_yaw;
    QVariant m_lat;
    QVariant m_lon;
};

#endif // MAVCOMMUNICATOR_H
