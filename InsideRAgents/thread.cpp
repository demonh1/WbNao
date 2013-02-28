#include "thread.h"

namespace thr {

static void ThreadCallback(Thread* who) {
#ifndef WIN32
  // 
  int old_thread_type;
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old_thread_type);
#endif
  who->execute(); 
}

#ifdef WIN32

Thread::~Thread() {
  CloseHandle(__handle);
}

void Thread::start() {
  __handle = CreateThread(
    0, 0, 
    reinterpret_cast<LPTHREAD_START_ROUTINE>(ThreadCallback), this,
    0, 0
  );
}

void Thread::join() {
  WaitForSingleObject(__handle,  INFINITE);
}

void Thread::kill() {
  TerminateThread(__handle, 0);
}

#else

Thread::~Thread() {
}

extern "C"
typedef void *(*pthread_callback)(void *);

void Thread::start() {
  pthread_create(
    &__handle, 0, 
    reinterpret_cast<pthread_callback>(ThreadCallback), 
    this
  );
}

void Thread::join() {
  pthread_join(__handle, 0);
}

void Thread::kill() {
  pthread_cancel(__handle);
}

#endif

} // thr
