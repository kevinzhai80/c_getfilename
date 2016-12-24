if [ `ls ./testp/ | grep file1` ]
then
	ls ./testp/ | grep file1 >> ./test.tmp
else 
	echo no >> ./test.tmp;
fi
cat ./test.tmp
