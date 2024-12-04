#ifndef MUSICNOTEREADER_H
#define MUSICNOTEREADER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class MusicNoteReader {
public:
    MusicNoteReader(const std::string& filename);

    std::vector<float> readNumbers();

private:
    std::string filename;
};

#endif 
