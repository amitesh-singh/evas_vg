#include <Elementary.h>
#include <Evas.h>

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
   Efl_VG *vg, *container, *line, *newline;

   const Efl_Gfx_Path_Command *op_get = NULL;
   const double *points_get = NULL;

   ecore_evas_init();
   ee = ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);

   ecore_evas_show(ee);

   vg = evas_object_vg_add(ecore_evas_get(ee));
   evas_object_resize(vg, WIDTH, HEIGHT);
   evas_object_show(vg);

   container = evas_vg_container_add(vg);
   evas_object_vg_root_node_set(vg, container);

   line = evas_vg_shape_add(container);
   _draw_line(line);

   newline = evas_vg_shape_add(container);
   evas_vg_shape_dup(newline, line);

   evas_vg_shape_path_get(newline, &op_get, &points_get);

   if (!newline)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed", __FILE__, __LINE__);
     }

   if (!op_get)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed", __FILE__, __LINE__);
     }

   if (!points_get)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed", __FILE__, __LINE__);
     }

   if (op_get[0] != EFL_GFX_PATH_COMMAND_TYPE_MOVE_TO && op_get[1] != EFL_GFX_PATH_COMMAND_TYPE_LINE_TO)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed", __FILE__, __LINE__);
     }
   if (points_get[0] != 0.0 && points_get[1] != 0.0 &&
       points_get[2] != 0.0 && points_get[3] != 100.0)
     {
        ck_abort_msg("[TEST_FAIL]:: %s[%d] : Test has failed", __FILE__, __LINE__);
     }

   ecore_main_loop_begin();

   ecore_evas_free(ee);
   ecore_evas_shutdown();
   return 0;
}
