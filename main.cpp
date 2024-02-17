#include <iostream>
#include <fstream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_File_Chooser.H>

class FixedHeightMenuBar : public Fl_Menu_Bar {

private:
    void resize(int x, int y, int w, int) override {
        Fl_Widget::resize(x, y, w, this->h());
    }

public:
    FixedHeightMenuBar(int X, int Y, int W, int H, const char *l = nullptr) : Fl_Menu_Bar(X, Y, W, H, l) {
    }

};

class MainWindow : public Fl_Window {
private:

    Fl_Text_Buffer tb;

    static void quit_callback(Fl_Widget *, void *data) {
        std::cout << "Quit" << std::endl;
        auto mw = (MainWindow *) data;
        mw->hide();
    }

    static void open_callback(Fl_Widget* w, void* data) {
    	std::cout << "Open" << std::endl;
	auto mw = (MainWindow* ) data;
	auto file_name  = fl_file_chooser("Open...", "*", NULL);
	if (file_name == nullptr)
		return;

	std::cout << "Choosen " << file_name << std::endl;
	mw->tb.loadfile(file_name);
    }

public:
    MainWindow(int x, int y, int w, int h, const char *title) : Fl_Window(x,y,w,h, title) {
        this->begin();

        auto menu_bar = new FixedHeightMenuBar(0, 0, this->w(), 25);
        menu_bar->add("File/Quit", FL_COMMAND + 'q', quit_callback, this);
	menu_bar->add("File/Open", FL_COMMAND + 'o', open_callback, this);

        auto file_tree = new Fl_Tree(0, menu_bar->h(), 200, this->h());

        auto text_editor = new Fl_Text_Editor(file_tree->w(), menu_bar->h(), this->w() - file_tree->w(), this->h());
        text_editor->buffer(tb);
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
