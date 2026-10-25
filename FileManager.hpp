#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "IdeaTracker.hpp"
#include "Improvement.hpp"
#include <vector>

using namespace std;

// Save ideas and their revision history
void saveData(const vector<Idea>& ideas,
              const vector<Revision>& history);

// Load ideas and their revision history
void loadData(vector<Idea>& ideas,
              vector<Revision>& history);

#endif