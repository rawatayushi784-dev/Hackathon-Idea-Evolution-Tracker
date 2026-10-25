#include "Similarity.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

// Convert text into lowercase
string normalizeText(string text)
{
    transform(text.begin(), text.end(), text.begin(),
              [](unsigned char ch)
              {
                  return static_cast<char>(tolower(ch));
              });

    return text;
}

// Extract keywords from text
unordered_set<string> getKeywords(const string& text)
{
    unordered_set<string> keywords;
    stringstream ss(normalizeText(text));
    string word;

    // Common words that are not useful for comparison
    unordered_set<string> stopWords = {
        "the", "is", "a", "an", "and", "or",
        "to", "for", "of", "in", "on", "with",
        "using", "that", "this", "it", "app"
    };

    while (ss >> word)
    {
        // Remove punctuation from the beginning and end
        while (!word.empty() &&
               ispunct(static_cast<unsigned char>(word.front())))
        {
            word.erase(word.begin());
        }

        while (!word.empty() &&
               ispunct(static_cast<unsigned char>(word.back())))
        {
            word.pop_back();
        }

        if (word.length() > 2 &&
            stopWords.find(word) == stopWords.end())
        {
            keywords.insert(word);
        }
    }

    return keywords;
}

// Combine the important fields of an idea
string combineIdea(const Idea& idea)
{
    return idea.title + " " +
           idea.problem + " " +
           idea.targetUsers + " " +
           idea.features;
}

// Calculate Jaccard similarity percentage
double calculateSimilarity(const Idea& first, const Idea& second)
{
    unordered_set<string> keywords1 =
        getKeywords(combineIdea(first));

    unordered_set<string> keywords2 =
        getKeywords(combineIdea(second));

    if (keywords1.empty() && keywords2.empty())
    {
        return 0.0;
    }

    int common = 0;

    for (const string& word : keywords1)
    {
        if (keywords2.find(word) != keywords2.end())
        {
            common++;
        }
    }

    int total = static_cast<int>(keywords1.size() +
                                 keywords2.size()) - common;

    return (static_cast<double>(common) / total) * 100.0;
}

// Find ideas similar to a selected idea
void findSimilarIdeas(const vector<Idea>& ideas)
{
    if (ideas.size() < 2)
    {
        cout << "\nAt least two ideas are required for comparison.\n";
        return;
    }

    int selectedId;

    cout << "\nEnter the ID of the idea to compare: ";
    cin >> selectedId;

    int selectedIndex = -1;

    for (int i = 0; i < static_cast<int>(ideas.size()); i++)
    {
        if (ideas[i].id == selectedId)
        {
            selectedIndex = i;
            break;
        }
    }

    if (selectedIndex == -1)
    {
        cout << "Idea ID not found.\n";
        return;
    }

    cout << "\nSimilar Ideas for: "
         << ideas[selectedIndex].title << "\n";

    cout << "----------------------------------------\n";

    bool found = false;

    for (const Idea& other : ideas)
    {
        if (other.id == selectedId)
        {
            continue;
        }

        double score =
            calculateSimilarity(ideas[selectedIndex], other);

        cout << fixed << setprecision(2);

        cout << "\nIdea ID: " << other.id;
        cout << "\nTitle: " << other.title;
        cout << "\nSimilarity: " << score << "%\n";

        if (score >= 30.0)
        {
            cout << "Status: Potentially similar idea\n";
        }
        else
        {
            cout << "Status: Low keyword similarity\n";
        }

        cout << "----------------------------------------\n";
        found = true;
    }

    if (!found)
    {
        cout << "No other ideas available.\n";
    }
}