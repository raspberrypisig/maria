#!/usr/bin/env bash

source ~/emsdk/emsdk_env.sh
make PLATFORM=PLATFORM_WEB -B -e
sudo python -m http.server 80 &
