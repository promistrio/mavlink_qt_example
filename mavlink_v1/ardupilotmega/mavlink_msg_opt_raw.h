#pragma once
// MESSAGE OPT_RAW PACKING

#define MAVLINK_MSG_ID_OPT_RAW 187

MAVPACKED(
typedef struct __mavlink_opt_raw_t {
 float lat; /*< */
 float lon; /*< */
}) mavlink_opt_raw_t;

#define MAVLINK_MSG_ID_OPT_RAW_LEN 8
#define MAVLINK_MSG_ID_OPT_RAW_MIN_LEN 8
#define MAVLINK_MSG_ID_187_LEN 8
#define MAVLINK_MSG_ID_187_MIN_LEN 8

#define MAVLINK_MSG_ID_OPT_RAW_CRC 13
#define MAVLINK_MSG_ID_187_CRC 13



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_OPT_RAW { \
    187, \
    "OPT_RAW", \
    2, \
    {  { "lat", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_opt_raw_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_opt_raw_t, lon) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_OPT_RAW { \
    "OPT_RAW", \
    2, \
    {  { "lat", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_opt_raw_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_opt_raw_t, lon) }, \
         } \
}
#endif

/**
 * @brief Pack a opt_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param lat 
 * @param lon 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_opt_raw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float lat, float lon)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPT_RAW_LEN];
    _mav_put_float(buf, 0, lat);
    _mav_put_float(buf, 4, lon);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OPT_RAW_LEN);
#else
    mavlink_opt_raw_t packet;
    packet.lat = lat;
    packet.lon = lon;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OPT_RAW_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OPT_RAW;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_OPT_RAW_MIN_LEN, MAVLINK_MSG_ID_OPT_RAW_LEN, MAVLINK_MSG_ID_OPT_RAW_CRC);
}

/**
 * @brief Pack a opt_raw message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lat 
 * @param lon 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_opt_raw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float lat,float lon)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPT_RAW_LEN];
    _mav_put_float(buf, 0, lat);
    _mav_put_float(buf, 4, lon);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OPT_RAW_LEN);
#else
    mavlink_opt_raw_t packet;
    packet.lat = lat;
    packet.lon = lon;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OPT_RAW_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OPT_RAW;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_OPT_RAW_MIN_LEN, MAVLINK_MSG_ID_OPT_RAW_LEN, MAVLINK_MSG_ID_OPT_RAW_CRC);
}

/**
 * @brief Encode a opt_raw struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param opt_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_opt_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_opt_raw_t* opt_raw)
{
    return mavlink_msg_opt_raw_pack(system_id, component_id, msg, opt_raw->lat, opt_raw->lon);
}

/**
 * @brief Encode a opt_raw struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param opt_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_opt_raw_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_opt_raw_t* opt_raw)
{
    return mavlink_msg_opt_raw_pack_chan(system_id, component_id, chan, msg, opt_raw->lat, opt_raw->lon);
}

/**
 * @brief Send a opt_raw message
 * @param chan MAVLink channel to send the message
 *
 * @param lat 
 * @param lon 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_opt_raw_send(mavlink_channel_t chan, float lat, float lon)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPT_RAW_LEN];
    _mav_put_float(buf, 0, lat);
    _mav_put_float(buf, 4, lon);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPT_RAW, buf, MAVLINK_MSG_ID_OPT_RAW_MIN_LEN, MAVLINK_MSG_ID_OPT_RAW_LEN, MAVLINK_MSG_ID_OPT_RAW_CRC);
#else
    mavlink_opt_raw_t packet;
    packet.lat = lat;
    packet.lon = lon;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPT_RAW, (const char *)&packet, MAVLINK_MSG_ID_OPT_RAW_MIN_LEN, MAVLINK_MSG_ID_OPT_RAW_LEN, MAVLINK_MSG_ID_OPT_RAW_CRC);
#endif
}

/**
 * @brief Send a opt_raw message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_opt_raw_send_struct(mavlink_channel_t chan, const mavlink_opt_raw_t* opt_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_opt_raw_send(chan, opt_raw->lat, opt_raw->lon);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPT_RAW, (const char *)opt_raw, MAVLINK_MSG_ID_OPT_RAW_MIN_LEN, MAVLINK_MSG_ID_OPT_RAW_LEN, MAVLINK_MSG_ID_OPT_RAW_CRC);
#endif
}

#if MAVLINK_MSG_ID_OPT_RAW_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_opt_raw_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float lat, float lon)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, lat);
    _mav_put_float(buf, 4, lon);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPT_RAW, buf, MAVLINK_MSG_ID_OPT_RAW_MIN_LEN, MAVLINK_MSG_ID_OPT_RAW_LEN, MAVLINK_MSG_ID_OPT_RAW_CRC);
#else
    mavlink_opt_raw_t *packet = (mavlink_opt_raw_t *)msgbuf;
    packet->lat = lat;
    packet->lon = lon;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPT_RAW, (const char *)packet, MAVLINK_MSG_ID_OPT_RAW_MIN_LEN, MAVLINK_MSG_ID_OPT_RAW_LEN, MAVLINK_MSG_ID_OPT_RAW_CRC);
#endif
}
#endif

#endif

// MESSAGE OPT_RAW UNPACKING


/**
 * @brief Get field lat from opt_raw message
 *
 * @return 
 */
static inline float mavlink_msg_opt_raw_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field lon from opt_raw message
 *
 * @return 
 */
static inline float mavlink_msg_opt_raw_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Decode a opt_raw message into a struct
 *
 * @param msg The message to decode
 * @param opt_raw C-struct to decode the message contents into
 */
static inline void mavlink_msg_opt_raw_decode(const mavlink_message_t* msg, mavlink_opt_raw_t* opt_raw)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    opt_raw->lat = mavlink_msg_opt_raw_get_lat(msg);
    opt_raw->lon = mavlink_msg_opt_raw_get_lon(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_OPT_RAW_LEN? msg->len : MAVLINK_MSG_ID_OPT_RAW_LEN;
        memset(opt_raw, 0, MAVLINK_MSG_ID_OPT_RAW_LEN);
    memcpy(opt_raw, _MAV_PAYLOAD(msg), len);
#endif
}
