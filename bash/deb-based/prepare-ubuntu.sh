#!/bin/bash

echo "TODO: setup git, bashrc, meld, Mate, vscode"
sudo apt-get install                  \
    texlive-full lyx                  \
    git git-cola meld build-essential \
    qemu qemu-kvm virt-manager        \
    virtualbox virtualbox-ext-pack    \
    docker.io                         \
    wireshark nmap                    \
    gimp inkscape                     \
    apt-transport-https               \
    fortune-mod                       \
    mc vim mutt \
    gnome-disk-utility

sudo add-apt-repository 'deb https://typora.io/linux ./'
sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys BA300B7755AFCFAE
sudo apt-get update
sudo apt-get install typora

## WARN: NOT TESTED
echo WARN: INSTALL vscode MANUALLY NOT TESTED
# curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg
# sudo install -o root -g root -m 644 microsoft.gpg /etc/apt/trusted.gpg.d/
# sudo sh -c 'echo "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main" > /etc/apt/sources.list.d/vscode.list'
# sudo apt-get update
# sudo apt-get install code # or code-insiders

