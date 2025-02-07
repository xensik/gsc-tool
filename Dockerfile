FROM ubuntu:24.04
ARG TARGETARCH

COPY --chmod=755 ./linux-${TARGETARCH}-release/gsc-tool /usr/local/bin/

RUN groupadd gsc-tool && useradd -r -g gsc-tool gsc-tool
USER gsc-tool

ENTRYPOINT ["/usr/local/bin/gsc-tool"]
