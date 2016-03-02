#! /bin/sh

home_app=~/app

if test -d /llj/app ; then
   home_app=/llj/app
fi

home_zoe=${home_app}/zoe

./configure --prefix=${home_zoe}

if test -d ${home_zoe}; then
    rm -rf ${home_zoe}
fi

make install

make distclean
