#ifndef DISTRIBUTED_SENSORS_SENSOR_SPAWNER_H
#define DISTRIBUTED_SENSORS_SENSOR_SPAWNER_H

#include <process_manager/ProcessManager.h>

#include <string>

class SensorSpawner
{
public:
    SensorSpawner() = default;

    void RegisterSensor(std::string type, uint64_t id);
    void UnregisterSensor(std::string type, uint64_t id);

private:

    ProcessManager proces_manager_;
};

#endif