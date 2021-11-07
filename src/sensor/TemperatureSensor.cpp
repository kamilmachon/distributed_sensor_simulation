
#include <chrono>
#include <thread>

#include <sensor/TemperatureSensor.h>
#include <sensor/Utils.h>


void TemperatureSensor::SimulatedDataAquisition()
{
    int rate = utils::generate_random_int(100, 1000);
    while (true)
    {
        Publish(GenerateData());
        Sleep(rate);
    }
}

std::string TemperatureSensor::GenerateData()
{
    return sensor_type_ + "/" + std::to_string(sensor_id_) + ". " + msg_ + std::to_string(utils::generate_random_int(-20, 40));
}

void TemperatureSensor::Sleep(const int &rate)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(std::chrono::milliseconds(rate));
}
