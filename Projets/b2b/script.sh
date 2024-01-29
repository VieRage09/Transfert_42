#!/bin/bash
echo "Introduction msg blablabla"

echo "	# Architecture: $(uname -a)"

echo "	# MAC address: $(ip a | grep 'link/ether' | awk -F " " '{print$2}')"