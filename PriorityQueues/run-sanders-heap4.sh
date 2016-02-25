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
echo "Executing sanders_heap4_test"
./${BUILDDIR}/PriorityQueues 2 > ${DATADIR}/sanders_heap4_test.data
echo "BYE"