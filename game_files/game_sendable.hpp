#ifndef GAME_SENDABLE_HPP
#define GAME_SENDABLE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

class GameSendable
{
public:

  enum { header_length = 6 };
  enum {type_length = 2};
  enum {max_body_length = 1000};
  
  GameSendable()
    : body_length_(0)
  {
  }

  const char* data() const
  {
    return data_;
  }

  char* data()
  {
    return data_;
  }

  std::size_t length() const
  {
    return header_length + body_length_;
  }

  const char* body() const
  {
    return data_ + header_length;
  }

  char* body()
  {
    return data_ + header_length;
  }

	void SetType(unsigned int type){
		type_=type;
		}
	int getType(){
		return type_;
		}
  std::size_t body_length() const
  {
    return body_length_;
  }

  void body_length(std::size_t new_length)
  {
    body_length_ = new_length;
  }

  bool decode_header()
  {
    char body_length[header_length - type_length + 1] = "";
    char type[type_length + 1]= "";
    std::strncat(body_length, data_, header_length);
    std::strncat(type, data_ + (header_length-type_length), type_length);
    body_length_ = std::atoi(body_length);
    type_ = std::atoi(type);
  }

  void encode_header()
  {
    char header[header_length + 1] = "";
    std::sprintf(header, "%4d%2d", static_cast<int>(body_length_), type_);
    std::memcpy(data_, header, header_length);
  }

protected:
  char data_[header_length + max_body_length];
  std::size_t body_length_;
  unsigned int type_;
};

#endif // GAME_SENDABLE_HPP
