#!/usr/bin/env bash

clear
rm -r ../obj/
rm -r ../libs/
ndk-build clean
ndk-build