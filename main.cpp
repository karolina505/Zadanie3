
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

#include "arraylist.hpp"

int main() {
    ArrayList<int> a(5);
    assert(a.empty());
    assert(!a.full());
    assert(a.size() == 0);
    assert(a.max_size() == 5);

    // push_back / push_front / front / back
    a.push_back(2);
    a.push_back(3);
    a.push_front(1);
    assert(a.size() == 3);
    assert(a.front() == 1);
    assert(a.back() == 3);
    assert(a[1] == 2);

    // front() i back() pozwaaja zapisywac
    a.front() = 10;
    a.back() = 30;
    assert(a[0] == 10 && a[2] == 30);

    // insert / erase / index
    a.insert(1, 15);  // 10 15 2 30
    assert(a.size() == 4 && a[1] == 15 && a[2] == 2 && a[3] == 30);
    a.insert(4, 40);  // na koniec: 10 15 2 30 40
    assert(a.full());
    assert(a.back() == 40);
    assert(a.index(30) == 3);
    assert(a.index(999) == -1);
    a.erase(1);       // 10 2 30 40
    assert(a.size() == 4 && a[1] == 2);
    assert(!a.full());

    // sort / reverse
    a.sort();         // 2 10 30 40
    assert(a[0] == 2 && a[1] == 10 && a[2] == 30 && a[3] == 40);
    a.reverse();      // 40 30 10 2
    assert(a[0] == 40 && a[3] == 2);

    // pop_front / pop_back
    a.pop_front();
    a.pop_back();
    assert(a.size() == 2 && a.front() == 30 && a.back() == 10);

    // przepelnienie
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    assert(a.full());
    bool thrown = false;
    try { a.push_back(4); } catch (const std::length_error&) { thrown = true; }
    assert(thrown);
    thrown = false;
    try { a.push_front(4); } catch (const std::length_error&) { thrown = true; }
    assert(thrown);
    thrown = false;
    try { a.insert(0, 4); } catch (const std::length_error&) { thrown = true; }
    assert(thrown);

    // bledne indeksy
    thrown = false;
    try { (void)a[5]; } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);
    thrown = false;
    try { a.erase(5); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    // clear i operacje na pustej liscie
    a.clear();
    assert(a.empty() && a.size() == 0);
    thrown = false;
    try { a.front(); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);
    thrown = false;
    try { a.pop_back(); } catch (const std::out_of_range&) { thrown = true; }
    assert(thrown);

    // kopiowanie
    ArrayList<std::string> s(4);
    s.push_back("kot");
    s.push_back("pies");
    s.push_front("ala");
    ArrayList<std::string> c(s);
    c[0] = "ola";
    assert(s[0] == "ala" && c[0] == "ola");
    ArrayList<std::string> d(2);
    d = s;
    assert(d.size() == 3 && d[2] == "pies" && d.max_size() == 4);

    s.display();
    c.display();
    std::cout << "Wszystkie testy OK" << std::endl;
    return 0;
}