FROM ubuntu:latest

RUN apt-get -y update 
RUN apt-get install -y git g++ make cmake 
RUN mkdir -p /tmp
WORKDIR /tmp/
RUN git clone https://github.com/google/googletest.git
WORKDIR /tmp/googletest
RUN mkdir gbuild && cd gbuild && cmake .. && make
RUN cp -r ./googletest/include/gtest /usr/local/include
RUN cp gbuild/googlemock/gtest/lib*.a /usr/local/lib
RUN cp gbuild/googlemock/lib*.a /usr/local/lib
VOLUME /code
WORKDIR /code
