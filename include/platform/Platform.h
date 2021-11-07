#ifndef DISTRIBUTED_SENSORS_PLATFORM_H
#define DISTRIBUTED_SENSORS_PLATFORM_H

#include <communication/Mqtt.h>
#include <process_manager/SensorSpawner.h>

#include <mutex>
#include <boost/asio.hpp>
#include <boost/circular_buffer.hpp>

class Platform
{
public:
    Platform(std::string hostname, std::string port);

    void RegisterSensor(const std::string sensor_type, const uint64_t sensor_id, const std::string hostname, const std::string port);
    void UnregisterSensor(const std::string sensor_type, const uint64_t sensor_id);
    void RegisterUserCallback(std::function<void(boost::circular_buffer<std::string> &)>, const float rate); 

private:
    void MqttCallback(const std::string &msg);
    void StartUserCallbackHandling(float rate);
    void HandleUserCallback();

    mqtt::MqttClient mqtt_client_;
    SensorSpawner sensor_spawner_;

    std::function<void(boost::circular_buffer<std::string>&)> user_callback_;
    uint user_callback_rate_ = 0;

    std::mutex buffer_mutex_;
    boost::circular_buffer<std::string> cbuffer_;
    
    boost::asio::io_service io_service_;
    std::unique_ptr<boost::asio::steady_timer> user_callback_timer_;

    const std::string hostname_;
    const std::string port_;
};

#endif