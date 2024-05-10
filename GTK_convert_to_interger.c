#include <gtk/gtk.h>

// Callback function for the button
void convert_to_integer(GtkWidget *widget, gpointer data) {
    GtkEntry *entry = GTK_ENTRY(data);
    const gchar *text = gtk_entry_get_text(entry);
    
    // Convert the text to an integer (you should add error handling)
    int integer_value = atoi(text);

    // Now you have the integer value, you can use it as needed
    // For example, you can print it to the console
    if(integer_value == 0)
    g_print("invalid option\n");
    g_print("Integer Value: %d\n", integer_value);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Integer Input Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *entry = gtk_entry_new();
    GtkWidget *button = gtk_button_new_with_label("Convert to Integer");

    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(convert_to_integer), entry);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_box_pack_start(GTK_BOX(vbox), entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
