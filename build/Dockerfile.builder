FROM francomelandri/lib-tiny-fp-builder:0.20.1

WORKDIR /src
COPY ./src/*.cpp .
COPY ./src/*.h .
COPY ./src/Makefile .

WORKDIR /src
RUN make all

CMD /usr/local/bin/shell.sh ; sleep infinity