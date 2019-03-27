= KIO AWS =

== Links ==

[KIO GDrive](https://github.com/KDE/kio-gdrive)
[Debugging kioslave](https://community.kde.org/Guidelines_and_HOWTOs/Debugging/Debugging_IOSlaves)

== Developing ==

Build docker image:
```
docker build . -t pawelkorus/kio-aws
```

Run docker container
```
docker run -it --rm -e DISPLAY=$DISPLAY -e QT_XCB_GL_INTEGRATION=none -v /tmp/.X11-unix:/tmp/.X11-unix -v $PWD:/home/user/project --cap-add=SYS_PTRACE --security-opt seccomp=unconfined pawelkorus/kio-aws bash
```

Then you can use qtcreator and other tools.

Sources are mounted to `/home/user/project`

== Tips & Trics ==

Check which *.so libraries are loaded with `kioclient5`:
```
strace kioclient5 ls s3aws://pawelkorus-testbucketccc 2>&1 | grep --color openat
```