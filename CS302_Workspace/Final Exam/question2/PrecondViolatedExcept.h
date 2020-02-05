// Abraham Meza //
// CS 302 - Project 3 //

//--------------------------------------------------------------------
//
//  PrecondViolateedExcept.h
// 
//  Class declaration for Precond Violated Except (Error)
//
//--------------------------------------------------------------------

#ifndef PRECOND_VIOLATED_EXCEPT
#define PRECOND_VIOLATED_EXCEPT

// header files //

#include <iostream>
#include <memory>

// namespace declarations //

using namespace std;

class PrecondViolatedExcept : public logic_error{ // class declaration w/ inheritance to logic_error (inherit virtual functions of logic_error)
    public:
        //------------------------------------------------------------ 
        // Public Methods Section.
        //------------------------------------------------------------

        PrecondViolatedExcept(const string& msg = ""); // method PrecondViolatedExcept()
}; // end of class declaration

PrecondViolatedExcept::PrecondViolatedExcept(const string& msg) : logic_error("Precondition Violated Exception: " + msg){} // method PrecondViolatedExcept() definition

#endif // PRECOND_VIOLATED_EXCEPT_H