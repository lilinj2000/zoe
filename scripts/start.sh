#!/bin/sh

cur_dir=`pwd`

####streamer proxy####
cd ~/app/md_pull_proxy
. ./env.sh
./proxy >/dev/null 2>&1 &

####forwarder proxy####
cd ~/app/md_pub_proxy
. ./env.sh
./proxy >/dev/null 2>&1 &

####text sub####
cd $cur_dir/../text
. ./env.sh
./text >/dev/null 2>&1 &

####db sub####
# cd $cur_dir/../db
# . ./env.sh
# ./db >/dev/null 2>&1 &

####md pub####
sleep 1

cd $cur_dir/../md
. ./env.sh
./md >/dev/null 2>&1 &

####mdcli push####
# cd $cur_dir/../mdcli
# . ./env.sh
# ./mdcli >/dev/null 2>&1 &

# cd $cur_dir



