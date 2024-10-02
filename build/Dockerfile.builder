FROM francomelandri/lib-tiny-fp-builder:0.20.3

WORKDIR /src
COPY ./src/*.cpp .
COPY ./src/*.inc .
COPY ./src/*.h .
COPY ./src/Makefile .

WORKDIR /src
RUN make all

WORKDIR /test
COPY ./test/*.cpp .
COPY ./test/*.h .
COPY ./test/Makefile .
WORKDIR /test
RUN make all

CMD /usr/local/bin/shell.sh ; sleep infinity