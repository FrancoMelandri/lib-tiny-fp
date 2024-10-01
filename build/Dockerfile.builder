FROM francomelandri/lib-tiny-fp-builder:0.20.1

WORKDIR /src

COPY ./*.cpp .
COPY ./*.h .
COPY ./Makefile .

CMD make all
