#include <iostream>
#include <vector>
#include <limits>

const int INF = std::numeric_limits<int>::max();

struct RoutingTableEntry {
    int nextHop;
    int cost;

    RoutingTableEntry() : nextHop(-1), cost(INF) {}
};

void distanceVectorRouting(std::vector<std::vector<int>>& costMatrix, std::vector<std::vector<RoutingTableEntry>>& routingTable) {
    const int numRouters = costMatrix.size();

    routingTable.resize(numRouters, std::vector<RoutingTableEntry>(numRouters));

    for (int i = 0; i < numRouters; ++i) {
        for (int j = 0; j < numRouters; ++j) {
            if (i == j) {
                routingTable[i][j].nextHop = i;
                routingTable[i][j].cost = 0;
            } else if (costMatrix[i][j] != INF) {
                routingTable[i][j].nextHop = j;
                routingTable[i][j].cost = costMatrix[i][j];
            }
        }
    }

    for (int k = 0; k < numRouters; ++k) {
        for (int i = 0; i < numRouters; ++i) {
            for (int j = 0; j < numRouters; ++j) {
                if (routingTable[i][j].cost > routingTable[i][k].cost + routingTable[k][j].cost) {
                    routingTable[i][j].cost = routingTable[i][k].cost + routingTable[k][j].cost;
                    routingTable[i][j].nextHop = k;
                }
            }
        }
    }
}

int main() {
    int numRouters;

    std::cout << "Enter the number of routers: ";
    std::cin >> numRouters;

    std::vector<std::vector<int>> costMatrix(numRouters, std::vector<int>(numRouters, INF));

    std::cout << "Enter the cost matrix (use INF for no direct link):\n";
    for (int i = 0; i < numRouters; ++i) {
        for (int j = 0; j < numRouters; ++j) {
            std::cin >> costMatrix[i][j];
        }
    }

    std::vector<std::vector<RoutingTableEntry>> routingTable;
    distanceVectorRouting(costMatrix, routingTable);

    std::cout << "\nRouting Table:\n";
    for (int i = 0; i < numRouters; ++i) {
        for (int j = 0; j < numRouters; ++j) {
            if (i != j) {
                std::cout << "Router " << i << " to Router " << j << " via Router " << routingTable[i][j].nextHop
                          << " Cost: " << routingTable[i][j].cost << '\n';
            }
        }
    }

    return 0;
}