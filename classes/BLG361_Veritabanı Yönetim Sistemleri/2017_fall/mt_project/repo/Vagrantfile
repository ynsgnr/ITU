# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
    config.vm.box = "trusty32"
    config.vm.box_url = "https://cloud-images.ubuntu.com/vagrant/trusty/current/trusty-server-cloudimg-i386-vagrant-disk1.box"

    config.vm.network :forwarded_port, guest: 5432, host: 5432
    config.vm.network :forwarded_port, guest: 5000, host: 5050
    config.vm.network :forwarded_port, guest:   80, host: 5080

    config.vm.provider "virtualbox" do |vb|
        # vb.customize ["modifyvm", :id, "--memory", "1024"]
        vb.customize ["modifyvm", :id, "--name", "itucsdb" ]
    end

    # fix locale
    config.vm.provision :shell do |shell|
        shell.path = "vagrant/fixlocale.sh"
    end

    # Run apt-get update as a separate step in order to avoid
    # package install errors
    config.vm.provision :puppet do |puppet|
        puppet.manifests_path = "vagrant"
        puppet.manifest_file  = "aptgetupdate.pp"
    end

    # ensure we have the packages we need
    config.vm.provision :puppet do |puppet|
        puppet.manifests_path = "vagrant"
        puppet.manifest_file  = "itucsdb.pp"
    end

    # initialize database
    config.vm.provision :shell do |shell|
        shell.path = "vagrant/initpg.sh"
    end

    # configure phppgadmin
    config.vm.provision :shell do |shell|
        shell.path = "vagrant/phppgadmin.sh"
    end

    # install Python modules
    config.vm.provision :shell do |shell|
        shell.path = "vagrant/installpymods.sh"
    end
end
