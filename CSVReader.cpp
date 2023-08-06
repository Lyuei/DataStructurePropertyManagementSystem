#include <fstream>
#include <sstream>
#include <iomanip>
#include "CSVReader.hpp"

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
        dateStream >> get_time(&lastLogin, "%d-%m-%Y");

        list.insert(new Tenant(userId, username, password, name, stoi(ageStr), lastLogin));
    }
}