#!/bin/bash
DATADIR=$1
BUILDDIR="build"
echo "Compiling into "${BUILDDIR}"/"
rm -r ${BUILDDIR}
mkdir ${BUILDDIR}
cd ${BUILDDIR}
cmake ../
make
cd ../
echo "Compilation done!"

echo "Executing test recmult parallel"
./${BUILDDIR}/MatrixMult 1 3

echo "BYE"