#!/bin/bash

# clean current library assets
rm -rf /opt/tinyfp

# copy shared object
mkdir -p /opt/tinyfp/lib
cp libtinyfp.so /opt/tinyfp/lib

# copy headers
mkdir -p /opt/tinyfp/include
find . -name "*.h*" -print0 | xargs -0 -I {} sh -c 'mkdir -p /opt/tinyfp/include/$(dirname "{}"); cp {} /opt/tinyfp/include/$(dirname "{}")'

# copy package config
cp tinyfp.pc /usr/lib/pkgconfig/
