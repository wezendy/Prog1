/* Compile command
g++ drill13.cpp Graph.cpp Window.cpp GUI.cpp Simple_window.cpp -o drill13 `fltk-config --ldflags --use-images`
*/
#include "Simple_window.h"
#include "Graph.h"

#include <string>
#include <iostream>

using namespace Graph_lib;

int main()
try {
    // Ch 13 Drill

    // 1. Make an 800x1000 window
    const Point tl {100, 100};
    Simple_window win {tl, 800, 1000, "Chapter 13 Drill"};
    win.wait_for_button();

    // 2. Put an 8x8 grid of 100 pixel squares
    int x_size = 800;
    int y_size = 800;
    int x_grid = 100;
    int y_grid = 100;

    Lines grid;
    for (int x = x_grid; x < x_size; x += x_grid)
        grid.add(Point{x, 0}, Point{x, y_size});    // vertical lines
    for (int y = y_grid; y < y_size; y += y_grid)
        grid.add(Point{0, y}, Point{x_size, y});

    grid.set_color(Color::red);
    
    win.attach(grid);
    win.wait_for_button();

    // 3. Make top left diagonal down all red
    Vector_ref<Rectangle> rects;     
    for (int i = 0; i < x_size; i += x_grid) {
        rects.push_back(new Rectangle{Point{i,i}, Point{i+x_grid,i+x_grid}});
        rects[rects.size() - 1].set_color(Color::invisible);
        rects[rects.size() - 1].set_fill_color(Color::red);
        win.attach(rects[rects.size() - 1]);
    }

    win.wait_for_button();

    // 4. Add 3 copies of a 200x200 image
    Image badge1 {Point{100,349}, "badge.jpg"};
    badge1.set_mask(Point{40,40},200,200);
    Image badge2 {Point{581,600}, "badge.jpg"};
    badge2.set_mask(Point{45,45},200,200);
    Image badge3 {Point{11,73}, "badge.jpg"};
    badge3.set_mask(Point{50,50},200,200);

    win.attach(badge1);
    win.attach(badge2);
    win.attach(badge3);
    win.wait_for_button();

    // 5. Add a 100x100 image and make it move when next is pressed
    Image badge4 {Point{0,0}, "badge.jpg"};
    badge4.set_mask(Point{90,90},100,100);
    win.attach(badge4);
    

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j<8; ++j)
        {
            win.wait_for_button();
            if (i == 7 and j == 7) break; //this prevents the img to move outside of the grid
            if(j<7) badge4.move(100,0);
            else badge4.move(-700,100);
        }
    }
}

catch(exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch(...) {
    cerr << "error\n";
    return 2;
}
