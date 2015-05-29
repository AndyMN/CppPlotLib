#include "Figure.h"


int Figure::num_figures = 0;

Figure::Figure() {
    num_figures++;

    id = num_figures;

    gnuplot_stream = popen("/usr/bin/gnuplot","w");


}

Figure::~Figure() {
    num_figures--;
}


void Figure::set_plot_style(std::string plot_style) {
    if (plot_style.size() > 4) {
        std::cerr << "Too many specifiers." << std::endl;
    }


}

void Figure::show() {
    if (gnuplot_stream != NULL) {
        fprintf(gnuplot_stream, "set term x11 persist\n");
        draw();
    }
}

void Figure::save(std::string file_name) {
	if (gnuplot_stream != NULL) {
		fprintf(gnuplot_stream, "set term png\n");
		std::string gnuplot_command = "set output '"+file_name+"'\n";
		fprintf(gnuplot_stream, gnuplot_command.c_str());
		draw();
	}
}

void Figure::draw() {
    std::string gnuplot_command;
    if (gnuplot_stream != NULL) {
        if (temp_data_files.size() > 1){
            for (int i = 0; i < temp_data_files.size(); i++) {
                if (i == 0) {
                    gnuplot_command = "plot '"+ temp_data_files[i]+"' using 1:2 with " + line_styles[i] +", \\\n";
                    fprintf(gnuplot_stream, gnuplot_command.c_str());
                } else if (i < temp_data_files.size() - 1) {
                    gnuplot_command = "'"+temp_data_files[i]+"' using 1:2 with " + line_styles[i] +", \\\n";
                    fprintf(gnuplot_stream, gnuplot_command.c_str());
                } else {
                    gnuplot_command = "'"+temp_data_files[i]+"' using 1:2 with " + line_styles[i] +"\n";
                    fprintf(gnuplot_stream, gnuplot_command.c_str());
                }
            }
        } else {
            gnuplot_command = "plot '"+temp_data_files[0]+"' using 1:2 with " + line_styles[0];
            fprintf(gnuplot_stream, gnuplot_command.c_str());
        }

        fflush(gnuplot_stream);
    }
}
