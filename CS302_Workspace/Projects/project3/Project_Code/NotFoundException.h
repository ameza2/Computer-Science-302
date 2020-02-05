// Abraham Meza //
// CS 302 - Project 3 //

//--------------------------------------------------------------------
//
//  NotFoundException.h
// 
//  Class declaration for Not Found Exception (Error)
//
//--------------------------------------------------------------------

#ifndef NOT_FOUND_EXCEPTION
#define NOT_FOUND_EXCEPTION

// header files //

#include <iostream>
#include <memory>

// namespace declarations //

using namespace std;

class NotFoundException : public logic_error{ // class declaration w/ inheritance to logic_error (inherit virtual functions of logic_error)
    public:
        //------------------------------------------------------------ 
        // Public Methods Section.
        //------------------------------------------------------------

        NotFoundException(const string& msg = ""); // method NotFoundException()
}; // end of class declaration

NotFoundException::NotFoundException(const string& msg) : logic_error("Not Found Exception: " + msg){} // method NotFoundException() definition

#endif // NOT_FOUND_EXCEPTION_H