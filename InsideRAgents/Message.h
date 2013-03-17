#ifndef Message_h
#define Message_h

class Message { 
public:
// types
 int INFORM, QUERY;
  // time-stamp
long timeStamp;
char* msg;
//constructor 
Message();
Message (char* _msg, long time );
virtual ~ Message ();
// methods
int getTypeMessage (int type);
void setMessage (char* _msg);
char* getMessage() const;

protected:
// time-stamp
long timeStamp;
char* msg;

};
#endif
