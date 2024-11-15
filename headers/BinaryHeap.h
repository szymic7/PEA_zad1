//
// Created by szymo on 10.11.2024.
//

#ifndef PEA_ZAD1_BINARYHEAP_H
#define PEA_ZAD1_BINARYHEAP_H

#include <stdexcept>
#include "C:\Users\szymo\CLionProjects\PEA_zad1\headers\little.h"

using namespace std;

// Kopiec minimalny, do przechowywania uporządkowanych węzłów
class BinaryHeap {

    public:
        void push(Node node) {
            heap.push_back(node);
            heapifyUp(heap.size() - 1);
        }

        Node pop() {
            if (heap.empty()) throw out_of_range("Heap is empty");
            Node minNode = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            if (!heap.empty()) heapifyDown(0);
            return minNode;
        }

        Node top() const {
            if (heap.empty()) throw out_of_range("Heap is empty");
            return heap[0];
        }

        bool empty() const {
            return heap.empty();
        }

    private:
        std::vector<Node> heap;

        void heapifyUp(int index) {
            while (index > 0 && heap[parent(index)].cost > heap[index].cost) {
                swap(heap[index], heap[parent(index)]);
                index = parent(index);
            }
        }

        void heapifyDown(int index) {
            int minIndex = index;
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < heap.size() && heap[left].cost < heap[minIndex].cost)
                minIndex = left;

            if (right < heap.size() && heap[right].cost < heap[minIndex].cost)
                minIndex = right;

            if (index != minIndex) {
                std::swap(heap[index], heap[minIndex]);
                heapifyDown(minIndex);
            }
        }

        int parent(int index) const { return (index - 1) / 2; }
        int leftChild(int index) const { return 2 * index + 1; }
        int rightChild(int index) const { return 2 * index + 2; }
};

#endif //PEA_ZAD1_BINARYHEAP_H
