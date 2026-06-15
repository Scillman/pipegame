#!/usr/bin/env bash

CONTAINER_NAME=pipegame-builder

if docker container inspect "$CONTAINER_NAME" >/dev/null 2>&1; then
    STATUS=$(docker container inspect -f '{{.State.Status}}' "$CONTAINER_NAME")
    case "$STATUS" in
        created|running|paused|restarting)
            echo "Stopping Docker container..."
            docker stop "$CONTAINER_NAME"
            echo "Removing Docker container..."
            docker container rm "$CONTAINER_NAME"
            ;;
        exited|dead)
            echo "Removing Docker container..."
            docker container rm "$CONTAINER_NAME"
            ;;
        *)
            echo "Container exists but in unsupported of $STATUS"
            ;;
    esac
else
    echo "Container does not exist"
fi

echo "Starting Docker container..."
docker run \
    -v './ai_code:/app' \
    --name "$CONTAINER_NAME" \
    pipegame:latest \
    make clean pipegame

# docker logs pipegame
