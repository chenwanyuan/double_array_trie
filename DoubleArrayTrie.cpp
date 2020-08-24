/*
 * DoubleArrayTrie.cpp
 *
 *  Created on: 2017年6月21日
 *      Author: chenwanyuan
 */
#include"DoubleArrayTrie.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include<map>
#include<string>
#include<vector>
#include"utils.h"


int DoubleArrayTrie::mapbuild(const map<string,string>& key2value)
{
    vector< const char * > keys;
    clear();
    for(map<string,string>::const_iterator it = key2value.begin();it != key2value.end();++it){
            keys.push_back(it->first.c_str());
            this->values.push_back(it->second);
    }

    int a = dat.build(keys.size(), &(keys[0]),0,0);
    return 0;
}



int DoubleArrayTrie::build(const string& file_path,const string& s_split)
{
	map<string,string> key2value;
	vector< const char * > keys;
	std::ifstream fp(file_path.c_str());
	std::string s;

	while(std::getline(fp, s)){
		vector<string> arr;
		//std::cout<<s<<std::endl;
		split(s,s_split,arr);
		if(arr.size() != 2){
			continue;
		}

		string key = arr[0];
		string value = arr[1];
		//std::cout<<key<<"  "<<value<<std::endl;
		if(key.empty() || value.empty()){
			continue;
		}
		key2value.insert(std::make_pair(key, value));
	}
	for(map<string,string>::iterator it = key2value.begin();it != key2value.end();++it){
		keys.push_back(it->first.c_str());
		this->values.push_back(it->second);
	}

	int a = dat.build(keys.size(), &(keys[0]),0,0);
	return 0;
}

int DoubleArrayTrie::save(const string& file_path){
	string value_file = file_path +".value";
	this->dat.save(file_path.c_str());
	std::ofstream fp(value_file.c_str());
	for(int i = 0;i < this->values.size();++i){
		fp<<values[i]<<endl;
	}

	return 0;
}
int DoubleArrayTrie::open(const string& file_path){
	string value_file = file_path + ".value";
	this->values.clear();
	this->dat.open(file_path.c_str());
	std::ifstream fp(value_file.c_str());
	std::string s;
	while(std::getline(fp, s)){
		this->values.push_back(s);
	}
	return 0;
}
vector<pair<int,vector<pair<string,string> > > > DoubleArrayTrie::all_match(const string& word)
{
	vector<pair<int,vector<pair<string,string> > > > results;
	std::vector<DAT::result_pair_type> result_pairs(1024);
	for(int i = 0,len = 0;i < word.size();++len){
		const char * key = word.c_str() +i;
		int size = this->dat.commonPrefixSearch(key, &result_pairs[0], result_pairs.size());

		vector< pair<string,string> > searchs;
		for(int j = 0;j < size && j < result_pairs.size();++j){
			const DAT::result_pair_type& result_pair = result_pairs[j];
			string k = word.substr(i,result_pair.length);
			string v = this->values[result_pair.value];
			searchs.push_back(make_pair(k,v));
		}
		if(!searchs.empty()){
			results.push_back(std::make_pair(len,searchs) );
		}
		i+= UTFLEN((unsigned char)*key);

	}
	return results;
}
vector<pair<int,pair<string,string> > > DoubleArrayTrie::max_match(const string& word)
{
	vector<pair< int,pair<string,string> > > results;
	std::vector<DAT::result_pair_type> result_pairs(1024);
	for(int i = 0,len = 0;i < word.size();){
		const char* key = word.c_str() + i;
		size_t size = this->dat.commonPrefixSearch(key, &result_pairs[0], result_pairs.size());
		if (size == 0){
			i += UTFLEN((unsigned char)*key);
			++len;
		}else{
			size = std::min(size, result_pairs.size());

			const DAT::result_pair_type& result_pair = result_pairs[size - 1];
			size_t length = result_pair.length;

			string k = word.substr(i,length);
			string v = this->values[result_pair.value];

			results.push_back(std::make_pair(len,std::make_pair(k, v)) );
			//cout<<len<<" "<<k<<" "<<v<<endl;
			len += get_utf8_length(k.c_str());
			i += length;
		}

	}
	return results;

}


string DoubleArrayTrie::match_replace(const string & word)
{

	std::vector<DAT::result_pair_type> result_pairs(1024);

	vector<char> new_chars;
	new_chars.reserve(word.length() * 2);

	for(int i = 0,len = 0;i < word.size();){
		const char* key = word.c_str() + i;
		size_t size = this->dat.commonPrefixSearch(key, &result_pairs[0], result_pairs.size());
		if (size == 0){
		    int utf_len = UTFLEN((unsigned char)*key);
		    std::copy(key, key + utf_len, std::back_inserter(new_chars));

			i += utf_len;
		}else{
			size = std::min(size, result_pairs.size());

			const DAT::result_pair_type& result_pair = result_pairs[size - 1];
			size_t length = result_pair.length;

			string v = this->values[result_pair.value];
			std::copy(v.begin(), v.end(), std::back_inserter(new_chars));

			i += length;
		}
	}
	string new_string(new_chars.begin(), new_chars.end());
	return new_string;
}

