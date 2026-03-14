#include <stdio.h>
#include <pipewire/pipewire.h>
#include <spa/param/audio/format-utils.h>

static void on_process(void *userdata) {
    struct pw_stream *stream = userdata;
    struct pw_buffer *buf;
    struct spa_buffer *spa_buf;

    if (pw_stream_dequeue_buffer(stream, &buf) < 0)
        return;

    spa_buf = buf->buffer;
    if (spa_buf->datas[0].data == NULL)
        return;

    int16_t *samples = spa_buf->datas[0].data;
    uint32_t frames = spa_buf->datas[0].chunk->size / sizeof(int16_t);

    // Aquí puedes manipular samples directamente
    printf("Recibidos %d samples\n", frames);

    pw_stream_queue_buffer(stream, buf);
}

int main(int argc, char *argv[]) {
    pw_init(&argc, &argv);

    struct pw_loop *loop = pw_loop_new(NULL);
    struct pw_context *context = pw_context_new(loop, NULL, 0);

    const char *node_name = "alsa_input.usb-Yamaha_Corporation_Steinberg_UR22-00.analog-stereo";

    struct pw_stream *stream = pw_stream_new_simple(
        context,
        "UR22 Capture",
        node_name,
        PW_STREAM_FLAG_AUTOCONNECT | PW_STREAM_FLAG_MAP_BUFFERS
    );

    pw_stream_add_listener(stream, &(struct pw_stream_events){
        .process = on_process
    }, stream);

    pw_stream_connect(stream,
                      PW_DIRECTION_INPUT,
                      PW_STREAM_FLAG_AUTOCONNECT | PW_STREAM_FLAG_MAP_BUFFERS,
                      NULL);

    pw_loop_run(loop);
    return 0;
}

