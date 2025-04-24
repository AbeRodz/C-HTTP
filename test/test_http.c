/************************************************************************************************
Copyright (c) 2025, Abraham Rodriguez <abraham.rodz17@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file test_http.c
 ** @brief unit tests for http statuses
 **/

/* === Headers files inclusions =============================================================== */
#include "unity.h"
#include "http_status.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */
/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

void setUp(void) {
}

/** @test evaluates 200 status codes */
void test_get_http_status_text_success_statuses(void) {
    TEST_ASSERT_EQUAL_STRING("OK", get_http_status_text(HTTP_STATUS_OK));
    TEST_ASSERT_EQUAL_STRING("Created", get_http_status_text(HTTP_STATUS_CREATED));
    TEST_ASSERT_EQUAL_STRING("Accepted", get_http_status_text(HTTP_STATUS_ACCEPTED));
    TEST_ASSERT_EQUAL_STRING("Non-Authoritative Information",
                             get_http_status_text(HTTP_STATUS_NON_AUTHORITATIVE_INFORMATION));
    TEST_ASSERT_EQUAL_STRING("No Content", get_http_status_text(HTTP_STATUS_NO_CONTENT));
    TEST_ASSERT_EQUAL_STRING("Reset Content", get_http_status_text(HTTP_STATUS_RESET_CONTENT));
    TEST_ASSERT_EQUAL_STRING("Partial Content", get_http_status_text(HTTP_STATUS_PARTIAL_CONTENT));
    TEST_ASSERT_EQUAL_STRING("Multi-Status", get_http_status_text(HTTP_STATUS_MULTI_STATUS));
    TEST_ASSERT_EQUAL_STRING("Already Reported",
                             get_http_status_text(HTTP_STATUS_ALREADY_REPORTED));
    TEST_ASSERT_EQUAL_STRING("IM Used", get_http_status_text(HTTP_STATUS_IM_USED));
}

/** @test evaluates 400 status codes */
void test_get_http_status_text_client_statuses(void) {
    TEST_ASSERT_EQUAL_STRING("Bad Request", get_http_status_text(HTTP_STATUS_BAD_REQUEST));
    TEST_ASSERT_EQUAL_STRING("Unauthorized", get_http_status_text(HTTP_STATUS_UNAUTHORIZED));
    TEST_ASSERT_EQUAL_STRING("Payment Required",
                             get_http_status_text(HTTP_STATUS_PAYMENT_REQUIRED));
    TEST_ASSERT_EQUAL_STRING("Forbidden", get_http_status_text(HTTP_STATUS_FORBIDDEN));
    TEST_ASSERT_EQUAL_STRING("Not Found", get_http_status_text(HTTP_STATUS_NOT_FOUND));
    TEST_ASSERT_EQUAL_STRING("Method Not Allowed",
                             get_http_status_text(HTTP_STATUS_METHOD_NOT_ALLOWED));
    TEST_ASSERT_EQUAL_STRING("Not Acceptable", get_http_status_text(HTTP_STATUS_NOT_ACCEPTABLE));
    TEST_ASSERT_EQUAL_STRING("Proxy Authentication Required",
                             get_http_status_text(HTTP_STATUS_PROXY_AUTHENTICATION_REQUIRED));
    TEST_ASSERT_EQUAL_STRING("Request Timeout", get_http_status_text(HTTP_STATUS_REQUEST_TIMEOUT));
    TEST_ASSERT_EQUAL_STRING("Conflict", get_http_status_text(HTTP_STATUS_CONFLICT));
    TEST_ASSERT_EQUAL_STRING("Gone", get_http_status_text(HTTP_STATUS_GONE));
    TEST_ASSERT_EQUAL_STRING("Length Required", get_http_status_text(HTTP_STATUS_LENGTH_REQUIRED));
    TEST_ASSERT_EQUAL_STRING("Precondition Failed",
                             get_http_status_text(HTTP_STATUS_PRECONDITION_FAILED));
    TEST_ASSERT_EQUAL_STRING("Payload Too Large",
                             get_http_status_text(HTTP_STATUS_PAYLOAD_TOO_LARGE));
    TEST_ASSERT_EQUAL_STRING("URI Too Long", get_http_status_text(HTTP_STATUS_URI_TOO_LONG));
    TEST_ASSERT_EQUAL_STRING("Unsupported Media Type",
                             get_http_status_text(HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE));
    TEST_ASSERT_EQUAL_STRING("Range Not Satisfiable",
                             get_http_status_text(HTTP_STATUS_RANGE_NOT_SATISFIABLE));
    TEST_ASSERT_EQUAL_STRING("Expectation Failed",
                             get_http_status_text(HTTP_STATUS_EXPECTATION_FAILED));
    TEST_ASSERT_EQUAL_STRING("I'm a teapot", get_http_status_text(HTTP_STATUS_IM_A_TEAPOT));
    TEST_ASSERT_EQUAL_STRING("Too Many Requests",
                             get_http_status_text(HTTP_STATUS_TOO_MANY_REQUESTS));
}

/** @test evaluates 500 status codes */
void test_get_http_status_text_server_statuses(void) {
    TEST_ASSERT_EQUAL_STRING("Internal Server Error",
                             get_http_status_text(HTTP_STATUS_INTERNAL_SERVER_ERROR));
    TEST_ASSERT_EQUAL_STRING("Not Implemented", get_http_status_text(HTTP_STATUS_NOT_IMPLEMENTED));
    TEST_ASSERT_EQUAL_STRING("Bad Gateway", get_http_status_text(HTTP_STATUS_BAD_GATEWAY));
    TEST_ASSERT_EQUAL_STRING("Service Unavailable",
                             get_http_status_text(HTTP_STATUS_SERVICE_UNAVAILABLE));
    TEST_ASSERT_EQUAL_STRING("Gateway Timeout", get_http_status_text(HTTP_STATUS_GATEWAY_TIMEOUT));
    TEST_ASSERT_EQUAL_STRING("HTTP Version Not Supported",
                             get_http_status_text(HTTP_STATUS_HTTP_VERSION_NOT_SUPPORTED));
    TEST_ASSERT_EQUAL_STRING("Variant Also Negotiates",
                             get_http_status_text(HTTP_STATUS_VARIANT_ALSO_NEGOTIATES));
    TEST_ASSERT_EQUAL_STRING("Insufficient Storage",
                             get_http_status_text(HTTP_STATUS_INSUFFICIENT_STORAGE));
    TEST_ASSERT_EQUAL_STRING("Loop Detected", get_http_status_text(HTTP_STATUS_LOOP_DETECTED));
    TEST_ASSERT_EQUAL_STRING("Not Extended", get_http_status_text(HTTP_STATUS_NOT_EXTENDED));
    TEST_ASSERT_EQUAL_STRING("Network Authentication Required",
                             get_http_status_text(HTTP_STATUS_NETWORK_AUTHENTICATION_REQUIRED));
}

/* === Public function implementation ========================================================== */

/* === End of documentation ==================================================================== */
