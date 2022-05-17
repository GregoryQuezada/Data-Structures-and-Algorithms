#include "frequency_table.h"

frequency_table::frequency_table(const std::string &file_name) {
	
    ifstream file;
    file.open(file_name);
    if (file.fail())
        throw runtime_error("File not found or cannot be opened");

    char readC;
    while (file.get(readC)) 
    {
        if (fmap.find(readC) != fmap.end())
        {
            fmap[readC] = fmap[readC] + 1;
        }
        else 
        {
            fmap[readC] = 1;
        }
    }
}

frequency_table::~frequency_table() {

}

int frequency_table::get_frequency(char c) const {
    if (fmap.find(c) == fmap.end())
    {
        return 0;
    }
    else 
    {
        return fmap.at(c);
    }
}