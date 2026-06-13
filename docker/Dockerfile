FROM archlinux:latest

# Generate a key because apparently we need one
RUN pacman-key --init

# Update and install dependencies
RUN pacman -Syu --noconfirm && \
    pacman -Syu --noconfirm \
    spirv-headers \
    spirv-tools \
    volk \
    vulkan-extra-layers \
    vulkan-extra-tools \
    vulkan-headers \
    vulkan-icd-loader \
    vulkan-profiles \
    vulkan-tools \
    vulkan-utility-libraries \
    vulkan-validation-layers \
    wayland \
    wayland-protocols \
    clang \
    make

# Non-privileged user, same uid and gid as host system
RUN groupadd -g 1001 developer && \
    useradd --no-create-home --home-dir /app -u 1001 -g developer developer
USER developer

# Set working directory
WORKDIR /app
