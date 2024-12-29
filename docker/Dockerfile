FROM ubuntu:22.04

COPY install_deps.sh /
RUN sh install_deps.sh

RUN ln -s /usr/bin/clang-17 /usr/bin/clang
RUN ln -s /usr/bin/clang++-17 /usr/bin/clang++

ENV TZ=Europe/Moscow
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

# SSH
EXPOSE 22
RUN mkdir /var/run/sshd
CMD ["/usr/sbin/sshd", "-D"]

# ADD USER
ARG USERNAME
RUN useradd -m -s /bin/bash $USERNAME
COPY .bashrc /home/$USERNAME/.bashrc
RUN chown $USERNAME:$USERNAME /home/$USERNAME/.bashrc

RUN usermod -aG sudo $USERNAME
