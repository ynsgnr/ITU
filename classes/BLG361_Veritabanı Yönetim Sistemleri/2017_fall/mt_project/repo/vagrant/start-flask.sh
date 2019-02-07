#!/bin/sh

vagrant ssh -c "cd /vagrant && sudo pip3 install -U -r requirements.txt && python3 server.py"
