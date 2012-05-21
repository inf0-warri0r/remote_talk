/*
*Author :Tharindra Galahena
*Project:walkie-talkie application for linux
*Date   :28/04/2012
*/

#include <gtk/gtk.h>
#include <sys/prctl.h>
#include "sound.h"

int pid = 0;
GtkWidget *label;
static void receiver( GtkWidget *widget, gpointer   data )
{
	if(pid == 0){
		gtk_label_set_text((GtkLabel *)label, "listening!!!");  
		if(!(pid = fork())){
			prctl(PR_SET_PDEATHSIG, SIGHUP);
			so_init();
		}
	}
}
static void receiver_stop( GtkWidget *widget, gpointer data){
	if(pid != 0){
		gtk_label_set_text((GtkLabel *)label, "(0_0)");
		kill(pid, SIGKILL);
		pid = 0;
	}
}
int main( int   argc, char *argv[]) 
{
    GtkWidget *window;
	
	GtkWidget *play;
	GtkWidget *stop; 
	GtkWidget *button3; 
	
	GtkWidget *main_box;
	GtkWidget *box1;
	GtkWidget *box2;
	
	GtkWidget *separator;
	GtkWidget *separator2;
	GtkWidget *separator3;
	
	
	
    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_resizable((GtkWindow *)window, FALSE);
    g_signal_connect (window, "delete-event",
		      G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    //main_box
    main_box = gtk_vbox_new (FALSE, 0);

	label = gtk_label_new ("(0_0)");
	
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0);

	gtk_box_pack_start (GTK_BOX (main_box), label, FALSE, FALSE, 0);
	
	gtk_widget_show (label);
	
	separator = gtk_hseparator_new ();
	gtk_box_pack_start (GTK_BOX (main_box), separator, FALSE, TRUE, 5);
	gtk_widget_show (separator);

	//box1
	box1 = gtk_hbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (main_box), box1, FALSE, FALSE, 0);
	gtk_widget_show (box1);
	
	play = gtk_button_new_with_label ("Play");
	gtk_signal_connect (GTK_OBJECT (play), "clicked",
					GTK_SIGNAL_FUNC (receiver), NULL);

	gtk_box_pack_start (GTK_BOX (box1), play, TRUE, TRUE, 0);
    gtk_widget_show (play);
    
    separator3 = gtk_hseparator_new ();
	gtk_box_pack_start (GTK_BOX (box1), separator3, FALSE, TRUE, 5);
	gtk_widget_show (separator3);
	
    stop = gtk_button_new_with_label ("stop");
	gtk_signal_connect (GTK_OBJECT (stop), "clicked",
		      GTK_SIGNAL_FUNC (receiver_stop), NULL);
    gtk_box_pack_start (GTK_BOX (box1), stop, TRUE, TRUE, 0);
    gtk_widget_show (stop);
    
    separator2 = gtk_hseparator_new ();
	gtk_box_pack_start (GTK_BOX (main_box), separator2, FALSE, TRUE, 5);
	gtk_widget_show (separator2);
	
	//box2
    box2 = gtk_hbox_new (FALSE, 0);
	
    button3 = gtk_button_new_with_label ("Quit");
    
    g_signal_connect_swapped (button3, "clicked",
			      G_CALLBACK (gtk_main_quit),
			      window);

    gtk_box_pack_start (GTK_BOX (box2), button3, TRUE, FALSE, 0);

	gtk_box_pack_start (GTK_BOX (main_box), box2, FALSE, FALSE, 0);
	 
    gtk_container_add (GTK_CONTAINER (window), main_box);
    
    gtk_widget_show (button3);
    gtk_widget_show (box2);
    
    gtk_widget_show (main_box);
    gtk_widget_show (window);
    
    gtk_main ();
    
    return 0;
}
