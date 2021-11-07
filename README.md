# Distributed sensors simulation.

## Components
There are 4 main components of this project.

### Communication

I decided to use MQTT for interprocess communication. It's light, simple and sutable for IoT applications.
I used [this](https://github.com/redboltz/mqtt_cpp), boost asio based implementation.

### Process Manager

I implemented 2 simple classes, first uses boost.process for spawning and terminating processes.
It's used by SensorSpawner, which provides project specific functionalities.

### Sensor

New sensor can be simulated by creating a class inherited from ISensor. 
Thanks to that communication methods is reused in every sensor.

### Platform

Platform consists of the system logic and functionalities. It provides methods to register and unregister a sensor as well as a method for registering user callback function, which provides buffered sensor data.

## Dependencies

Unfortunately I didn't manage to finish Dockerfile (problems with building mqtt_cpp library), so the application has to be built on users host.
It depends on Boost >=1.71 [mqtt_cpp library](https://github.com/redboltz/mqtt_cpp), and mqtt server application e.q. mosquitto.

## Build guide

The build process unfortunately takes some time, so once again I'm sorry for not finishing the docker image. 

### install mosquitto

`apt-get install -y mosquitto`

### build and install mqtt_cpp

``` 
git clone https://github.com/redboltz/mqtt_cpp.git \
    && cd mqtt_cpp \
    && git fetch --all --tags --prune \
    && git checkout v12.0.0 \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make -j8 \
    && sudo make install
``` 

### build aplication

```
mkdir build \ 
    && cd build \
    && cmake .. \
    && make -j8 
```

## Launch

Launch mosquitto server

`mosquitto -p 6500 -d`

Enter build directory and 

`./main`


### Potencial TODOs

Due to lack of time I hardocoded hostname and port number in few places, so it's not configurable right now.

Simulated sensors produce only strings, so it's easy to send them. More professional approach would be sending serialized structures (protobuff ) would probably do the trick. 

