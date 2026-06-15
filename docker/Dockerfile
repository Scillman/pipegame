FROM archlinux:latest

ARG SDL_VERSION=3.4.10

# Generate a key because apparently we need one
RUN pacman-key --init

# Update and install dependencies
RUN pacman -Syu --noconfirm && \
    pacman -Syu --noconfirm \
        alsa-lib \
        base-devel \
        clang \
        cmake \
        curl \
        git \
        glslang \
        libdecor \
        libxkbcommon \
        make \
        mesa \
        nano \
        ninja \
        pkgconf \
        shaderc \
        spirv-headers \
        spirv-tools \
        vim \
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
        wget

# Non-privileged user, same uid and gid as host system
RUN groupadd -g 1001 developer && \
    useradd --no-create-home --home-dir /app -u 1001 -g developer developer

RUN mkdir /redist && \
    chown -R developer:developer /redist

USER developer

# Set working directory
WORKDIR /tmp

RUN wget "https://github.com/libsdl-org/SDL/releases/download/release-3.4.10/SDL3-$SDL_VERSION.tar.gz" && \
    tar -xf "SDL3-${SDL_VERSION}".tar.gz

RUN cmake \
        -S "SDL3-${SDL_VERSION}" \
        -B "SDL3-${SDL_VERSION}/build" \
        -G Ninja \
        -DBUILD_SHARED_LIBS=OFF \
        -DSDL_STATIC=ON \
        -DSDL_SHARED=OFF \
        -DSDL_X11=OFF \
        -DSDL_WAYLAND=ON \
        -DCMAKE_INSTALL_PREFIX=/redist && \
    cmake --build "SDL3-${SDL_VERSION}/build"&& \
    cmake --install "SDL3-${SDL_VERSION}/build"

RUN rm -r \
    "SDL3-${SDL_VERSION}" \
    "SDL3-${SDL_VERSION}".tar.gz

# Set working directory
WORKDIR /app
