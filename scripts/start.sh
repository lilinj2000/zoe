#!/bin/sh

cur_dir=`pwd`

####forwwarder####
cd /llj/libs/zod/bin
. ./env.sh
./forwarder >/dev/null 2>&1 &

####text sub####
cd $cur_dir/../text
. ./env.sh
./text >/dev/null 2>&1 &

####db sub####
cd $cur_dir/../db
. ./env.sh
./db >/dev/null 2>&1 &

####md pub####
cd $cur_dir/../md
. ./env.sh
./md >/dev/null 2>&1 &

# cd $cur_dir



