#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> // for dynamic memory

// #inlude <stdint.h> for standarized types like uint8_t int32_t etc
// standarized types are used to make sure that each type will be exactly the
// same on every system normal int might be 16 bits on one system and 32 on
// anther

uint8_t a = 255;    // 8 bit unsigned integer
int32_t b = -32768; // 32 bit signed integer

#include <stddef.h> // for size_t
// size_t is gauranteed to be big enough to hold the size of any object in
// memory on given architecture for example 64 or 32 bits
size_t num = 1e18; // wont fit in 32 bit system but will fit in 64 bit system

#include <stdatomic.h> // atomic types libery
// atomic types - ATOMIC means something that cant be interupted paused or
// paratialy completed it is either fully completed or not at all
// it is used to eliminated data races compiler forces cpu to do instructions in
// strict and safe order

#include <threads.h> // mutlithreading library
atomic_int acnt;
_Atomic int acnt_same; // diffrent syntax but same type as atomic_int
int cnt;

int f(void *thr_data) {
  for (int n = 0; n < 1000; ++n) {
    ++cnt;
    ++acnt;
    // for this example, relaxed memory order is sufficient, e.g.
    // atomic_fetch_add_explicit(&acnt, 1, memory_order_relaxed);
  }
  return 0;
}

void test(void) {
  thrd_t thr[10];
  for (int n = 0; n < 10; ++n)
    thrd_create(&thr[n], f, NULL);
  for (int n = 0; n < 10; ++n)
    thrd_join(thr[n], NULL);

  printf("The atomic counter is %u\n", acnt); // exactly 10000 as intended
  printf("The non-atomic counter is %u\n",
         cnt); // 8765 due to two theards modyfing variable at the same time
}

// TYPEDEFS in C are just fo cleander syntax

typedef struct {
  int health;
  int stamina;
} Player;

Player p1; // Much cleaner than struct Player p1;

// typedefs in header files to hide syestem specyfic details

#ifdef _WIN32
typedef __int64 FileOffset;
#else
typedef long long FileOffset;
#endif

FileOffset pos = 0; // Works on both Windows and Linux correctly

// use typedefs when you are writing more complex longer types more then few
// times

// struct niunces pointer to struct actuall points to first element
struct Bad {
  char a;
  double b;
  char c;
}; // sizeof = 24 (on 64-bit)
struct Good {
  double b;
  char a;
  char c;
}; // sizeof = 16 (on 64-bit) //compiler inserts pading to if cpu boundreis

// unions and emums

typedef enum { EVENT_MOUSE_CLICK, EVENT_KEY_PRESS, EVENT_NONE } EventType;

// 2. The Tagged Union
typedef struct {
  EventType type; // The Tag
  union {
    struct {
      int x, y;
    } mouse; // 8 bytes
    struct {
      char keycode;
    } key; // 1 byte
  } data;
} Event;

// example of switching union and enum
void handle_event(Event e) {
  // 3. Use a switch statement to safely access the union
  switch (e.type) {
  case EVENT_MOUSE_CLICK:
    printf("Mouse clicked at (%d, %d)\n", e.data.mouse.x, e.data.mouse.y);
    break;
  case EVENT_KEY_PRESS:
    printf("Key pressed: %c\n", e.data.key.keycode);
    break;
  default:
    printf("Unknown event type.\n");
  }
}
// In a raw union, the compiler doesn't "remember" which member is active. The
// Tagged Union (also called a Sum Type or Variant) solves this by wrapping the
// union in a struct along with an enum that acts as a label.

// enums are basicly name integers compiler translates them to basic intgers
// since c23 you can force their type to avoid name colisions
enum Color : uint8_t { RED, GREEN, BLUE }; // C23 feature

// lifetime good example

int *foo(void) {
  int a = 17; // a has automatic storage duration
  return &a;
} // lifetime of a ends
int test2(void) {
  int *p = foo(); // p points to an object past lifetime ("dangling pointer")
  int n = *p;     // undefined behavior
}

// storage duration vs lifetime
// lifetime is the time where object is guarented to exist
// storage duration how long memory i reserved : automatic, static, thread etc

