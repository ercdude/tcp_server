FROM alpine

RUN apk update

# fetch and build dependencies
RUN apk add g++ \
            make \
            cmake \
            boost-dev

VOLUME /build
VOLUME /src
