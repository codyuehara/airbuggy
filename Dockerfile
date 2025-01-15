FROM ros:foxy 

SHELL ["/bin/bash", "-c"]

RUN apt-get update --fix-missing && \
    apt-get install -y git \
    vim \
    ros-foxy-gazebo-ros-pkgs \
    tmux \
    ros-foxy-rviz2 \
    ros-foxy-xacro
RUN apt-get -y dist-upgrade 

RUN mkdir -p sim_ws/src
COPY . sim_ws/src

RUN source /opt/ros/foxy/setup.bash && \
    cd sim_ws/ && \
    apt-get update --fix-missing && \
    rosdep install -i --from-path src --rosdistro foxy -y && \
    colcon build

WORKDIR '/sim_ws'
ENTRYPOINT ["/bin/bash"]
 
