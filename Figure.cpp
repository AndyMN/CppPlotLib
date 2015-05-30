#include "Figure.h"


int Figure::num_figures = 0;

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
   /* if (plot_style.size() > 4) {
        std::cerr << "Too many specifiers." << std::endl;
        return;
    }*/
    bool line_style_set = false;
    bool line_colour_set = false;
    bool line_marker_set = false;

    if (plot_style.find("--") != std::string::npos && !line_style_set) {
		std::cout << "-- found" << std::endl;
		line_styles.push_back("2");
		line_style_set = true;
    }
    if (plot_style.find("r") != std::string::npos && !line_colour_set) {
		std::cout << "r found" << std::endl;
		line_colours.push_back("1");
		line_colour_set = true;
    }
    if (plot_style.find("+") != std::string::npos && !line_marker_set) {
		std::cout << "+ found" << std::endl;
		line_markers.push_back("1");
		line_marker_set = true;
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
    if (gnuplot_stream != NULL) {
        if (temp_data_files.size() > 1){
            for (int i = 0; i < temp_data_files.size(); i++) {
                if (i == 0) {
                    gnuplot_command = "plot '"+ temp_data_files[i]+"' using 1:2 lt " + line_styles[i] +" lc "+ line_colours[i]+", \\\n";
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
			gnuplot_command = "plot '"+ temp_data_files[0]+"' using 1:2 with linespoints lt " + line_styles[0] +" lc "+ line_colours[0]+" pt "+line_markers[0] +" \\\n";
            fprintf(gnuplot_stream, gnuplot_command.c_str());
        }

        fflush(gnuplot_stream);
    }
}
