#include <iostream>
#include <string>
#include <regex>
#include <boost/regex.hpp>

using namespace std;


int main(){
	boost::regex re("#");
	std::string ss;

	ss = "type#id1#id2";
  	boost::sregex_token_iterator i(ss.begin(), ss.end(), re, -1);
  	boost::sregex_token_iterator j;
  	while (i != j) {
     		std::cout << *i++ << endl;
	}
		std::cout << std::endl;
	
	/*
	string s= "id#ddddd#ddd#";	
	regex r("#");
	vector<string> splits;
	smatch m; // <-- need a match object
	regex_search(s, m, r); // <-- use it here to get the match
	int split_on = m.position(); // <-- use the match position
	string w1 = (s.substr(0, split_on));
	string w2 = s.substr(split_on + m.length()); // <-- also, skip the whole mat

	cout<<endl <<w1;
	cout<<endl <<w2;*/
	return 0;

}
