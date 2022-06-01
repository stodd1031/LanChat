clear
mkdir build
cd build
qmake ..
make -j$(cat /proc/cpuinfo | grep -c ^processor)
cd ..