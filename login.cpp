#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

// Function to read data from a CSV file and store it in an unordered_map
void readCSV(const string& filename, unordered_map<string, pair<string, string>>& dataMap) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    string line, userId, username, password;
    while (getline(file, line)) {
        size_t commaPos1 = line.find(',');
        size_t commaPos2 = line.find(',', commaPos1 + 1);
        if (commaPos1 != string::npos && commaPos2 != string::npos) {
            userId = line.substr(0, commaPos1);
            username = line.substr(commaPos1 + 1, commaPos2 - commaPos1 - 1);
            password = line.substr(commaPos2 + 1);
            dataMap[username] = make_pair(userId, password);
        }
    }

    file.close();
}

int main() {
    // Initialize data maps for admin, manager, and tenant
    unordered_map<string, pair<string, string>> adminData;
    unordered_map<string, pair<string, string>> managerData;
    unordered_map<string, pair<string, string>> tenantData;

    // Read data from respective CSV files
    readCSV("admin.csv", adminData);
    readCSV("manager.csv", managerData);
    readCSV("tenant.csv", tenantData);

    // User login
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    // Check if the user is an admin, manager, or tenant and verify the credentials
    bool isLoggedIn = false;
    if (adminData.find(username) != adminData.end() && adminData[username].second == password) {
        cout << "Admin login successful!" << endl;
        isLoggedIn = true;
    } else if (managerData.find(username) != managerData.end() && managerData[username].second == password) {
        cout << "Manager login successful!" << endl;
        isLoggedIn = true;
    } else if (tenantData.find(username) != tenantData.end() && tenantData[username].second == password) {
        cout << "Tenant login successful!" << endl;
        isLoggedIn = true;
    } else {
        cout << "Invalid username or password. Login failed." << endl;
    }

    return 0;
}
