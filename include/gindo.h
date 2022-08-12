#ifndef GINDO_H_
#define GINDO_H_

#include <stdbool.h>

#ifdef GINDO_TYPEDEF
typedef struct gnd_window gnd_window;
typedef enum gnd_error gnd_error;
typedef enum gnd_renderer gnd_renderer;
typedef struct gnd_init_opt gnd_init_opt;
typedef struct gnd_opengl_ver gnd_opengl_ver;
typedef struct gnd_window_opt gnd_window_opt
typedef struct gnd_state gnd_state;
#endif

#define DEFAULT_STATE (struct gnd_state){.error_FN = gnd_default_error_fn}
#define DEFAULT_INIT_OPT (struct gnd_init_opt){1}
#define DEFAULT_INIT &(struct gnd_state){.error_FN = gnd_default_error_fn}, (struct gnd_init_opt){1}
#define DEFAULT_WIND_OPT (struct gnd_window_opt){0}

enum gnd_error {
  gnd_error_none,
  gnd_error_nomem,
  gnd_error_null_param,
  gnd_error_glfw_init,
  gnd_error_glfw_ivalue, /// Invalid value
  gnd_error_glfw_window_create,
  gnd_error_glfw_platform
};

typedef void(*gnd_error_FN)(enum gnd_error error_code);

struct gnd_state {
  gnd_error_FN error_FN;
};

struct gnd_window {
  struct gnd_state *state;
  void *ptr;
};

enum gnd_renderer {
  gnd_renderer_opengl,
  gnd_renderer_vulkan
};

/// Default values must be true
struct gnd_init_opt {
  bool joystick_hat_buttons;
  bool cocoa_chdir_res;
  bool cocoa_menubar;
};

struct gnd_opengl_ver {
  int major;
  int minor;
};

/// Default values must be zero
struct gnd_window_opt {
  int width;
  int height;
  enum gnd_renderer renderer;
  const struct gnd_opengl_ver *gl_version;
  bool resizable;
};

void gnd_default_error_fn(enum gnd_error error_code);
void gnd_init(struct gnd_state *state, struct gnd_init_opt opt);
void gnd_deinit(void);
struct gnd_window gnd_window_create(struct gnd_state *state, const char *title, struct gnd_window_opt options);
void gnd_window_destroy(struct gnd_window wind);
bool gnd_window_should_close(struct gnd_window wind);
void gnd_poll_events(const struct gnd_state *state);
void gnd_set_error_fn(gnd_error_FN errfn);
gnd_error_FN gnd_get_error_fn(void);

#endif
