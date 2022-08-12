#include "gindo.h"
#include <stdio.h>

void error_function(enum gnd_error error_code) {
  switch(error_code) {
    case gnd_error_glfw_window_create:
      printf("Window failed to create\n");
    break;
    case gnd_error_glfw_ivalue:
      printf("Invalid value!\n");
    break;
    default:
      printf("Werror\n");
  }
}

int main(void) {
  struct gnd_state state = {
    .error_FN = error_function
  };
  gnd_init(&state, (struct gnd_init_opt){0});
  struct gnd_opengl_ver gl_ver = {
    .major = 2,
    .minor = 0
  };
  
  const struct gnd_window_opt options = {
    .width = 1200,
    .height = 720,
    .renderer = gnd_renderer_opengl,
    .gl_version = &gl_ver
  };
  const struct gnd_window window = gnd_window_create(&state, "Titile", options);
  
  while(!gnd_window_should_close(window)) {
    gnd_poll_events(NULL);
  }
  
  gnd_window_destroy(window);
  gnd_deinit();
}
