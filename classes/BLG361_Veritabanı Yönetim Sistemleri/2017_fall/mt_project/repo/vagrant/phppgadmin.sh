#!/bin/sh

sudo perl -pi -e "s/^(allow from 127)/# \1/" /etc/apache2/conf.d/phppgadmin
sudo perl -pi -e "s/^#\s*(allow from all)/\1/" /etc/apache2/conf.d/phppgadmin
sudo echo "Include /etc/apache2/conf.d/phppgadmin" >> /etc/apache2/apache2.conf
sudo service apache2 restart
