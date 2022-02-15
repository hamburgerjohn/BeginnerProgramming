
a=$(cat /usr/x86_64-w64-mingw32/include/*)
for i in {1..3}
do
	echo -e "\033[00;31m$a]"
done
exit 0
