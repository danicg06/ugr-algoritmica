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

// nodes structure
struct node
{
    int selectedItem;          // selected item from the alive nodes list
    vector<int> boxesCapacity; // each of the opened boxes' capacity
    vector<int> notBoxedItems; // items not selected yet.
    int capacity;              // initial capacity of each package.
    int boxIndex = 0;          // box in which the selected item has been packed.

    int index = 0;      // index of the current node
    int prevIndex = -1; // index of the previous node
};

/**
 * @brief Updates the capacity of the opened boxes and opens a new one if needed,
 *        while saving the box index where the selected item has been introduced.
 *        It also removes the selected item from the notUsedItems vector.
 *
 * @param n node to update.
 * @param selectedItem selected item form the alive nodes list.
 */
void updateBoxesItems(node &n)
{
    // updates the notUsedItems vector.
    n.notBoxedItems.erase(find(n.notBoxedItems.begin(), n.notBoxedItems.end(), n.selectedItem));

    int i = 0;

    // iterates over every box and checks if the selected item fits in it.
    while (i < n.boxesCapacity.size())
    {

        // if the selected item fits in the box.
        if (n.selectedItem <= n.boxesCapacity[i])
        {
            n.boxesCapacity.at(i) -= n.selectedItem;
            n.boxIndex = i;
            return; // not executing the following code lines.
        }
        ++i;
    }

    // if this code is executed, then the selected item has not been boxed or
    // no package had been opened yet.
    // -> opens a new box and introduces the selected item.
    n.boxesCapacity.push_back(n.capacity - n.selectedItem);
    n.boxIndex = i;
}

/**
 * @brief Counts the number of boxes fully packaged.
 *
 * @param boxesCapacity vector of integers representing each box's capacity.
 * @param capacity the initial capacity of the box.
 * @return int
 */
int filledBoxes(const vector<int> &boxesCapacity)
{

    int nFilledBoxes = 0;
    for (auto it = boxesCapacity.begin(); it != boxesCapacity.end(); ++it)
    {
        if (*it == 0)
            ++nFilledBoxes;
    }

    return nFilledBoxes;
}

/**
 * @brief Calculates the lower bound of the given node:
 *        closed packages
 *        + (not used items total size + capacity left in the boxes)/capacity
 *
 * @param n proper node from which obtain the lower bound.
 * @return int
 */
int CI(const node &n)
{

    // number of packages closed.
    int closedPackages = filledBoxes(n.boxesCapacity);

    // sumatory of the not packaged items' size and the capacity not filled from
    // the opened boxes.
    int sum = 0;

    for (auto it = n.boxesCapacity.begin(); it != n.boxesCapacity.end(); ++it)
    {
        // if the box is not totally filled.
        if (*it != 0)
        {
            sum += *it;
        }
    }

    for (auto it = n.notBoxedItems.begin(); it != n.notBoxedItems.end(); ++it)
    {
        sum += *it;
    }

    return (closedPackages + sum / n.capacity);
}

/**
 * @brief Calculates the upper bound of the given node:
 *        closed packages + number of not used items.
 *
 * @param n proper node from which obtain the upper bound.
 * @return int
 */
int CS(const node &n)
{
    return (filledBoxes(n.boxesCapacity) + n.notBoxedItems.size());
}

/**
 * @brief Selection function for the next node by the Least Cost strategy.
 *        Picks the most promising node (the smallest CI) from the alive nodes
 *        list and REMOVES the selected item from the given vector.
 *
 * @param aliveNodes vector of the nodes from which the function will select the
 *                   next node.
 * @return node
 */
node select(vector<node> &aliveNodes)
{

    int bestNodeIndex = 0;

    for (int i = 0; i < aliveNodes.size(); ++i)
    {
        if (CI(aliveNodes[i]) < CI(aliveNodes[bestNodeIndex]))
            bestNodeIndex = i;
    }

    node selected = aliveNodes[bestNodeIndex]; // selected node

    aliveNodes.erase(aliveNodes.begin() + bestNodeIndex); // erase the selected node

    return selected;
}

/**
 * @brief BRANCH&BOUND
 * Idea:      The idea is to found the exact order in which every item is placed
 *            in a box, minimizing the number of boxes packed without exceeding
 *            their capacity.
 *
 *            A solution will be found whenever every item is packaged.
 *
 *            The selection strategy will be to pick the biggest element that
 *            has not been already selected.
 *
 *            Every item will have a respective lower and upper bound, so, if
 *            the lower bound of the selected item is equal or bigger than the
 *            global upper bound, then the picked item does not lead to the
 *            minimizing solution and it is pruned of the hypothetical tree.
 *
 *            When the selected item's bounds fit in the global bounds, every
 *            of its hypothetical childs (boxes' capacities with the packaging
 *            of each of the not boxed items) are checked if they are a final
 *            solution:
 *            if it is a solution, it is compared with the best current solution.
 *            if it is not a final solution and its bounds fit, it will be taken
 *            into account in the future as it can lead to a final solution;
 *            then, the global upper bound is updated as the minimum of the
 *            its value and the item's upper bound.
 *
 *            If a new final solution is better than the best current solution,
 *            it is considered as the new current best solution and the upper
 *            bound is calculated as explained before. Otherwise, it is
 *            backtracked.
 *
 *            As the main aim is to minimize, the initial upper boind will be
 *            the number of items to package (a greedy solution would be more
 *            efficient).
 *
 *            The items' lower bound will be calculated as:
 *            number of boxes +
 *            (lasting items' size + open boxes 'capacity) / initial capacity
 *
 * @param items vector of the given items to be boxed.
 * @param bestSolution last node of the best current solution.
 * @param capacity initial capacity of the packages.
 * @return node
 */
