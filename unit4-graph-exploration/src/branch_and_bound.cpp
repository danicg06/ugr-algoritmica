#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <unistd.h>

using namespace std;

// adds the corresponding selected item's size to the current box's filled
// capacity.
// updates the number of packages used and the capacity filled of the current.
void updatePackagesNumSum(int &packagedCapFilled, int &nPackagesUsed,
                          int capacity, int selectedItem)
{
    if (packagedCapFilled + selectedItem < capacity)
        // add the selected item's size.
        packagedCapFilled += selectedItem;
    else
    {
        packagedCapFilled = selectedItem;
        nPackagesUsed++;
    }

    // else, not update.
}

// BRANCH&BOUND
// Idea:      The idea is to found the exact order in which every item is placed
//            a box, minimizing the number of boxes packed without exceeding its
//            capacity.
//
//            A solution will be found whenever every item is packaged.
//
//            The selection strategy will be to pick the biggest element left,
//            as it is the most difficult to fit in a package.
//
//            Every item will have a respective lower and upper bound, so, if
//            the lower bound of the selected item is equal or bigger than the
//            global upper bound, then the picked one does not lead to the
//            minimizing solution and it is pruned of the hypothetical tree.
//
//            When the selected item's bounds fit in the previous bounds, every
//            of its hypothetical childs are checked if they are a final
//            solution:
//            if it is a solution, it is compared with the best found solution.
//            if it is not a final solution and its bounds fit, it will be taken
//            into account in the future as it can lead to a final solution;
//            then, the global upper bound is updated as the minimum of the
//            previous value and the item's upper bound.
//
//            If a new final solution is better than the best current solution,
//            it is considered as the new current best solution and the upper
//            bound is calculated as explained before. Otherwise, it is
//            backtracked.
//
//            Notice that, in this problem, a item's child is any of the other
//            items because every item is pickable whenever a item is selected.
//
//            As the main aim is to minimize, the initial upper boind will be
//            the number of items to package (a greedy solution would be more
//            efficient).
//
//            The items' lower bound will always be the number of packages
//            used at the moment.
//
//
// Input:     ·) items, integer vector of each item's size.
//            ·) bestSolution, current best solution.
//            ·) bestNPackagesUsed, number of packages used of the best solution.
//            ·) capacity, packages' capacity.
void branch_and_bound_bin(const vector<int> &items, vector<int> &bestSolution,
                          int bestNPackagesUsed, int capacity)
{
    // sorted items, so it is more efficient the selection strategy.
    vector<int> orderedItems = items;
    sort(orderedItems.begin(), orderedItems.end(), greater<int>());

    // current upper bound.
    int c = items.size();

    // current lower bound.
    int nPackagesUsed = 1;

    // current alive nodes.
    vector<int> aliveNodes;
    aliveNodes.push_back(orderedItems.at(0));

    // current items used, possible future solution.
    vector<int> solution;

    // items not used.
    vector<int> notUsedItems = orderedItems;

    // sum of the items size in the actual box. Set to 0 whenever a box is
    // filled or the next item does not fit in it, going for the next package.
    int packagedCapFilled = 0;

    while (!aliveNodes.empty())
    {
        // select next item.
        int selectedItem = aliveNodes.at(0);

        // delete the selected item from the alive nodes.
        aliveNodes.erase(aliveNodes.begin());

        // if the selected item does not fit the bounds, restore the modified
        // values.
        int prevCapFilled = packagedCapFilled;
        int prevNPackagesUsed = nPackagesUsed;

        // update the number of packages used and the package sum.
        updatePackagesNumSum(packagedCapFilled, nPackagesUsed, capacity, selectedItem);

        // check if the item's bound fit.
        if (nPackagesUsed < c)
        {
            solution.push_back(selectedItem);
            notUsedItems.erase(notUsedItems.begin());

            // for each child of the selected item (given items not in solution).
            for (auto it = notUsedItems.begin(); it != notUsedItems.end(); ++it)
            {

                // if the solution is not the best or the bounds do not fit,
                // restore the modified values.
                prevCapFilled = packagedCapFilled;
                prevNPackagesUsed = nPackagesUsed;

                updatePackagesNumSum(packagedCapFilled, nPackagesUsed, capacity, *it);

                // if only this child left, it is a final solution.
                if (aliveNodes.size() == 1)
                {

                    // check if the solution is the best.
                    if (nPackagesUsed < bestNPackagesUsed)
                    {
                        solution.push_back(*it);
                        notUsedItems.erase(it);

                        // new best solution.
                        bestSolution = solution;
                        bestNPackagesUsed = nPackagesUsed;

                        // update upper bound.
                        c = min(c, nPackagesUsed);
                    }
                    else // it is not the best solution, backtrack.
                    {
                        packagedCapFilled = prevCapFilled;
                        nPackagesUsed = prevNPackagesUsed;
                    }
                }
                else // if it not a final solution.
                {

                    if (nPackagesUsed < c)
                    {

                        // the current child is an alive node.
                        // Insert in the correct position to maintain decreasing order
                        aliveNodes.insert(aliveNodes.begin(), *it);

                        // update upper bound.
                        int CS = nPackagesUsed + notUsedItems.size();
                        c = min(c, CS);

                        solution.push_back(*it);
                        notUsedItems.erase(it);
                    }
                    else
                    {
                        packagedCapFilled = prevCapFilled;
                        nPackagesUsed = prevNPackagesUsed;
                    }
                }
            }
        }
        else // if its bounds do not fit, backtrack.
        {
            packagedCapFilled = prevCapFilled;
            nPackagesUsed = prevNPackagesUsed;
        }
    }
}