// volotile keyword tell compiler that varible can be changed at any time form
// outside code currnetly anaiysing compiler wont be able to aply lots of
// optimizattions for every time value is used it has to be retrived for memory
// not cpu register witch is redundent and slower

volatile int keep_running = 1;
// whitout volatile it can cause infinite loop
// this is refers to cpu interupts

void handle_interrupt() {
  keep_running = 0; // Triggered by a button press or timer
}

void infinite_loop() {
  while (keep_running) {
    // Do work...
  }
}
// AS IF RULE - allows any and all code transformations that do not change the
// observable behavior of the program.

// DATA RACES when two or moore theaads acces same memory location concurenty
// to prevent this you can either use atomic types or mutexes
// MUTEXES - mutual exclusion it acts as gatekeaper to ensure that only one
// thread can acces critical section

#include <threads.h> // multihteeading libery

mtx_t lock;
int shared_resource = 0;

int thread_func(void *arg) {
  mtx_lock(&lock);

  // START CRITICAL SECTION
  shared_resource++;
  // END CRITICAL SECTION

  mtx_unlock(&lock);
  return 0;
}

// storage class specifiers - auto, register, static, extern, thread_local
// STORAGE DURATION - how long memory is reserved for a variable
// LINKAGE - how names are shared across translation units (files)

// AUTO
void func() {
  int auto a = 10; // redundant auto means that varible is alocated in the stack
                   // when {} starts and ends when {} ends it is deallocated
                   // AUTO is derault for local variables
}

// REGISTER
void func2() { int register b = 20; }
// tell she comiler to store this in cpu register for
// faster access but modern compilers ignore this hint
// it is redundant and not recommended to use since modern compilers are good at
// optimizing variable storage

// STATIC
static void fun() { // static function is gonna only be visible in this file
                    // acts like a private function in other languages
  static int val = 10;
  // val is gona be remembered between function calls and only initialized once
}
static int local_to_file =
    42; // this variable is only visible in this file acts like a private
        // variable in other languages

// EXTERN
extern int someVal = 10; // tells the comiler that this variable is defined in
                         // another file and can be used here used in header
                         // files to share variables between files
// LOCAL_THREAD
thread_local int requests_handled =
    0; // gives every thread its own copy of this variable prior to c23
       // _Thread_local was used for this purpose

void *worker_thread(void *arg) {
  requests_handled++;
  // If you have 4 threads, you have 4 distinct 'requests_handled' variables.
  // Thread A modifying its copy does NOT affect Thread B's copy.
}

// RESTRICT KEYWORD tells the compiler that this valude will be the only way to
// access the data it points to this allows for better optimization since
// compiler can assume that no other pointer will modify the data since without
// it technicaly a and b and result cant point to same value and then everything
// will get buggy (IT IS EXCLUTSIVE FOR POINTERS ONLY AND IT DOSENT EXITS IN
// CPP)
void update_values(int *restrict a, int *restrict b, int *restrict result) {
  *result += *a;
  *result += *b;
}
// VOALTILE - tells the compiler that the value of this variable can change at
// any time so it should be featured from memory every time it is accessed and
// not cached in a register this is important for variables that can be modified
// by other threads or hardware interrupts

void example() {
  volatile int flag = 0; // without volative compiler might optimize this to an
                         // infinite loop since it thinks flag will never change
  while (!flag) {
    // do something
  }
}

// _GENERIC - allows you to write type-generic macros that can work with
// different (function oveloading in C)

void print_int(int x) { printf("Integer: %d\n", x); }
void print_float(float x) { printf("Float: %f\n", x); }
void print_string(char *x) { printf("String: %s\n", x); }

// The _Generic macro acts as a compile-time switch statement based on TYPE
#define print(X)                                                               \
  _Generic((X),                                                                \
      int: print_int,                                                          \
      float: print_float,                                                      \
      char *: print_string,                                                    \
      default: print_int)(X) // Notice the (X) at the end, which actually calls
                             // the selected function

int main() { return 0; }
