#include <gtk/gtk.h>

GtkWidget *counter_label;
int counter_value = 0;
gboolean is_upcounting = TRUE; // To keep track of counting direction

void update_counter_label() {
    gchar *counter_text = g_strdup_printf("Counter: %d", counter_value);
    gtk_label_set_text(GTK_LABEL(counter_label), counter_text);
    g_free(counter_text);
}

void count_callback(GtkWidget *widget, gpointer data) {
    if (is_upcounting) {
        counter_value++;
    } else {
        counter_value--;
    }
    update_counter_label();
}

void radio_toggled_callback(GtkWidget *widget, gpointer data) {
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
        is_upcounting = GPOINTER_TO_INT(data);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *button = gtk_radio_button_new_with_label(NULL, "Upcount");
    GtkWidget *button1 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(button), "Downcount");

    g_signal_connect(button, "toggled", G_CALLBACK(radio_toggled_callback), GINT_TO_POINTER(TRUE));
    g_signal_connect(button1, "toggled", G_CALLBACK(radio_toggled_callback), GINT_TO_POINTER(FALSE));

    GtkWidget *count_button = gtk_button_new_with_label("Count");
    g_signal_connect(count_button, "clicked", G_CALLBACK(count_callback), NULL);

    counter_label = gtk_label_new("Counter: 0");
    GtkWidget *box = gtk_box_new(TRUE, 10);

    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), count_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), counter_label, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(win), box);
    gtk_widget_show_all(win);

    gtk_main();

    return 0;
}
