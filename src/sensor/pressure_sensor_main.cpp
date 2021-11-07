#include <sensor/PressureSensor.h>

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        std::cout << "Uncorrect amount of arguments provided to launch a pressure sensor instance.";
        exit(-1);
    }
    PressureSensor pressure_sensor{"pressure_sensor",
                                      std::stoull(argv[1]),
                                      std::string(argv[2]),
                                      std::string(argv[3])};
    return 0;
}