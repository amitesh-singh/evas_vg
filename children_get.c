#include <Elementary.h>
#define WIDTH 400
#define HEIGHT 500

#define ck_abort_msg printf

static void
_draw_line(Efl_VG *line)
{
   evas_vg_shape_append_move_to(line, 0, 0);
   evas_vg_shape_append_line_to(line, 100, 100);
   evas_vg_shape_stroke_color_set(line, 255, 0, 0, 255);
   evas_vg_shape_stroke_width_set(line, 5);
   evas_vg_node_origin_set(line, 50, 50);
   evas_vg_node_color_set(line, 255, 255, 255, 255);
   evas_vg_shape_stroke_cap_set(line, EFL_GFX_CAP_ROUND);
}

int main()
{
   Ecore_Evas *ee;
   ecore_evas_init();
   ee = ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);

   ecore_evas_show(ee);

   Efl_VG *vg, *container, *line, *circle1, *circle2, *circle3;
   vg = evas_object_vg_add(ecore_evas_get(ee));
   evas_object_name_set(vg, "vg");
   evas_object_resize(vg, WIDTH, HEIGHT);
   evas_object_show(vg);

   container = evas_vg_container_add(vg);
   evas_object_vg_root_node_set(vg, container);

   line = evas_vg_shape_add(container);
   _draw_line(line);
   evas_object_name_set(line, "line");

   //draw circle
   circle1 = evas_vg_shape_add(container);
   evas_object_name_set(circle1, "circle1");
   evas_vg_shape_append_circle(circle1, 50, 50, 50);
   evas_vg_shape_stroke_color_set(circle1, 255, 0, 0, 255);
   evas_vg_shape_stroke_width_set(circle1, 5);
   evas_vg_node_color_set(circle1, 255, 0, 0, 100);
   evas_vg_node_origin_set(circle1, 55, 120);

   //draw circle
   circle2 = evas_vg_shape_add(container);
   evas_object_name_set(circle2, "circle2");
   evas_vg_shape_dup(circle2, circle1);
   evas_vg_shape_stroke_color_set(circle2, 0, 0, 0, 0);
   evas_vg_node_color_set(circle2, 0, 255, 0, 255);
   evas_vg_node_origin_set(circle2, 45, 110);

   //draw circle
   circle3 = evas_vg_shape_add(container);
   evas_object_name_set(circle3, "circle3");
   evas_vg_shape_dup(circle3, circle1);
   evas_vg_shape_stroke_color_set(circle3, 150, 0, 0, 150);
   evas_vg_node_color_set(circle3, 0, 0, 255, 255);
   evas_vg_node_origin_set(circle3, 35, 150);
   printf("circle1: %p, circle2: %p, Circle3: %p\n", circle1, circle2, circle3);
   printf("vg= %s\n", evas_object_name_get(vg));

   if (evas_vg_container_child_get(container, "line") != line)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d][%p] [object: %s]: Test has failed\n", __FILE__, __LINE__, evas_vg_container_child_get(container, "line"), 
        evas_object_name_get(line));
     }
   if (evas_vg_container_child_get(container, "circle1") != circle1)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed\n", __FILE__, __LINE__);
     }
   if (evas_vg_container_child_get(container, "circle2") != circle2)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed\n", __FILE__, __LINE__);
     }
   if (evas_vg_container_child_get(container, "circle3") != circle3)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed\n", __FILE__, __LINE__);
     }
   fflush(stdout);

   ecore_main_loop_begin();

   ecore_evas_free(ee);
   ecore_evas_shutdown();
   return 0;
}
