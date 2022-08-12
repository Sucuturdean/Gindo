#include <GLFW/glfw3.h>
#include "gindo.h"

static bool init = false;

void gnd_default_error_fn(enum gnd_error error_code) {
  (void)error_code;
}

void gnd_init(struct gnd_state *state, struct gnd_init_opt opt) {
  if(opt.joystick_hat_buttons) glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_TRUE);
  if(opt.cocoa_chdir_res) glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_TRUE);
  if(opt.cocoa_menubar) glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_TRUE);
  
  if(glfwInit() == GLFW_FALSE) {
    if(state != NULL) state->error_FN(gnd_error_glfw_init);
  }
  init = true;
}

void gnd_deinit(void) {
  init = false;
  glfwTerminate();
}

struct gnd_window gnd_window_create(
  struct gnd_state *state,
  const char *title,
  struct gnd_window_opt opt
) {
  if(init == false && state != NULL) state->error_FN(gnd_error_glfw_init);
  if(title == NULL && state != NULL) state->error_FN(gnd_error_null_param);
  if(opt.width == 0) {
    opt.width = 800;
  }
  if(opt.height == 0) {
    opt.height = 600;
  }
  if(!opt.resizable) {
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  }
  switch(opt.renderer) {
    case gnd_renderer_opengl:
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opt.gl_version->major);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opt.gl_version->minor);
    break;
    case gnd_renderer_vulkan:
      glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    break;
  }
  GLFWwindow *const glfw_window = glfwCreateWindow(opt.width, opt.height, title, NULL, NULL);
  if(glfw_window == NULL && state != NULL) {
    const int error_code = glfwGetError(NULL);
    switch(error_code) {
      case GLFW_OUT_OF_MEMORY:
        state->error_FN(gnd_error_nomem);
      break;
      case GLFW_INVALID_VALUE:
        state->error_FN(gnd_error_glfw_ivalue);
      break;
      case GLFW_PLATFORM_ERROR:
        state->error_FN(gnd_error_glfw_platform);
      break;
      default:
        state->error_FN(gnd_error_glfw_window_create);
    }
  }

  glfwMakeContextCurrent(glfw_window);

  return (struct gnd_window){
    .state = state,
    .ptr = glfw_window
  };
}

void gnd_window_destroy(struct gnd_window wind) {
  glfwDestroyWindow(wind.ptr);
}

bool gnd_window_should_close(struct gnd_window wind) {
  return glfwWindowShouldClose(wind.ptr);
}

void gnd_poll_events(const struct gnd_state *state) {
  if(init == false && state != NULL) state->error_FN(gnd_error_glfw_init);
  glfwPollEvents();
}
