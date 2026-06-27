#!/usr/bin/env bash

CONTAINER_NAME=pipegame-builder

ARG_CLEAN=false
ARG_BUILD=true
ARG_RUN=false
ARG_DIR=game

function printUsage()
{
    echo ""
    echo "USAGE: build.sh <OPTIONS> <game_dir> <run_args>"
    echo ""
    echo "OPTIONS"
    echo "  --clean      Clean before compiling"
    echo "  --help       Display this help message"
    echo "  --no-build   Do not compile and/or build"
    echo "  --run        Run the game after compiling"
    echo ""
}

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
    elif [ "$PARAM" = "--help" ]; then
        printUsage
        exit 0
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
    BIN_FILE="./${ARG_DIR}/pipegame"
    if [ -f "$BIN_FILE" ]; then
        $BIN_FILE $@
    fi
fi
