#include <process_manager/SensorSpawner.h>

void SensorSpawner::RegisterSensor(std::string type, uint64_t id)
{
    if (type == "temperature_sensor")
    {
        proces_manager_.SpawnProcess("./temperature_sensor " + std::to_string(id) + " 127.0.0.1 6500", id);
    }
    else if (type == "pressure_sensor")
    {
        proces_manager_.SpawnProcess("./pressure_sensor " + std::to_string(id) + " 127.0.0.1 6500", id);
    }
    else
    {
        throw std::runtime_error("Unable ot register a sensor of type " + type);
    }
}

void SensorSpawner::UnregisterSensor(std::string type, uint64_t id)
{
    proces_manager_.TerminateProcess(id);
}
