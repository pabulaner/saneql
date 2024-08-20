#!/bin/sh

export BLOCK=./block
export VIRTGB=4
export PHYSGB=4

dd if=/dev/zero of=./block bs=4M count=256