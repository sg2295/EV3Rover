FROM ev3dev/debian-stretch-cross

# RUN apt-get install cmake make
USER root

# TODO: Can add --no-install-recommends to save more space...
RUN sudo apt-get update -y ; \
    sudo apt-get install -y build-essential git
# RUN sudo apt-get install -y build-essential git
# RUN sudo apt-get install -y git

RUN git clone https://github.com/ddemidov/ev3dev-lang-cpp.git ; \
    cd ev3dev-lang-cpp ; mkdir build ; cd build ; \
    cmake .. -DEV3DEV_PLATFORM=EV3 ; make -j4 ; make install ; cd ../..
