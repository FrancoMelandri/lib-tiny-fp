FROM francomelandri/lib-tiny-fp-builder:0.24.0

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

WORKDIR /src/pipeline
COPY ./src/pipeline/*.cpp .
COPY ./src/pipeline/*.h .
COPY ./src/pipeline/subdir.mk .

WORKDIR /src/extensions
COPY ./src/extensions/*.cpp .
COPY ./src/extensions/*.h .
COPY ./src/extensions/subdir.mk .

WORKDIR /src/types
COPY ./src/types/*.cpp .
COPY ./src/types/*.h .
COPY ./src/types/subdir.mk .

WORKDIR /src
RUN make all

WORKDIR /test
COPY ./test/*.cpp .
COPY ./test/*.h .
COPY ./test/Makefile .
WORKDIR /test
RUN make all

CMD /usr/local/bin/shell.sh ; sleep infinity