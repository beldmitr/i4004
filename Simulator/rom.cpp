#include "rom.h"

ROM::ROM(unsigned int pages) : QObject(),
    pages(pages)
{    
    if (pages > maxPossiblePages)
    {
        std::cerr << "Number of pages of ROM may be less than 16. "
                  << pages << " is too much pages." << std::endl;
        throw "Number of pages of ROM may be less than 16";
    }

    for (unsigned int i = 0; i < pages * bytesPerPage; i++)
    {
        table.push_back(0);
    }

    for (unsigned int i = 0; i < pages; i++)
    {
        io.push_back(0);
    }

}

ROM::~ROM()
{
    // delete or finalize here something
}

unsigned int ROM::getValue(unsigned int index) const
{
    if(index > pages * bytesPerPage)
    {
        std::string msg;
        msg.append("ROM memory has ").append(std::to_string(pages * bytesPerPage))
                .append(" bytes, so it is possible to read cells from 0 to ")
                .append(std::to_string(pages * bytesPerPage - 1)).append(". ")
                .append(std::to_string(index)).append(" is wrong address");

        std::cerr << msg << std::endl;
        throw msg;
    }

    return table[index];
}

unsigned int ROM::getPages() const
{
    return pages;
}

void ROM::setValue(unsigned int index, int value)
{
    if(index >= pages * bytesPerPage)
    {
        std::string msg;
        msg.append("ROM memory has ").append(std::to_string(pages * bytesPerPage))
                .append(" bytes, so it is possible to write cells from 0 to ")
                .append(std::to_string(pages * bytesPerPage - 1)).append(". ")
                .append(std::to_string(index))
                .append(" is wrong address and it will be ignore.");

        std::cerr << msg << std::endl;
        return;
    }

    if (value < 0 || value > 0xFF)
    {
        std::cerr << "ROM is 8 byte memory, so it can be a 1B value [0x0 - 0xFF] at a cell. "
             << value << " will be reduced to 8 byte." << std::endl;
    }

    table[index] = value & 0xFF;

    emit onRomChanged(index, value);
}

void ROM::clearRom()
{
    /*
     * Do not use table.clear(), because we need there cells with 0 values, but clear() function
     * delete every data and every cell in the table.
     * So It is better for us to assigne to a zero every value in table,
     * but do not delete that cells from the memory table.
     *
     * The same is for Input/Output vector (io).
     */
    for (unsigned int i = 0; i < pages * bytesPerPage; i++)
    {
        table[i] = 0;
    }

    for (unsigned int i = 0; i < pages; i++)
    {
        io[i] = 0;
    }

    emit onRomCleared();
}

void ROM::flashRom(std::vector<unsigned int> compiledCode)
{
    unsigned int addr = 0;

    for (int code : compiledCode)
    {
        /*
         * If this byte is an instruction, then look for length of this instruction.
         * Because 2 byte instructions can't be cutted between 2 pages:
         * first byte at one page and the second byte at the next page.
         *
         * There are 5 instructons, which are 2 byte long:
         * JCN - 0001 CCCC AAAA AAAA
         * FIM - 0010 RRR0 DDDD DDDD
         * JUN - 0100 AAAA AAAA AAAA
         * JMS - 0101 AAAA AAAA AAAA
         * ISZ - 0111 RRRR AAAA AAAA
         *
         * So before to save them to ROM we should to check if the place of saveing has got enaugh bytes.
         * And the 2 byte long instruction won't be cutted by 2 pages after flashing it to ROM.
         *
         * So, we look if this is an instruction, look a length of it and if there is enough place.
         * If it is enaugh, just write it as is, if not enought, place a NOP (0x0) instruction
         * and write a 2 byte instruction at a new page.
         */

        if (code & 0xFF00) // if 2 byte long instruction
        {
            // if it is not enaugh place in a ROM page
            if ((bytesPerPage - addr % bytesPerPage) < 2)
            {
                setValue(addr, 0x0); // Write a NOP and this cause a step to a next page
                addr += 1;
            }
            setValue(addr, (code & 0xFF00) >> 8); // write hi byte
            addr += 1;
            setValue(addr, code & 0xFF); // write low byte
            addr += 1;
        }
        else // if 1 byte long instruction
        {
            setValue(addr, code & 0xFF); // write this 1 byte instruction
            addr += 1;
        }
    }

    //  We do not need here "emit onRomChanged();", because it is emitted in setValue method
}

int ROM::getIO(unsigned int page) const
{
    if (page > pages)
    {
        std::string msg;
        msg.append("There are ").append(std::to_string(pages)).append(" pages in ROM. ")
                .append(std::to_string(page)).append(" is bad value.");

        std::cerr << msg << std::endl;
        throw msg;
    }
    return io[page] & 0xF;
}

void ROM::setIO(unsigned int page, int value)
{
    if (page > pages)
    {
        std::string msg;
        msg.append("There are ").append(std::to_string(pages)).append(" pages in ROM. ")
                .append(std::to_string(page)).append(" is bad value.");

        std::cerr << msg << std::endl;
        throw msg;
    }

    if (value < 0 || value > 0xF)
    {
        std::cerr << value << " is wrong value of ROM IO. ROM IO is 4 bit. Value will be reduced by 0xF mask."
                  << std::endl;
    }

    io[page] = value & 0xF;

    emit onRomIOChanged(page, value);
}
