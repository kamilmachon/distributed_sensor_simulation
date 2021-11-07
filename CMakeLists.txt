cmake_minimum_required (VERSION 2.8.12)
project (distributed-sensors)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package (Boost 1.71 COMPONENTS system thread)

include_directories(include)

add_library (Platform 
    src/platform/Platform.cpp
    src/process_manager/ProcessManager.cpp
    src/process_manager/SensorSpawner.cpp)
    
target_include_directories (Platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (Platform LINK_PUBLIC ${Boost_LIBRARIES})


add_executable (temperature_sensor 
src/sensor/TemperatureSensor.cpp
src/sensor/temperature_sensor_main.cpp)
target_link_libraries (temperature_sensor LINK_PUBLIC   ${Boost_LIBRARIES})

add_executable (pressure_sensor 
src/sensor/PressureSensor.cpp
src/sensor/pressure_sensor_main.cpp)
target_link_libraries (pressure_sensor LINK_PUBLIC   ${Boost_LIBRARIES})

add_executable (main src/main.cpp)
target_link_libraries (main LINK_PUBLIC ${Boost_LIBRARIES} Platform)

