
home_3rd=~/3rd

if test -d /llj/3rd ; then
   home_3rd=/llj/3rd
fi

home_boost=$home_3rd/boost

export LD_LIBRARY_PATH=$home_boost/lib


