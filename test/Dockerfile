FROM ubuntu:24.04

COPY entrypoint.sh entrypoint.sh

RUN yes | unminimize && apt-get update && apt-get install -y cron && apt-get install -y vim && apt-get install -y gcc && apt-get install -y man && apt-get install -y manpages-posix

RUN chmod +x /entrypoint.sh


