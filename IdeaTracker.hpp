#ifndef IDEATRACKER_HPP
#define IDEATRACKER_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Stores the details of one hackathon idea
struct Idea
{
    int id;
    string title;
    string problem;
    string targetUsers;
    string features;
};

// Manages all hackathon ideas
class IdeaTracker
{
private:
    vector<Idea> ideas;
    int nextId;

public:
    IdeaTracker();

    void addData();
    void listIdeas();
    void searchIdeas();

    // Gives access to ideas for other modules
    const vector<Idea>& getIdeas() const;
    vector<Idea>& getIdeas();

    // Updates ID after loading saved ideas
    void updateNextId();
};

#endif