node branch_and_bound_bin(const vector<int> &items, int capacity, vector<node> &nodeHistory)
{
    // ensure that the node history list is empty.
    nodeHistory.clear();

    // indexes of the current and parent nodes.
    int currentIndex = 0;

    // initialize the best solution with the worst possible solution.
    node bestSolution;
    bestSolution.boxesCapacity.assign(items.size(), 0);

    // sort the given items, so it is easier to select the next item (the
    // biggest in the aliveNodes vector)
    vector<int> orderedItems = items;
    sort(orderedItems.begin(), orderedItems.end());

    // the root will be the biggest item.
    node root = {orderedItems.back(), {}, items, capacity};
    // preset indexes: 0 and -1.
    updateBoxesItems(root);
    nodeHistory.push_back(root);

    int C = CS(root);

    // vector of pickable nodes.
    vector<node> aliveNodes;
    aliveNodes.push_back(root);

    // current solution.
    vector<node> solution;

    // selected node in each iteration of the while loop.
    node selectedNode;

    while (!aliveNodes.empty())
    {

        selectedNode = select(aliveNodes); // selects and removes the next node
                                           // from the alive nodes list

        // the index of the selected, the future parent index for the children.
        int parentNodeIndex = selectedNode.index;

        // check if the item's bounds fit.
        if (CI(selectedNode) <= C)
        {

            // for each child of the selected item (given items not in solution).
            for (auto it = selectedNode.notBoxedItems.begin();
                 it != selectedNode.notBoxedItems.end(); ++it)
            {
                node childNode = {{*it}, {selectedNode.boxesCapacity}, {selectedNode.notBoxedItems}, capacity};

                // set the corresponding indexes.
                childNode.index = ++currentIndex;
                childNode.prevIndex = parentNodeIndex;

                // update the boxes capacity and the not selected items.
                updateBoxesItems(childNode);

                // add to the node history list.
                nodeHistory.push_back(childNode);

                // if there is no item left to pack, it is a solution.
                if (childNode.notBoxedItems.size() == 0)
                {

                    // check if the solution is the best.
                    if (childNode.boxesCapacity.size() < bestSolution.boxesCapacity.size())
                    {
                        bestSolution = childNode;
                    }
                }
                else // if it not a final solution.
                {

                    if (CI(childNode) < C)
                    {
                        // consider this node for a possible future solution.
                        aliveNodes.push_back(childNode);

                        // update upper global bound.
                        C = min(C, CS(childNode));

                    } // else, prune the child node.
                }
            }
        } // otherwise, prune the selected node.
    }

    return bestSolution;
}

void printBinPacking(const node &n, const vector<node> &nodeHistory)
{
    int index = n.index;
    vector<node> path;

    // Recollect the nodes path to the solution
    while (index >= 0 && index < nodeHistory.size())
    {
        path.push_back(nodeHistory[index]);
        index = nodeHistory[index].prevIndex;
    }

    cout << "--- Items packaging ---" << endl;
    for (int i = path.size() - 1; i >= 0; --i)
    {
        node actualNode = path[i];
        cout << "Item size: " << actualNode.selectedItem;

        cout << " -> Box: " << actualNode.boxIndex + 1
             << " (Remaining capacity in the box: "
             << actualNode.boxesCapacity[actualNode.boxIndex] << ")";
        cout << endl;
    }
    cout << "----------------------------------------------" << endl;
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

        vector<node> nodeHistory;

        node bestSolution = branch_and_bound_bin(items, capacity, nodeHistory);

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
        cout << "Packages used: " << bestSolution.boxesCapacity.size() << endl;

        // printBinPacking(bestSolution);
    }

    return true;
}

void runExamples()
{
    cout << "Example 1: Simple bin packing problem" << endl;
    vector<int> items1 = {6, 5, 4, 3, 3, 2};
    int capacity1 = 10;
    vector<node> nodeHistory1;

    node bestSolution1 = branch_and_bound_bin(items1, capacity1, nodeHistory1);
    cout << "Items: 6 5 4 3 3 2" << endl;
    cout << "Capacity: " << capacity1 << endl;
    cout << "Packages used: " << bestSolution1.boxesCapacity.size() << endl;
    printBinPacking(bestSolution1, nodeHistory1);

    cout << endl
         << "Example 2: Another bin packing problem" << endl;
    vector<int> items2 = {7, 5, 9, 3, 4, 8, 2};
    int capacity2 = 15;
    vector<node> nodeHistory2;

    node bestSolution2 = branch_and_bound_bin(items2, capacity2, nodeHistory2);
    cout << "Items: 7 5 9 3 4 8 2" << endl;
    cout << "Capacity: " << capacity2 << endl;
    cout << "Packages used: " << bestSolution2.boxesCapacity.size() << endl;
    printBinPacking(bestSolution2, nodeHistory2);
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
