#include "pch.h"

using namespace FootballSimulation;

TEST(TestEnumBasedArray, InitializeArray) {

  
    EnumIndexedArray<double, uint8_t, PlayerAction> indexedArray(PlayerAction::EnumCount);

    EXPECT_EQ(indexedArray.size(), 3);
    indexedArray[PlayerAction::Keep] = .025;
    auto val = indexedArray[PlayerAction::Pass];
    EXPECT_EQ(val, 0.0);
    
}


TEST(TestEnumBasedArray, InitializeArray2D) {


    EnumIndexedArray2D<double, uint8_t, PlayerAction, FieldPosition> indexedArray(PlayerAction::EnumCount, FieldPosition::EnumCount);

    EXPECT_EQ(indexedArray.size(), 3);

    auto inner = indexedArray[PlayerAction::Keep];

    EXPECT_EQ(inner.size(), _uint8(FieldPosition::EnumCount));

    indexedArray[PlayerAction::Keep][FieldPosition::Center] = 0.18;
    auto chk = indexedArray[PlayerAction::Keep][FieldPosition::Center];
    EXPECT_EQ(chk, .18);   

    auto val = indexedArray[PlayerAction::Pass][FieldPosition::Center];
    EXPECT_EQ(val, 0.0);

}


TEST(TestEnumBasedArray, InitializeArray3D) {


    EnumIndexedArray3D<double, uint8_t, PlayerAction, FieldPosition, DistributionDirection> indexedArray(PlayerAction::EnumCount, FieldPosition::EnumCount, DistributionDirection::EnumCount);

    EXPECT_EQ(indexedArray.size(), 3);

    auto inner = indexedArray[PlayerAction::Keep];

    EXPECT_EQ(inner.size(), _uint8(FieldPosition::EnumCount));

    auto innerNext = inner[FieldPosition::Center];

    EXPECT_EQ(innerNext.size(), _uint8(DistributionDirection::EnumCount));
    
    indexedArray[PlayerAction::Keep][FieldPosition::Center][DistributionDirection::Backward] = 0.18;
    auto chk = indexedArray[PlayerAction::Keep][FieldPosition::Center][DistributionDirection::Backward];
    EXPECT_EQ(chk, .18);

    auto val = indexedArray[PlayerAction::Pass][FieldPosition::Center][DistributionDirection::Forward];
    EXPECT_EQ(val, 0.0);

}