#include "IdeaTracker.hpp"
#include <algorithm>
#include <cctype>

using namespace std;

// Constructor
IdeaTracker::IdeaTracker()
{
    nextId = 1;
}

// Add a new hackathon idea
void IdeaTracker::addData()
{
    Idea idea;

    idea.id = nextId++;

    cin.ignore(10000, '\n');

    cout << "\nEnter idea title: ";
    getline(cin, idea.title);

    cout << "Enter the problem it solves: ";
    getline(cin, idea.problem);

    cout << "Enter target users: ";
    getline(cin, idea.targetUsers);

    cout << "Enter main features: ";
    getline(cin, idea.features);

    ideas.push_back(idea);

    cout << "\nIdea added successfully!\n";
    cout << "Your Idea ID is: " << idea.id << "\n";
}

// Display all saved ideas
void IdeaTracker::listIdeas()
{
    if (ideas.empty())
    {
        cout << "\nNo ideas available.\n";
        return;
    }

    cout << "\n========== ALL HACKATHON IDEAS ==========\n";

    for (const Idea& idea : ideas)
    {
        cout << "\nIdea ID: " << idea.id << "\n";
        cout << "Title: " << idea.title << "\n";
        cout << "Problem: " << idea.problem << "\n";
        cout << "Target Users: " << idea.targetUsers << "\n";
        cout << "Features: " << idea.features << "\n";
        cout << "-----------------------------------------\n";
    }
}

// Search ideas by title or problem
void IdeaTracker::searchIdeas()
{
    if (ideas.empty())
    {
        cout << "\nNo ideas available to search.\n";
        return;
    }

    string keyword;

    cin.ignore(10000, '\n');

    cout << "\nEnter a title or problem keyword: ";
    getline(cin, keyword);

    // Convert keyword to lowercase
    transform(keyword.begin(), keyword.end(), keyword.begin(),
              [](unsigned char ch)
              {
                  return static_cast<char>(tolower(ch));
              });

    bool found = false;

    for (const Idea& idea : ideas)
    {
        string searchableText = idea.title + " " + idea.problem;

        transform(searchableText.begin(), searchableText.end(),
                  searchableText.begin(),
                  [](unsigned char ch)
                  {
                      return static_cast<char>(tolower(ch));
                  });

        if (searchableText.find(keyword) != string::npos)
        {
            cout << "\nIdea Found!\n";
            cout << "ID: " << idea.id << "\n";
            cout << "Title: " << idea.title << "\n";
            cout << "Problem: " << idea.problem << "\n";
            cout << "Target Users: " << idea.targetUsers << "\n";
            cout << "Features: " << idea.features << "\n";

            found = true;
        }
    }

    if (!found)
    {
        cout << "\nNo matching idea found.\n";
    }
}

// Read-only access to ideas
const vector<Idea>& IdeaTracker::getIdeas() const
{
    return ideas;
}

// Editable access for improvement and file-management modules
vector<Idea>& IdeaTracker::getIdeas()
{
    return ideas;
}

// Set the next ID based on loaded ideas
void IdeaTracker::updateNextId()
{
    nextId = 1;

    for (const Idea& idea : ideas)
    {
        if (idea.id >= nextId)
        {
            nextId = idea.id + 1;
        }
    }
}