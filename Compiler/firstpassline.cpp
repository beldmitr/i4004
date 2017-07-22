#include "firstpassline.h"

FirstPassLine::FirstPassLine(std::string line)
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
     * Check if the parsed line is empty now, so that means, that at the line was only a comment.
     * It isn't an error. Just finish a parsing
     */
    if (String::trimStrong(parsedLine).empty())
    {
        return;
    }

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
    if (!label.isEmpty())
    {
        std::string labelName = label.find; // This is our label in format ABC,
        labelName = labelName.substr(0, labelName.size() - 1);  // delete a comma from a label: ABC, => ABC

        /*
         * Everything after this label is a parameter of this label.
         * Which may be:
         * - a Number       ABC, 5
         * - a Constant,    ABC, PI314
         * - a MathExpr     ABC, PI314 + CCC - 9
         * - an Instruction ABC, FIM P0, 0xFF
         * But this parameter is parsed in Label class and on this phaze we don't worry about this
         */
        std::string labelParam = String::trimBeginEnd(label.suffix);

        std::shared_ptr<Label>(new Label(labelName, labelParam));

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

    if (!String::trim(command.find).empty() && CommandSet::isCommand(command.find))
    {
        unsigned length = CommandSet::getLength(command.find);
        unsigned pc = ObjectCode::getProgramCounter();

        ObjectCode::setProgramCounter(pc + length);
    }
}

FirstPassLine::~FirstPassLine()
{

}
