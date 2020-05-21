#include <Elementary.h>

static Ecore_Evas *ee = NULL, *ee2 = NULL;

static Eina_Bool _quit_timer_cb(void *d)
{
   int *counter = (int *)d; 
   ecore_evas_focus_set(ee, EINA_TRUE);
   if (*counter >= 2)
   {
      ecore_main_loop_quit();
      return 0;
   }
   printf("counter = %d\n", *counter);
   fflush(stdout);

   (*counter)++;
   return 1;
}

int main(int argc, char **argv)
{
   Evas_Object *bg;
   Evas_Object *bg2;
   int counter = 0;
   ecore_evas_init();

   ee = ecore_evas_new(NULL, 0, 0, 200, 200, NULL);
   ee2 = ecore_evas_new(NULL, 400, 0, 400, 200, NULL);
   ecore_evas_show(ee);
   ecore_evas_show(ee2);

   bg = evas_object_rectangle_add(ecore_evas_get(ee));
   evas_object_color_set(bg, 0, 0, 255, 255);
   evas_object_resize(bg, 200, 200);
   evas_object_show(bg);

   bg2 = evas_object_rectangle_add(ecore_evas_get(ee2));
   evas_object_color_set(bg2, 255, 128, 0, 255);
   evas_object_resize(bg2, 400, 200);
   evas_object_show(bg2);

   ecore_evas_focus_set(ee, EINA_TRUE);

   Ecore_Timer *timer = NULL;
  
   timer = ecore_timer_add(0.5, _quit_timer_cb, &counter);
   ecore_main_loop_begin();

   if (!ecore_evas_focus_get(ee))
     {
        printf("[TEST_FAIL]:: %s[%d] : Test has failed..", __FILE__, __LINE__);
     }
   printf("\n\n");
   fflush(stdout);

  
   return 0;
}
