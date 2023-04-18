FROM ubuntu:latest
RUN apt-get -y update && apt-get -y upgrade && apt-get -y install cmake qtbase5-dev \
qtdeclarative5-dev qtdeclarative5-dev-tools \
libqt5serialport5-dev build-essential
WORKDIR /app
COPY . /app
RUN cmake
ENTRYPOINT [./app/server]