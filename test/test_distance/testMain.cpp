#include <unity.h>
#include "DistanceZone.h"


void setUp(void) {
}

void tearDown(void) {
}

void testNegativeDistance(void) {
    // Valores negativos (timeout o lectura errónea del sensor) deben ser OutOfRange
    TEST_ASSERT_TRUE(evaluateDistanceZone(-0.01f) == DistanceZone::OutOfRange);
    TEST_ASSERT_TRUE(evaluateDistanceZone(-1.0f) == DistanceZone::OutOfRange);
    TEST_ASSERT_TRUE(evaluateDistanceZone(-50.0f) == DistanceZone::OutOfRange);
}

void testNearZoneBoundaries(void) {
    // Zona cercana (de 0.0 cm a 10.0 cm inclusive)
    TEST_ASSERT_TRUE(evaluateDistanceZone(0.0f) == DistanceZone::Near);
    TEST_ASSERT_TRUE(evaluateDistanceZone(0.1f) == DistanceZone::Near);
    TEST_ASSERT_TRUE(evaluateDistanceZone(5.0f) == DistanceZone::Near);
    TEST_ASSERT_TRUE(evaluateDistanceZone(9.99f) == DistanceZone::Near);
    TEST_ASSERT_TRUE(evaluateDistanceZone(10.0f) == DistanceZone::Near);
}

void testMediumZoneBoundaries(void) {
    // Zona media (entre 10 y 20 cm)
    TEST_ASSERT_TRUE(evaluateDistanceZone(10.01f) == DistanceZone::Medium);
    TEST_ASSERT_TRUE(evaluateDistanceZone(15.0f) == DistanceZone::Medium);
    TEST_ASSERT_TRUE(evaluateDistanceZone(19.99f) == DistanceZone::Medium);
    TEST_ASSERT_TRUE(evaluateDistanceZone(20.0f) == DistanceZone::Medium);
}

void testFarZoneBoundaries(void) {
    // Zona lejana (entre 20 y 30 cm)
    TEST_ASSERT_TRUE(evaluateDistanceZone(20.01f) == DistanceZone::Far);
    TEST_ASSERT_TRUE(evaluateDistanceZone(25.0f) == DistanceZone::Far);
    TEST_ASSERT_TRUE(evaluateDistanceZone(29.99f) == DistanceZone::Far);
    TEST_ASSERT_TRUE(evaluateDistanceZone(30.0f) == DistanceZone::Far);
}

void testOutOfRangeBoundaries(void) {
    // Fuera de alcance (mayor a 30 cm)
    TEST_ASSERT_TRUE(evaluateDistanceZone(30.01f) == DistanceZone::OutOfRange);
    TEST_ASSERT_TRUE(evaluateDistanceZone(35.0f) == DistanceZone::OutOfRange);
    TEST_ASSERT_TRUE(evaluateDistanceZone(100.0f) == DistanceZone::OutOfRange);
    TEST_ASSERT_TRUE(evaluateDistanceZone(400.0f) == DistanceZone::OutOfRange);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(testNegativeDistance);
    RUN_TEST(testNearZoneBoundaries);
    RUN_TEST(testMediumZoneBoundaries);
    RUN_TEST(testFarZoneBoundaries);
    RUN_TEST(testOutOfRangeBoundaries);

    return UNITY_END();
}
