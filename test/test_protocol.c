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
#include <string.h>

#include "greatest.h"
#include "anki_greatest.h"

#include "protocol.h"
#include "anki_util.h"

SUITE(vehicle_protocol);

TEST test_struct_attribute_packed(void) {
    ASSERT_EQ(sizeof(anki_vehicle_msg_sdk_mode_t), ANKI_VEHICLE_MSG_SDK_MODE_SIZE+ANKI_VEHICLE_MSG_BASE_SIZE);
    PASS();
}

TEST test_set_sdk_mode(void) {
    anki_vehicle_msg_t msg;
    uint8_t size = anki_vehicle_msg_set_sdk_mode(&msg, 1, ANKI_VEHICLE_SDK_OPTION_OVERRIDE_LOCALIZATION);
    ASSERT_EQ(size, 4);

    uint8_t expect[4] = { 0x03, 0x90, 0x01, 0x01 };
    ASSERT_BYTES_EQ(&msg, expect, 4);
    PASS();
}

TEST test_set_speed(void) {
    anki_vehicle_msg_t msg;
    uint8_t size = anki_vehicle_msg_set_speed(&msg, 1000, 25000);
    ASSERT_EQ(size, sizeof(anki_vehicle_msg_set_speed_t));

    uint8_t expect[7] = { 0x06, 0x24, 0xe8, 0x03, 0xa8, 0x61, 0x00 };
    ASSERT_BYTES_EQ(&msg, expect, 7);
    PASS();
}

TEST test_set_offset_from_center(void) {
    anki_vehicle_msg_t msg;
    memset(&msg, 0, sizeof(anki_vehicle_msg_t));
    uint8_t size = anki_vehicle_msg_set_offset_from_road_center(&msg, 0.0);

    ASSERT_EQ(size, sizeof(anki_vehicle_msg_set_offset_from_road_center_t));

    uint8_t expect[6] = { 0x5, 0x2c, 0, 0, 0, 0 };
    ASSERT_BYTES_EQ(&msg, expect, 6);
    PASS();
}

TEST test_change_lane(void) {
    anki_vehicle_msg_t msg;
    memset(&msg, 0, sizeof(anki_vehicle_msg_change_lane_t));
    uint8_t size = anki_vehicle_msg_change_lane(&msg, 1000, 10000, 20.f);
    ASSERT_EQ(size, sizeof(anki_vehicle_msg_change_lane_t));

    uint8_t expect[12] = { 0x0b, 0x25, 0xe8, 0x03, 0x10, 0x27, 0x00, 0x00, 0xa0, 0x41, 0, 0 };
    ASSERT_BYTES_EQ(&msg, expect, 12);
    PASS();
}

TEST test_light_config(void) {
    anki_vehicle_light_config_t config;
    memset(&config, 0, sizeof(anki_vehicle_light_config_t));
    //uint8_t size = anki_vehicle_light_config(&config, LIGHT_RED, EFFECT_THROB, 0, 20, 5);
    anki_vehicle_light_config(&config, LIGHT_RED, EFFECT_THROB, 0, 10, 10);
    ASSERT(config.cycles_per_10_sec > 0);

    anki_vehicle_msg_lights_pattern_t msg;
    memset(&msg, 0, sizeof(anki_vehicle_msg_lights_pattern_t));

    const uint8_t size = anki_vehicle_msg_lights_pattern_append(&msg, &config);
    ASSERT_EQ(size, sizeof(config));

    ASSERT_EQ(msg.msg_id, ANKI_VEHICLE_MSG_C2V_LIGHTS_PATTERN);
    ASSERT_EQ(msg.size, ANKI_VEHICLE_MSG_C2V_LIGHTS_PATTERN_SIZE);
    ASSERT_EQ(msg.channel_count, 1);
    ASSERT_BYTES_EQ(&(msg.channel_config[0]), &config, sizeof(config));

    PASS();
}

// Regression test against a STEADY LIGHT_BLUE, max intensity
TEST test_lights_steady_blue(void) {
    anki_vehicle_msg_lights_pattern_t msg;
    memset(&msg, 0, sizeof(anki_vehicle_msg_lights_pattern_t));

    uint8_t intensity = ANKI_VEHICLE_MAX_LIGHT_INTENSITY;
    uint8_t cycles_per_min = 0;

    anki_vehicle_light_config_t config;
    {
        memset(&config, 0, sizeof(anki_vehicle_light_config_t));
        anki_vehicle_light_config(&config, LIGHT_RED, EFFECT_STEADY, 0, 0, cycles_per_min);
        uint8_t append_size = anki_vehicle_msg_lights_pattern_append(&msg, &config);
        ASSERT_EQ(append_size, sizeof(config));
        ASSERT_EQ(msg.channel_count, 1);
    }
    {
        memset(&config, 0, sizeof(anki_vehicle_light_config_t));
        anki_vehicle_light_config(&config, LIGHT_GREEN, EFFECT_STEADY, 0, 0, cycles_per_min);
        uint8_t append_size = anki_vehicle_msg_lights_pattern_append(&msg, &config);
        ASSERT_EQ(append_size, sizeof(config));
        ASSERT_EQ(msg.channel_count, 2);
    }
    {
        memset(&config, 0, sizeof(anki_vehicle_light_config_t));
        anki_vehicle_light_config(&config, LIGHT_BLUE, EFFECT_STEADY, intensity, intensity, cycles_per_min);
        uint8_t append_size = anki_vehicle_msg_lights_pattern_append(&msg, &config);
        ASSERT_EQ(append_size, sizeof(config));
        ASSERT_EQ(msg.channel_count, 3);
    }

    uint8_t expected[18] = {
        0x11, 0x33,
        0x03,
        0x00, 0x00, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x0e, 0x0e, 0x00
    };

    ASSERT_BYTES_EQ(&msg, expected, sizeof(expected));
    PASS();
}

