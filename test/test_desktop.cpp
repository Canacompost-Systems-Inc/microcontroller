/*
 * This file covers tests that can run locally
 * on your machine and not on the MCU.
 * 
 * We rely on mocking to do our testing.
 * 
 */

#include <unity.h>
#include <CRC32.h>

void test_configure_polling(void) {
    // 4 byte payload, Poll sensor 0 at every 3 seconds
    char test_array[] = { 4, 'P', 0x00, 3 };

    CRC32 crc;

    for (size_t i = 0; i < sizeof(test_array); i++) {
        crc.update(test_array[i]);
    }

    uint32_t checksum = crc.finalize();

    TEST_ASSERT_EQUAL(0x5B933741, checksum);
}

void test_configure_actuator(void) {

}

void test_request_sensor_update(void) {

}

void test_request_actuator_state(void) {

}

void test_request_all_state(void) {

}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_configure_polling);
    return UNITY_END();
}