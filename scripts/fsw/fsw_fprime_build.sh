#!/bin/bash -i
#
# Convenience script for NOS3 development
# Use with the Dockerfile in the deployment repository
# https://github.com/nasa-itc/deployment
#

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[1]}" )/scripts" && pwd )
source $SCRIPT_DIR/env.sh


# Check that local NOS3 directory exists
if [ ! -d $USER_NOS3_DIR ]; then
    echo ""
    echo "    Need to run make prep first!"
    echo ""
    exit 1
fi

# Check that configure build directory exists
if [ ! -d $BASE_DIR/cfg/build ]; then
    echo ""
    echo "    Need to run make config first!"
    echo ""
    exit 1
fi

# Make flight software build directory
mkdir -p $BASE_DIR/fsw/build

$DFLAGS_CPUS -v $BASE_DIR:$BASE_DIR --name "nos_build_fsw" -w $BASE_DIR $DBOX make -j$NUM_CPUS -e FLIGHT_SOFTWARE=fprime build-fsw
