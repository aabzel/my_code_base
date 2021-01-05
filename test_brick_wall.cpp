#include "test_brick_wall.h"

#include <vector>

#include "brick_wall.h"
#include "uTests.h"

using namespace std;

bool test_brick_wall (void) {
	vector<vector<int>> wall2={ {6, 2, 2}, {1, 4, 4, 1}, {2, 5, 3}};
	EXPECT_EQ(2, leastBricks(wall2));
	vector<vector<int>> wall={ {1,2,2,1},
						        {3,1,2},
						        {1,3,2},
						        {2,4},
						        {3,1,2},
						        {1,3,1,1}};
	EXPECT_EQ(2, leastBricks(wall));

    return true;
}
