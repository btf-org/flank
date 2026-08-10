#!/bin/bash

docker run --name flank-ubuntu-day-0 --platform linux/amd64 -p 8085:8084 -it ubuntu:24.04 bash
