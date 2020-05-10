#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Human-readable name", "[shortname]"){
    REQUIRE(true);
}

TEST_CASE("Whatever's algorithm", "[whatever-alg]"){
    REQUIRE(true);
}
