#!/bin/bash

mkdir -p Build
cmake -BBuild -H.
cd Build
make
