#include <Elementary.h>
#define WIDTH 400
#define HEIGHT 500

#define ck_abort_msg printf

int main()
{
   Ecore_Evas *ee;
   ecore_evas_init();
   ee = ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);

   ecore_evas_show(ee);

   Efl_VG *vg, *container, *circle1, *circle2, *circle3;
   vg = evas_object_vg_add(ecore_evas_get(ee));
   evas_object_resize(vg, WIDTH, HEIGHT);
   evas_object_show(vg);

   container = evas_vg_container_add(vg);
   evas_object_vg_root_node_set(vg, container);

   //draw circle
   circle1 = evas_vg_shape_add(container);
   evas_vg_shape_append_circle(circle1, 50, 50, 50);
   evas_vg_shape_stroke_color_set(circle1, 255, 0, 0, 255);
   evas_vg_shape_stroke_width_set(circle1, 5);
   evas_vg_node_color_set(circle1, 255, 0, 0, 100);
   evas_vg_node_origin_set(circle1, 55, 120);

   //draw circle
   circle2 = evas_vg_shape_add(container);
   evas_vg_shape_dup(circle2, circle1);
   evas_vg_shape_stroke_color_set(circle2, 0, 0, 0, 0);
   evas_vg_node_color_set(circle2, 0, 255, 0, 255);
   evas_vg_node_origin_set(circle2, 45, 110);

   //draw circle
   circle3 = evas_vg_shape_add(container);
   evas_vg_shape_dup(circle3, circle1);
   evas_vg_shape_stroke_color_set(circle3, 150, 0, 0, 150);
   evas_vg_node_color_set(circle3, 0, 0, 255, 255);
   evas_vg_node_origin_set(circle3, 35, 150);
   printf("circle1: %p, circle2: %p, Circle3: %p\n", circle1, circle2, circle3);

   //move circle3 below circle2
   evas_vg_node_stack_below(circle3, circle2);
   printf("Circle3 Above object: %p\n", evas_object_above_get(circle3));
   if (evas_object_above_get(circle3) != circle2)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed", __FILE__, __LINE__);
     }

   //move circle1 below circle2
   evas_vg_node_stack_below(circle1, circle2);
   printf("Circle1 Above object: %p\n", evas_object_above_get(circle1));
   if (evas_object_above_get(circle1) != circle2)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed", __FILE__, __LINE__);
     }

   //move circle2 below circle3
   evas_vg_node_stack_below(circle2, circle3);
   printf("Circle2 Above object: %p\n", evas_object_above_get(circle2));
   if (evas_object_above_get(circle2) != circle3)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed", __FILE__, __LINE__);
     }


   ecore_main_loop_begin();

   ecore_evas_free(ee);
   ecore_evas_shutdown();
   return 0;
}
