# KIO AWS

KIO slave for AWS S3 buckets

## Links

* [KIO GDrive](https://github.com/KDE/kio-gdrive)
* [Debugging kioslave](https://community.kde.org/Guidelines_and_HOWTOs/Debugging/Debugging_IOSlaves)

## Developing

Build dependency:

```
docker build -t pawelkorus/cpp-dev https://github.com/pawelkorus/dockerfiles.git#master:cpp-dev
```

Build docker image:
```
docker build . -t pawelkorus/kio-aws
```

Run docker container
```
docker run -it --rm -e DISPLAY=$DISPLAY -e QT_XCB_GL_INTEGRATION=none -v /tmp/.X11-unix:/tmp/.X11-unix -v $PWD:/home/user/project --cap-add=SYS_PTRACE --security-opt seccomp=unconfined pawelkorus/kio-aws bash
```
Sources are mounted to `/home/user/project`

Image comes with preinstalled qtcreator IDE. You can run it using following command:
```
qtcreator -settingspath /home/user/project
```
This way qtcreator settings are persisted in mounted volume and you don't have to reconfigure it each time you run container.

## Tips

Check which *.so libraries are loaded with `kioclient5`:
```
strace kioclient5 ls s3aws://<your-domain> 2>&1 | grep --color openat
```
