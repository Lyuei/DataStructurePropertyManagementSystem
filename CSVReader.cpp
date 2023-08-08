#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <limits>

#include "CSVReader.hpp"
#include "Property.hpp"

vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

string removeNonDigit(const string &input)
{
    string output;
    for (char c : input)
    {
        if (isdigit(c))
        {
            output.push_back(c);
        }
    }
    return output;
}

bool isNumber(const string &s)
{
    char *end = nullptr;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0' && val != numeric_limits<double>::infinity();
}

string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void readAdmins(LinkedList &list)
{
    ifstream file("csv_files/admin.csv");
    string line;
    getline(file, line); // discard header
    while (getline(file, line))
    {
        istringstream ss(line);
        string userId, username, password;
        getline(ss, userId, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        list.insert(new Admin(userId, username, password));
    }
}

void readManagers(LinkedList &list)
{
    ifstream file("csv_files/manager.csv");
    string line;
    getline(file, line); // discard header
    while (getline(file, line))
    {
        istringstream ss(line);
        string userId, username, password, status;
        getline(ss, userId, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, status, ',');
        list.insert(new Manager(userId, username, password, status == "1"));
    }
}

void readTenants(LinkedList &list)
{
    ifstream file("csv_files/tenant.csv");
    string line;
    getline(file, line); // discard header
    while (getline(file, line))
    {
        istringstream ss(line);
        string userId, username, password, name, ageStr, lastLoginStr;
        getline(ss, userId, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, lastLoginStr, ',');

        istringstream dateStream(lastLoginStr);
        tm lastLogin = {};
        dateStream >> get_time(&lastLogin, "%Y-%m-%d");

        list.insert(new Tenant(userId, username, password, name, stoi(ageStr), lastLogin));
    }
}

void deleteTenantFromFile(const string &filename, const string &userIdToDelete)
{
    ifstream inFile(filename);
    ofstream outFile("csv_files/temp.csv");

    string line;
    while (getline(inFile, line))
    {
        istringstream ss(line);
        string userId;
        getline(ss, userId, ','); // assuming userId is the first field in the CSV line

        if (userId != userIdToDelete)
        {
            outFile << line << "\n";
        }
    }

    inFile.close();
    outFile.close();

    remove(filename.c_str());
    rename("csv_files/temp.csv", filename.c_str());
}

void readProperties(PropertyLinkedList &propertyList)
{
    // Open the file
    ifstream inFile("csv_files/mudah-apartment-kl-selangor.csv");

    // Check if the file is open
    if (!inFile)
    {
        cerr << "Unable to open file mudah-apartment-kl-selangor.csv" << endl;
        throw runtime_error("File not found");
    }

    string line;
    getline(inFile, line); // Skip the first line (header)

    // Read line by line
    while (getline(inFile, line))
    {
        vector<string> row;
        string field;
        bool inQuotes = false;

        // Split the line into columns, handling fields that contain commas within double quotes
        for (char c : line)
        {
            if (c == '"')
            {
                inQuotes = !inQuotes; // Toggle flag
            }
            else if (c == ',' && !inQuotes)
            {
                // If comma is not inside quotes, end the field
                row.push_back(field);
                field = "";
            }
            else
            {
                // Otherwise, append the character to the current field
                field.push_back(c);
            }
        }
        // Push the last field to the vector
        row.push_back(field);

        // Convert and assign each column to the corresponding property attribute
        string ads_id = row[0];
        string prop_name = row[1].empty() ? "N/A" : row[1];
        int completion_year = isNumber(row[2]) ? static_cast<int>(stof(row[2])) : 0;
        int monthly_rent = isNumber(removeNonDigit(row[3])) ? stoi(removeNonDigit(row[3])) : 0;
        string location = row[4];
        string property_type = row[5];
        int rooms = 0;
        if (row[6] == "More than 10")
        {
            rooms = 11; // More than 10, not necessary 11
        }
        else if (isNumber(row[6]))
        {
            rooms = stoi(row[6]);
        }
        int parking = isNumber(row[7]) ? static_cast<int>(stof(row[7])) : 0;
        int bathroom = isNumber(row[8]) ? static_cast<int>(stof(row[8])) : 0;
        int size = isNumber(removeNonDigit(row[9])) ? stoi(removeNonDigit(row[9])) : 0;
        string furnished = row[10];
        vector<string> facilities = split(row[11], ',');
        for (string &facility : facilities)
        {
            facility = trim(facility);
        }

        vector<string> additional_facilities;
        if (!row[12].empty())
        {
            additional_facilities = split(row[12], ',');
            for (string &additional_facility : additional_facilities)
            {
                additional_facility = trim(additional_facility);
            }
        }
        string region = row[13];

        // Create a new Property object with these attributes
        Property *newProperty = new Property(ads_id, prop_name, completion_year, monthly_rent, location, property_type, rooms, parking, bathroom, size, furnished, facilities, additional_facilities, region);

        // Insert the new Property object into the linked list
        propertyList.insertAtEnd(newProperty);
    }

    // Close the file
    inFile.close();
}
