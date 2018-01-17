#include "rom.h"

ROM::ROM(unsigned pages) : QObject(),
    pages(pages)
{    
    if (pages > maxPossiblePages)
    {
        std::cerr << "Number of pages of ROM may be less than 16. "
                  << pages << " is too much pages." << std::endl;
        std::string msg = "Number of pages of ROM may be less than 16";
        throw LogExceptions("Rom", msg);
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

unsigned int ROM::getValue(unsigned index) const
{
    if(index > pages * bytesPerPage)
    {
        std::string msg;
        msg.append("ROM memory has ").append(String::int2hex_string(pages * bytesPerPage))
                .append(" bytes, so it is possible to read cells from 0 to ")
                .append(std::to_string(pages * bytesPerPage - 1)).append(". ")
                .append(std::to_string(index)).append(" is wrong address");

        std::cerr << msg << std::endl;
        throw LogExceptions("Rom", msg);
    }

    return table[index];
}

unsigned int ROM::getPages() const
{
    return pages;
}

void ROM::setValue(unsigned addr, unsigned value)
{
    if(addr >= pages * bytesPerPage)
    {
        std::string msg;
        msg.append("ROM memory has ").append(String::int2hex_string(pages * bytesPerPage))
                .append(" bytes, so it is possible to write cells from 0 to ")
                .append(std::to_string(pages * bytesPerPage - 1)).append(". ")
                .append(std::to_string(addr))
                .append(" is wrong address and it will be ignore.");

        std::cerr << msg << std::endl;
        return;
    }

    if (value > 0xFF)
    {
        std::cerr << "ROM is 8 bit memory, so it can be a 1B value [0x0 - 0xFF] at a cell. "
             << value << " will be reduced to 8 byte." << std::endl;
    }

    table[addr] = value & 0xFF;

    emit onRomChanged(addr, value);
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

void ROM::flashRom(std::vector<unsigned> compiledCode)
{
    unsigned int addr = 0;

    for (int code : compiledCode)
    {
        setValue(addr, code & 0xFF);
        addr += 1;
    }

    //  We do not need here "emit onRomChanged();", because it is emitted in setValue method
}

void ROM::reset()
{
    for (unsigned i = 0; i < pages; i++)
    {
        setIO(i, 0);
    }
}

int ROM::getIO(unsigned page) const
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

void ROM::setIO(unsigned page, unsigned value)
{
    if (page > pages)
    {
        std::string msg;
        msg.append("There are ").append(std::to_string(pages)).append(" pages in ROM. ")
                .append(std::to_string(page)).append(" is bad value.");

        std::cerr << msg << std::endl;
        throw msg;
    }

    if (value > 0xF)
    {
        std::cerr << value << " is wrong value of ROM IO. ROM IO is 4 bit. Value will be reduced by 0xF mask."
                  << std::endl;
    }

    io[page] = value & 0xF;

    emit onRomIOChanged(page, value);
}
