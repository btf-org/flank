#!/bin/bash

docker run --name flank-ubuntu-day-0 --platform linux/amd64 --privileged -p 8086:8083 -d flank-ubuntu-test
docker exec -it flank-ubuntu-day-0 bash
