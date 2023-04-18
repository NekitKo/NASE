FROM ubuntu:latest
RUN apt-get -y update && apt-get -y upgrade && apt-get -y install qt5-default \
qtbase5-dev qtdeclarative5-dev qtdeclarative5-dev-tools \
libqt5serialport5-dev build-essential
COPY . /app
WORKDIR /app
RUN qmake && make
CMD ["./server"]