
#include <chrono>
#include <thread>

#include <sensor/PressureSensor.h>
#include <sensor/Utils.h>

void PressureSensor::SimulatedDataAquisition()
{
    int rate = utils::generate_random_int(100, 1000);
    while (true)
    {
        Publish(GenerateData());
        Sleep(rate);
    }
}

std::string PressureSensor::GenerateData()
{
    return sensor_type_ + "/" + std::to_string(sensor_id_) + ". " + msg_ + std::to_string(utils::generate_random_int(950, 1100));
}

void PressureSensor::Sleep(const int &rate)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(std::chrono::milliseconds(rate));
}
