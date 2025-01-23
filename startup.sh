docker run -it --user buggy --net=host --ipc=host -v /tmp/.X11-unix:/tmp/.X11-unix:rw --env=DISPLAY --privileged -v /dev:/dev test
