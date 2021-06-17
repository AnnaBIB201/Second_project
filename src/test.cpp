#include "catch.hpp"
#include "lib.hpp"

using namespace std;
using namespace sf;

TEST_CASE("TestCharCoord") {
    Character niko("nik.png", 0, 520, 300, 280);
    REQUIRE(niko.x == 0);
    REQUIRE(niko.y == 520);
}
TEST_CASE("TestAlex") {
    Character alex("nik.png", 10, 520, 300, 280);
    float time = 10.00;
    float times = 10.00;
    int jumpNum = -10;
    float CurrentFrame = 3.96;
    alex.MoveToLeft(CurrentFrame, times);
    alex.update(time,jumpNum);
    REQUIRE(alex.x == 5);
    REQUIRE(CurrentFrame==doctest::Approx(4.01));
    ChangeCadr(CurrentFrame);
    REQUIRE(CurrentFrame==doctest::Approx(0.01));
}

TEST_CASE("TestCharacterJump"){
    Character gamer("nik.png", 10, 520, 300, 280);
    gamer.jump = true;
    float times =0;
    int jumpNum = 2;
    gamer.update(times,jumpNum);
    REQUIRE(gamer.y == 518);
    REQUIRE(jumpNum == 1);

}


//TEST_CASE("TestBonus") {
    
    //float time = 10;
    //nice.speed=5;
    //nice.update(time);
    //REQUIRE(nice.y == 100);
//}
