use vs2015 to build tcmalloc

windows mingw:

pexports libtcmalloc_minimal.dll > tcmalloc.def
dlltool -d tcmalloc.def -D libtcmalloc_minimal -l libtcmalloc_minimal.a

or

http://sourceforge.net/projects/mingw/files/MSYS/
./autogen.sh
./configure
./make

