#include "nstring/nstring_ctors_gt.hpp"
#include "nstring/nstring_ops_gt.hpp"
#include "nstring/nstring_playground_gt.hpp"
#include "nstring/nstring_plus_ops_gt.hpp"
#include "nstring/nstring_reserve_gt.hpp"
#include "nstring/nstring_resize_gt.hpp"
#include "nstring/nstring_shrink_to_feet_gt.hpp"
#include "gtest/gtest.h"

int main( int argc, char** argv )
{
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
