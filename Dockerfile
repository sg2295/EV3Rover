FROM ev3dev/debian-stretch-cross

USER root

# Can add --no-install-recommends to save more space...
RUN sudo apt-get update -y ; \
    sudo apt-get install -y build-essential git

RUN echo 'export QEMU_LD_PREFIX=/usr/arm-linux-gnueabi' >> ~/.bashrc ; \
    echo 'export CXX=/usr/bin/arm-linux-gnueabi-g++' >> ~/.bashrc ; \
    echo 'export C=/usr/bin/arm-linux-gnueabi-gcc' >> ~/.bashrc

RUN git clone https://github.com/ddemidov/ev3dev-lang-cpp.git ; \
    cd ev3dev-lang-cpp ; mkdir build ; cd build ; \
    cmake .. -DEV3DEV_PLATFORM=EV3 ; make -j4 ; make install ; cd ../..
