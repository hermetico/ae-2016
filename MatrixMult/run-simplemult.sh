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
echo "Executing test simplemult"
./${BUILDDIR}/MatrixMult 1 0
echo "BYE"