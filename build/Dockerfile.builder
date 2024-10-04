FROM francomelandri/lib-tiny-fp-builder:0.20.3

WORKDIR /src
COPY ./src/*.cpp .
COPY ./src/*.inc .
COPY ./src/*.h .
COPY ./src/Makefile .

WORKDIR /src/option
COPY ./src/option/*.cpp .
COPY ./src/option/*.inc .
COPY ./src/option/*.h .
COPY ./src/option/subdir.mk .

WORKDIR /src/either
COPY ./src/either/*.cpp .
COPY ./src/either/*.inc .
COPY ./src/either/*.h .
COPY ./src/either/subdir.mk .

WORKDIR /src
RUN make all

WORKDIR /test
COPY ./test/*.cpp .
COPY ./test/*.h .
COPY ./test/Makefile .
WORKDIR /test
RUN make all

CMD /usr/local/bin/shell.sh ; sleep infinity