#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::string formatFunctions(const std::string& line, const std::string& className) {
    std::string returnType = line.substr(0, line.find(" "));
    std::string functionName = line.substr(line.find(" ") + 1, line.find("(") - line.find(" ") - 1);

    if (returnType.find(";") != std::string::npos) {
        returnType = "";
    }
    else {
        returnType += " ";
    }

    std::string returnLine = returnType + className + "::" + functionName + "() {\n\t// " +
                            functionName + " Implementation\n}\n";

    return returnLine;
}

int main() {
    std::string filename = "headertest.h";
    std::ifstream file(filename);
    std::string line;

    std::vector<std::string> lines;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    // We have all the lines, now let's clean up and start writing to the new file

    // Start by removing all spaces/tabs at the beginning of the line
    for (int i = 0; i < lines.size(); i++) {
        std::string currentLine = lines[i];
        int j = 0;
        while (currentLine[j] == ' ' || currentLine[j] == '\t'){
            j++;
        }
        lines[i] = currentLine.substr(j);
    }

    // Remove all empty lines, comments, includes, usings, and variables
    for (int i = lines.size(); i >= 0; i--) {
        std::string currentLine = lines[i];
        if (currentLine.find("#") == 0 || currentLine.find("using") == 0 || currentLine.find("/*") == 0 || currentLine.find("*") == 0
            || currentLine == "") {
            // std::cout << currentLine << std::endl;
            lines.erase(lines.begin() + i);
        }
    }

    // Grab the class name
    std::string className = lines[0].erase(0, 6).erase(lines[0].length()-2);

    lines.erase(lines.begin());

    // Add include to new file
    std::vector<std::string> newFileLines;
    newFileLines.push_back("#include \"" + filename + "\"" + "\n");

    // find all functions to format
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].find("()") != std::string::npos) {
            newFileLines.push_back(formatFunctions(lines[i], className));
        }
    }

    // Create the new file
    std::string newFilename = filename.erase(filename.length()-2) + ".cpp";
    std::ofstream newFile(newFilename);

    if (newFile.is_open()) {
        for (int i = 0; i < newFileLines.size(); i++) {
            newFile << newFileLines[i] << std::endl;
        }
        newFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    


    // print all current lines
    // for (int i = 0; i < lines.size(); i++) {
    //     std::cout << lines[i] << std::endl;
    // }

    return 0;
}