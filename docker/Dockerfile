FROM osrf/ros:humble-desktop-full

SHELL ["/bin/bash", "-c"]

ARG USER=buggy

RUN groupadd --gid 1000 $USER && useradd -s /bin/bash --uid 1000 --gid 1000 \
    -m $USER && mkdir /home/$USER/.config && chown 1000:1000 /home/$USER/.config

USER root

RUN apt-get update --fix-missing && \
    apt-get install -y git \
    vim \
    ros-humble-ros-gz \
    tmux \
    ros-humble-rviz2 \
    ros-humble-xacro
RUN apt-get -y dist-upgrade 

RUN mkdir -p sim_ws/src
COPY . sim_ws/src

RUN source /opt/ros/humble/setup.bash && \
    cd sim_ws/ && \
    apt-get update --fix-missing && \
    rosdep install -i --from-path src --rosdistro humble -y && \
    colcon build

WORKDIR '/sim_ws'

COPY bashrc /home/${USER}/.bashrc

COPY entrypoint.sh /entrypoint.sh

ENTRYPOINT ["/bin/bash", "/entrypoint.sh"]

CMD ["bash"] 
