# Dev Container configuration for PSP development
FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    autoconf \
    automake \
    bison \
    flex \
    libncurses5-dev \
    libreadline-dev \
    libusb-dev \
    texinfo \
    libgmp3-dev \
    libmpfr-dev \
    libmpc-dev \
    libelf-dev \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

# Set up PSP development environment
ENV PSPDEV=/opt/pspdev
ENV PATH=${PATH}:${PSPDEV}/bin
ENV PSPSDK=${PSPDEV}/psp/sdk

# Create directory for PSPDEV
RUN mkdir -p ${PSPDEV}

# Clone and build PSP toolchain
RUN cd /tmp && \
    git clone https://github.com/pspdev/psptoolchain.git && \
    cd psptoolchain && \
    ./toolchain.sh && \
    cd / && \
    rm -rf /tmp/psptoolchain

# Set working directory
WORKDIR /workspace

CMD ["/bin/bash"]
