/*
 * Copyright (c) 2014 Anki, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>

#include "greatest.h"

#include "eir.h"
#include "adv_data.h"

SUITE(ble_advertisement);

TEST ble_adv_parse_scan_record_count(void) {
    size_t count = 0;
    int err = 0;

    err = ble_adv_parse_scan(adv0_scan, sizeof(adv0_scan), &count, NULL);
    ASSERT_EQ(err, 0);
    ASSERT_EQ(count, 3); 

    err = ble_adv_parse_scan(adv1_scan, sizeof(adv1_scan), &count, NULL);
    ASSERT_EQ(err, 0);
    ASSERT_EQ(count, 2);

    err = ble_adv_parse_scan(st0_scan, sizeof(st0_scan), &count, NULL);
    ASSERT_EQ(err, 0);
    ASSERT_EQ(count, 1);

    err = ble_adv_parse_scan(st1_scan, sizeof(st1_scan), &count, NULL);
    ASSERT_EQ(err, 0);
    ASSERT_EQ(count, 3);

    PASS();
}

TEST ble_adv_parse_scan_records(void) {
    size_t count = 0;
    int err = 0;

    err = ble_adv_parse_scan(adv0_scan, sizeof(adv0_scan), &count, NULL);
    ASSERT_EQ(err, 0);
    ASSERT_EQ(count, 3);
    
    ble_adv_record_t records[3];
    memset(records, 0, sizeof(ble_adv_record_t) * 3);
    err = ble_adv_parse_scan(adv0_scan, sizeof(adv0_scan), &count, records);

    ble_adv_record_type_t expected_types[3] = { ADV_TYPE_FLAGS, ADV_TYPE_UUID_128, ADV_TYPE_MANUFACTURER_DATA };

    int i = 0;
    for (i = 0; i < count; ++i) {
        ASSERT_EQ(records[i].type, expected_types[i]);
    }

    PASS();
}

GREATEST_SUITE(ble_advertisement) {
    RUN_TEST(ble_adv_parse_scan_record_count);
    RUN_TEST(ble_adv_parse_scan_records);
}
