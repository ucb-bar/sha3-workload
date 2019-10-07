#!/bin/bash
set -e

pushd ../
for config in bare-rocc bare-sw linux linux-test \
    linux-jtr linux-jtr-test linux-jtr-crack
do
    ln -sf "sha3/marshal-configs/sha3-${config}.json" .
done
popd
