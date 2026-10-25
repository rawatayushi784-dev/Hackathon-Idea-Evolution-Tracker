#include "Improvement.hpp"
#include <iostream>
#include <limits>

using namespace std;

// Display the details of an idea
void displayIdea(const Idea& idea)
{
    cout << "\nIdea ID: " << idea.id << "\n";
    cout << "Title: " << idea.title << "\n";
    cout << "Problem: " << idea.problem << "\n";
    cout << "Target Users: " << idea.targetUsers << "\n";
    cout << "Features: " << idea.features << "\n";
}

// Improve an existing idea
void improveIdea(vector<Idea>& ideas,
                 vector<Revision>& history)
{
    if (ideas.empty())
    {
        cout << "\nNo ideas available to improve.\n";
        return;
    }

    int id;

    cout << "\nEnter the Idea ID to improve: ";

    if (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. Please enter a number.\n";
        return;
    }

    // Find the selected idea
    int index = -1;

    for (int i = 0; i < static_cast<int>(ideas.size()); i++)
    {
        if (ideas[i].id == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Idea ID not found.\n";
        return;
    }

    cout << "\nCurrent Idea Details:";
    displayIdea(ideas[index]);

    cout << "\nWhat would you like to improve?\n";
    cout << "1. Title\n";
    cout << "2. Problem\n";
    cout << "3. Target Users\n";
    cout << "4. Features\n";
    cout << "Enter your choice: ";

    int choice;

    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice.\n";
        return;
    }

    if (choice < 1 || choice > 4)
    {
        cout << "Please select a choice from 1 to 4.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Save the old version before modifying the idea
    Revision revision;

    revision.ideaId = ideas[index].id;
    revision.oldVersion = ideas[index];
    revision.changeNote = "Updated field: ";

    string newValue;

    switch (choice)
    {
        case 1:
            cout << "Enter the improved title: ";
            getline(cin, newValue);
            revision.changeNote += "Title";
            ideas[index].title = newValue;
            break;

        case 2:
            cout << "Enter the improved problem description: ";
            getline(cin, newValue);
            revision.changeNote += "Problem";
            ideas[index].problem = newValue;
            break;

        case 3:
            cout << "Enter the updated target users: ";
            getline(cin, newValue);
            revision.changeNote += "Target Users";
            ideas[index].targetUsers = newValue;
            break;

        case 4:
            cout << "Enter the improved features: ";
            getline(cin, newValue);
            revision.changeNote += "Features";
            ideas[index].features = newValue;
            break;
    }

    // Assign a revision number
    revision.versionNumber = 1;

    for (const Revision& oldRevision : history)
    {
        if (oldRevision.ideaId == id)
        {
            revision.versionNumber++;
        }
    }

    // Store the previous version in history
    history.push_back(revision);

    cout << "\nIdea updated successfully!\n";
    cout << "Previous version saved in history.\n";

    displayIdea(ideas[index]);
}

// Display the revision history of an idea
void showImprovementHistory(const vector<Idea>& ideas,
                            const vector<Revision>& history)
{
    int id;

    cout << "\nEnter the Idea ID to view its history: ";

    if (!(cin >> id))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. Please enter a number.\n";
        return;
    }

    bool ideaExists = false;

    for (const Idea& idea : ideas)
    {
        if (idea.id == id)
        {
            ideaExists = true;
            break;
        }
    }

    if (!ideaExists)
    {
        cout << "Idea ID not found.\n";
        return;
    }

    bool historyFound = false;

    cout << "\n========== IMPROVEMENT HISTORY ==========\n";

    for (const Revision& revision : history)
    {
        if (revision.ideaId == id)
        {
            cout << "\nPrevious Version "
                 << revision.versionNumber << "\n";

            cout << "Change: " << revision.changeNote << "\n";

            displayIdea(revision.oldVersion);

            historyFound = true;
        }
    }

    if (!historyFound)
    {
        cout << "\nNo previous revisions found for this idea.\n";
    }

    // Display the latest version
    for (const Idea& idea : ideas)
    {
        if (idea.id == id)
        {
            cout << "\n========== CURRENT VERSION ==========\n";
            displayIdea(idea);
            break;
        }
    }
}