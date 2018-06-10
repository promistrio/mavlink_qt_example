#include "mavcommunicator.h"

MavCommunicator::MavCommunicator(QObject *parent) : QObject(parent)
{
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        qDebug() << info.portName();
    QString portName("COM6");
    serial.setPortName(portName);
    serial.setBaudRate(QSerialPort::Baud115200);
    //serial.baudRate(QSerialPort::Baud57600);
    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << QString("Can't open %1, error code %2").arg(portName).arg(serial.error());
    }

    QObject::connect(&serial, &QSerialPort::readyRead, this, &MavCommunicator::readData);

    QTimer *timer = new QTimer(this);
    //QObject::connect(timer, &QTimer::timeout, this, &MavCommunicator::missionRequestListPack);
    QObject::connect(timer, &QTimer::timeout, this, &MavCommunicator::send_opt_raw);
    //QObject::connect(timer, &QTimer::timeout, this, &MavCommunicator::missionRequestHome);
    timer->start(5000);
}

QVariant MavCommunicator::getPitch()
{
    return this->m_pitch;
}

QVariant MavCommunicator::getRoll()
{
    return this->m_roll;
}

QVariant MavCommunicator::getYaw()
{
    return this->m_yaw;
}

QVariant MavCommunicator::getLat()
{
    return this->m_lat;
}

QVariant MavCommunicator::getLon()
{
    return this->m_lon;
}

void MavCommunicator::readData()
{
    mavlink_message_t message;
    mavlink_status_t status;

    QByteArray data = serial.readAll();
    for (int pos = 0; pos < data.length(); ++pos)
    {
        if (mavlink_parse_char(MAVLINK_COMM_0, (uint8_t)data[pos],
                                &message, &status))
        {
            //emit messageReceived(message);
            if (message.msgid == MAVLINK_MSG_ID_HEARTBEAT)
            {
                mavlink_heartbeat_t heartbeat;
                mavlink_msg_heartbeat_decode(&message, &heartbeat);

               /* qDebug() << "Heartbeat received, system type:" << heartbeat.type
                         << "System status:" << heartbeat.system_status;*/
            }
            if (message.msgid == MAVLINK_MSG_ID_ATTITUDE && message.sysid != 0)
            {
                printf("MAVLINK_MSG_ID_ATTITUDE\n");
                mavlink_attitude_t attitude;
                mavlink_msg_attitude_decode(&message, &attitude);


                //qDebug() << qRadiansToDegrees(attitude.pitch);
                QVariant pitch(qRadiansToDegrees(attitude.pitch));
                QVariant roll(qRadiansToDegrees(attitude.roll));
                QVariant yaw(qRadiansToDegrees(attitude.yaw));
                m_pitch = pitch;
                m_roll = roll;
                m_yaw = yaw;
                emit pitchChanged();
                emit rollChanged();
                emit yawChanged();
            }
            if (message.msgid == MAVLINK_MSG_ID_GPS_RAW_INT)
            {
                //qDebug() << "MAVLINK_MSG_ID_GPS_RAW_INT";
                mavlink_gps_raw_int_t gps_raw;
                mavlink_msg_gps_raw_int_decode(&message, &(gps_raw));
                //qDebug() <<"lat: " << gps_raw.lat / 1.0e7 << " lon: " << gps_raw.lon / 1.0e7 << " alt: " << gps_raw.alt;

                m_lat = gps_raw.lat / 1.0e7;
                m_lon = gps_raw.lon / 1.0e7;
                emit latChanged();
                emit lonChanged();
            }

            if (message.msgid == MAVLINK_MSG_ID_MISSION_COUNT)
            {
                //qDebug() << "MAVLINK_MSG_ID_MISSION_COUNT";
                mavlink_mission_count_t m_count;
                mavlink_msg_mission_count_decode(&message, &(m_count));
                qDebug() <<"Count of WP: " << m_count.count;


                startWPread = true;
                last_wp_id = 0;
                wp_count = m_count.count;
                missionRequestWP();
                break;
            }

            if (message.msgid == MAVLINK_MSG_ID_OPT_RAW)
            {
                qDebug() << "MAVLINK_MSG_ID_OPT_RAW";
                mavlink_opt_raw_t m_opt_raw;
                mavlink_msg_opt_raw_decode(&message, &(m_opt_raw));

                qDebug() <<"lat: " << m_opt_raw.lat << " lon: " << m_opt_raw.lon;
                break;
            }

            if (message.msgid == MAVLINK_MSG_ID_MISSION_ITEM)
            {
                //qDebug() << "MAVLINK_MSG_ID_MISSION_ITEM";
                mavlink_mission_item_t m_item;
                mavlink_msg_mission_item_decode(&message, &(m_item));
                if (m_item.seq == last_wp_id)
                {
                    qDebug() << "lat:" << m_item.x
                             << "lon:" << m_item.y
                             << "alt:" << m_item.z
                             << "seq:" << m_item.seq;
                    last_wp_id ++;
                    if (last_wp_id != wp_count) // wp_count = real_count+1
                    {
                        missionRequestWP();
                    }
                }
                break;
            }
        }
        continue;
    }
}

