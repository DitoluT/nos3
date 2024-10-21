#!/bin/bash -i
#
# Convenience script for NOS3 development
#

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source $SCRIPT_DIR/env.sh

echo "Cleaning up all COSMOS files..."
yes | rm $BASE_DIR/gsw/cosmos/Gemfile 2> /dev/null
yes | rm $BASE_DIR/gsw/cosmos/Gemfile.lock 2> /dev/null
yes | rm -r $BASE_DIR/gsw/cosmos/COMPONENTS 2> /dev/null
yes | rm -r $BASE_DIR/gsw/cosmos/outputs 2> /dev/null

echo "Cleaning up Minicom log..."
yes | rm $BASE_DIR/minicom.cap 2> /dev/null

echo "Cleaning up CryptoLib build..."
yes | rm $BASE_DIR/minicom.cap 2> /dev/null

$DCALL system prune -f

echo "Cleaning up local user directory..."
yes | rm -r $USER_NOS3_DIR 2> /dev/null

echo "Removing superfluous Docker networks and such..."
yes | docker network prune
yes | docker swarm leave --force

exit 0
