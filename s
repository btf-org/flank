if [ -n "$(which cc)" ]; then
	cc flankserver.c -o fsl && ./fsl --iflank-path ./iflank
elif [ -n "$(which gcc)" ]; then
	gcc flankserver.c -o fsl && ./fsl --iflank-path ./iflank
else
	echo 'Cannot find gcc or cc!'
fi

