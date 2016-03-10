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
echo "Executing test simplemult"
./${BUILDDIR}/MatrixMult 1 0 > ${DATADIR}/simplemult.data
echo "Executing test tiledmult"
./${BUILDDIR}/MatrixMult 1 1 > ${DATADIR}/tiledmult.data
echo "Executing test recmult"
./${BUILDDIR}/MatrixMult 1 2 > ${DATADIR}/recmult.data
echo "BYE"