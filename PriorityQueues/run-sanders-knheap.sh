#!/bin/bash
DATADIR=$1
BUILDDIR="build"
mkdir ${DATADIR}
echo "Compiling into build/"
rm -r ${BUILDDIR}
mkdir ${BUILDDIR}
cd ${BUILDDIR}
cmake ../
make
cd ../
echo "Compilation done!"
echo "Executing sanders_knheap_test"
./${BUILDDIR}/PriorityQueues 3 > ${DATADIR}/sanders_knheap_test.data
echo "BYE"