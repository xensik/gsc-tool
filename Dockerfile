FROM alpine:3.19

RUN apk add --no-cache gcompat libstdc++

COPY --chmod=755 ./linux-x64-release/gsc-tool /usr/local/bin/

ENTRYPOINT ["/usr/local/bin/gsc-tool"]
