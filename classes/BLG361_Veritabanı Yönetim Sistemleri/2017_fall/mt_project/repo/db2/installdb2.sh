#!/bin/sh

tar xzf /vagrant/*_expc.tar.gz
sudo ./expc/db2setup -r /vagrant/db2expc.rsp
rm -rf expc
sudo addgroup vagrant db2iadm1
sudo chmod 755 /opt/ibm/db2/V10.5/adm/db2start
sudo /opt/ibm/db2/V10.5/adm/db2start
sudo -u vagrant -H /opt/ibm/db2/V10.5/bin/db2 create database itucsdb
