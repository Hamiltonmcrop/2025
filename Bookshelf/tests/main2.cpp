 
#include <iostream>
 
#include <algorithm>
 
#include <vector>
 
 
#define NMAX 10000
 
#define KMAX 10000
 
 
using namespace std;
 
 
struct Book {
 
    uint32_t id, height, thickness, width;
 
    uint32_t shelf_id, corner_x, corner_y;
 
    bool rotated = false;
 
};
 
 
struct Free_Rectangle {
 
    uint32_t corner_x, corner_y, width, height;
 
};
 
 
struct Shelf {
 
    uint32_t id, width, height, thickness;
 
    uint32_t cost;
 
    vector<Free_Rectangle> list_free_rectangles;
 
    vector<Book> list_books;
 
};
 
 
uint32_t n_books, n_shelves;
 
Book book[NMAX];
 
Shelf shelf[KMAX];
 
 
bool compareBook(Book a, Book b) {
 
    if (a.height == b.height)
 
        return a.thickness > b.thickness;
 
    return a.height > b.height;
 
}
 
 
void rotateBook(Book &book) {
 
    book.rotated = !book.rotated;
 
    uint32_t temp = book.width;
 
    book.width = book.thickness;
 
    book.thickness = temp;
 
}
 
 
bool isFitToFreeRectangle(Free_Rectangle rec, Book book, bool rotated) {
 
    if (rotated)
 
        return (book.width <= rec.height) && (book.height <= rec.width);
 
    return (book.width <= rec.width) && (book.height <= rec.height);
 
}
 
 
pair<uint32_t, uint32_t> getFreeRectangleScore(Free_Rectangle rec, Book book, bool rotated) {
 
    pair<uint32_t, uint32_t> score;
 
    uint32_t remain_width = rec.width - (rotated ? book.height : book.width);
 
    uint32_t remain_height = rec.height - (rotated ? book.width : book.height);
 
    score.first = min(remain_width, remain_height);
 
    score.second = max(remain_width, remain_height);
 
    return score;
 
}
 
 
bool compareFreeRectangleScore(pair<uint32_t, uint32_t> a, pair<uint32_t, uint32_t> b) {
 
    return (a.first == b.first) ? (a.second < b.second) : (a.first < b.first);
 
}
 
 
Free_Rectangle findSuitableFreeRectangle(Shelf shelf, Book book) {
 
    Free_Rectangle suitable_rec;
 
    pair<uint32_t, uint32_t> best_score = {UINT32_MAX, UINT32_MAX};
 
 
    const uint32_t n_rectangles = shelf.list_free_rectangles.size();
 
    for (uint32_t i = 0; i < n_rectangles; ++i) {
 
        Free_Rectangle rec = shelf.list_free_rectangles[i];
 
 
        // Not rotate case
 
        pair<uint32_t, uint32_t> rec_score = getFreeRectangleScore(rec, book, false);
 
        if (isFitToFreeRectangle(rec, book, false) && compareFreeRectangleScore(rec_score, best_score)) {
 
            best_score = rec_score;
 
            suitable_rec = rec;
 
        }
 
 
        // Rotate case
 
        rec_score = getFreeRectangleScore(rec, book, true);
 
        if (isFitToFreeRectangle(rec, book, true) && compareFreeRectangleScore(rec_score, best_score)) {
 
            best_score = rec_score;
 
            suitable_rec = rec;
 
        }
 
    }
 
 
    return suitable_rec;
 
}
 
 
void splitFreeRectangle(bool isHorizontalSplit, Free_Rectangle rec, Book book, Shelf &shelf) {
 
    Free_Rectangle right_rec;
 
    right_rec.width = rec.width - book.width;
 
    if (right_rec.width > 0) {
 
        right_rec.corner_x = rec.corner_x + book.width;
 
        right_rec.corner_y = rec.corner_y;
 
        right_rec.height = isHorizontalSplit ? book.height : rec.height;
 
        shelf.list_free_rectangles.push_back(right_rec);
 
    }
 
 
    Free_Rectangle top_rec;
 
    top_rec.height = rec.height - book.height;
 
    if (top_rec.height > 0) {
 
        top_rec.corner_x = rec.corner_x;
 
        top_rec.corner_y = rec.corner_y + book.height;
 
        top_rec.width = isHorizontalSplit ? rec.width : book.width;
 
        shelf.list_free_rectangles.push_back(top_rec);
 
    }
 
}
 
 
void solve() {
 
    for (uint32_t i = 1; i <= n_books; ++i) {
 
        for (uint32_t j = 1; j <= n_shelves; ++j) {
 
            cout << "Enter width, height, and thickness for book " << i << " and shelf " << j << ": ";
 
            cin >> book[i].width >> book[i].height >> book[i].thickness;
 
            book[i].id = i;
 
            if (book[i].width > book[i].height)
 
                rotateBook(book[i]);
 
 
            Free_Rectangle suitable_rec = findSuitableFreeRectangle(shelf[j], book[i]);
 
            if (suitable_rec.width != 0 && suitable_rec.height != 0) {
 
                // Add the book into the chosen free_rec
 
                book[i].shelf_id = shelf[j].id;
 
                book[i].corner_x = suitable_rec.corner_x;
 
                book[i].corner_y = suitable_rec.corner_y;
 
                shelf[j].list_books.push_back(book[i]);
 
 
                // Replace the used free_rec by the new split rec(s)
 
                shelf[j].list_free_rectangles.erase(
 
                    remove_if(shelf[j].list_free_rectangles.begin(), shelf[j].list_free_rectangles.end(),
 
                              [&suitable_rec](const Free_Rectangle &rec) {
 
                                  return (rec.corner_x == suitable_rec.corner_x) && (rec.corner_y == suitable_rec.corner_y);
 
                              }),
 
                    shelf[j].list_free_rectangles.end());
 
 
                splitFreeRectangle(suitable_rec.width <= suitable_rec.height, suitable_rec, book[i], shelf[j]);
 
                break;
 
            }
 
        }
 
    }
 
}
 
 
void printSolution() {
 
    for (uint32_t i = 1; i <= n_books; ++i) {
 
        cout << "Book " << book[i].id << " is placed on shelf " << book[i].shelf_id << " at position (" << book[i].corner_x << ", "
 
             << book[i].corner_y << ") and is" << (book[i].rotated ? " rotated" : " not rotated") << "\n";
 
    }
 
}
 
 
int main() {
 
    ios_base::sync_with_stdio(0);
 
    cin.tie(0);
 
    cout.tie(0);
 
 
    cout << "Enter the number of books and shelves: ";
 
    cin >> n_books >> n_shelves;
 
 
    for (uint32_t i = 1; i <= n_shelves; ++i) {
 
        cout << "Enter width, height, thickness, and cost for shelf " << i << ": ";
 
        cin >> shelf[i].width >> shelf[i].height >> shelf[i].thickness >> shelf[i].cost;
 
 
        Free_Rectangle first_rec;
 
        first_rec.width = shelf[i].width;
 
        first_rec.height = shelf[i].height;
 
        first_rec.corner_x = 0;
 
        first_rec.corner_y = 0;
 
        shelf[i].list_free_rectangles.push_back(first_rec);
 
    }
 
 
    solve();
 
    printSolution();
 
    return 0;
 
}
 

