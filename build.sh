#!/usr/bin/env bash

CONTAINER_NAME=pipegame-builder

ARG_CLEAN=false
ARG_BUILD=true
ARG_RUN=false
ARG_DIR=game

i=1;
j=$#;
while [ $i -le $j ]; do
    PARAM=$1;
    if [ "$PARAM" = "--clean" ]; then
        ARG_CLEAN=true
    elif [ "$PARAM" = "--no-build" ]; then
        ARG_BUILD=false
    elif [ "$PARAM" = "--run" ]; then
        ARG_RUN=true
    else
        ARG_DIR=$1
        shift 1
        break
    fi

    i=$((i + 1));
    shift 1;
done

if [ ! -d "$ARG_DIR" ]; then
    echo "Source directory '$ARG_DIR' not found..."
    exit 0
fi

MAKE_ARGS=

if [ $ARG_CLEAN = true ]; then
    MAKE_ARGS="$MAKE_ARGS clean"
fi

if [ $ARG_BUILD = true ]; then
    MAKE_ARGS="$MAKE_ARGS all"
fi

DOCKER_MAKE="docker run --rm \
    --name "$CONTAINER_NAME" \
    -v "./$ARG_DIR:/app" \
    pipegame:latest \
    make $MAKE_ARGS"
echo $DOCKER_MAKE
$DOCKER_MAKE

if [ $ARG_RUN = true ]; then
    "./${ARG_DIR}/pipegame" $@
fi
