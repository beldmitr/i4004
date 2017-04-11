#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <vector>

#include "Instruction/operand.h"
#include "utils.h"

namespace Instruction {
    class Params
    {
    private:
        std::shared_ptr<Operand> left;
        std::shared_ptr<Operand> right;

    public:
        Params(const std::string& params);
        std::shared_ptr<Operand> getLeft() const;
        std::shared_ptr<Operand> getRight() const;
    };
}

#endif // PARAMS_H
