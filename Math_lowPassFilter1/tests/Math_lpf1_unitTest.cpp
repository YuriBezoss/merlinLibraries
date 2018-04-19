////
//// Created by Sparrow on 26.01.2016.
////
//
//
//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
//#include <Math_lowPassFilter1.h>
//#include <TestHelper.h>
//#include <csv.h>
//#include <StatisticalAnalysis.h>
//
//
//namespace {
//    using ::testing::Return;
//
//// The fixture for testing class Foo.
//    class Math_lpf1_simple_Test : public ::testing::Test {
//    protected:
//        // You can remove any or all of the following functions if its body
//        // is empty.
//
//        Math_lpf1_simple_Test() {
//            // You can do set-up work for each test here.
//
//        }
//
//        virtual ~Math_lpf1_simple_Test() {
//            // You can do clean-up work that doesn't throw exceptions here.
//        }
//
//        // If the constructor and destructor are not enough for setting up
//        // and cleaning up each test, you can define the following methods:
//
//        virtual void SetUp() {
//            lpf = new Math_lowPassFilter1<Vector3f>();
//            lpf->setcutoffFreq(20);
//            lpf->setsampleDTime(.01);
//            lpf->init();
//
//
//        }
//
//        virtual void TearDown() {
//           delete(lpf);
//        }
//
//        Math_lowPassFilter1<Vector3f> *lpf;
//
//
//        // Objects declared here can be used by all tests in the test case for Foo.
//    };
//
//
//// Tests that the Foo::Bar() method does Abc.
//    TEST_F(Math_lpf1_simple_Test, CheckLPF1) {
//        Vector3f in = Vector3f(1,2,3);
//        Vector3f out = lpf->applyFilter(in);
//
//        EXPECT_THAT(out, VectorNear(in,1e-6));
//
//        Vector3f in2 = in / 2.f;
//        out = lpf->applyFilter(in2);
//        Vector3f expectedResult = in*0.7215686;
//
//        EXPECT_THAT(out, VectorNear(expectedResult,1e-6));
//
//        lpf->reset();
//
//        out = lpf->applyFilter(in);
//
//        EXPECT_THAT(out, VectorNear(in,1e-6));
//    }
//
//    TEST_F(Math_lpf1_simple_Test, CheckLPFSeries) {
//       io::CSVReader<6> input(TestHelper::LOCAL_FILE(__FILE__,"series.csv"));
//
//        input.read_header(io::ignore_extra_column, "in1", "in2", "in3", "out1", "out2", "out3");
//        float in1, in2, in3, out1, out2, out3;
//        int i=0;
//        lpf->reset();
//        while(input.read_row(in1, in2, in3, out1, out2, out3)){
//
//            i++;
//            Vector3f out_calc = lpf->applyFilter(Vector3f(in1, in2, in3));
//            EXPECT_THAT(out_calc, VectorNear(Vector3f(out1, out2, out3),1e-6)) << "error" << i;
//        }
//
//    }
//
//}
//
//
//
//
//
//
//
//
//
//#ifndef DC_ALL_TESTS
//int main(int argc, char **argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}
//#endif
//
