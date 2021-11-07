#include <platform/Platform.h>

#include <chrono>
#include <thread>

void user_callback(boost::circular_buffer<std::string> &buffer)
{
    std::cout << "user callback start" << '\n';
    while (!buffer.empty())
    {
        auto data = buffer.back();
        buffer.pop_back();
        std::cout << data << '\n';
    }
    std::cout << "user callback end" << '\n';
}

int main(int argv, char *argc[])
{
    Platform platform{"127.0.0.1", "6500"};

    platform.RegisterUserCallback(&user_callback, 1.0);
    platform.RegisterSensor("temperature_sensor", 1, "127.0.0.1", "6500");
    platform.RegisterSensor("temperature_sensor", 2, "127.0.0.1", "6500");
    platform.RegisterSensor("temperature_sensor", 3, "127.0.0.1", "6500");
    platform.RegisterSensor("temperature_sensor", 4, "127.0.0.1", "6500");
    platform.RegisterSensor("pressure_sensor", 5, "127.0.0.1", "6500");
    platform.RegisterSensor("pressure_sensor", 6, "127.0.0.1", "6500");
    platform.RegisterSensor("pressure_sensor", 7, "127.0.0.1", "6500");
    platform.RegisterSensor("pressure_sensor", 8, "127.0.0.1", "6500");
    platform.RegisterSensor("pressure_sensor", 9, "127.0.0.1", "6500");
    platform.RegisterSensor("pressure_sensor", 10, "127.0.0.1", "6500");

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}