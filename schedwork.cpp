

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper(const AvailabilityMatrix& avail,
            const size_t maxShifts,
            DailySchedule& sched,
            vector<int> shiftsRecord,
            int currentDay,
            vector<vector<Worker_T>>
);

vector<vector<Worker_T>> combinations(int workers, int dailyNeeded);


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
    int days = avail.size();
    int workers = avail.front().size();
    vector<int> shifts;

    sched.resize(days);
    shifts.resize(workers);

    //All combinations of workers, i.e. total workers choose needed workers
    vector<vector<Worker_T>> combos = combinations(workers, dailyNeed);

    //Backtracking function
    return helper(avail, maxShifts, sched, shifts, 0, combos);
}


//Backtracking helper function
bool helper(const AvailabilityMatrix& avail,
            const size_t maxShifts,
            DailySchedule& sched,
            vector<int> shiftsRecord,
            int currentDay,
            vector<vector<Worker_T>> combos)
{

    if(currentDay == avail.size())                                                          //Reached the end
    {
        return true;
    }

    //Iterating through every worker combinations to see if it can fit on that day
    for(int i = 0; i < combos.size(); i++)
    {
        bool exceeded = false;
        vector<Worker_T> temp = combos[i];
        //Iterating through each worker
        for(int j = 0; j < temp.size(); j++)
        {
            //Member is unavaliable/maxshifts. Combination fails.
            if(shiftsRecord[temp[j]] == maxShifts || avail[currentDay][temp[j]] == 0)
            {
                exceeded = true;
                break;
            }
        }
        if(exceeded)
        {
            continue;
        }

        //Update shifts taken
        for(int j = 0; j < temp.size(); j++)
        {
            shiftsRecord[temp[j]]++;
        }

        sched.at(currentDay) = temp;

        //Next Backtracking iteration
        if(helper(avail, maxShifts, sched, shiftsRecord, currentDay + 1, combos))
            return true;

        //Backtracking fails, update shifts taken again
        for(int j = 0; j < temp.size(); j++)
        {
            shiftsRecord[temp[j]]--;
        }
    }

    return false;
}


//Function for finding all needed combination of workers, i.e. total workers choose needed workers
vector<vector<Worker_T>> combinations(int workers, int dailyNeed)
{

    vector<vector<Worker_T>> sol;
    vector<bool> v(workers);
    fill(v.end() - dailyNeed, v.end(), true);

    do {
        vector<Worker_T> temp;
        for (int i = 0; i < workers; ++i) {
            if (v[i]) {
                temp.push_back(i);
            }
        }
        sol.push_back(temp);
    } while (next_permutation(v.begin(), v.end()));
    return sol;
}
