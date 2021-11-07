FROM ubuntu

SHELL ["/bin/bash", "-c"]

ARG DEBIAN_FRONTEND=noninteractive

# install dependencies
RUN apt-get update \
    && apt-get install -y libboost-all-dev \
    && apt-get install -y build-essential cmake  \
    && apt-get install -y git \
    && apt-get install -y mosquitto \
    && rm -rf /var/lib/apt/lists/*

# build mqtt_cpp library

RUN git clone https://github.com/redboltz/mqtt_cpp.git \
    && cd mqtt_cpp \
    && git fetch --all --tags --prune \
    && git checkout v12.0.0 \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make -j8 \
    && make install 

USER runner

ADD ./* $HOME/distributed_sensor_simulation/

WORKDIR $HOME/distributed_sensor_simulation/

RUN mkdir build \
    && cmake .. \
    && make -j8

ENTRYPOINT [ "entrypoint.sh" ]

