#include <gtk/gtk.h>
#define WINDOW_TITLE "C Web Scraper"

GtkWidget *window, *grid, *button, *label;

static void prevString(GtkWidget *widget, gpointer data) {
	gtk_label_set_text(GTK_LABEL(label), "It works!");
}

static void nextString(GtkWidget *widget, gpointer data) {
	gtk_label_set_text(GTK_LABEL(label), "It works again!");
}

// https://developer.gnome.org/gtk3/stable/gtk-getting-started.html
static void activate (GtkApplication* app, gpointer user_data) {

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), WINDOW_TITLE);
	gtk_container_set_border_width(GTK_CONTAINER (window), 10);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER (window), grid);

	button = gtk_button_new_with_label("<");
	g_signal_connect(button, "clicked", G_CALLBACK(prevString), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

	label = gtk_label_new(" ... ");
	gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 2, 1);

	button = gtk_button_new_with_label(">");
	g_signal_connect(button, "clicked", G_CALLBACK(nextString), NULL);
	gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

	gtk_widget_show_all (window);
}

int main (int argc, char **argv) {
	GtkApplication *app;
	int status;

	// http://www.cplusplus.com/forum/windows/36638/
	CURL* curl = curl_easy_init();
	CURLcode res;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	app = gtk_application_new ("com.avedati.cwebscraper", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
