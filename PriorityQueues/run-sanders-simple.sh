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
echo "Executing sanders_simple_heap_test"
./${BUILDDIR}/PriorityQueues 1 > ${DATADIR}/sanders_simple_heap_test.data
echo "BYE"
