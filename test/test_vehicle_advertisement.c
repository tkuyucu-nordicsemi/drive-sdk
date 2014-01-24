#include <stdio.h>
#include <stdlib.h>

#include "greatest.h"

#include "advertisement.h"
#include "adv_data.h"

SUITE(vehicle_advertisement);

TEST test_is_anki_vehicle(void) {
    int is_anki = 0;
    is_anki =  anki_vehicle_adv_record_has_anki_uuid(adv0_scan, sizeof(adv0_scan));
    ASSERT_EQ(is_anki, 1);

    is_anki =  anki_vehicle_adv_record_has_anki_uuid(adv1_scan, sizeof(adv1_scan));
    ASSERT_EQ(is_anki, 0);

    PASS();
}

TEST test_is_anki_vehicle_ignores_sensortag(void) {
    int is_anki = 0;
    is_anki =  anki_vehicle_adv_record_has_anki_uuid(st0_scan, sizeof(st0_scan));
    ASSERT_EQ(is_anki, 0);

    is_anki =  anki_vehicle_adv_record_has_anki_uuid(st1_scan, sizeof(st1_scan));
    ASSERT_EQ(is_anki, 0);

    PASS();
}

TEST test_anki_vehicle_parse_adv_record(void) {
    anki_vehicle_adv_t adv;

    // parse first packet
    uint8_t err = 0;
    err = anki_vehicle_parse_adv_record(adv0_scan, sizeof(adv0_scan), &adv);
    ASSERT_EQ(err, 0);

    err = anki_vehicle_parse_adv_record(adv1_scan, sizeof(adv1_scan), &adv);
    ASSERT_EQ(err, 0);

    PASS();
}

TEST test_vehicle_parse_mfg_data(void) {
    uint8_t data0[] = { 0xBE, 0xEF, 0x00, 0x01, 0x00, 0xE0, 0x0A, 0xA3 };
    anki_vehicle_adv_mfg_t mfg_data;
    int err = anki_vehicle_parse_mfg_data(data0, 8, &mfg_data);
    ASSERT_EQ(err, 0);

    ASSERT_EQ(mfg_data.product_id, 0xbeef);
    ASSERT_EQ(mfg_data.model_id, 0x01);
    ASSERT_EQ(mfg_data.identifier & 0xffff, 0x0aa3);

    PASS();
}

TEST test_vehicle_parse_local_name(void) {
    uint8_t data0[] = { 0x50, 0x20, 0x21, 0x01, 0x20, 0x20, 0x5A, 0x39, 0x41, 0x41, 0x33, 0x20, 0x54, 0x4F, 0x4D, 0x4D, 0x59, 0x00 };
    anki_vehicle_adv_info_t info;
    uint8_t err = anki_vehicle_parse_local_name(data0, sizeof(data0), &info);
    ASSERT_EQ(err, 0);
    ASSERT_EQ(info.state.full_battery, 1);
    ASSERT_EQ(info.state.low_battery, 0);
    ASSERT_EQ(info.state.on_charger, 1);
    ASSERT_EQ(info.version, 0x2120);
    ASSERT_STR_EQ((const char *)info.name, (const char *)&data0[8]);

    PASS();
}

GREATEST_SUITE(vehicle_advertisement) {
    RUN_TEST(test_is_anki_vehicle);
    RUN_TEST(test_is_anki_vehicle_ignores_sensortag);
    RUN_TEST(test_anki_vehicle_parse_adv_record);
    RUN_TEST(test_vehicle_parse_mfg_data);
    RUN_TEST(test_vehicle_parse_local_name);
}
