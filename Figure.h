#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>


class Figure{
public:
    Figure();
    ~Figure();
    void show();
    void save(std::string file_name = "plot.png");


private:

    void set_plot_style(std::string plot_style);
    void draw();

    FILE* gnuplot_stream;
    std::vector<std::string> temp_data_files;
    std::vector<std::string> line_styles;
    std::vector<std::string> line_colours;
    std::vector<std::string> line_markers;
    std::vector<std::string> line_spec;
    static int num_figures;

    static std::vector<std::string> matlab_line_styles;
    static std::vector<std::string> gnuplot_line_styles;

    static std::vector<std::string> matlab_line_colours;
    static std::vector<std::string> gnuplot_line_colours;

    static std::vector<std::string> matlab_line_markers;
    static std::vector<std::string> gnuplot_line_markers;

    int id;
    int num_plots = 0;




public: // VIEZE TEMPLATES
    template <typename T, typename D>
    void plot(std::vector<T>& x, std::vector<D>& y, std::string plot_style = "-") {
        num_plots++;
        set_plot_style(plot_style);
        std::string filename = "temp"+std::to_string(id)+"data"+std::to_string(num_plots)+".txt";
        std::ofstream f(filename);
        for (int i = 0; i < x.size(); i++) {
            f << x[i] << " " << y[i] << std::endl;
        }
        temp_data_files.push_back(filename);
    }

    template <typename T>
    void plot(std::vector<T>& y, std::string plot_style = "-"){
        num_plots++;
        set_plot_style(plot_style);
        std::string filename = "temp"+std::to_string(id)+"data"+std::to_string(num_plots)+".txt";
        std::ofstream f(filename);
        for (int i = 0; i < y.size(); i++) {
            f << i << " " << y[i] << std::endl;
        }
        temp_data_files.push_back(filename);
    }
};


