#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
GtkWidget *wid[9][9], *window;
int array[9][9];
int outputArray[9][9];

int input_value(int x, int y, int value)
{
    int i, j;
    /*check columns and rows */
    for (i = 0; i < 9; i++) {
	if (value == outputArray[i][y] || value == outputArray[x][i])
	    return 0;
    }
    /*check boxes */
    if (x < 3) {
	if (y < 3) {
	    for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
		    if (value == outputArray[i][j]) {
			return 0;
		    }
		}
	    }
	} else if (y < 6) {
	    for (i = 0; i < 3; i++) {
		for (j = 3; j < 6; j++) {
		    if (value == outputArray[i][j]) {
			return 0;
		    }
		}
	    }
	} else {
	    for (i = 0; i < 3; i++) {
		for (j = 6; j < 9; j++) {
		    if (value == outputArray[i][j]) {
			return 0;
		    }
		}
	    }
	}
    } else if (x < 6) {
	if (y < 3) {
	    for (i = 3; i < 6; i++) {
		for (j = 0; j < 3; j++) {
		    if (value == outputArray[i][j]) {
			return 0;
		    }
		}
	    }
	} else if (y < 6) {

	    for (i = 3; i < 6; i++) {
		for (j = 3; j < 6; j++) {
		    if (value == outputArray[i][j]) {
			return 0;
		    }
		}
	    }
	} else {
	    for (i = 3; i < 6; i++) {
		for (j = 6; j < 9; j++) {
		    if (value == outputArray[i][j]) {
			return 0;
		    }
		}
	    }
	}
    } else {
	if (y < 3) {
	    for (i = 6; i < 9; i++) {
		for (j = 0; j < 3; j++) {
		    if (value == outputArray[i][j]) {
			return 0;
		    }
		}
	    }
	} else if (y < 6) {
	    for (i = 6; i < 9; i++) {
		for (j = 3; j < 6; j++) {
		    if (value == outputArray[i][j]) {
			return 0;
		    }
		}
	    }
	} else {
	    for (i = 6; i < 9; i++) {
		for (j = 6; j < 9; j++) {
		    if (value == outputArray[i][j]) {
			return 0;
		    }
		}
	    }
	}
    }
    return value;
}

int backtrack(int x, int y)
{
    int temp, i;
    if (outputArray[x][y] == 0) {
	for (i = 1; i < 10; i++) {
	    temp = input_value(x, y, i);
	    if (temp > 0) {
		outputArray[x][y] = temp;
		if (x == 8 && y == 8) {
		    return 1;
		} else if (x == 8) {
		    if (backtrack(0, y + 1))
			return 1;
		} else {
		    if (backtrack(x + 1, y))
			return 1;
		}
	    }
	}
	if (i == 10) {
	    if (outputArray[x][y] != array[x][y])
		outputArray[x][y] = 0;
	    return 0;
	}
    } else {
	if (x == 8 && y == 8) {
	    return 1;
	} else if (x == 8) {
	    if (backtrack(0, y + 1))
		return 1;
	} else {
	    if (backtrack(x + 1, y))
		return 1;
	}
    }
    outputArray[x][y] = 0;
    return 0;
}
void bad_symbol(void)
{
    GtkWidget *dialog, *label;
    dialog =
    gtk_dialog_new_with_buttons("Error", GTK_WINDOW(window),
                    GTK_DIALOG_MODAL, GTK_STOCK_OK,
                    GTK_RESPONSE_OK, NULL);
    label = gtk_label_new("Enter numbers only in each cell");
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

    } 
    else
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
	       } 
           else {
		      bad_symbol();
		      return;
	       }
	   }
    }
    solve();
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
