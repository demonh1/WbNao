#ifndef Message_h
#define Message_h

class Message { 
public:

// types 
enum MessageType
{ 
	INFORM = 1,
	QUERY	
};
  
//constructor 
Message();
Message (char* _msg, long time, int _type );
 ~ Message ();
// methods
int getTypeMessage (int type);
void setMessage (char* _msg);
char* getMessage() const;

private:
// time-stamp
long timeStamp;
char* msg;
int type;

};
#endif
