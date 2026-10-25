#include <iostream>
#include <vector>
#include "IdeaTracker.hpp"
#include "Similarity.hpp"
#include "Improvement.hpp"
#include "FileManager.hpp"

using namespace std;

int main()
{
    IdeaTracker tracker;
    vector<Revision> history;

    // Load previously saved ideas and revision history
    loadData(tracker.getIdeas(), history);
    tracker.updateNextId();

    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "   HACKATHON IDEA EVOLUTION TRACKER\n";
        cout << "====================================\n";
        cout << "1. Add New Idea\n";
        cout << "2. Display All Ideas\n";
        cout << "3. Search Ideas\n";
        cout << "4. Find Similar Ideas\n";
        cout << "5. Improve an Existing Idea\n";
        cout << "6. View Improvement History\n";
        cout << "7. Save Data\n";
        cout << "8. Load Data\n";
        cout << "9. Exit\n";
        cout << "====================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        // Handle invalid input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
            case 1:
                tracker.addData();
                break;

            case 2:
                tracker.listIdeas();
                break;

            case 3:
                tracker.searchIdeas();
                break;

            case 4:
                findSimilarIdeas(tracker.getIdeas());
                break;

            case 5:
                improveIdea(tracker.getIdeas(), history);
                break;

            case 6:
                showImprovementHistory(tracker.getIdeas(), history);
                break;

            case 7:
                saveData(tracker.getIdeas(), history);
                break;

            case 8:
                loadData(tracker.getIdeas(), history);
                tracker.updateNextId();
                break;

            case 9:
                saveData(tracker.getIdeas(), history);
                cout << "Thank you for using Hackathon Idea Evolution Tracker!\n";
                break;

            default:
                cout << "Invalid choice! Please select 1 to 9.\n";
        }

    } while (choice != 9);

    return 0;
}