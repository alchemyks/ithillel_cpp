#include <cassert>
#include <utility>

#include "lib/unique_ptr.h"

//using namespace hmwrk2;


void test_unique_ptr() {
    {
        hmwrk2::unique_ptr<int> testDef1(new int(1));
        assert(*testDef1 == 1);
        assert(testDef1);
        assert(*testDef1.get() == 1);
        hmwrk2::unique_ptr<int> testDef2(new int(2));
        //testDef1 = testDef2;
      
    }
        
}






int main(int argc, char** argcv){
    test_unique_ptr();
    
}