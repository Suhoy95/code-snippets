#!/bin/bash

echo "ERROR: snippets is not a script. Finish"
exit -1

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
    mc vim mutt htop \
    gnome-disk-utility	\
    dstat tree \
    sshfs \
    libreoffice

sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys BA300B7755AFCFAE
sudo add-apt-repository 'deb https://typora.io/linux ./'
sudo apt-get install typora

sudo mkdir /windows
sudo fdisk -l
# sudo mount -t ntfs -o nls=utf8,umask=0077,uid=$(id -u suhoy),gid=$(id -g suhoy) \
#     /dev/sdXXX /windows
sudo blkid && id
cat <<EOF >> /etc/fstab
# windows partition
UUID=06A0CBF1A0CBE4F1 /windows ntfs nls=utf8,umask=0077,uid=1000,gid=1000 0 0
EOF

for dirname in Documents Music Videos Downloads Pictures Desktop; do
    tree $dirname
    read -p "mv $dirname Continue?"
    mv $dirname/* /windows/Users/suhoy/$dirname/
    rmdir $dirname
    ln --symbolic /windows/Users/suhoy/$dirname/ $dirname
done
rmdir Public Templates
