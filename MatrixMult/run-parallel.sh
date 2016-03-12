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

echo "Executing test recmult parallel 1 threads"
./${BUILDDIR}/MatrixMult 1 3 1 > ${DATADIR}/recmult_1_thread.data

echo "Executing test recmult parallel 2 threads"
./${BUILDDIR}/MatrixMult 1 3 2 > ${DATADIR}/recmult_2_threads.data

echo "Executing test recmult parallel 4 threads"
./${BUILDDIR}/MatrixMult 1 3 4 > ${DATADIR}/recmult_4_threads.data

echo "Executing test recmult parallel 8 threads"
./${BUILDDIR}/MatrixMult 1 3 8 > ${DATADIR}/recmult_8_threads.data

echo "BYE"