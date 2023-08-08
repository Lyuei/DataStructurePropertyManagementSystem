#pragma once

#include "LinkedList.hpp"
#include "Property.hpp"

void readAdmins(LinkedList& list);
void readManagers(LinkedList& list);
void readTenants(LinkedList& list);
void deleteTenantFromFile(const string& filename, const string& userIdToDelete);
void readProperties(PropertyLinkedList &propertyList);

