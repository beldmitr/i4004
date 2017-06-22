#include "pram.h"

PRAM::PRAM(unsigned int pages) : QObject(),
    pages(pages)
{
    if (pages > maxPossiblePages)
    {
        std::cerr << "Number of pages of Program RAM may be less than " << maxPossiblePages
                  << ". " << pages << " is too much pages." << std::endl;
        throw "Too big number of pages of Program RAM";
    }

    for (unsigned int i = 0; i < pages * bytesPerPage; i++)
    {
        table.push_back(0);
    }
}

PRAM::~PRAM()
{
    // delete or finalize here something
}

int PRAM::getValue(unsigned int index) const
{
    if(index > pages * bytesPerPage)
    {
        std::string msg;
        msg.append("Program RAM memory has ").append(std::to_string(pages * bytesPerPage))
                .append(" bytes, so it is possible to read cells from 0 to ")
                .append(std::to_string(pages * bytesPerPage - 1)).append(". ")
                .append(std::to_string(index)).append(" is wrong address");

        std::cerr << msg << std::endl;
        throw msg;
    }

    return table[index];
}

void PRAM::setValue(unsigned int index, int value)
{
    if(index >= pages * bytesPerPage)
    {
        std::string msg;
        msg.append("Program RAM memory has ").append(std::to_string(pages * bytesPerPage))
                .append(" bytes, so it is possible to write cells from 0 to ")
                .append(std::to_string(pages * bytesPerPage - 1)).append(". ")
                .append(std::to_string(index))
                .append(" is wrong address and it will be ignore.");

        std::cerr << msg << std::endl;
        return;
    }

    if (value < 0 || value > 0xFF)
    {
        std::cerr << "Program RAM is 8 byte memory, so it can be a 1B value [0x0 - 0xFF] at a cell. "
             << value << " will be reduced to 8 byte." << std::endl;
    }

    /*
     * There are 5 instructons, which are 2 byte long:
     * JCN - 0001 CCCC AAAA AAAA
     * FIM - 0010 RRR0 DDDD DDDD
     * JUN - 0100 AAAA AAAA AAAA
     * JMS - 0101 AAAA AAAA AAAA
     * ISZ - 0111 RRRR AAAA AAAA
     *
     * If there is a 2 byte instruction, but there is only 1 byte free space in a page,
     * then this free byte space is written by NOP (0x00) instruction and the whole
     * 2 byte instruction is written to the next page.
     * So 2 byte instruction can't be cutted between 2 pages, when the first byte of instruction
     * is in a one page and the next byte of instruction is at the next page.
     */
    table[index] = value & 0xFF; // FIXME: explaining is close above

    emit onPramChanged(index, value);
}

void PRAM::clearPRam()
{
    /*
     * Do not use table.clear(), because we need there cells with 0 values, but clear() function
     * delete every data and every cell in the table.
     * So It is better for us to assigne to a zero every value in table,
     * but do not delete that cells from the memory table
     */
    for (unsigned int i = 0; i < pages * bytesPerPage; i++)
    {
        table[i] = 0;
    }

    emit onPramClear();
}
