#ifndef GET_REGEX_FUNCTION_HPP
#define GET_REGEX_FUNCTION_HPP

#include <string>
#include <boost/regex.hpp>
	
inline std::string getRegex(std::string &request,std::string pattern){
        boost::regex rgxIp(pattern);
        boost::smatch matchIp;
        if(boost::regex_search(request,matchIp ,rgxIp)){
            return matchIp[0];
        }else{
            return "";
        }
}


#endif // GET_REGEX_FUNCTION_HPP
