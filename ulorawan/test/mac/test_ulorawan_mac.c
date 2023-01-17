/**
 * \file
 *
 * \brief 
 *
 * Copyright (c) 2023 Derek Goslin
 *
 * @author Derek Goslin
 *
 * \page License
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "unity.h"
#include "ulorawan_mac.h"
#include "ulorawan_mac_frame.h"

void setUp(void) {}

void tearDown(void) {}

void test_ulorawan_mac_read_fhdr_index_error()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 0;

    struct ulorawan_mac_fhdr fhdr;

    // Act
    int32_t result = ulorawan_mac_read_fhdr(&context, &fhdr);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_INDEX, result);
}

void test_ulorawan_mac_read_fhdr_success()
{
    // Arrange
    struct ulorawan_mac_frame_context context = 
    {
        { 0xA0, 0xEF, 0xBE, 0x55, 0xAA, 0x55, 0xED, 0xFE, 0xDE, 0xAD, 0xBE, 0xEF, 0xAA },
        1
    };
    
    struct ulorawan_mac_fhdr fhdr;

    // Act
    int32_t result = ulorawan_mac_read_fhdr(&context, &fhdr);
    
    // Assert
    uint8_t expected[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xAA };

    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(13, context.eof);
    TEST_ASSERT_EQUAL_HEX32(0xAA55BEEF, fhdr.dev_addr);
    TEST_ASSERT_EQUAL_HEX32(0xFEED, fhdr.fcnt);
    TEST_ASSERT_EQUAL_HEX32(0x55, fhdr.fctrl.value);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, fhdr.fopts, fhdr.fctrl.bits.fopts_len);
}

void test_ulorawan_mac_read_fport_index_error()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 0;

    uint8_t port;

    // Act
    int32_t result = ulorawan_mac_read_fport(&context, &port);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_INDEX, result);
}

void test_ulorawan_mac_read_fport_success()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = sizeof(union ulorawan_mac_mhdr) + sizeof(struct ulorawan_mac_fhdr);
    context.buf[sizeof(union ulorawan_mac_mhdr) + sizeof(struct ulorawan_mac_fhdr)] = 0xAA;

    uint8_t port;

    // Act
    int32_t result = ulorawan_mac_read_fport(&context, &port);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(0xAA, port);
}

void test_ulorawan_mac_read_frmpayload_index_error()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 0;

    size_t i = 10;
    uint8_t payload[10];

    // Act
    int32_t result = ulorawan_mac_read_frmpayload(&context, payload, &i);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_INDEX, result);
}

void test_ulorawan_mac_read_frmpayload_success()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = sizeof(union ulorawan_mac_mhdr) + sizeof(struct ulorawan_mac_fhdr);

    size_t i = 10;
    uint8_t payload[10];

    // Act
    int32_t result = ulorawan_mac_read_frmpayload(&context, payload, &i);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(0x21, context.eof);
}

void test_ulorawan_mac_read_mhdr_index_error()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 1;

    union ulorawan_mac_mhdr mhdr;

    // Act
    int32_t result = ulorawan_mac_read_mhdr(&context, &mhdr );
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_INDEX, result);
}

void test_ulorawan_mac_read_mhdr_success()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.buf[0] = 0xAA;
    context.eof = 0;

    union ulorawan_mac_mhdr mhdr;

    // Act
    int32_t result = ulorawan_mac_read_mhdr(&context, &mhdr);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(0xAA, mhdr.value);
}

void test_ulorawan_mac_write_mhdr_index_error()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 10;

    union ulorawan_mac_mhdr mhdr;

    // Act
    int32_t result = ulorawan_mac_write_mhdr(&context, &mhdr);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_INDEX, result);
}

void test_ulorawan_mac_write_mhdr_success()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 0;
    
    union ulorawan_mac_mhdr mhdr = {0};
    mhdr.bits.ftype = FRAME_TYPE_DATA_CONFIRMED_DOWN;
    mhdr.bits.major = LORAWAN_MAJOR_R1;

    // Act
    int32_t result = ulorawan_mac_write_mhdr(&context, &mhdr);
    
    // Assert
    uint8_t expected[] = { 0xA0 };

    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(1, context.eof);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, context.buf, sizeof(union ulorawan_mac_mhdr));
}

void test_ulorawan_mac_write_fhdr_index_error()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 10;

    struct ulorawan_mac_fhdr fhdr;

    // Act
    int32_t result = ulorawan_mac_write_fhdr(&context, &fhdr);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_INDEX, result);
}

void test_ulorawan_mac_write_fhdr_success()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 1;
    context.buf[0] = 0xA0;

    struct ulorawan_mac_fhdr fhdr;
    fhdr.dev_addr = 0xAA55BEEF;
    fhdr.fctrl.value = 0x55;
    fhdr.fcnt = 0xFEED;
    fhdr.fopts[0] = 0xDE;
    fhdr.fopts[1] = 0xAD;
    fhdr.fopts[2] = 0xBE;
    fhdr.fopts[3] = 0xEF;
    fhdr.fopts[4] = 0xAA;

    // Act
    int32_t result = ulorawan_mac_write_fhdr(&context, &fhdr);
    
    // Assert
    uint8_t expected[] = {0xA0, 0xEF, 0xBE, 0x55, 0xAA, fhdr.fctrl.value, 0xED, 0xFE, 0xDE, 0xAD, 0xBE, 0xEF, 0xAA };

    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(0x0D, context.eof);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, context.buf, 0x0D);
}

void test_ulorawan_mac_write_fport_index_error()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 0;
    
    // Act
    int32_t result = ulorawan_mac_write_fport(&context, 0x55);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_INDEX, result);
}

void test_ulorawan_mac_write_fport_success()
{
    // Arrange
    uint8_t i = sizeof(union ulorawan_mac_mhdr) + sizeof(struct ulorawan_mac_fhdr);
    struct ulorawan_mac_frame_context context;
    context.eof = i;
    
    // Act
    int32_t result = ulorawan_mac_write_fport(&context, 0x55);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(i + 1, context.eof);
    TEST_ASSERT_EQUAL_HEX8(0x55, context.buf[i]);
}

void test_ulorawan_mac_write_frmpayload_success()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 0;
    uint8_t payload[] = { 0x55, 0xAA };

    // Act
    int32_t result = ulorawan_mac_write_frmpayload(&context, payload, 2);
    
    // Assert
    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(0x02, context.eof);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(payload, context.buf, 1);
}

void test_ulorawan_mac_write_mic_success()
{
    // Arrange
    struct ulorawan_mac_frame_context context;
    context.eof = 0;
    
    // Act
    int32_t result = ulorawan_mac_write_mic(&context, 0xAA55FEED);
    
    // Assert
    uint8_t expected[] = { 0xED, 0xFE, 0x55, 0xAA };

    TEST_ASSERT_EQUAL_HEX8(ULORAWAN_MAC_ERR_NONE, result);
    TEST_ASSERT_EQUAL_HEX8(0x04, context.eof);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, context.buf, sizeof(uint32_t));
}