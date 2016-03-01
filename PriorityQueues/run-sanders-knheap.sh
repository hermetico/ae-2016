#!/bin/bash
DATADIR=$1
BUILDDIR="build"
echo "Compiling into build/"
rm -r ${BUILDDIR}
mkdir ${BUILDDIR}
cd ${BUILDDIR}
cmake ../
make
cd ../
echo "Compilation done!"
echo "Executing sanders_knheap_test"
./${BUILDDIR}/PriorityQueues 3 r > ${DATADIR}
echo "BYE"