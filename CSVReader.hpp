#pragma once

#include "LinkedList.hpp"

void readAdmins(LinkedList& list);
void readManagers(LinkedList& list);
void readTenants(LinkedList& list);
void deleteTenantFromFile(const string& filename, const string& userIdToDelete);
