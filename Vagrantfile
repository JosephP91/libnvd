# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = '2'

@script = <<SCRIPT

# Fix for https://bugs.launchpad.net/ubuntu/+source/livecd-rootfs/+bug/1561250
if ! grep -q "ubuntu-xenial" /etc/hosts; then
    echo "127.0.0.1 ubuntu-xenial" >> /etc/hosts
fi

# Install dependencies, update system and eventually remove unused packages.

sudo apt-get update
sudo apt-get install -y g++ cmake git curl pkg-config mongodb lynx unzip tar rsync
sudo apt-get -y upgrade
sudo apt-get -y autoremove

# Reset home directory for vagrant user.
if ! grep -q "cd /vagrant" /home/ubuntu/.profile; then
    echo "cd /vagrant" >> /home/ubuntu/.profile
fi

SCRIPT

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = 'ubuntu/xenial64'
  config.vm.network "forwarded_port", guest: 27017, host: 27017, auto_correct: true
  config.vm.synced_folder '.', '/vagrant', type: "rsync", rsync__exclude: ".git", rsync__auto: true, owner: "vagrant"
  config.vm.provision 'shell', inline: @script

  config.vm.provider "virtualbox" do |vb|
    vb.customize ["modifyvm", :id, "--memory", "2048"]
    vb.customize ["modifyvm", :id, "--name", "nvd - Ubuntu 16.04"]
  end
end
