#!/bin/bash

# 如果编译后缺少lapack，应该考虑执行sudo apt install liblapack-dev进行安装后重新编译 #
rm -rf OpenBLAS-0.3.17
tar -zxf OpenBLAS-0.3.17.tar.gz
cd OpenBLAS-0.3.17
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=../../../lean/OpenBLAS0.3.17 ..
make all -j16 && make install -j16

cd ../../
rm -rf OpenBLAS-0.3.17
rm -f OpenBLAS-0.3.17.tar.gz
