#include "process/interpreter.h"

#include "types/odouble.h"
#include "types/obool.h"
#include "types/onull.h"
#include "types/oexception.h"

interpreter::interpreter() 
{

}

interpreter::~interpreter() 
{

}

std::shared_ptr<object> interpreter::execute(std::shared_ptr<statement> &stmt)
{

}

void interpreter::visit_expressionstatement(expressionstatement *to_visit) 
{

}

void interpreter::visit_printstatement(printstatement *to_visit) 
{

}

