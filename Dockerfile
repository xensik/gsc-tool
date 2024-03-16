FROM ubuntu:24.04

COPY --chmod=755 ./linux-x64-release/gsc-tool /usr/local/bin/

RUN groupadd gsc-tool && useradd -r -g gsc-tool gsc-tool
USER gsc-tool

ENTRYPOINT ["/usr/local/bin/gsc-tool"]