void MavCommunicator::missionRequestListPack()
{
    qDebug() << "request List Pack";

    mavlink_message_t message;
    mavlink_mission_request_list_t wprl;

    wprl.target_system = 1;
    wprl.target_component = MAV_COMP_ID_MISSIONPLANNER;
    mavlink_msg_mission_request_list_encode(255, 1, &message, &wprl);

    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint8_t len = mavlink_msg_to_send_buffer(buf, &message);

    serial.write( ( char * ) ( buf ), len);
}

void MavCommunicator::send_opt_raw()
{

    mavlink_message_t msg;
    mavlink_opt_raw_t packet;


    packet.lat = 15.0f;
    packet.lon = 10.0f;

    //mavlink_msg_opt_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_opt_raw_t* opt_raw)
    mavlink_msg_opt_raw_encode(255, 1, &msg, &packet);

    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint8_t len = mavlink_msg_to_send_buffer(buf, &msg);

    serial.write( ( char * ) ( buf ), len);
}



void MavCommunicator::missionRequestWP()
{

    mavlink_message_t msg;
    mavlink_mission_request_t wpr;

    wpr.target_system = 1;
    wpr.target_component = MAV_COMP_ID_MISSIONPLANNER;
    wpr.seq = last_wp_id;
    mavlink_msg_mission_request_encode(255, 1, &msg, &wpr);

    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint8_t len = mavlink_msg_to_send_buffer(buf, &msg);

    serial.write( ( char * ) ( buf ), len);
}

void MavCommunicator::missionRequestHome()
{
    mavlink_message_t msg1;
    mavlink_msg_command_long_pack(255,
                                  1,
                                  &msg1,
                                  1,
                                  MAV_COMP_ID_MISSIONPLANNER,
                                  MAV_CMD_DO_REPOSITION,
                                  1,
                                  0.0f,
                                  NAN,
                                  NAN,
                                  NAN,
                                  20,
                                  20, 20);


    uint8_t bf[MAVLINK_MAX_PACKET_LEN];
    uint8_t l = mavlink_msg_to_send_buffer(bf, &msg1);

    serial.write( ( char * ) ( bf ), l);

    mavlink_message_t msg;
    mavlink_set_gps_global_origin_t home;
    home.target_system = 1;
    home.latitude = 20*1E7;
    home.longitude = 20*1E7;
    home.altitude = 20*1000;
    qDebug() << "Set HOME. lat:" << home.latitude << " lon:" << home.longitude;
    mavlink_msg_set_gps_global_origin_encode(255, 1, &msg, &home);

    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint8_t len = mavlink_msg_to_send_buffer(buf, &msg);

    serial.write( ( char * ) ( buf ), len);
}


