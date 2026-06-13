FROM archlinux:latest

# Generate a key because apparently we need one
RUN pacman-key --init

# Update system dependencies
RUN pacman -Syu --noconfirm

# These require confirmations for which packages to install (default=all)
RUN pacman -S --noconfirm base-devel
RUN pacman -S --noconfirm vulkan-devel

# Not sure if this needs confirmation (or even needs to be installed) or not, lets test this later okay?!
RUN pacman -S --noconfirm mesa

# These do not require any confirmation
RUN pacman -S --noconfirm \
    wayland \
    wayland-protocols \
    clang \
    make \
    git

# Non-privileged user, same uid and gid as host system
RUN groupadd -g 1001 developer && \
    useradd --no-create-home --home-dir /app -u 1001 -g developer developer
USER developer

# Set working directory
WORKDIR /app
