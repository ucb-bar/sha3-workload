#!/bin/bash
set -e

SPIKE_SRC=$PWD/spike-sha3
SPIKE_INSTALL=$PWD/spike-local
mkdir -p $SPIKE_INSTALL

# Build the custom spike
if [ ! -d $SPIKE_SRC/build ]; then
  mkdir -p $SPIKE_SRC/build
  pushd $SPIKE_SRC/build
  ../configure --with-fesvr=$RISCV --prefix=$SPIKE_INSTALL
  popd
fi

pushd $SPIKE_SRC/build
make -j
make install
popd

# Build bare-metal tests
pushd bare
make
popd
