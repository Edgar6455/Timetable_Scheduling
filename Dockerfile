FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    curl \
    vim

WORKDIR /usr/src/app

COPY . .

RUN /usr/src/app/scripts/build.sh

CMD /usr/src/app/bin/TimetablingLib
