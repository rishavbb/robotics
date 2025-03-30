FROM ros:noetic

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

# Avoid tzdata hanging during install
RUN apt update && apt install -y tzdata

# Install Gazebo, OpenGL, GUI, and useful tools
RUN apt update && apt install -y \
    gazebo11 \
    ros-noetic-desktop-full \
    ros-noetic-gazebo-ros-pkgs \
    ros-noetic-gazebo-ros-control \
    python3-pip \
    git \
    nano \
    x11-apps \
    libgl1-mesa-glx \
    libgl1-mesa-dri \
    libglu1-mesa \
    mesa-utils \
    && rm -rf /var/lib/apt/lists/*

# Setup ROS env in .bashrc
RUN echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc

# Setup catkin workspace
RUN mkdir -p /root/catkin_ws/src && \
    /bin/bash -c "source /opt/ros/noetic/setup.bash && cd /root/catkin_ws && catkin_make"

WORKDIR /root/catkin_ws

CMD ["/bin/bash"]

