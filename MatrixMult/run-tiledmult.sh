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
echo "Executing test tiledmult"
./${BUILDDIR}/MatrixMult 1 1
echo "BYE"