#!/bin/sh

docker run -it --rm -e DISPLAY=$DISPLAY -e QT_XCB_GL_INTEGRATION=none -v /tmp/.X11-unix:/tmp/.X11-unix -v $PWD:/home/user/project --cap-add=SYS_PTRACE --security-opt seccomp=unconfined pawelkorus/kio-aws bash
