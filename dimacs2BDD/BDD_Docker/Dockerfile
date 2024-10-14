FROM debian:sid
LABEL authors="jahns"

RUN apt-get update && apt-get install -y \
    flex \
    bison \
    gperf \
    libfl-dev \
    autoconf \
    m4 \
    perl \
    build-essential \
    libgmp3-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY code_logic2bdd /app/Logic2BDD

RUN cd Logic2BDD && make && cd ..

COPY code_bddsampler /app/BDDSampler

RUN cd BDDSampler && ./configure && make

ENV LD_LIBRARY_PATH=/app/Logic2BDD/lib:$LD_LIBRARY_PATH

CMD ["/bin/bash"]