#!/bin/bash
BUILDDIR="build"
echo "Compiling into "${BUILDDIR}"/"
rm -r ${BUILDDIR}
mkdir ${BUILDDIR}
cd ${BUILDDIR}
cmake ../
make
cd ../
echo "Compilation done!"
echo "Executing test recmult"
./${BUILDDIR}/MatrixMult 1 2
echo "BYE"