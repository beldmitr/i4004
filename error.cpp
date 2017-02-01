#include "error.h"

Error::Error(int line, string text, string command): line(line), text(text), command(command)
{

}

Error::~Error()
{
    // delete or finalize here something
}