void printBinPacking(const vector<int> &solution)
{
    cout << "Items order: ";
    for (int i = 0; i < solution.size(); ++i)
    {
        cout << solution[i];
        if (i < solution.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}

bool runAutomated()
{
    if (isatty(fileno(stdin)))
    {
        cerr << "Auto mode: waiting data from stdin.\n";
        cerr << "You must redirect or write the data and terminate with EOF (Ctrl+D).\n";
        cerr << "Example: printf \"1\\n5\\n6 8 2 9 5\\n100\\n\" | ./branch&bound --auto\n";
    }
    int t;
    if (!(cin >> t))
    {
        cerr << "Use: ./branch&bound --auto <n_cases>\n";
        cerr << "Each case needs: <n_items> <item_sizes...> <capacity>\n";
        return false;
    }

    for (int caseIndex = 0; caseIndex < t; ++caseIndex)
    {
        int n;
        cin >> n;

        vector<int> items(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> items[i];
        }

        int capacity;
        cin >> capacity;

        vector<int> bestSolution;
        int bestNPackagesUsed = n;

        branch_and_bound_bin(items, bestSolution, bestNPackagesUsed, capacity);

        cout << endl;
        cout << "Case " << caseIndex + 1 << ":" << endl;
        cout << "Items: ";
        for (int i = 0; i < n; ++i)
        {
            cout << items[i];
            if (i < n - 1)
                cout << " ";
        }
        cout << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Packages used: " << bestNPackagesUsed << endl;

        if (!bestSolution.empty())
            printBinPacking(bestSolution);
    }

    return true;
}

void runExamples()
{
    cout << "Example 1: Simple bin packing problem" << endl;
    vector<int> items1 = {6, 5, 4, 3, 3, 2};
    vector<int> bestSolution1;
    int bestNPackagesUsed1 = items1.size();
    int capacity1 = 10;

    branch_and_bound_bin(items1, bestSolution1, bestNPackagesUsed1, capacity1);
    cout << "Items: 6 5 4 3 3 2" << endl;
    cout << "Capacity: " << capacity1 << endl;
    cout << "Packages used: " << bestNPackagesUsed1 << endl;
    if (!bestSolution1.empty())
        printBinPacking(bestSolution1);

    cout << endl
         << "Example 2: Another bin packing problem" << endl;
    vector<int> items2 = {7, 5, 9, 3, 4, 8, 2};
    vector<int> bestSolution2;
    int bestNPackagesUsed2 = items2.size();
    int capacity2 = 15;

    branch_and_bound_bin(items2, bestSolution2, bestNPackagesUsed2, capacity2);
    cout << "Items: 7 5 9 3 4 8 2" << endl;
    cout << "Capacity: " << capacity2 << endl;
    cout << "Packages used: " << bestNPackagesUsed2 << endl;
    if (!bestSolution2.empty())
        printBinPacking(bestSolution2);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cerr << "No arguments: hard-coded examples will be resolved.\n";
        runExamples();
        return 0;
    }

    string mode = argv[1];
    if (mode == "--auto" || mode == "--stdin")
    {
        return runAutomated() ? 0 : 1;
    }
    else if (mode == "--examples")
    {
        runExamples();
        return 0;
    }

    cerr << "Use: ./branch&bound [--examples | --auto]\n";
    cerr << "  --examples   Executes hard-coded bin packing problems.\n";
    cerr << "  --auto       Read bin packing problems from the input.\n";
    cerr << "Format: n_cases times <n_items> followed by item sizes and capacity.\n";

    return 1;
}
