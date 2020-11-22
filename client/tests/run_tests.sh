cd build 
for i in * 
do
	if [ "$i" != "Makefile" ];
	then
		./$i/$i
	fi
done;