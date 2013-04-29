#include "main_engine.h"
#include <gtk/gtk.h>

GtkWidget *wid[9][9], *window;

int check_input_sudoku()
{
    int i, j, temp, value;
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++) {
            temp = array[i][j];
            array[i][j] = outputArray[i][j] = 0;
            value = input_value(i, j, temp);
            array[i][j] = outputArray[i][j] = temp;
            if (!value && temp)
                return 0;
        }
    return 1;
}

void error_dialog(int error_num)
{
    GtkWidget *dialog, *label;
    dialog =
        gtk_dialog_new_with_buttons("Error", GTK_WINDOW(window),
                                    GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                    GTK_RESPONSE_OK, NULL);
    if (error_num == 1)
        label = gtk_label_new("Enter numbers only in each cell");
    else
        label = gtk_label_new("Bad sudoku!");
    gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), label, 0, 0, 0);
    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void solve()
{
    int i, j;
    if (backtrack(0, 0)) {
        for (i = 0; i < 9; i++) {
            for (j = 0; j < 9; j++) {
                char c[2];
                sprintf(c, "%d", outputArray[i][j]);
                gtk_entry_set_text(GTK_ENTRY(wid[i][j]), c);
            }
        }

    } else
        puts("No solution");
}


void get_elements(GtkWidget * widget, gpointer data)
{
    int i, j;
    char c;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            c = *gtk_entry_get_text(GTK_ENTRY(wid[i][j]));
            if ((c >= '0' && c <= '9') || c == 0) {
                outputArray[i][j] = array[i][j] = atoi(&c);
            } else {
                error_dialog(1);
                return;
            }
        }
    }
    if (check_input_sudoku())
        solve();
    else
        error_dialog(2);
}

int main(int argc, char *argv[])
{
    int i, j;
    gtk_init(&argc, &argv);
    GtkWidget *vbox, *hbox, *separator, *button;
    vbox = gtk_vbox_new(0, 0);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    for (i = 0; i < 9; i++) {
        hbox = gtk_hbox_new(0, 0);
        for (j = 0; j < 9; j++) {
            wid[i][j] = gtk_entry_new();
            gtk_entry_get_text(GTK_ENTRY(wid[i][j]));
            gtk_entry_set_width_chars(GTK_ENTRY(wid[i][j]), 1);
            gtk_entry_set_max_length(GTK_ENTRY(wid[i][j]), 1);
            gtk_widget_set_size_request(wid[i][j], 25, 25);
            gtk_box_pack_start(GTK_BOX(hbox), wid[i][j], 0, 0, 0);
            if ((j + 1) % 3 == 0) {
                separator = gtk_vseparator_new();
                gtk_box_pack_start(GTK_BOX(hbox), separator, 0, 0, 0);
            }
        }
        gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 0);
        if ((i + 1) % 3 == 0) {
            separator = gtk_hseparator_new();
            gtk_box_pack_start(GTK_BOX(vbox), separator, 0, 0, 0);
        }
    }
    button = gtk_button_new_with_label("Solve the sudoku");
    g_signal_connect(button, "clicked", G_CALLBACK(get_elements), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);
    g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit),
                     NULL);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
