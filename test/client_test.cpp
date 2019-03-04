#include "ros/ros.h"
#include "calculator/AddTwoInts.h"
#include <cstdlib>
#include <gtest/gtest.h>
//#include <limits>


ros::ServiceClient client;

//normal case

TEST(TestSuite, normalTest)
{
  

  calculator::AddTwoInts srv;
  srv.request.a = 4;
  srv.request.b = 3;
  client.call(srv);

  EXPECT_EQ(7, srv.request.a + srv.request.b);
}


//a is a negative number

TEST(TestSuite, negative_a)
{
  

  calculator::AddTwoInts srv;
  srv.request.a = -4;
  srv.request.b = 3;
  client.call(srv);

  EXPECT_EQ(-1, srv.request.a + srv.request.b);
}

// b is a negtive number
TEST(TestSuite, negative_b)
{
  

  calculator::AddTwoInts srv;
  srv.request.a = 4;
  srv.request.b = -3;
  client.call(srv);
  
  EXPECT_EQ(1, srv.request.a + srv.request.b);
}

// a && b both negative number

TEST(TestSuite, negative_ab)
{
  

  calculator::AddTwoInts srv;
  srv.request.a = -4;
  srv.request.b = -3;
  client.call(srv);
  //std::cout << "sum:2222222222222222222222222222222222222222222222222222" << srv.response.sum << "\n";
  //ROS_INFO("Sum:!!!!!!!!!!!!!!!!!!!!!!!!!%ld", srv.response.sum);
  EXPECT_EQ(-7, srv.request.a + srv.request.b);
}

//overflow

TEST(TestSuite, max)
{
  
  calculator::AddTwoInts srv;
  srv.request.a = 0x7fffffffffffffff;
  srv.request.b = 3;
  client.call(srv);
  ASSERT_LT(0, srv.request.a + srv.request.b);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "client_test");
  ros::NodeHandle nh;
  client = nh.serviceClient<calculator::AddTwoInts>("add_two_ints");
  testing::InitGoogleTest(&argc, argv);
	
  return RUN_ALL_TESTS();
}
