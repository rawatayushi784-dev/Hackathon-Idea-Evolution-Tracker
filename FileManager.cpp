#include "FileManager.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Save ideas and revision history to text files
void saveData(const vector<Idea>& ideas,
              const vector<Revision>& history)
{
    // Save all current ideas
    ofstream ideaFile("ideas.txt");

    if (!ideaFile)
    {
        cout << "Error: Could not open ideas.txt for saving.\n";
        return;
    }

    for (const Idea& idea : ideas)
    {
        ideaFile << idea.id << " "
                 << quoted(idea.title) << " "
                 << quoted(idea.problem) << " "
                 << quoted(idea.targetUsers) << " "
                 << quoted(idea.features) << "\n";
    }

    ideaFile.close();

    if (!ideaFile)
    {
        cout << "Error while writing ideas.txt.\n";
        return;
    }

    // Save previous versions of ideas
    ofstream historyFile("history.txt");

    if (!historyFile)
    {
        cout << "Ideas saved, but history.txt could not be opened.\n";
        return;
    }

    for (const Revision& revision : history)
    {
        const Idea& old = revision.oldVersion;

        historyFile << revision.ideaId << " "
                    << revision.versionNumber << " "
                    << quoted(revision.changeNote) << " "
                    << old.id << " "
                    << quoted(old.title) << " "
                    << quoted(old.problem) << " "
                    << quoted(old.targetUsers) << " "
                    << quoted(old.features) << "\n";
    }

    historyFile.close();

    if (!historyFile)
    {
        cout << "Error while writing history.txt.\n";
        return;
    }

    cout << "\nIdeas and improvement history saved successfully.\n";
}

// Load ideas and revision history from text files
void loadData(vector<Idea>& ideas,
              vector<Revision>& history)
{
    // Load current ideas
    ifstream ideaFile("ideas.txt");

    if (ideaFile)
    {
        vector<Idea> loadedIdeas;
        Idea idea;

        while (ideaFile >> idea.id
                        >> quoted(idea.title)
                        >> quoted(idea.problem)
                        >> quoted(idea.targetUsers)
                        >> quoted(idea.features))
        {
            loadedIdeas.push_back(idea);
        }

        if (!ideaFile.eof())
        {
            cout << "Error: Invalid data in ideas.txt.\n";
            return;
        }

        ideas = loadedIdeas;
    }
    else
    {
        cout << "ideas.txt not found. Starting without saved ideas.\n";
    }

    // Load revision history
    ifstream historyFile("history.txt");

    if (historyFile)
    {
        vector<Revision> loadedHistory;
        Revision revision;

        while (historyFile >> revision.ideaId
                           >> revision.versionNumber
                           >> quoted(revision.changeNote)
                           >> revision.oldVersion.id
                           >> quoted(revision.oldVersion.title)
                           >> quoted(revision.oldVersion.problem)
                           >> quoted(revision.oldVersion.targetUsers)
                           >> quoted(revision.oldVersion.features))
        {
            // Ensure the old version has the correct idea ID
            revision.oldVersion.id = revision.ideaId;

            loadedHistory.push_back(revision);
        }

        if (!historyFile.eof())
        {
            cout << "Error: Invalid data in history.txt.\n";
            return;
        }

        history = loadedHistory;
    }
    else
    {
        cout << "history.txt not found. No saved history loaded.\n";
    }

    cout << "Data loading completed.\n";
}