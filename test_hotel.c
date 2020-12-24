#include "test_hotel.h"
#include "hotel.h"

#include "uTests.h"

bool test_guests (void) {
    printf ("\n[d] %s()", __FUNCTION__);
    Guest_t guests_array1[5] = {{72, 80}, {9, 11}, {4, 7}, {1, 2}, {16, 17}};
    Guest_t guests_array3[7] = {{2, 80}, {16, 17}, {16, 17}, {5, 18}, {8, 13}, {1, 3}, {9, 11}};
    Guest_t guests_array2[5] = {{2, 80}, {16, 17}, {5, 7}, {1, 3}, {9, 11}};

    Guest_t guests_array6[6] = {{2, 28}, {6, 19}, {8, 15}, {9, 25}, {3, 4}, {2, 9}};

    //  EXPECT_EQ (4, max_guests (guests_array3, 7));
    // EXPECT_EQ (2, max_guests (guests_array2, 5));
    //    EXPECT_EQ (1, max_guests (guests_array1, 5));

    EXPECT_EQ (max_guests_vector_slshn (guests_array6, 6), max_guests (guests_array6, 6));
    // EXPECT_EQ (max_guests_vector_slshn (guests_array3, 7), max_guests (guests_array3, 7));
    // EXPECT_EQ (max_guests_vector_slshn (guests_array2, 5), max_guests (guests_array2, 5));
    // EXPECT_EQ (max_guests_vector_slshn (guests_array1, 5), max_guests (guests_array1, 5));

    printf ("\n[d] %s() end", __FUNCTION__);
    return true;
}
