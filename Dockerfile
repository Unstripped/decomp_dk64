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

# IDO 5.3 trace compiler for tools/uopt_trace.sh: uopt rebuilt from ido-static-recomp v1.2 with
# tools/ido/ecvt_fcvt.patch (upstream stubs ecvt/fcvt with assert(0), which aborts -Wo,-zdbug traces).
# Installed as /opt/ido5.3-trace; the production compiler /opt/ido5.3 stays the release binaries.
COPY tools/ido/ecvt_fcvt.patch /tmp/ecvt_fcvt.patch
RUN <<'EOF'
set -e
git clone --depth 1 --branch v1.2 https://github.com/decompals/ido-static-recomp /tmp/ido-recomp
cd /tmp/ido-recomp
patch -p1 < /tmp/ecvt_fcvt.patch
make VERSION=5.3 RELEASE=1 IDO_TC=uopt setup
make -j$(nproc) VERSION=5.3 RELEASE=1 IDO_TC=uopt build/5.3/out/uopt
cp -r /opt/ido5.3 /opt/ido5.3-trace
cp build/5.3/out/uopt /opt/ido5.3-trace/uopt
rm -rf /tmp/ido-recomp /tmp/ecvt_fcvt.patch
EOF

# asm-processor (GLOBAL_ASM/INCLUDE_ASM with IDO), asm-differ (diff.py), m2c (decompiler).
RUN git clone --depth 1 https://github.com/simonlindholm/asm-processor /opt/asm-processor \
    && git clone --depth 1 https://github.com/simonlindholm/asm-differ /opt/asm-differ \
    && git clone --depth 1 https://github.com/matt-kempster/m2c /opt/m2c

# decomp-permuter (randomised C permutator for near-miss matching), pinned to commit 8556c81d80d1c1af98a858c8f4dc951357f29139
RUN git clone https://github.com/simonlindholm/decomp-permuter /opt/decomp-permuter \
    && cd /opt/decomp-permuter \
    && git checkout 8556c81d80d1c1af98a858c8f4dc951357f29139

# GNU gzip 1.2.4 -9 -n reproduces all 20 code/data gzip members in the ROM; modern gzip and zlib do not.
RUN curl -fsSL "https://ftp.gnu.org/gnu/gzip/gzip-1.2.4.tar.gz" -o /tmp/gzip-1.2.4.tar.gz \
    && echo "1ca41818a23c9c59ef1d5e1d00c0d5eaa2285d931c0fb059637d7c0cc02ad967  /tmp/gzip-1.2.4.tar.gz" | sha256sum -c - \
    && tar -xzf /tmp/gzip-1.2.4.tar.gz -C /tmp \
    && cd /tmp/gzip-1.2.4 \
    && ./configure \
    && make \
    && cp gzip /usr/local/bin/gzip-1.2.4 \
    && rm -rf /tmp/gzip-1.2.4*

WORKDIR /dk64
