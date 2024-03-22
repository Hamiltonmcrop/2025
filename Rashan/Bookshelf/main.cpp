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

bool compareHeight(const Book& a, const Book& b) {
    return a.height > b.height;
}

vector<Shelf> layout_books(const vector<int>& heights, const vector<int>& thicknesses, int W) {
    vector<Shelf> shelves;
    Shelf current_shelf;
    int current_shelf_height = 0;

    for (size_t i = 0; i < heights.size(); ++i) {
        if (current_shelf_height + thicknesses[i] <= W) {
            current_shelf.books.push_back({static_cast<int>(i) + 1, heights[i], thicknesses[i]});
            current_shelf_height += thicknesses[i];
        } else {
            shelves.push_back(current_shelf);
            current_shelf = Shelf{{}, 0};
            current_shelf.books.push_back({static_cast<int>(i) + 1, heights[i], thicknesses[i]});
            current_shelf_height = thicknesses[i];
        }
    }

    if (!current_shelf.books.empty()) {
        shelves.push_back(current_shelf);
    }

    sort(shelves.begin(), shelves.end(), [](const Shelf& a, const Shelf& b) {
        return a.books[0].height > b.books[0].height;
    });

    for (auto& shelf : shelves) {
        sort(shelf.books.begin(), shelf.books.end(), compareHeight);
        int max_book_height = shelf.books.front().height;
        shelf.total_height = max_book_height;
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
