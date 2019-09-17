#swig -c++ -python dat.i


INCLUDE_CONFIGS=`python3-config --includes`
PYTHON_PATH=`python3-config --prefix`
LIB_CONFIGS=`python3-config --libs`


g++ -shared -fPIC $INCLUDE_CONFIGS -L$PYTHON_PATH/lib $LIB_CONFIGS  DoubleArrayTrie.cpp dat_wrap.cxx -o _dat.so
