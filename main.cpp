#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tile.H>

class MainWindow : public Fl_Window {
private:
    static void quit_callback(Fl_Widget *, void *data) {
        std::cout << "Quit" << std::endl;
        auto mw = (MainWindow *) data;
        mw->hide();
    }

public:
    MainWindow(int x, int y, int w, int h, const char *title) : Fl_Window(x,y,w,h, title) {
        this->begin();

        auto menu_bar = new Fl_Menu_Bar(0,0, this->w(), 25);
        menu_bar->add("File/Quit", FL_COMMAND + 'q', quit_callback, this);

        auto file_tree = new Fl_Tree(0, menu_bar->h(), 200, this->h());

        auto text_editor = new Fl_Text_Editor(file_tree->w(), menu_bar->h(), this->w() - file_tree->w(), this->h());
        auto text_buffer = new Fl_Text_Buffer();
        text_editor->buffer(text_buffer);
        this->end();

        resizable(this);
    }
};

int main()
{
    auto main_window = new MainWindow(100, 100, 640, 480, "alcode");

    main_window->show();

    return Fl::run();
}