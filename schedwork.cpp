#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include <functional>

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
// static bool backtrack(const AvailabilityMatrix &avail, size_t dailyNeed,
//                     size_t maxShifts, DailySchedule &sched, vector<size_t> &shiftUsed,
//                     size_t day, size_t slot);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t n = avail.size();
    size_t k = avail[0].size();
    // prepare schedule output
    sched.assign(n, vector<Worker_T>(dailyNeed, INVALID_ID));
    //track shifts
    vector<size_t> shiftsUsed(k, 0);
    function<bool(size_t, size_t)> solve = [&](size_t day, size_t slot) -> bool
    {
        if (day == n)
        {
            return true;
        }
        if (slot == dailyNeed)
        {
            return solve(day + 1, 0);
        }
        for (size_t w = 0; w < k; w ++)
        {
            // check availability
            if (!avail[day][w])
            {
                continue;
            }
            if (shiftsUsed[w] >= maxShifts)
            {
                continue;
            }
            if (find(sched[day].begin(), sched[day].begin() + slot, w) != sched[day].begin() + slot)
            {
                continue;
            }
            // if we get to this point choose this worker
            sched[day][slot] = w;
            shiftsUsed[w] ++;
            if (solve(day, slot + 1))
            {
                return true;
            } 

            // backtrack
            shiftsUsed[w]--;
            sched[day][slot] = INVALID_ID;
        }
        // return false otherwise
        return false;
    };
    // call the program
    return solve(0, 0);
}

