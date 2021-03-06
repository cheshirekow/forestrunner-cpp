#!/bin/bash

export PREFIX=$HOME/devroot/usr

export SCRIPT_DIR=`dirname $0`;
export CMAKE_PREFIX_PATH=$PREFIX:$CMAKE_PREFIX_PATH
export CMAKE_INSTALL_PREFIX=$PREFIX
export PKG_CONFIG_PATH=$PREFIX/lib/pkgconfig/:$PKG_CONFIG_PATH
cmake -G "Eclipse CDT4 - Unix Makefiles" \
    -DFORESTRUNNER_DESKTOP=TRUE \
    -DFORESTRUNNER_LINUX=TRUE \
	-DECLIPSE_CDT4_GENERATE_SOURCE_PROJECT=TRUE \
    -DCMAKE_INSTALL_PREFIX=$PREFIX \
    -DCMAKE_PREFIX_PATH="$CMAKE_PREFIX_PATH" \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_ECLIPSE_MAKE_ARGUMENTS="-j6" \
    $SCRIPT_DIR

