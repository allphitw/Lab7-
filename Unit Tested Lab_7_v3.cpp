#include "pch.h"
#include "CppUnitTest.h"
#include "BinarySearchTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinarySearchTreeTests
{
    TEST_CLASS(BinarySearchTreeTests)
    {
    public:
        BinarySearchTree bst;

        // Test the left rotation function
        TEST_METHOD(TestLeftRotation)
        {
            bst.Insert("A");
            bst.Insert("B");
            bst.Insert("C");  // This should trigger a left rotation

            Assert::AreEqual(std::string("B"), bst.Find("B"));
            Assert::AreEqual(std::string("A"), bst.Find("A"));
            Assert::AreEqual(std::string("C"), bst.Find("C"));
        }

        // Test the right rotation function
        TEST_METHOD(TestRightRotation)
        {
            bst.Insert("C");
            bst.Insert("B");
            bst.Insert("A");  // This should trigger a right rotation

            Assert::AreEqual(std::string("B"), bst.Find("B"));
            Assert::AreEqual(std::string("A"), bst.Find("A"));
            Assert::AreEqual(std::string("C"), bst.Find("C"));
        }

        // Test left-right rotation
        TEST_METHOD(TestLeftRightRotation)
        {
            bst.Insert("C");
            bst.Insert("A");
            bst.Insert("B");  // This should trigger a left-right rotation

            Assert::AreEqual(std::string("B"), bst.Find("B"));
            Assert::AreEqual(std::string("A"), bst.Find("A"));
            Assert::AreEqual(std::string("C"), bst.Find("C"));
        }

        // Test right-left rotation
        TEST_METHOD(TestRightLeftRotation)
        {
            bst.Insert("A");
            bst.Insert("C");
            bst.Insert("B");  // This should trigger a right-left rotation

            Assert::AreEqual(std::string("B"), bst.Find("B"));
            Assert::AreEqual(std::string("A"), bst.Find("A"));
            Assert::AreEqual(std::string("C"), bst.Find("C"));
        }

        // Test balancing after insertions and removals
        TEST_METHOD(TestInsertAndRemoveBalance)
        {
            bst.Insert("F");
            bst.Insert("B");
            bst.Insert("G");
            bst.Insert("A");
            bst.Insert("D");
            bst.Insert("I");
            bst.Insert("C");
            bst.Insert("E");

            bst.Remove("B");  // This should trigger rebalancing

            Assert::AreEqual(std::string("F"), bst.Find("F"));
            Assert::AreEqual(std::string("A"), bst.Find("A"));
            Assert::AreEqual(std::string("D"), bst.Find("D"));
            Assert::AreEqual(std::string("G"), bst.Find("G"));
            Assert::AreEqual(std::string("C"), bst.Find("C"));
            Assert::AreEqual(std::string("E"), bst.Find("E"));
            Assert::AreEqual(std::string("I"), bst.Find("I"));
        }
    };
}
