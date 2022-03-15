### PREPARE ###
FROM ubuntu:latest as base
# Dependencies
RUN apt-get update && apt-get install -y \
    # runtime libraries
    libcurl4-gnutls-dev \
    wget \
    build-essential\
    libb64-dev

# Install CMAKE
RUN wget https://github.com/Kitware/CMake/releases/download/v3.17.2/cmake-3.17.2-Linux-x86_64.sh \
      -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /usr/bin/cmake \
      && /tmp/cmake-install.sh --skip-license --prefix=/usr/bin/cmake \
      && rm /tmp/cmake-install.sh

### BUILD ###
FROM base AS builder

COPY . ./usr/src/app/

WORKDIR /usr/src/app/

RUN /usr/bin/cmake/bin/cmake . && /usr/bin/cmake/bin/cmake --build ./

### RUN ###
FROM base AS runtime

COPY --from=builder /usr/src/app/Client /usr/src/app/

WORKDIR /usr/src/app

CMD ["./Client"]