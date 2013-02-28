#ifndef _THR_THREAD_H
#define _THR_THREAD_H

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#include <signal.h>
#endif

namespace thr {

#ifdef WIN32
typedef HANDLE ThreadType;
#else
typedef pthread_t ThreadType;
#endif

class Thread {
public:
  Thread() { }
  virtual ~Thread();
 
  void start();

  virtual void execute() = 0;

  void join();

  void kill();

private:
  ThreadType __handle;

  Thread(const Thread&);
  void operator=(const Thread&);
};

} // thr

#endif
