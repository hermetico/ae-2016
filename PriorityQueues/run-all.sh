#!/bin/bash
DATADIR=$1
BUILDDIR="build"
mkdir -p ${DATADIR}
echo "Compiling into "${BUILDDIR}"/"
rm -r ${BUILDDIR}
mkdir ${BUILDDIR}
cd ${BUILDDIR}
cmake ../
make
cd ../
echo "Compilation done!"
echo "Executing simple_heap_test"
./${BUILDDIR}/PriorityQueues 0 > ${DATADIR}/simple_heap_test.data
#echo "Executing sanders_simple_heap_test"
#./${BUILDDIR}/PriorityQueues 1 > ${DATADIR}/sanders_simple_heap_test.data
#echo "Executing sanders_heap4_test"
#./${BUILDDIR}/PriorityQueues 2 > ${DATADIR}/sanders_heap4_test.data
echo "Executing sanders_knheap_test"
./${BUILDDIR}/PriorityQueues 3 > ${DATADIR}/sanders_knheap_test.data
echo "BYE"
