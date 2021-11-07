#ifndef DISTRIBUTED_SENSORS_TEMPERATURE_SENSOR_H
#define DISTRIBUTED_SENSORS_TEMPERATURE_SENSOR_H


#include <sensor/ISensor.h>


class TemperatureSensor : public ISensor
{
    public:
        TemperatureSensor() = delete;
        TemperatureSensor(const std::string sensor_type, const uint64_t sensor_id, const std::string hostname, const std::string port)
            : ISensor(sensor_type, sensor_id, hostname, port),
              sensor_type_(sensor_type),
              sensor_id_(sensor_id)
        {
            SimulatedDataAquisition();
        }

    private:

        void SimulatedDataAquisition() override;

        std::string GenerateData();
        void Sleep(const int &rate);

        const uint64_t sensor_id_;
        const std::string sensor_type_;
        const std::string msg_ = "Measured temperature in Celsius: ";
};


#endif