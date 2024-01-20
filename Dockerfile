FROM alpine:3.19

RUN apk add --no-cache gcompat libstdc++

COPY --chmod=755 ./linux-x64-release/gsc-tool /usr/local/bin/

RUN addgroup -S gsc-tool && adduser -S gsc-tool -G gsc-tool
USER gsc-tool

ENTRYPOINT ["/usr/local/bin/gsc-tool"]
