#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>
#include "../header/struct_Planet.h"
#include "../header/forces_calc.h"

#define N 2
#define G 1
#define DELTA 0.1

extern float x_diff, y_diff, dist, dist_cubed, temp;
extern float forcesX[N][N]; //array which contained all forces on X direction betwin planets
extern float forcesY[N][N]; //array which contained all forces on Y direction betwin planets
extern float posX[N], posY[N]; //arrays which contained all X and Y positions
extern float masses[N];


int main(int argc, char **argv) {

    /* Declarations */
    int q, k;
    int n = N;
    float deltaT = DELTA;
    Planet Q, K; //declare 2 struct Planet


    //    float g = G;
    //    float forceqkX, forceqkY;

    /* initialize PLanet */
    Q.masse = 5.2;
    Q.pos_x = 5.3;
    Q.pos_y = 12.2;
    Q.velocity_x = 0.0;
    Q.velocity_y = 5.0;
    K.masse = 5.3;
    K.pos_x = 7.2;
    K.pos_y = 12.2;
    Q.velocity_x = 0.0;
    K.velocity_y = 6.0;

    char str[10], str2[10], str3[10], str4[10], str5[10], str6[10], str7[10], str8[10];

    sprintf(str, "%f", Q.pos_x);
    sprintf(str2, "%f", Q.pos_y);
    sprintf(str3, "%f", Q.velocity_x);
    sprintf(str4, "%f", Q.velocity_y);
    sprintf(str5, "%f", K.pos_x);
    sprintf(str6, "%f", K.pos_y);
    sprintf(str7, "%f", K.velocity_x);
    sprintf(str8, "%f", K.velocity_y);


    /***  GTK  ***/

    GtkBuilder *builder;
    GtkWidget *window;
    GError *error = NULL;

    /* Init GTK+ */
    gtk_init(&argc, &argv);

    /* Create new GtkBuilder object */
    builder = gtk_builder_new();
    /* Load UI from file. If error occurs, report it and quit application.
     * Replace "tut.glade" with your saved project. */
    if (!gtk_builder_add_from_file(builder, "./source/glade/nbodyP.glade", &error)) {
        g_warning("%s", error->message);
        g_free(error);
        return ( 1);
    }

    /* Get main window pointer from UI */
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    /* end of loop to destroy the window */
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(builder, "res_posXQ"));
    gtk_label_set_text(GTK_LABEL(label), str);

    GtkWidget *label2 = GTK_WIDGET(gtk_builder_get_object(builder, "res_posYQ"));
    gtk_label_set_text(GTK_LABEL(label2), str2);

    GtkWidget *label3 = GTK_WIDGET(gtk_builder_get_object(builder, "res_velXQ"));
    gtk_label_set_text(GTK_LABEL(label3), str3);

    GtkWidget *label4 = GTK_WIDGET(gtk_builder_get_object(builder, "res_velYQ"));
    gtk_label_set_text(GTK_LABEL(label4), str4);

    GtkWidget *label5 = GTK_WIDGET(gtk_builder_get_object(builder, "res_posXK"));
    gtk_label_set_text(GTK_LABEL(label5), str5);

    GtkWidget *label6 = GTK_WIDGET(gtk_builder_get_object(builder, "res_posYK"));
    gtk_label_set_text(GTK_LABEL(label6), str6);

    GtkWidget *label7 = GTK_WIDGET(gtk_builder_get_object(builder, "res_velXK"));
    gtk_label_set_text(GTK_LABEL(label7), str7);

    GtkWidget *label8 = GTK_WIDGET(gtk_builder_get_object(builder, "res_velYK"));
    gtk_label_set_text(GTK_LABEL(label8), str8);

    /* Connect signals */
    gtk_builder_connect_signals(builder, NULL);

    /* Destroy builder, since we don't need it anymore */
    g_object_unref(G_OBJECT(builder));

    /* Show window. All other widgets are automatically shown by GtkBuilder */
    gtk_widget_show(window);

    /* Start main loop */
    gtk_main();

    /***   END GTK  ***/

    /* put position of all planets in the array*/
    posX[0] = Q.pos_x;
    posX[1] = K.pos_x;
    posY[0] = Q.pos_y;
    posY[1] = K.pos_y;

    /* put masse of all planets in the arrey */
    masses[0] = Q.masse;
    masses[1] = K.masse;

    /* ******** */

    /* to initialize all forces at 0 */
    for (q = 0; q < n; q++) {
        forcesX[q][q] = 0;
        forcesY[q][q] = 0;
        if (q == 0) {
            forcesX[q + 1][q] = 0;
            forcesX[q][q + 1] = 0;
            forcesY[q + 1][q] = 0;
            forcesY[q][q + 1] = 0;
        }
    }

    forces_calc(Q, K);


}

