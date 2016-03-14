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

for i in {8,16,32,40,64}; do
    echo "Executing test recmult with limit $i"
	./${BUILDDIR}/MatrixMult 1 2 > "$i" ${DATADIR}"/recmult_$i.data"
done

echo "BYE"