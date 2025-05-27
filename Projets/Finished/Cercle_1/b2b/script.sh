#!/bin/bash


echo "Introduction msg blablabla"

echo "	# Architecture: $(uname -a)"A
echo "	# MAC address: $(ip a | grep 'link/ether' | awk -F " " '{print$2}')"A