#!/bin/bash
set -e

pushd ../
ln -sf sha3/marshal-configs/sha3-bare-rocc.json .
ln -sf sha3/marshal-configs/sha3-bare-sw.json .
ln -sf sha3/marshal-configs/sha3-linux.json .
ln -sf sha3/marshal-configs/sha3-linux-test.json .
popd
