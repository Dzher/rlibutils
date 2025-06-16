#!/bin/bash

# build debug & release
cmake -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DCMAKE_INSTALL_PREFIX=I:/workspace/rlibutils/install -DCMAKE_BUILD_TYPE=Debug -DCMAKE_DEBUG_POSTFIX:STRING=d -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -SI:/workspace/rlibutils -BI:/workspace/rlibutils/build-dbg -G Ninja
cmake --build I:/workspace/rlibutils/build-dbg --parallel 18 --

cmake -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DCMAKE_INSTALL_PREFIX=I:/workspace/rlibutils/install -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -SI:/workspace/rlibutils -BI:/workspace/rlibutils/build-rel -G Ninja
cmake --build I:/workspace/rlibutils/build-rel --parallel 18 --

# install debug & release
cmake --install build-dbg --config Debug
cmake --install build-rel --config Release

# packing the install direction
# cpack -G ZIP --config build-dbg/CPackConfig.cmake
cd install
zip -r ../rlibutils.zip */

echo "Success Packing rlibutils!"
rm -rf _CPack_Packages/
