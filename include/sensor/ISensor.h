#ifndef DISTRIBUTED_SENSORS_I_SENSOR_H
#define DISTRIBUTED_SENSORS_I_SENSOR_H

#include <communication/Mqtt.h>

class ISensor
{

public:
    ISensor(const std::string sensor_type, const uint32_t sensor_id, const std::string hostname, const std::string port)
        : mqtt_client_(sensor_type + '_' + std::to_string(sensor_id), hostname, port),
          topic_name_(sensor_type + '/' + std::to_string(sensor_id))
    {
    }

    virtual ~ISensor() {}

protected:
    virtual void SimulatedDataAquisition() = 0;
    virtual void Publish(const std::string &msg)
    {
        mqtt_client_.Publish(topic_name_, msg);
    }

    std::string topic_name_;
    mqtt::MqttClient mqtt_client_;
};

#endif