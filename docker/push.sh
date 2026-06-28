#!/usr/bin/env bash
REGISTRY="registry.local:5000"
docker tag pipegame:latest $REGISTRY/pipegame:latest
docker image push $REGISTRY/pipegame:latest
