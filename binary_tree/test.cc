#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include "AVLTree.h" // Подключаем заголовочный файл с реализацией AVL-дерева

// Тестирование вставки элементов в AVL-дерево
TEST(AVLTreeTest, InsertTest) {
    AVLTree<int> tree;
    
    // Вставка элементов
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    
    // Ожидаемый результат
    std::stringstream expected;
    expected << "10 20 30 40 50 \n";
    
    // Получение фактического результата
    std::ostringstream actual; // Используем std::ostringstream вместо std::stringstream
    tree.printInOrder(actual);
    
    // Проверка соответствия ожидаемого и фактического результатов
    ASSERT_EQ(expected.str(), actual.str());
}

// Тестирование вставки и обхода пустого AVL-дерева
TEST(AVLTreeTest, EmptyTreeTest) {
    AVLTree<int> tree;
    
    // Ожидаемый результат
    std::stringstream expected;
    expected << "\n";
    // Получение фактического результата
    std::ostringstream actual; // Используем std::ostringstream вместо std::stringstream
    tree.printInOrder(actual);
    
    // Проверка соответствия ожидаемого и фактического результатов
    ASSERT_EQ(expected.str(), actual.str());
}

// Тестирование вставки и обхода AVL-дерева с одним элементом
TEST(AVLTreeTest, SingleElementTest) {
    AVLTree<int> tree;
    
    // Вставка элемента
    tree.insert(10);
    
    // Ожидаемый результат
    std::stringstream expected;
    expected << "10 \n";
    
    // Получение фактического результата
    std::ostringstream actual; // Используем std::ostringstream вместо std::stringstream
    tree.printInOrder(actual);
    
    // Проверка соответствия ожидаемого и фактического результатов
    ASSERT_EQ(expected.str(), actual.str());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
