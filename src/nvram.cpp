// SPDX-License-Identifier: Apache-2.0
/*
 * Copyright (C) 2020 sonal.santan@gmail.com
 *
 */

#include <iostream>
#include <string>
#include <regex>
#include <iostream>
#include <sstream>
#include <fstream>

#include <boost/iostreams/device/mapped_file.hpp>

int main(int argc, char *argv[])
{
    std::cout << "Using VFIO trace input file: " << argv[1] << std::endl;
    std::ifstream ins(argv[1]);

    std::cout << "Using output dump file: " << argv[2] << std::endl;
    boost::iostreams::mapped_file_params params(argv[2]);
    params.length = 0x1000000;
    params.new_file_size = params.length;
    params.flags = boost::iostreams::mapped_file::mapmode::readwrite;

    boost::iostreams::mapped_file_sink sink(params);

    const std::regex pieces_regex("^.+region2\\+(0x[0-9a-fA-F]+), (0x[0-9a-fA-F]+), ([0-9])\\)");

    // Go through each line and overlay the write operation on the dump file map so we capture the
    // memory contents as populated by the original driver
    unsigned base = 0;
    unsigned max = 0;
    for (std::string line; std::getline(ins, line); ) {
        std::smatch pieces_match;
        if (!std::regex_match(line, pieces_match, pieces_regex))
            continue;
        std::cout << line << '\n';
        if (pieces_match.size() != 4)
            continue;

        if (!base)
            base = std::stoi(pieces_match[1].str(), nullptr, 0);
        char *off = sink.data() + std::stoi(pieces_match[1].str(), nullptr, 0) - base;
        size_t size = std::stoi(pieces_match[3].str(), nullptr, 0);
        if (size == 1) {
            unsigned char val = (unsigned char)std::stoi(pieces_match[2].str(), nullptr, 0);
            unsigned char *data = reinterpret_cast<unsigned char*>(off);
            *data = val;
        }
        else if (size == 2) {
            unsigned short val = (unsigned short)std::stoi(pieces_match[2].str(), nullptr, 0);
            unsigned short *data = reinterpret_cast<unsigned short*>(off);
            *data = val;
        }
        else if (size == 4) {
            unsigned val = std::stoul(pieces_match[2].str(), nullptr, 0);
            unsigned *data = reinterpret_cast<unsigned *>(off);
            *data = val;
        }
        else if (size == 8) {
            unsigned long long val = std::stoull(pieces_match[2].str(), nullptr, 0);
            unsigned long long *data = reinterpret_cast<unsigned long long *>(off);
            *data = val;
        }
    }
    sink.close();
    ins.close();
    return 0;
}
