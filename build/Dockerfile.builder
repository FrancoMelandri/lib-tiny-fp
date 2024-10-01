FROM francomelandri/lib-tiny-fp-builder:0.20.1

WORKDIR /src

COPY ./src/*.cpp .
COPY ./src/*.h .
COPY ./src/Makefile .

CMD make all
