FROM francomelandri/lib-tiny-fp-builder:0.20.3

WORKDIR /src
COPY ./src/*.cpp .
COPY ./src/*.h .
COPY ./src/Makefile .

WORKDIR /src/option
COPY ./src/option/*.cpp .
COPY ./src/option/*.h .
COPY ./src/option/subdir.mk .

WORKDIR /src/either
COPY ./src/either/*.cpp .
COPY ./src/either/*.h .
COPY ./src/either/subdir.mk .

WORKDIR /src/try
COPY ./src/try/*.cpp .
COPY ./src/try/*.h .
COPY ./src/try/subdir.mk .

WORKDIR /src/sequence
COPY ./src/sequence/*.cpp .
COPY ./src/sequence/*.h .
COPY ./src/sequence/subdir.mk .

WORKDIR /src/extensions
COPY ./src/extensions/*.cpp .
COPY ./src/extensions/*.h .

WORKDIR /src
RUN make all

WORKDIR /test
COPY ./test/*.cpp .
COPY ./test/*.h .
COPY ./test/Makefile .
WORKDIR /test
RUN make all

CMD /usr/local/bin/shell.sh ; sleep infinity