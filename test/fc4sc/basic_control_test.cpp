/******************************************************************************

   Copyright 2003-2018 AMIQ Consulting s.r.l.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

******************************************************************************/
/******************************************************************************
   Original Authors: Teodor Vasilache and Dragos Dospinescu,
                     AMIQ Consulting s.r.l. (contributors@amiq.com)

               Date: 2018-Feb-20
******************************************************************************/

#include "fc4sc.hpp"
#include "gtest/gtest.h"
class cvg_control_test : public covergroup {
public:

  CG_CONS(cvg_control_test) {};

  wildcard_cov cov_xxx1{"xxx1"};
  wildcard_cov cov_xx1x{"xx1x"};
  wildcard_cov cov_x1xx{"x1xx"};

  wildcard_cov cov_xxx0{"xxx0"};
  wildcard_cov cov_xx0x{"xx0x"};
  wildcard_cov cov_x0xx{"x0xx"};

  wildcard_cov cov_1010{"1010"};

  wildcard_cov cov_0101{"0101"};

  int SAMPLE_POINT(sample_point1, cvp1);
  int SAMPLE_POINT(sample_point2, cvp2);
  int SAMPLE_POINT(sample_point3, cvp3);

  int SAMPLE_POINT(sample_point4, cvp4);
  int SAMPLE_POINT(sample_point5, cvp5);
  int SAMPLE_POINT(sample_point6, cvp6);

  int SAMPLE_POINT(sample_point7, cvp7);

  int SAMPLE_POINT(sample_point8, cvp8);

  void sample(const int& x) {
    this->sample_point1 = x;
    this->sample_point2 = x;
    this->sample_point3 = x;

    this->sample_point4 = x;
    this->sample_point5 = x;
    this->sample_point6 = x;


    this->sample_point7 = x;
    this->sample_point8 = x;
    
    covergroup::sample();
  }

  coverpoint<int> cvp1 = coverpoint<int> (this, &cov_xxx1);
  coverpoint<int> cvp2 = coverpoint<int> (this, &cov_xx1x);
  coverpoint<int> cvp3 = coverpoint<int> (this, &cov_x1xx);
  
  coverpoint<int> cvp4 = coverpoint<int> (this, &cov_xxx0);
  coverpoint<int> cvp5 = coverpoint<int> (this, &cov_xx0x);
  coverpoint<int> cvp6 = coverpoint<int> (this, &cov_x0xx);
  
  coverpoint<int> cvp7 = coverpoint<int> (this, &cov_1010);
  
  coverpoint<int> cvp8 = coverpoint<int> (this, &cov_0101);
  
};


TEST(api, control) {

  cvg_control_test cvg;

  
  EXPECT_EQ(cvg.get_inst_coverage(), 0);
  /*  
  cvg.stop();
  cvg.sample(1);

  EXPECT_EQ(cvg.get_inst_coverage(), 0);
  */
  cvg.start();
  //cvg.cvp1.stop();
  /*  cvg.sample(1);
  cvg.sample(2);
  cvg.sample(4);
  */
  //cvg.sample(0x3);
  //cvg.sample(0x7);

  cvg.sample(3);

  EXPECT_EQ(cvg.cvp1.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp2.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp3.get_inst_coverage(), 0);  
  
  EXPECT_EQ(cvg.cvp4.get_inst_coverage(), 0);
  EXPECT_EQ(cvg.cvp5.get_inst_coverage(), 0);
  EXPECT_EQ(cvg.cvp6.get_inst_coverage(), 100);  


  EXPECT_EQ(cvg.cvp7.get_inst_coverage(), 0);  

  EXPECT_EQ(cvg.cvp8.get_inst_coverage(), 0);  
  
  fc4sc::global::coverage_save("basic_control_sample_1_" + std::string(::testing::UnitTest::GetInstance()->current_test_info()->name()) + ".xml");

  cvg.sample(2);

  EXPECT_EQ(cvg.cvp1.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp2.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp3.get_inst_coverage(), 0);  
  
  EXPECT_EQ(cvg.cvp4.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp5.get_inst_coverage(), 0);
  EXPECT_EQ(cvg.cvp6.get_inst_coverage(), 100);  

  EXPECT_EQ(cvg.cvp7.get_inst_coverage(), 0);  

  EXPECT_EQ(cvg.cvp8.get_inst_coverage(), 0);  

  fc4sc::global::coverage_save("basic_control_sample_2_" + std::string(::testing::UnitTest::GetInstance()->current_test_info()->name()) + ".xml");

  //1010
  cvg.sample(0xa);

  EXPECT_EQ(cvg.cvp1.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp2.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp3.get_inst_coverage(), 0);  

  EXPECT_EQ(cvg.cvp4.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp5.get_inst_coverage(), 0);
  EXPECT_EQ(cvg.cvp6.get_inst_coverage(), 100);  
  
  EXPECT_EQ(cvg.cvp7.get_inst_coverage(), 100);  

  EXPECT_EQ(cvg.cvp8.get_inst_coverage(), 0);  
  
  fc4sc::global::coverage_save("basic_control_sample_3_" + std::string(::testing::UnitTest::GetInstance()->current_test_info()->name()) + ".xml");
  
  cvg.sample(0x5);

  EXPECT_EQ(cvg.cvp1.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp2.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp3.get_inst_coverage(), 100);  

  EXPECT_EQ(cvg.cvp4.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp5.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp6.get_inst_coverage(), 100);  

  EXPECT_EQ(cvg.cvp7.get_inst_coverage(), 100);  

  EXPECT_EQ(cvg.cvp8.get_inst_coverage(), 100);  
  
  fc4sc::global::coverage_save("basic_control_sample_4_" + std::string(::testing::UnitTest::GetInstance()->current_test_info()->name()) + ".xml");
  
  
  //  EXPECT_EQ(cvg.get_inst_coverage(), 66.6667);
  /*
  cvg.cvp1.start();
   cvg.sample(1);
  
  //cvg.sample(0x3);
  cvg.sample(0x7);

    
  EXPECT_EQ(cvg.cvp1.get_inst_coverage(), 100);
  EXPECT_EQ(cvg.cvp2.get_inst_coverage(), 100);  

  cvg.sample(0x7);

    EXPECT_EQ(cvg.get_inst_coverage(), 100);

  fc4sc::global::coverage_save("basic_control_" + std::string(::testing::UnitTest::GetInstance()->current_test_info()->name()) + ".xml");
  */
}
