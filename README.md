This is an example set of workloads that uses the sha3 rocc accelerator.

# Getting Started

First install this repository into FireMarshal:

    cd /PATH/TO/FIREMARSHAL/FireMarshal/workloads
    git submodule add git@github.com:ucb-bar/sha3-workload.git sha3

When you first clone this repository, you should first update all submodules, and then install the workloads to FireMarshal:

    cd sha3
    git submodule update --init --recursive
    ./install.sh

The first time you build a workload using FireMarshal, the 'build.sh' script
will be run automatically. This script compiles all of our dependencies (e.g.
Linux and our custom software simulator, spike).

# Workloads
## Bare-Metal
bare/
sha3-bare.json

This workload runs bare-metal and directly accesses the rocc accelerator. To build the binary run:

    ./marshal build workloads/sha3-bare.json

## Linux
linux/
sha3-linux*.json

The linux-based workloads can boot in qemu so long as you don't actually access
the rocc accelerator. To use the custom hardware, you must boot in spike:

    ./marshal --initramfs build workloads/sha3-linux.json
    ./marshal --initramfs launch --spike workloads/sha3-linux.json

The '--initramfs' option tells marshal to build the root filesystem into the
binary as an initial ram filesystem (this is needed because spike does not
include a disk model). The '--spike' option tells marshal to boot the image in
spike (the custom spike we provided in this case).

### Interactive Linux
sha3-linux.json

This workload boots buildroot and uses the sha3 accelerator as a user-space
program. The basic workload boots into an interactive session. You can look at
'/root/linux' in the target for binaries to execute. 'sha3-sw' acts as a
baseline and computes the hash in software only. 'sha3-rocc' uses the rocc
accelerator to compute the hash.

### Automated Linux Test
sha3-linux-test.json

This workload inherits from sha3-linux.json and adds a 'command' field that
tells marshal to run a command automatically when the workload runs. It also
adds a 'testing' field that provides a reference output for Marshal to compare
against when running './marshal test workloads/sha3-linux-test.json'. Note that
in Marshal, the reference output needs to match some subset of the actual
output (notice that 'test-reference/linux/sha3-linux-test/uartlog' only has the
test output, while the actual program output is much longer.

To use this workload, try running:
    ./marshal --initramfs test --spike workloads/sha3-linux-test.json

# Key Components of this Workload

## riscv-linux
The default Linux kernel does not support rocc instructions. Instead, we must
use a fork. You can check the git log to see which changes we made.

The first two commits fix known incompatibilities between Linux and FireSim
(mostly relating to device tree differences). The final commit enables rocc
instructions by setting a CSR at thread creation time.

## riscv-isa-sim and spike-sha3
This is the standard riscv isa simulator (also known as 'spike'). We have
modified it to contain a golden model of our sha3 accelerator. In the case of
rocc accelerators, we can build the golden model out-of-tree (in the spike-sha3
directory) and simply have it installed along-side the standard spike. See
'build.sh' for how this is done.

We install our custom spike to 'spike-local'. Marshal is able to use this local
copy instead of the system-provided spike.

## marshal-configs
This directory contains our FireMarshal configurations for each workload.
'install.sh' creates symlinks to these in the FireMarshal workloads directory.

## test-reference
This directory contains reference outputs for each of our automated test
workloads.

## linux-benchmarks
Contains sources for our linux-based benchmarks. This directory is coppied into
the root directory of our Linux workloads. These are cross-compiled by the
'build.sh' script (run by FireMarshal when building the workload).

## bare-benchmarks
Contains sources for the bare-metal benchmarks and unit tests. These are
cross-compiled by the 'build.sh' script (run by FireMarshal when building the
workload). These benchmarks contain all of the code necessary to boot and run
on a bare-metal system (e.g. the c runtime and a basic implementation of common
system functions).
