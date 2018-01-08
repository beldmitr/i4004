#include "line.h"

Line::Line(std::string line)
{
    std::string parsedLine = line;

    /*
     * Parsing a COMMENT
     *
     * A comment marks with symbol slash (/).
     * Everything starts with this symbol is a comment and will be deleted by a compiler,
     * because in object code there is no need in describing.
     * And processor doesn't need comments for executing commands.
     */
    SearchResult comment = String::search(parsedLine, Compiler::commentRegex);
    if (!comment.isEmpty())
    {
        // we don't need a comment, so for next parsing we will take a line before a comment
        parsedLine = comment.prefix;
    }
    /*
     * Check if the parsed line is empty now, so that means, that this line considerred only the comment.
     * It isn't an error. Just finish a parsing
     */
    if (String::trimStrong(parsedLine).empty())
    {
        return;
    }


    /*
     * Deleting some aditional white symbols from the line, because we don't need them
     * So if there was a line: ABC,     FIM       P0,    5 / here is some comment
     * The line will be this one: ABC, FIM P0, 5
     * Comment was deleted before.
     */
    parsedLine = String::trimBeginEnd(parsedLine); // delete white symbols at the beginning and at the end
    parsedLine = String::trim(parsedLine);  // delete white symbols in the line


    /*
     * Parsing a PSEUDO instruction equal (=)
     *
     * In this case the line may be f.e. = 256
     * That means that we set a program counter to address 256
     * and a next instruction will be written on the address 256.
     * An instruction is "equal" (=), the parameter is 256.
     *
     * Parameter of the pseudo instruction may be:
     * - a Number   = 256
     * - a Constant = ABC
     * - a MathExpr = * + ABC + 5
     * where "star" (*) means the actual address
     */
    SearchResult pseudo = String::search(parsedLine, Compiler::pseudoRegex);
    if (!pseudo.isEmpty())
    {
        std::shared_ptr<Operand> operand = std::shared_ptr<Operand>(
                    new Operand(pseudo.suffix, CommandSet::OperandType::ADDRESS));

        unsigned int address = operand->getCode();

        ObjectCode::setProgramCounter(address);

        /*
         * There should be nothing before a pseudo,
         * because pseudo.find is "equal" (=) and pseudo.suffix is params
         */
        if (!String::trim(pseudo.prefix).empty())
        {
            std::string msg = "There is an unknown parameter " + pseudo.prefix
                    + " in line " + String::trim(line);
            throw CompilerException("Line", msg);
        }
        return;
    }


    /*
     * Parsing a LABEL
     *
     * A label has format "XYY,".
     * Where X is a letter, Y is letter and number and the length may by 3 and higher.
     *
     * So A3c, or bbbbbbb, or t123, are labels
     * BUT
     * ab, 3ff, c, g-g, ARE NOT LABELS
     */
    SearchResult label = String::search(parsedLine, Compiler::labelRegex);
    if (!String::trim(label.prefix).empty())
    {
        std::string msg = "There is an unknown parameter " + label.prefix
                + " in line " + String::trim(line);
        throw CompilerException("Line", msg);
    }

    if (!String::trim(label.find).empty())
    {
        parsedLine = label.suffix;

        // Commented return:
        /// return;
        // because it doesn't work with f.e. this line: end, JUN end
        // Probably this will cause some other bug
        // It is needed more time for testing
    }
    if (String::trim(parsedLine).empty())
    {
        return;
    }

    /*
     * Parsing an INSTRUCTION
     *
     * In this place, we think, that if there is no a comment or a pseudo or a label, this is an instruction.
     * Because it should be something of this
     */
    SearchResult command = String::search(parsedLine, Compiler::commandRegex); // find the command. FIM P0, 3 => FIM is command
    if (!command.isEmpty())
    {
        parsedLine = command.suffix;
    }

    // Here should be nothing to left before a command, f.e.: asdasd FIM p0, 5. What is "asdasd"?
    if (!String::trim(command.prefix).empty())
    {
        std::string msg = "There is an unknown parameter " + command.prefix
                + " in line " + String::trim(line);
        throw CompilerException("Line", msg);
    }

    SearchResult params = String::search(parsedLine, Compiler::paramsRegex);
    if (!params.isEmpty())
    {
        parsedLine = params.prefix + " " + params.suffix;   // there should be now nothing before params "P0, 3" and after it
    }

    // there should be nothing to left from the parsed line
    if (!String::trim(parsedLine).empty())
    {
        std::string msg = "There is an unknown parameter " + String::trimBeginEnd(parsedLine)
                + " in line " + String::trim(line) + ". Command is expected";
        throw CompilerException("Line", msg);
    }

    if (!String::trim(command.find).empty())
    {
        // create and execute the instruction
        std::shared_ptr<Instruction> instruction = std::shared_ptr<Instruction>(
                    new Instruction(String::trimBeginEnd(command.find),
                                    String::trimBeginEnd(params.find)));

        ObjectCode::write(instruction->getCode());
    }

    return;
}

