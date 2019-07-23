#include "../include/string.h"
#include "../include/vector.h"
#include <gtk/gtk.h>
#include <curl/curl.h>
#define WINDOW_TITLE "C Web Scraper"
#define WINDOW_WIDTH 240
#define WINDOW_HEIGHT 120

GtkWidget *window, *fixed, *button, *label;
struct vector *contents;
int pos;

static void prevString(GtkWidget *widget, gpointer data) {
	if(--pos < 0) {
		pos = contents->len - 1;
	}
	gtk_label_set_text(GTK_LABEL(label), (char*)vector_get(contents,pos));
}

static void nextString(GtkWidget *widget, gpointer data) {
	pos = (pos + 1) % contents->len;
	gtk_label_set_text(GTK_LABEL(label), (char*)vector_get(contents,pos));
}

// https://developer.gnome.org/gtk3/stable/gtk-getting-started.html
static void activate (GtkApplication* app, gpointer user_data) {
	window = gtk_application_window_new (app);
	gtk_window_set_default_size( GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);

	gtk_window_set_title (GTK_WINDOW (window), WINDOW_TITLE);
	gtk_container_set_border_width(GTK_CONTAINER (window), 10);

	fixed = gtk_fixed_new();
	gtk_container_add(GTK_CONTAINER(window), fixed);
	gtk_widget_show(fixed);

	button = gtk_button_new_with_label("<");
	g_signal_connect(button, "clicked", G_CALLBACK(prevString), NULL);
	gtk_fixed_put(GTK_FIXED(fixed), button, 10, 10);

	label = gtk_label_new(" ... ");
	gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
	gtk_fixed_put(GTK_FIXED(fixed), label, 10, 70);

	button = gtk_button_new_with_label(">");
	g_signal_connect(button, "clicked", G_CALLBACK(nextString), NULL);
	gtk_fixed_put(GTK_FIXED(fixed), button, 60, 10);

	gtk_widget_show_all (window);
}

// https://stackoverflow.com/questions/2329571/c-libcurl-get-output-into-a-string
static size_t write_function(void* ptr, size_t size, size_t nmemb, void* mem) {
	struct string* string = (struct string*)mem;
	string->str = realloc(string->str, strlen(string->str) + size*nmemb + sizeof(char));
	strcat(string->str, ptr);
	strcat(string->str, "\0");
	string->len += size * nmemb;
	return size * nmemb;
}

struct vector* parse(struct string* string) {
	struct vector* vec = vector_init();
	for(int i=0;i<strlen(string->str);i++) {
		if(string->str[i] == '<') {
			for(;i<strlen(string->str)&&string->str[i]!='>';i++) {}
		}
		else {
			char* content = malloc(0);
			int num_chars = 0;
			for(;i<strlen(string->str)&&string->str[i]!='<';i++) {
				content = realloc(content, sizeof(char) * (num_chars + 1));
				content[num_chars++] = string->str[i];
			}
			i--;
			content = realloc(content, sizeof(char) * (num_chars + 1));
			content[num_chars++] = 0;
			vector_add(vec, (void*)content);
		}
	}
	return vec;
}

int main (int argc, char **argv) {
	GtkApplication *app;
	int status;

	// http://www.cplusplus.com/forum/windows/36638/
	CURL* curl = curl_easy_init();
	CURLcode res;
	struct string string;
	string.str = malloc(1);
	string.len = 0;
	if(argc >= 2) {
		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&string);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}
	}

	contents = parse(&string);
	char* content;
	pos = 0;

	app = gtk_application_new ("com.avedati.cwebscraper", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	free(string.str);

	return status;
}
