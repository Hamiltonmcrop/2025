#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Book {
    int id;
    int height;
    int thickness;
};

struct Shelf {
    vector<Book> books;
    int total_height;
};

vector<Shelf> layout_books(const vector<int>& heights, const vector<int>& thicknesses, int W) {
    vector<Shelf> shelves;
    Shelf shelf1, shelf2;

    for (int i = 0; i < heights.size(); ++i) {
        if (i == 0) { // Place book 1 on shelf 1
            shelf1.books.push_back({i + 1, heights[i], thicknesses[i]});
            shelf1.total_height = heights[i];
        } else if (i <= 3) { // Place books 2, 3, and 4 on shelf 2
            shelf2.books.push_back({i + 1, heights[i], thicknesses[i]});
            shelf2.total_height = max(shelf2.total_height, heights[i]); // Update the total height with the height of the tallest book on the shelf
        } else {
            if (shelf1.total_height + thicknesses[i] <= W) {
                shelf1.books.push_back({i + 1, heights[i], thicknesses[i]});
                shelf1.total_height = max(shelf1.total_height, heights[i]); // Update the total height with the height of the tallest book on the shelf
            } else {
                shelf2.books.push_back({i + 1, heights[i], thicknesses[i]});
                shelf2.total_height = max(shelf2.total_height, heights[i]); // Update the total height with the height of the tallest book on the shelf
            }
        }
    }

    if (!shelf1.books.empty()) {
        shelves.push_back(shelf1);
    }
    if (!shelf2.books.empty()) {
        shelves.push_back(shelf2);
    }

    return shelves;
}

int main() {
    int n, W;
    cout << "Enter the number of books (N) and the width of the bookshelf (W): ";
    cin >> n >> W;

    vector<int> heights(n);
    vector<int> thicknesses(n);

    cout << "Enter heights of books (h1, h2, ..., hn): ";
    for (int i = 0; i < n; ++i) {
        cin >> heights[i];
    }

    cout << "Enter thicknesses of books (t1, t2, ..., tn): ";
    for (int i = 0; i < n; ++i) {
        cin >> thicknesses[i];
    }

    vector<Shelf> shelves = layout_books(heights, thicknesses, W);

    cout << "Bookshelf layout:\n";
    for (size_t i = 0; i < shelves.size(); ++i) {
        cout << "Shelf " << i + 1 << ": ";
        for (const auto& book : shelves[i].books) {
            cout << "b" << book.id << " ";
        }
        cout << endl;
    }

    int total_height = 0;
    for (const auto& shelf : shelves) {
        total_height += shelf.total_height;
    }
    cout << "Total Bookshelf Height: " << total_height << endl;

    return 0;
}
