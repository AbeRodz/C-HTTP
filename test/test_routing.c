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
static RouteNode *root, *parent, *child = NULL;

/* === Private variable declarations =========================================================== */
/* === Private function declarations =========================================================== */

void setUp(void) {
    root = newNode("root");
    parent = newNode("parent");
    child = newNode("child");
}

void tearDown(void) {
    if (root != NULL) {
        freeRouteTree(root);
        root = NULL;
    }
}
// Dummy handler for testing
void dummy_handler(int sock) {
    (void)sock;
}

/** @test asserts that a route node is created correctly */
void test_newNode_create_routing_node(void) {
    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_EQUAL_STRING("root", root->character);
    TEST_ASSERT_NULL(root->handler);
    TEST_ASSERT_NULL(root->method);
    TEST_ASSERT_EQUAL(0, root->childrenCount);
}

/** @test asserts that a route can have subroutes (children) */
void test_node_increment_childrenCount(void) {
    addChild(parent, child);

    TEST_ASSERT_EQUAL(1, parent->childrenCount);
    TEST_ASSERT_EQUAL_PTR(child, parent->children[0]);
}

/** @test asserts that a search can be performed to find a children route */
void test_findChild_return_children_node(void) {
    addChild(parent, child);

    RouteNode * found = findChild(parent, "child");
    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL_PTR(child, found);
}

/** @test asserts that a route exists */
void test_pathFinder_locate_existing_path(void) {
    addRouteNode(root, "users/create", "POST", dummy_handler);

    RouteNode * found = pathFinder(root, "users/create");

    TEST_ASSERT_NOT_NULL(found);
    TEST_ASSERT_EQUAL_PTR(dummy_handler, found->handler);
}

/** @test asserts that a route does not exists */
void test_pathFinder_nonexistent_path(void) {
    addRouteNode(root, "users/create", "POST", dummy_handler);

    RouteNode * found = pathFinder(root, "users/delete");
    TEST_ASSERT_NULL(found);
}

/* === Public function implementation ========================================================== */

/* === End of documentation ==================================================================== */
