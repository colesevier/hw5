#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void build(string &current, int idx, map<char, int> &need, int remaining, 
    const set<string> &dict, set<string> &out)
{
    int n = current.size();
    if (idx == n)
    {
        if (remaining == 0 && dict.find(current) != dict.end())
        {
            out.insert(current);
        }
        return;
    }
    if (current[idx] != '-')
    {
        build(current, idx + 1, need, remaining, dict, out);
        return;
    }
    int blanks = 0;
    for (int i = idx; i < n; i++)
    {
        if (current[i] == '-') 
        {
            blanks++;
        }
    }

    if (remaining > blanks) 
        return;

    for (auto &p : need) 
    {
        char c = p.first;
        if (p.second > 0) 
        {
            current[idx] = c;
            p.second--;
            build(current, idx+1, need, remaining-1, dict, out);
            p.second++;
        }
    }
    
    if (remaining < blanks)
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            if (need.find(c) == need.end() || need[c] == 0)
            {
                current[idx] = c;
                build(current, idx + 1, need, remaining, dict, out);
            }
        }
    }
    current[idx] = '-';
}

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> out;
    string current = in;
    map<char, int> need;

    // find the number of each letter in floating
    for (char c : floating)
    {
        need[c] ++;
    }
    int remaining = floating.size();
    // am i allowed to use the auto iterator?
    for (char c: in)
    {
        if (c != '-' && need[c] > 0)
        {
            need[c]--;
            remaining--;

        }
    }
    // call helper
    build(current, 0, need, remaining, dict, out);
    return out;
}

// Define any helper functions here
// Don't I write the code above?

