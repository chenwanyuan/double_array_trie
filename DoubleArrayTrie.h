/*
 * DoubleArrayTrie.h
 *
 *  Created on: 2017年6月21日
 *      Author: chenwanyuan
 */

#ifndef DOUBLEARRAYTRIE_H_
#define DOUBLEARRAYTRIE_H_
#include"dart.h"
#include<string>
#include<vector>

using namespace std;
typedef Darts::DoubleArray DAT;
class DoubleArrayTrie
{
public:
	int build(const string& file_path,const string& s_split = " ");
	int save(const string& file_path);
	int open(const string& file_path);
	vector<pair<int,vector<pair<string,string> > > > all_match(const string& word);
	vector<pair< int,pair<string,string> > > max_match(const string& word);
	string match_replace(const string & word);
private:
	vector<string> values;
	DAT dat;

};





#endif /* DOUBLEARRAYTRIE_H_ */
