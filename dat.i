/* File: dat.i */
%module dat

%include "std_string.i"
%include "std_list.i"

%include "std_vector.i"
%include "std_pair.i"

%template(PSS)     std::pair<std::string,std::string>;
%template(PIPSS)   std::pair<int,std::pair<std::string ,std::string> >;
%template(VPSS)    std::vector<std::pair<std::string,std::string> >;
%template(PIVPSS)  std::pair<int,std::vector<std::pair<std::string ,std::string> > >;
%template(VPIPSS)  std::vector<std::pair<int,std::pair<std::string ,std::string > > >;
%template(VPIVPSS) std::vector<std::pair<int,std::vector<std::pair<std::string ,std::string> > > >;

%{
#include <string>
#include <utility>
#include <vector>
using namespace std;
#include "DoubleArrayTrie.h"
%}

%include "DoubleArrayTrie.h"