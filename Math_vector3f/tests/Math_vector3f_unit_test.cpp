////
//// Created by Sparrow on 27.01.2016.
////
//
//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
//#include "../Math_vector3f.h"
//
//
//using ::testing::Return;
//
//TEST(Math_vector3f_test, CheckCreatinAndCloning) {
//    Vector3f v;
//
//    EXPECT_EQ(0, v.x);
//    EXPECT_EQ(0, v.y);
//    EXPECT_EQ(0, v.z);
//
//    Vector3f v1(1,2,3);
//
//    EXPECT_EQ(1, v1.x);
//    EXPECT_EQ(2, v1.y);
//    EXPECT_EQ(3, v1.z);
//
//    Vector3f v2 = *v1.clone();
//
//    EXPECT_EQ(1, v2.x);
//    EXPECT_EQ(2, v2.y);
//    EXPECT_EQ(3, v2.z);
//
//    EXPECT_EQ(1, v1.getAt(0));
//    EXPECT_EQ(2, v1.getAt(1));
//    EXPECT_EQ(3, v1.getAt(2));
//
//    v1.setAt(0,5);
//    v1.setAt(1,4);
//    v1.setAt(2,6);
//
//    EXPECT_EQ(5, v1.getAt(0));
//    EXPECT_EQ(4, v1.getAt(1));
//    EXPECT_EQ(6, v1.getAt(2));
//
//}
//
//TEST(Math_vector3f_test, CheckInfAndNAN) {
//    Vector3f v;
//
//    EXPECT_FALSE(v.isNan());
//    EXPECT_FALSE(v.isInf());
//
//    v.x = NAN;
//
//    EXPECT_TRUE(v.isNan());
//    EXPECT_FALSE(v.isInf());
//
//    v.y = INFINITY;
//
//    EXPECT_TRUE(v.isNan());
//    EXPECT_TRUE(v.isInf());
//}
//
//TEST(Math_vector3f_test, CheckComparisonOperators) {
//    Vector3f v1(1,2,3);
//    Vector3f v2(1,2,3);
//
//    EXPECT_TRUE((v1 == v2));
//    EXPECT_FALSE((v1 != v2));
//
//    v2(0,2,3);
//
//    EXPECT_TRUE((v1 != v2));
//    EXPECT_FALSE((v1 == v2));
//}
//
//TEST(Math_vector3f_test, CheckArithmeticOperators) {
//    Vector3f v1(1,2,3);
//    Vector3f v2(1,2,3);
//
//    Vector3f v = v1 + v2;
//
//    EXPECT_EQ(2, v.x);
//    EXPECT_EQ(4, v.y);
//    EXPECT_EQ(6, v.z);
//
//    v = v1 - v2;
//
//    EXPECT_EQ(0, v.x);
//    EXPECT_EQ(0, v.y);
//    EXPECT_EQ(0, v.z);
//
//    float a = 5;
//    v = v1*a;
//
//    EXPECT_EQ(5, v.x);
//    EXPECT_EQ(10, v.y);
//    EXPECT_EQ(15, v.z);
//
//    a = 10;
//    v = v1/a;
//
//    EXPECT_NEAR(0.1, v.x, 1e-6);
//    EXPECT_NEAR(0.2, v.y, 1e-6);
//    EXPECT_NEAR(0.3, v.z, 1e-6);
//
//    v = v1^v2;
//
//    EXPECT_EQ(1, v.x);
//    EXPECT_EQ(4, v.y);
//    EXPECT_EQ(9, v.z);
//
//    EXPECT_EQ(14, v1*v2);
//
//    v2(1,0,0);
//    v = v1%v2;
//
//    EXPECT_EQ(0, v.x);
//    EXPECT_EQ(3, v.y);
//    EXPECT_EQ(-2, v.z);
//}
//
//TEST(Math_vector3f_test, CheckVectorFunctions) {
//    Vector3f v(1,2,3);
//
//    EXPECT_EQ(14, v.normSquared());
//    EXPECT_NEAR(3.7417, v.norm(), 1e-4);
//
//    v.normalize();
//
//    EXPECT_NEAR(0.2673, v.x, 1e-4);
//    EXPECT_NEAR(0.5345, v.y, 1e-4);
//    EXPECT_NEAR(0.8018, v.z, 1e-4);
//
//    Vector3f v2 = v.normalized();
//
//    EXPECT_NEAR(0.2673, v2.x, 1e-4);
//    EXPECT_NEAR(0.5345, v2.y, 1e-4);
//    EXPECT_NEAR(0.8018, v2.z, 1e-4);
//
//    v2.zero();
//
//    EXPECT_EQ(0, v2.x);
//    EXPECT_EQ(0, v2.y);
//    EXPECT_EQ(0, v2.z);
//
//    v2.normalize();
//
//    EXPECT_EQ(0, v2.x);
//    EXPECT_EQ(0, v2.y);
//    EXPECT_EQ(0, v2.z);
//
//    Vector3f v3 = v2.normalized();
//
//    EXPECT_EQ(0, v3.x);
//    EXPECT_EQ(0, v3.y);
//    EXPECT_EQ(0, v3.z);
//
//    v2(1,0,0);
//    v3(1,0,0);
//
//    EXPECT_NEAR(0, v2.angle(v3), 1e-4);
//
//    v2(1,0,0);
//    v3(0,0,0);
//
//    EXPECT_NEAR(0, v2.angle(v3), 1e-4);
//
//    v2(0,0,0);
//    v3(1,0,0);
//
//    EXPECT_NEAR(0, v2.angle(v3), 1e-4);
//
//    v2(1,0,0);
//    v3(0,0,1);
//
//    EXPECT_NEAR(1.5708, v2.angle(v3), 1e-4);
//
//}
//
//
//#ifndef DC_ALL_TESTS
//int main(int argc, char **argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}
//#endif
