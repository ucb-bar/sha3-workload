#!/bin/bash

./install.sh
if [ $? != 0]; then
  echo "Failed to install sha3 suite"
fi

pushd ../../

./marshal test -s workloads/sha3-bare.json
if [ $? != 0 ]; then
  echo "Bare-metal test failed"
fi

./marshal -i test -s workloads/sha3-linux-test.json
if [ $? != 0 ]; then
  echo "Linux unit test failed"
fi

popd
