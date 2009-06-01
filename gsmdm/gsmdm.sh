#!/bin/sh

PATH=/sbin:/bin:/usr/sbin:/usr/bin

. /usr/sbin/ts7260.subr

d1=4
cmds=$1

resetout () {
   dio_dir_set $d1 1 >> /dev/null 2>&1
   dio_data_set $d1 1 >> /dev/null 2>&1
}

case "$cmds" in
    on)
         resetout
         dio_data_set $d1 1 >> /dev/null 2>&1;
         ;;
    off)
         resetout
         dio_data_set $d1 0 >> /dev/null 2>&1;
         ;;
    *)
         echo -e "\nUsage: gsmdm [on|off]";
         echo -e "\nThe command to turn GSM Modem on or off\n..."
         ;;
esac




