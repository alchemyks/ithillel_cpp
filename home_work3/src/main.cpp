#include <cassert>
#include <utility>
#include <iostream>

#include "lib/shared_ptr.h"

//using namespace hmwrk2;


void test_shared_ptr() {
    {
        hmwrk3::shared_ptr<int> testDef1(new int(1));
        assert(*testDef1 == 1);
        {
        hmwrk3::shared_ptr<int> testDef2 = testDef1;
        assert(testDef1.use_count() == 2);
        }
        {
        hmwrk3::shared_ptr<int> testDef3;
        testDef3 = testDef1;
        assert(testDef1.use_count() == 2);
        }
        assert(testDef1.use_count() == 1);

    }
        
}






int main(int argc, char** argv){
    test_shared_ptr();
}