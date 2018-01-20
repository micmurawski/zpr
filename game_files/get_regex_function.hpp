#ifndef GET_REGEX_FUNCTION_HPP
#define GET_REGEX_FUNCTION_HPP

#include <string>
#include <boost/regex.hpp>
	
inline std::string getRegex(const std::string& request,const std::string& pattern){
        boost::regex rgxIp(pattern);
        boost::smatch matchIp;
        if(boost::regex_search(request,matchIp ,rgxIp)){
            return matchIp[0];
        }else{
            return "";
        }
}

inline std::string getJoin(const std::string& request){
  boost::regex rgxPort("(?<=<join>)(.*)(?=</join>)");
  boost::smatch matchPort;
  if(boost::regex_search(request,matchPort ,rgxPort)){
    return matchPort[0];
  }else{
    return "";
  }
}

inline std::string getCreate(const std::string& request){
  boost::regex rgxPort("(?<=<create>)(.*)(?=</create>)");
  boost::smatch matchPort;
  if(boost::regex_search(request,matchPort ,rgxPort)){
    return matchPort[0];
  }else{
    return "";
  }
}

inline std::string getIp(const std::string& request){
  boost::regex rgxIp("(?<=<ip>)(.*)(?=</ip>)");
  boost::smatch matchIp;
if(boost::regex_search(request,matchIp ,rgxIp)){
    return matchIp[0];
  }else{
    return "";
  }
}

inline std::string getPort(const std::string& request){
  boost::regex rgxPort("(?<=<port>)(.*)(?=</port>)");
  boost::smatch matchPort;
  if(boost::regex_search(request,matchPort ,rgxPort)){
    return matchPort[0];
  }else{
    return "";
  }
  
}

inline std::string getName(const std::string& request){
  boost::regex rgxIp("(?<=<name>)(.*)(?=</name>)");
  boost::smatch matchIp;
if(boost::regex_search(request,matchIp ,rgxIp)){
    return matchIp[0];
  }else{
    return "";
  }
}


#endif // GET_REGEX_FUNCTION_HPP
