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

/** @file test_routing.c
 ** @brief unit tests for routing trie data structure
 **/

/* === Headers files inclusions =============================================================== */
#include "unity.h"
#include "routing.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */
/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

void setUp(void) {

}
// Dummy handler for testing
void dummy_handler(int sock) {
    (void)sock; // silence unused warning
}

/** @test initiates all LEDs as turned off. */
void test_newNode_should_create_node_with_correct_name(void)
{
    RouteNode *node = newNode("users");
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL_STRING("users", node->character);
    TEST_ASSERT_NULL(node->handler);
    TEST_ASSERT_NULL(node->method);
    TEST_ASSERT_EQUAL(0, node->childrenCount);
    free(node);
}

void test_addChild_should_increment_childrenCount(void)
{
    RouteNode *parent = newNode("parent");
    RouteNode *child = newNode("child");

    addChild(parent, child);

    TEST_ASSERT_EQUAL(1, parent->childrenCount);
    TEST_ASSERT_EQUAL_PTR(child, parent->children[0]);

    free(parent);
    free(child);
}

void test_findChild_should_return_matching_node(void)
{
    RouteNode *parent = newNode("root");
    RouteNode *child = newNode("users");
    addChild(parent, child);

    RouteNode *found = findChild(parent, "users");
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL_PTR(child, found);

    free(parent);
    free(child);
}

void test_pathFinder_should_locate_existing_path(void)
{
    RouteNode *root = newNode("/");
    addRouteNode(root, "users/create", "POST", dummy_handler);

    RouteNode *found = pathFinder(root, "users/create");
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL_PTR(dummy_handler, found->handler);

    free(root);
    free(found);
}

void test_pathFinder_should_return_null_for_nonexistent_path(void)
{
    RouteNode *root = newNode("/");
    addRouteNode(root, "users/create", "POST", dummy_handler);

    RouteNode *found = pathFinder(root, "users/delete");
    TEST_ASSERT_NULL(found);

    free(root);
}


/* === Public function implementation ========================================================== */

/* === End of documentation ==================================================================== */
