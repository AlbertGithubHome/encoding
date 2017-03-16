
#generate Makefile.am for sus project
cp generate_makefile_am.sh ../../code/detection
cd ../../code/detection && ./generate_makefile_am.sh "libdetection"

#copy necessary file
cd ../../tools/make4linux
cp NEWS README AUTHORS ChangeLog ../../code

cd ../../code

echo "- libtoolize."		&& \
libtoolize -f -c --force	&& \
echo "- aclocal."		&& \
aclocal				&& \
echo "- autoconf."		&& \
autoconf			&& \
#echo "- autoheader."		&& \
#autoheader			&& \
echo "- automake."		&& \
automake --add-missing --gnu	&& \
echo				&& \
./configure 

#compile
make clean
make

#move execute file
cp epoch ../bin

#clean temporary files
mkdir tmp
mv aclocal.m4 autom4te.cache config.guess config.status configure COPYING epoch.o install-sh ltmain.sh Makefile Makefile.in  NEWS AUTHORS ChangeLog config.log config.sub depcomp epoch INSTALL libtool missing README ./tmp
