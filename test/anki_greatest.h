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

#ifndef INCLUDE_anki_greatest_h__
#define INCLUDE_anki_greatest_h__

#define ANKI_GREATEST_HEX_DUMP(buffer, len) \
    do {                                                \
        const uint8_t *b = (const uint8_t *)buffer;     \
        int i;                                          \
        for (i = 0; i < (len); ++i) {                   \
            fprintf(GREATEST_STDOUT, "%02x ", b[i]);    \
        }                                               \
    } while(0)

#define ANKI_GREATEST_ASSERT_BYTES_EQm(MSG, EXP, GOT, LEN)                          \
    do {                                                                \
        const void *exp_s = (const void *)(EXP);                                      \
        const void *got_s = (const void *)(GOT);                                      \
        const size_t len_s = (const size_t)(LEN);                                      \
        greatest_info.msg = MSG;                                        \
        greatest_info.fail_file = __FILE__;                             \
        greatest_info.fail_line = __LINE__;                             \
        if (0 != memcmp(exp_s, got_s, len_s)) {                         \
            fprintf(GREATEST_STDOUT, "Expected:\n####\n");              \
            ANKI_GREATEST_HEX_DUMP(exp_s, len_s);                       \
            fprintf(GREATEST_STDOUT, "\n####\n");                       \
            fprintf(GREATEST_STDOUT, "Got:\n####\n");                   \
            ANKI_GREATEST_HEX_DUMP(got_s, len_s);                       \
            fprintf(GREATEST_STDOUT, "\n####\n");                       \
            return -1;                                                  \
        }                                                               \
        greatest_info.msg = NULL;                                       \
    } while (0)

#define ANKI_GREATEST_ASSERT_BYTES_EQ(EXP, GOT, LEN) ANKI_GREATEST_ASSERT_BYTES_EQm(#EXP " != " #GOT, EXP, GOT, LEN)

#define ASSERT_BYTES_EQm(MSG, EXP, GOT, LEN) ANKI_GREATEST_ASSERT_BYTES_EQm(MSG, EXP, GOT, LEN)
#define ASSERT_BYTES_EQ(EXP, GOT, LEN)  ANKI_GREATEST_ASSERT_BYTES_EQ(EXP, GOT, LEN)

#endif
