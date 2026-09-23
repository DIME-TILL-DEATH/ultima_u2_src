#!/bin/bash

for n in `seq 1 9`
do
        i="00$n.png"
        j=`basename $i .png`
        convert $i $j.pbm
        cjb2 -clean $j.pbm $j.djvu
#        djvm -i rig_veda.djvu $j.djvu
done

for n in `seq 10 99`
do
        i="0$n.png"
        j=`basename $i .png`
        convert $i $j.pbm
        cjb2 -clean $j.pbm $j.djvu
#        djvm -i rig_veda.djvu $j.djvu
done

for n in `seq 100 326`
do
        i="$n.png"
        j=`basename $i .png`
        convert $i $j.pbm
        cjb2 -clean $j.pbm $j.djvu
#        djvm -i rig_veda.djvu $j.djvu
done
