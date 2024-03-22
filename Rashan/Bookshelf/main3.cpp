#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct Book {
    int id;
    int height;
};

struct Shelf {
    vector<Book> books;
    int total_height;
};

vector<Shelf> layout_books(const vector<int>& heights, int W) {
    vector<Shelf> shelves;
    Shelf current_shelf;
    int current_shelf_height = 0;

    for (size_t i = 0; i < heights.size(); ++i) {
        if (current_shelf_height + heights[i] <= W) {
            current_shelf.books.push_back({static_cast<int>(i) + 1, heights[i]});
            current_shelf_height += heights[i];
        } else {
            shelves.push_back(current_shelf);
            current_shelf = Shelf{{}, 0};
            current_shelf.books.push_back({static_cast<int>(i) + 1, heights[i]});
            current_shelf_height = heights[i];
        }
    }

    if (!current_shelf.books.empty()) {
        shelves.push_back(current_shelf);
    }

    return shelves;
}

int main() {
    int num_sizes;
    cout << "Enter the number of input sizes: ";
    cin >> num_sizes;

    vector<int> input_sizes(num_sizes);
    cout << "Enter the input sizes: ";
    for (int i = 0; i < num_sizes; ++i) {
        cin >> input_sizes[i];
    }

    int W;
    cout << "Enter the width of the bookshelf: ";
    cin >> W;

    // Measure running time for each input size
    for (int size : input_sizes) {
        vector<int> heights(size);
        for (int i = 0; i < size; ++i) {
            heights[i] = rand() % 100 + 1; // Random height between 1 and 100
        }

        auto start = chrono::high_resolution_clock::now();
        vector<Shelf> shelves = layout_books(heights, W);
        auto end = chrono::high_resolution_clock::now();

        double duration = chrono::duration_cast<chrono::milliseconds>(end - start).count() / 1000.0;
        cout << "Input size: " << size << ", Running time: " << duration << " seconds" << endl;
    }

    return 0;
}
