#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <sstream>

using namespace std;

/// write a class MyClient inside a function init that gets argc and argv and all the processing happens in the class
bool opt_debug = false;

// get -i <ip address> and outputs ip address into integer (inside MyClient class as well or in global but also a class)
void convert_ip_address(string ip_address) {
    if (opt_debug) {
        cout << "Convert address " << ip_address << endl;
    }

    stringstream ss(ip_address);

    string token;
    vector<string> octets;
    char delimiter = '.';

    while (getline(ss, token, delimiter)) {
        octets.push_back(token);
    }

    cout << "String after splitting: " << endl;
    for (const auto& part : octets) {
        cout << part << endl;
    }

    vector<int> converted_octet;

    for (const auto &octet: octets) {
        converted_octet.push_back(stoi(octet));
        if (opt_debug) {
            cout << converted_octet[converted_octet.size() - 1] << endl;;
        }
    }

    // bitmaskl look into |
    int32_t result = 0;
    result = converted_octet[3];
    result |= converted_octet[2] << 8;
    result |= converted_octet[1] << 16;
    result |= converted_octet[0] << 24;

    cout << result << endl;

}

/// write function to do the reverse

int main(int argc, char** argv) {
    int opt;
    string input = "";
    /// instead of bool implement enum(typedef) or bitmask?
    bool opt_ip_address = false;
    
    opterr = 0;

    /// impemnt a way to handle many arguments (many of the same arguments seperated bt ,), -d no parametrs
    for(;;)
        {
        switch(getopt(argc, argv, "di:h")) // note the colon (:) to indicate that 'b' has a parameter and is not a switch
        {
            case 'd':
                opt_debug = true;
                continue;

            case 'i':
                convert_ip_address(optarg);
                continue;

            case '?':
            case 'h':
                default :
                printf("Help/Usage Example\n");
            break;

            case -1:
            break;
        }

        break;
        }


    return 0;
}