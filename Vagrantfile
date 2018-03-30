# -*- mode: ruby -*-
# vi: set ft=ruby :

VAGRANTFILE_API_VERSION = '2'

@script = <<SCRIPT

# Install dependencies, update system and eventually remove unused packages.
sudo apt-get update
sudo apt-get install -y g++ cmake git curl pkg-config mongodb cifs-utils
sudo apt-get -y dist-upgrade
sudo apt-get -y autoremove

SCRIPT

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = 'ubuntu/xenial64'
  config.vm.network "forwarded_port", guest: 27017, host: 27017, auto_correct: true
  config.vm.synced_folder '.', '/vagrant', type: "rsync"
  config.vm.provision 'shell', inline: @script

  config.vm.provider "virtualbox" do |vb|
    vb.customize ["modifyvm", :id, "--memory", "2048"]
    vb.customize ["modifyvm", :id, "--name", "nvd - Ubuntu 16.04"]
  end
end
