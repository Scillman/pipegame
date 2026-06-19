#!/usr/bin/env bash

CACHE=

if [[ "$1" = "-f" || "$1" = "--force" ]]; then
    CACHE=--no-cache
fi

docker buildx build --platform linux/amd64 $CACHE -t pipegame:latest -f Dockerfile .
