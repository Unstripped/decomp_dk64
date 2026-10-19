FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
        binutils-mips-linux-gnu \
        gcc-mips-linux-gnu \
        build-essential \
        ca-certificates \
        curl \
        git \
        make \
        python3 \
        python3-venv \
    && rm -rf /var/lib/apt/lists/*

# Python tooling: splat (splitter), spimdisasm (disassembler), m2c (MIPS -> C), asm-differ deps.
COPY requirements.txt /tmp/requirements.txt
RUN python3 -m venv /opt/venv \
    && /opt/venv/bin/pip install --no-cache-dir -r /tmp/requirements.txt
ENV PATH=/opt/venv/bin:$PATH

# IDO 5.3 (the compiler Rare used for DK64), static recompilation for the host arch.
RUN ARCH="$(dpkg --print-architecture)"; \
    case "$ARCH" in arm64) SUFFIX=linux-arm ;; amd64) SUFFIX=linux ;; *) echo "unsupported $ARCH"; exit 1 ;; esac; \
    mkdir -p /opt/ido5.3 \
    && curl -fsSL "https://github.com/decompals/ido-static-recomp/releases/download/v1.2/ido-5.3-recomp-${SUFFIX}.tar.gz" \
       | tar -xz -C /opt/ido5.3

# asm-processor (GLOBAL_ASM/INCLUDE_ASM with IDO), asm-differ (diff.py), m2c (decompiler).
RUN git clone --depth 1 https://github.com/simonlindholm/asm-processor /opt/asm-processor \
    && git clone --depth 1 https://github.com/simonlindholm/asm-differ /opt/asm-differ \
    && git clone --depth 1 https://github.com/matt-kempster/m2c /opt/m2c

WORKDIR /dk64
