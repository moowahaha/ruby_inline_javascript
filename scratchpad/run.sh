g++ -Iinclude example.cc /usr/local/Cellar/v8/HEAD/lib/libv8.dylib
./a.out  "function myConcat (a, b) { return(a + ' ' + b) }" "myConcat('jonpads', 'sucks')"
