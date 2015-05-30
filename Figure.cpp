#include "Figure.h"


int Figure::num_figures = 0;

std::vector<std::string> Figure::matlab_line_styles = {"--", "-", ":", "-."};
std::vector<std::string> Figure::gnuplot_line_styles = {"2", "1", "3", "5"};

std::vector<std::string> Figure::matlab_line_colours = {"y", "m", "c", "r", "g", "b", "w", "k"};
std::vector<std::string> Figure::gnuplot_line_colours = {"6", "4", "5", "1", "2", "3", "18", "7"};

// MISSING: Left triangle, Right triangle, Pentagram and Hexagram.
std::vector<std::string> Figure::matlab_line_markers = {"o", "+", "*", ".", "x", "s", "d", "^", "v"};
std::vector<std::string> Figure::gnuplot_line_markers = {"6", "1", "3", "0", "2", "4", "12", "8", "10"};

Figure::Figure() {
    num_figures++;

    id = num_figures;

    gnuplot_stream = popen("/usr/bin/gnuplot","w");


}

Figure::~Figure() {
	if (gnuplot_stream != NULL) {
		if (pclose(gnuplot_stream) == 0) {
			for (int i = 0; i < temp_data_files.size(); i++){
				remove(temp_data_files[i].c_str());
			}
		}
	}
    num_figures--;
}


void Figure::set_plot_style(std::string plot_style) {
   if (plot_style.size() > 4) {
        std::cerr << "Too many specifiers." << std::endl;
        return;
    }
    bool line_style_set = false;
    bool line_colour_set = false;
    bool line_marker_set = false;

    for (int i = 0; i < matlab_line_styles.size(); i++) {
		if (plot_style.find(matlab_line_styles[i]) != std::string::npos) {
			if (!line_style_set) {
				line_styles.push_back(gnuplot_line_styles[i]);
				line_style_set = true;
			} else {
				std::cerr << "Only 1 line style allowed !" << std::endl;
			}
		}
    }

    for (int i =0; i < matlab_line_colours.size(); i++) {
		if (plot_style.find(matlab_line_colours[i]) != std::string::npos) {
			if (!line_colour_set) {
				line_colours.push_back(gnuplot_line_colours[i]);
				line_colour_set = true;
			} else {
				std::cerr << "Only 1 line colour is allowed !" << std::endl;
			}
		}
    }

    for (int i = 0; i < matlab_line_markers.size(); i++) {
		if (plot_style.find(matlab_line_markers[i]) != std::string::npos) {
			if (!line_marker_set) {
				line_markers.push_back(gnuplot_line_markers[i]);
				line_marker_set = true;
			} else {
				std::cerr << "Only 1 line marker is allowed !" << std::endl;
			}
		}
    }

    if (!line_colour_set) {
		line_colours.push_back(std::to_string(num_plots)); //Cycle through colours
    }
    if (!line_marker_set) {
		line_markers.push_back("-1"); //No marker
    }
    if (!line_style_set) {
		line_styles.push_back("1"); //Solid line
		line_spec.push_back("points");
    } else {
		line_spec.push_back("linespoints");
    }

}

void Figure::show() {
    if (gnuplot_stream != NULL) {
        fprintf(gnuplot_stream, "set term wxt dashed persist\n");
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
    std::string style_string;
    if (gnuplot_stream != NULL) {
        if (temp_data_files.size() > 1){
            for (int i = 0; i < temp_data_files.size(); i++) {
				style_string = temp_data_files[i]+"' using 1:2 with " + line_spec[i] + " lt " + line_styles[i] +" lc "+ line_colours[i]+" pt " + line_markers[i];
                if (i == 0) {
                    gnuplot_command = "plot '" + style_string + ", \\\n";
                    fprintf(gnuplot_stream, gnuplot_command.c_str());
                } else if (i < temp_data_files.size() - 1) {
                    gnuplot_command = "'"+ style_string + ", \\\n";
                    fprintf(gnuplot_stream, gnuplot_command.c_str());
                } else {
                    gnuplot_command = "'"+ style_string + "\\\n";
                    fprintf(gnuplot_stream, gnuplot_command.c_str());
                }
            }
        } else {
			gnuplot_command = "plot '"+ temp_data_files[0]+"' using 1:2 with linespoints lt " + line_styles[0] +" lc "+ line_colours[0]+" pt "+line_markers[0] +" \\\n";
            fprintf(gnuplot_stream, gnuplot_command.c_str());
        }
        fflush(gnuplot_stream);
    }
}
