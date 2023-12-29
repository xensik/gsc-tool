FROM alpine:3.19

# glibc compatibility
RUN apk add --no-cache gcompat libstdc++

# copy gsc-tool
COPY --chmod=755 gsc-tool /usr/local/bin/

ENTRYPOINT ["/usr/local/bin/gsc-tool"]