TEST test_turn_180(void) {
    anki_vehicle_msg_t msg;
    memset(&msg, 0, sizeof(anki_vehicle_msg_turn_t));

    uint8_t size = anki_vehicle_msg_turn(&msg, VEHICLE_TURN_UTURN, VEHICLE_TURN_TRIGGER_IMMEDIATE);
    ASSERT_EQ(size, sizeof(anki_vehicle_msg_turn_t));

    uint8_t expect[4] = { ANKI_VEHICLE_MSG_C2V_TURN_SIZE,
                          ANKI_VEHICLE_MSG_C2V_TURN,
                          VEHICLE_TURN_UTURN,
                          VEHICLE_TURN_TRIGGER_IMMEDIATE };
    ASSERT_BYTES_EQ(&msg, expect, 4);
    PASS();
}

TEST test_lights_pattern(void) {
    anki_vehicle_msg_lights_pattern_t msg;
    memset(&msg, 0, sizeof(anki_vehicle_msg_lights_pattern_t));

    uint8_t intensity = ANKI_VEHICLE_MAX_LIGHT_INTENSITY;
    uint8_t cycles_per_min = 6;

    anki_vehicle_light_config_t config;
    {
        memset(&config, 0, sizeof(anki_vehicle_light_config_t));
        anki_vehicle_light_config(&config, LIGHT_RED, EFFECT_THROB, 0, intensity, cycles_per_min);
        uint8_t append_size = anki_vehicle_msg_lights_pattern_append(&msg, &config);
        ASSERT_EQ(append_size, sizeof(config));
        ASSERT_EQ(msg.channel_count, 1);
    }
    {
        memset(&config, 0, sizeof(anki_vehicle_light_config_t));
        anki_vehicle_light_config(&config, LIGHT_GREEN, EFFECT_THROB, 0, ANKI_VEHICLE_MAX_LIGHT_INTENSITY, cycles_per_min);
        uint8_t append_size = anki_vehicle_msg_lights_pattern_append(&msg, &config);
        ASSERT_EQ(append_size, sizeof(config));
        ASSERT_EQ(msg.channel_count, 2);
    }
    {
        memset(&config, 0, sizeof(anki_vehicle_light_config_t));
        anki_vehicle_light_config(&config, LIGHT_BLUE, EFFECT_THROB, 0, ANKI_VEHICLE_MAX_LIGHT_INTENSITY, cycles_per_min);
        uint8_t append_size = anki_vehicle_msg_lights_pattern_append(&msg, &config);
        ASSERT_EQ(append_size, sizeof(config));
        ASSERT_EQ(msg.channel_count, 3);
    }

    ASSERT_EQ(msg.msg_id, ANKI_VEHICLE_MSG_C2V_LIGHTS_PATTERN);
    ASSERT_EQ(msg.size, ANKI_VEHICLE_MSG_C2V_LIGHTS_PATTERN_SIZE);

    ASSERT_EQ(msg.channel_config[0].channel, LIGHT_RED);
    ASSERT_EQ(msg.channel_config[1].channel, LIGHT_GREEN);
    ASSERT_EQ(msg.channel_config[2].channel, LIGHT_BLUE);

    PASS();
}

TEST test_disconnect(void) {
    anki_vehicle_msg_t msg;
    anki_vehicle_msg_disconnect(&msg);

    uint8_t expect[2] = { ANKI_VEHICLE_MSG_BASE_SIZE, ANKI_VEHICLE_MSG_C2V_DISCONNECT };
    ASSERT_BYTES_EQ(&msg, expect, 2);

    PASS();
}

TEST test_get_version(void) {
    anki_vehicle_msg_t msg;
    uint8_t size = anki_vehicle_msg_get_version(&msg);

    ASSERT_EQ(size, 2);

    uint8_t expect[2] = { ANKI_VEHICLE_MSG_BASE_SIZE, ANKI_VEHICLE_MSG_C2V_VERSION_REQUEST };
    ASSERT_BYTES_EQ(&msg, expect, sizeof(expect));

    PASS();
}

TEST test_get_battery_level(void) {
    anki_vehicle_msg_t msg;
    uint8_t size = anki_vehicle_msg_get_battery_level(&msg);

    ASSERT_EQ(size, 2);

    uint8_t expect[2] = { ANKI_VEHICLE_MSG_BASE_SIZE, ANKI_VEHICLE_MSG_C2V_BATTERY_LEVEL_REQUEST };
    ASSERT_BYTES_EQ(&msg, expect, sizeof(expect));

    PASS();
}

GREATEST_SUITE(vehicle_protocol) {
    RUN_TEST(test_struct_attribute_packed);
    RUN_TEST(test_set_sdk_mode);
    RUN_TEST(test_set_speed);
    RUN_TEST(test_set_offset_from_center);
    RUN_TEST(test_change_lane);
    RUN_TEST(test_light_config);
    RUN_TEST(test_lights_pattern);
    RUN_TEST(test_lights_steady_blue);
    RUN_TEST(test_turn_180);
    RUN_TEST(test_disconnect);
    RUN_TEST(test_get_version);
    RUN_TEST(test_get_battery_level);
}
