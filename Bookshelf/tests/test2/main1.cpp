 
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
 
    Shelf current_shelf;
 
    int current_shelf_height = 0;
 
    for (size_t i = 0; i < heights.size(); ++i) {
 
        if (current_shelf_height + thicknesses[i] <= W) {
 
            // Add book to current shelf
 
            current_shelf.books.push_back({static_cast<int>(i) + 1, heights[i], thicknesses[i]});
 
            current_shelf_height += thicknesses[i];
 
        } else {
 
            // Start a new shelf
 
            shelves.push_back(current_shelf);
 
            current_shelf = Shelf{{}, 0};
 
            current_shelf.books.push_back({static_cast<int>(i) + 1, heights[i], thicknesses[i]});
 
            current_shelf_height = thicknesses[i];
 
        }
 
    }
 
    // Add the last shelf
 
    if (!current_shelf.books.empty()) {
 
        shelves.push_back(current_shelf);
 
    }
 
    return shelves;
 
}
 
 
int total_bookshelf_height(const vector<Shelf>& shelves) {
 
    int total_height = 0;
 
    for (const auto& shelf : shelves) {
 
        int max_book_height = 0;
 
        for (const auto& book : shelf.books) {
 
            max_book_height = max(max_book_height, book.height);
 
        }
 
        total_height += max_book_height;
 
    }
 
    return total_height;
 
}
 
 
int main() {
 
    int N, W;
 
    cout << "Enter the number of books (N) and the width of the bookshelf (W): ";
 
    cin >> N >> W;
 
 
    vector<int> heights(N);
 
    vector<int> thicknesses(N);
 
 
    cout << "Enter heights of books (h1, h2, ..., hn): ";
 
    for (int i = 0; i < N; ++i) {
 
        cin >> heights[i];
 
    }
 
 
    cout << "Enter thicknesses of books (t1, t2, ..., tn): ";
 
    for (int i = 0; i < N; ++i) {
 
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
 
 
    cout << "Total Bookshelf Height: " << total_bookshelf_height(shelves) << endl;
 
 
    return 0;
 
}
 

