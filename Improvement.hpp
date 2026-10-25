#ifndef IMPROVEMENT_HPP
#define IMPROVEMENT_HPP

#include "IdeaTracker.hpp"
#include <vector>
#include <string>

using namespace std;

// Stores an old version of an idea
struct Revision
{
    int ideaId;
    int versionNumber;
    Idea oldVersion;
    string changeNote;
};

// Updates an idea and saves its previous version
void improveIdea(vector<Idea>& ideas,
                 vector<Revision>& history);

// Displays previous versions of an idea
void showImprovementHistory(const vector<Idea>& ideas,
                            const vector<Revision>& history);

#endif

