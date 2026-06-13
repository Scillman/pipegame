#!/usr/bin/env bash

# Stop and delete old container
docker stop pipegame
docker container rm pipegame

# Start a new container
docker run \
    -v './game:/app' \
    --name pipegame \
    pipegame:latest \
    make pipegame

# docker logs pipegame
