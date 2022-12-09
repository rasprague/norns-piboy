#include <SDL2/SDL.h>

#include "events.h"
#include "event_types.h"
#include "hardware/io.h"
#include "hardware/input.h"
#include "hardware/input/inputs.h"

typedef struct _input_sdl_priv {
} input_sdl_priv_t;

static int input_sdl_config(matron_io_t* io, lua_State *l);
static int input_sdl_setup(matron_io_t* io);
static void input_sdl_destroy(matron_io_t* io);
static void* input_sdl_poll(void* data);

input_ops_t input_sdl_ops = {
    .io_ops.name      = "input:sdl",
    .io_ops.type      = IO_INPUT,
    .io_ops.data_size = sizeof(input_sdl_priv_t),
    .io_ops.config    = input_sdl_config,
    .io_ops.setup     = input_sdl_setup,
    .io_ops.destroy   = input_sdl_destroy,
    .poll             = input_sdl_poll,
};

int input_sdl_config(matron_io_t *io, lua_State *l) {
    (void)io;
    (void)l;
    return 0;
}

int input_sdl_setup(matron_io_t *io) {
    return input_setup(io);
}

void input_sdl_destroy(matron_io_t *io) {
    input_destroy(io);
}

static void* input_sdl_poll(void* data) {
    (void)data;
    // for now, we don't actually want to use keyboard input
    // (leave it for scripts / menu)
#if 1
    SDL_Event event;
    union event_data *ev;
    fprintf(stderr, "starting SDL input loop\n"); 
    while (true) {
        SDL_WaitEvent(&event);
        fprintf(stderr, "got SDL input %d\n", event.type);
        switch (event.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP: {
                fprintf(stderr, "key event\n");
                int z = event.type == SDL_KEYDOWN ? 1 : 0;

                switch (event.key.keysym.sym) {
		     case SDLK_q:
                        ev = event_data_new(EVENT_KEY);
                        ev->key.n = 1;
                        ev->key.val = z;
                        event_post(ev);
                        break;
		     case SDLK_a:
                        ev = event_data_new(EVENT_KEY);
                        ev->key.n = 2;
                        ev->key.val = z;
                        event_post(ev);
                        break;
		     case SDLK_z:
                        ev = event_data_new(EVENT_KEY);
                        ev->key.n = 3;
                        ev->key.val = z;
                        event_post(ev);
                        break;
		     case SDLK_w:
                        ev = event_data_new(EVENT_ENC);
                        ev->enc.n = 1;
                        ev->enc.delta = -1;
                        event_post(ev);
                        break;
		     case SDLK_e:
                        ev = event_data_new(EVENT_ENC);
                        ev->enc.n = 1;
                        ev->enc.delta = 1;
                        event_post(ev);
                        break;
		     case SDLK_s:
                        ev = event_data_new(EVENT_ENC);
                        ev->enc.n = 2;
                        ev->enc.delta = -1;
                        event_post(ev);
                        break;
		     case SDLK_d:
                        ev = event_data_new(EVENT_ENC);
                        ev->enc.n = 2;
                        ev->enc.delta = 1;
                        event_post(ev);
                        break;
		     case SDLK_x:
                        ev = event_data_new(EVENT_ENC);
                        ev->enc.n = 3;
                        ev->enc.delta = -1;
                        event_post(ev);
                        break;
		     case SDLK_c:
                        ev = event_data_new(EVENT_ENC);
                        ev->enc.n = 3;
                        ev->enc.delta = 1;
                        event_post(ev);
                        break;
		     case SDLK_ESCAPE:
		        ev = event_data_new(EVENT_QUIT);
		        event_post(ev);
		        break;
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
    }
#endif
    return NULL;
}
