//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2017, Lawrence Livermore National Security, LLC.
//
// Produced at the Lawrence Livermore National Laboratory
//
// LLNL-CODE-725085
//
// All rights reserved.
//
// This file is part of BLT.
//
// For additional details, please also read BLT/LICENSE.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the disclaimer below.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the disclaimer (as noted below) in the
//   documentation and/or other materials provided with the distribution.
//
// * Neither the name of the LLNS/LLNL nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
// LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#include "gtest/gtest.h"
#include "gmock/gmock.h" 

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Interface to Mock
//------------------------------------------------------------------------------
class Thing
{
  public:
      virtual ~Thing() {}
      virtual void Method() = 0;
};

//------------------------------------------------------------------------------
// Interface User
//------------------------------------------------------------------------------
class MethodCaller
{
  public: 
        MethodCaller(Thing *thing)
        :m_thing(thing)
        {
            // empty
        }

        void Go()
        {
            // call Method() on thing 2 times
            m_thing->Method();
            m_thing->Method();
        }

  private:
      Thing* m_thing;
};

//------------------------------------------------------------------------------
// Mocked Interface
//------------------------------------------------------------------------------
class MockThing : public Thing
{
  public:
        MOCK_METHOD0(Method, void());
};


//------------------------------------------------------------------------------
// Actual Test
//------------------------------------------------------------------------------
using ::testing::AtLeast;
TEST(blt_gtest_smoke,basic_mock_test)
{
    MockThing m;
    EXPECT_CALL(m, Method()).Times(AtLeast(2));

    MethodCaller mcaller(&m);

    mcaller.Go();
}


//------------------------------------------------------------------------------
// Main Driver
//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    // The following lines must be executed to initialize Google Test
    // and Google Mock before running the tests.
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}