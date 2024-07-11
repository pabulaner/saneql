#!/bin/sh

export BLOCK=./block
export VIRTGB=2
export PHYSGB=2

dd if=/dev/zero of=./block bs=4M count=16