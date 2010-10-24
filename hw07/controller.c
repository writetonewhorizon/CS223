// Michael J. Fischer
// CPSC 223b, Spring 2008

#include <gtk/gtk.h>
#include <stdlib.h>
#include "viewer.h"
#include "util.h"

// ------------------------------------------------------------------------
// Private function prototypes
// ------------------------------------------------------------------------
static gboolean on_expose_event(GtkWidget *widget, 
		GdkEventExpose *event, gpointer data);
static gboolean clicked(GtkWidget *widget,
		GdkEventButton *event, gpointer data);
static void undo(GtkWidget *widget, gpointer data);
static void redo(GtkWidget *widget, gpointer data);
static void gameOver( Game gm, gchar* message );

// ------------------------------------------------------------------------
// Private global variables
// ------------------------------------------------------------------------
// We use static global variables here instead of encapsulating them
// into a controller object.  Since there can only be one instance of
// a gtk+ event loop running at a time, there is no need to provide
// for more than one controller object.
static GtkWidget *window;	// Main window
static GtkWidget *vbox;	// Vertical layout: canvas, buttons
static GtkWidget *canvas;	// Drawing surface for Hex board
static GtkWidget *buttons;	// Horizontal button box

// ------------------------------------------------------------------------
// Public functions
// ------------------------------------------------------------------------

// ------------------------------------------------------------------------
// Starts the controller
void startController( Game game, int argc, char* argv[] )
{
	// Initialize gtk
    gtk_init (&argc, &argv);

	// Get Hexboard geometry for use in sizing window
	Hexboard hb = getHexboardGame( game );
	const Geometry* geo = getGeoHex( hb );
	
    // Make window
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Hex Game");
    gtk_window_set_default_size(GTK_WINDOW(window), -1, -1); 
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    // Make layout container and put in window
    vbox = gtk_vbox_new (FALSE, 10);
    gtk_container_add(GTK_CONTAINER (window), vbox);
       
    // Make drawing canvas and place in vbox
    canvas = gtk_drawing_area_new ();
    gtk_widget_set_size_request(GTK_WIDGET (canvas),
    		geo->x1 - geo->x0 + 1, geo->y1 - geo->y0 + 1);
    gtk_box_pack_start( GTK_BOX (vbox), canvas, TRUE, TRUE, 0);
 
    // Make button box and place in vbox
    buttons = gtk_hbutton_box_new ();
    gtk_box_pack_start( GTK_BOX (vbox), buttons, TRUE, TRUE, 0);
       
    // Make some buttons and place in button box
    GtkWidget *undo_button;
    GtkWidget *redo_button;
    GtkWidget *quit_button;
    undo_button = gtk_button_new_with_label ("Undo");
    gtk_box_pack_start (GTK_BOX(buttons), undo_button, TRUE, TRUE, 0);
    redo_button = gtk_button_new_with_label ("Redo");
    gtk_box_pack_start(GTK_BOX (buttons), redo_button, TRUE, TRUE, 0);
    quit_button = gtk_button_new_with_label ("Quit");
    gtk_box_pack_start(GTK_BOX (buttons), quit_button, TRUE, TRUE, 0);
    
    // Enable mouse events on canvas
    gtk_widget_add_events (canvas, GDK_BUTTON_PRESS_MASK);

    // Connect event handlers
    g_signal_connect(G_OBJECT (window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);
    
    g_signal_connect(G_OBJECT (canvas), "expose-event",
        G_CALLBACK(on_expose_event), game);
    
    g_signal_connect(G_OBJECT (canvas), "button-press-event", 
        G_CALLBACK(clicked), game);
   
    g_signal_connect(G_OBJECT (quit_button), "clicked",
    	G_CALLBACK(gtk_main_quit), NULL);
    
    g_signal_connect(G_OBJECT (undo_button), "clicked",
    	G_CALLBACK(undo), game);
 
    g_signal_connect(G_OBJECT (redo_button), "clicked",
     	G_CALLBACK(redo), game);
    
     // Show window
    gtk_widget_show_all(window);
      
    // Enter main event loop
    gtk_main ();
}

// ------------------------------------------------------------------------
// Called when it's time to redraw the window.
// Creates a cairo drawing canvas and calls user's redisplay function
static gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event,
		gpointer data)
{
	cairo_t *cr;
	cr = gdk_cairo_create(widget->window);

	Game gm = data;
	displayGame(gm, cr);
	
	cairo_destroy(cr);
	return FALSE;
}

// ------------------------------------------------------------------------
// Called when mouse is clicked on the canvas.
// Translates from screen coordinates to Cartesian coordinates assumed
// by Hexboard and calls user click handler.
// User handler returns true if board has changed, in which case the
// widget is scheduled for redrawing.
static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer data)
{
	Game gm = data;
 	Hexboard hb = getHexboardGame( gm );
	const Geometry* geo = getGeoHex( hb );

    if (event->button == 1) {
    	// translate screen coordinates to cartesian coordinates
    	double cartx = geo->x0 + event->x;
    	double carty = geo->y1 - event->y;
    	if (playGame( gm, cartx, carty )) {
    		gtk_widget_queue_draw(widget);
    	}
    	switch (getStateGame(gm)) {
    	case GameWonRed:
    		gameOver( gm, "Red Wins!!!");
    		break;
    	case GameWonBlue:
    		gameOver( gm, "Blue Wins!!!");
    		break;
    	default:
    		break;
    	}
    }
    return TRUE;
}

// ------------------------------------------------------------------------
// Called when undo button is pressed
static void undo(GtkWidget *widget, gpointer data) 
{
	Game gm = data;
	if (undoGame( gm )) {
		gtk_widget_queue_draw( canvas );
	}
}

// ------------------------------------------------------------------------
// Called when redo button is pressed
static void redo(GtkWidget *widget, gpointer data) 
{
	Game gm = data;
	if (redoGame( gm )) {
		gtk_widget_queue_draw( canvas );
	}
}

// ------------------------------------------------------------------------
// Called by user when game is won
static void gameOver( Game gm, gchar* message ) {
	GtkWidget *game_over_dialog;
	GtkWidget *label;

    // Construct game over dialog box but don't show yet
    game_over_dialog = gtk_dialog_new_with_buttons("Game Over", 
    		GTK_WINDOW (window), 
    		GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
			"OK", GTK_RESPONSE_OK, NULL);
    gtk_window_set_default_size( GTK_WINDOW (game_over_dialog), 200, -1 );
	label = gtk_label_new( message );
	gtk_box_pack_start( GTK_BOX (GTK_DIALOG (game_over_dialog)->vbox),
			label, TRUE, TRUE, 10);
	gtk_widget_show(label);
	gtk_widget_show( GTK_WIDGET(game_over_dialog) );
	g_signal_connect(G_OBJECT (game_over_dialog), "response",
			G_CALLBACK(gtk_main_quit), NULL);
}

