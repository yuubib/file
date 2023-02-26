# Destructor

+ when any object of class type is created, the compiler generates a call to a constructor of that type
+ when any object's lifetime ends, the compiler generates a call to the destructor of that type

# Copy constructor

The destructor is responsible for freeing resources tot avoid ***leaks***. The copy constructor is responsible for duplicating resources to avoid ***double frees***

# The Rule of Five

+ If your class directly manages some kind of resource (such as a new'ed pointer), then you almost certainly need to hand-write three special member functions:

+ + A ***destructor*** to free the resource

  + A ***copy constructor*** to copy the resource

  + A ***move constructor*** to transfer ownership of the resource

  + A ***copy assignment operator*** to free the left-hand resource and copy the right-hand one

  + A ***move assignment operator*** to free the left-hand resource and transfer ownership of the right-hand one

+ Use the copy-and-swap idiom to implement assignment.

# RAII and exception safety
"Resource Acquisition Is Initialization."Resource Freeing Is Destruction
Destructors help us write code that is robust against exceptions

+ C++ supports try/catch and throw
+ When an exception is thrown, the runtime looks "up the call stack" until it finds a suitable catch handler for the type of the exception being thrown. Assuming it finds one...
+ The runtime performs ***stack unwinding***. For every local scope between the throw and the catch handler, the runtime invokes the destructors of all local variables in that scope.
+ To avoid leaks, place all your ***cleanup*** code in ***destructors***.

# The Rule of Zero

+ lf your class does not directly manage any resource, but merely uses library components such as vector and string, then you should strive to write ***no*** special member functions.

  Default them all!

  + Let the compiler implicitly generate a defaulted destructor
  + Let the compiler generate the copy constructor
  + Let the compiler generate the copy assignment operator
  + Prefer Rule of Zero when possible

![Screenshot_20230226_115753](C:\Users\Administrator\Pictures\Screenshots\Screenshot_20230226_115753.png)