# developer

## builder

### abstract

the builder docker generating by Dockerfile.ubuntu20 let to use a set of predefined tools in order to:

- using the g++ compiler
- build a project using makefile approach
- creating awesome unit test leveragin on `lib-boosts`
- perform memory check using `valgrind`

### how to

you can buil the your own builder image, locally suing docker, following these steps.

build the image:

```bash
> docker build -t lib-tiny-fp-builder -f ./build/Dockerfile.ubuntu20 .
```

tag the image with your own name:

```bash
> docker tag lib-tiny-fp-builder <your-account>/lib-tiny-fp-builder:x.y.z
```

push the image to you repository:

```bash
> docker push <your-account>/lib-tiny-fp-builder:x.y.z
```


