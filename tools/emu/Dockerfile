# Dockerfile for dk64-emu: Donkey Kong 64 N64 emulator container
# Provides ares (HailToDodongo/ares-64 with angrylion CPU renderer & GDB remote server),
# Xvfb virtual display, x11vnc, xdotool, and gdb-multiarch.

FROM ubuntu:24.04 AS ares-builder

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    git \
    ca-certificates \
    libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxfixes-dev libxss-dev libxkbcommon-dev \
    libgl1-mesa-dev libegl1-mesa-dev \
    libasound2-dev libpulse-dev libdbus-1-dev libudev-dev \
    libvulkan-dev \
    && rm -rf /var/lib/apt/lists/*

ARG ARES_COMMIT=6b65e1beacf8b2af66aaee72541ab154382b7e6a
RUN git clone https://github.com/HailToDodongo/ares-64.git /ares-64 \
    && cd /ares-64 \
    && git checkout ${ARES_COMMIT} \
    && git submodule update --init --recursive

WORKDIR /ares-64
RUN cmake -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DARES_ENABLE_VULKAN=OFF \
    -DARES_ENABLE_DEBUG_TOOLS=ON \
    -DARES_BUILD_HEADLESS=OFF \
    -DARES_CORES=n64 \
    -DENABLE_CCACHE=OFF \
    && ninja -C build desktop-ui

# Stage 2: Runtime image
FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    xvfb \
    x11-utils \
    x11vnc \
    xdotool \
    imagemagick \
    gdb-multiarch \
    netcat-openbsd \
    mesa-vulkan-drivers \
    libvulkan1 \
    libgl1 \
    libegl1 \
    libasound2t64 \
    libpulse0 \
    libx11-6 \
    libxext6 \
    libxrandr2 \
    libxcursor1 \
    libxi6 \
    libxfixes3 \
    libxss1 \
    libxkbcommon0 \
    procps \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Copy emulator build
COPY --from=ares-builder /ares-64/build/desktop-ui /opt/ares
RUN ln -s /opt/ares/ares /usr/local/bin/ares

# Helper scripts and pre-seeded settings
RUN mkdir -p /opt/emu
COPY tools/emu/container/default_settings.bml /opt/emu/default_settings.bml
COPY tools/emu/container/gdb_helper.py /opt/emu/gdb_helper.py
COPY tools/emu/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

WORKDIR /dk64
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
