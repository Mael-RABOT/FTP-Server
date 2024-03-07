

#include <criterion/criterion.h>

#include "../include/protoype.h"

Test(circular_buffer, should_create_circular_buffer)
{
    t_circular_buffer *cb = cb_init(4096);

    cr_assert_not_null(cb);
    cr_assert_not_null(cb->buffer);
    cr_assert_eq(cb->size, 4096);
    cr_assert_eq(cb->write_head, 0);
    cr_assert_eq(cb->read_head, 0);
    cr_assert_eq(cb->tail, 0);
    cb_free(&cb);
}

Test(circular_buffer, cb_push)
{
    t_circular_buffer *cb = cb_init(10);
    char *str = "test";

    cb_push(&cb, str);

    cr_assert_str_eq(cb->buffer, str, "cb_push failed to push string to buffer");
    cr_assert_eq(cb->write_head, strlen(str), "cb_push failed to update write_head");

    cb_free(&cb);
}

Test(circular_buffer, get_command)
{
    t_circular_buffer *cb = cb_init(10);
    char *str = "test\r\n";

    cb_push(&cb, str);
    char *command = get_command(&cb);

    cr_assert_str_eq(command, str, "get_command failed to get correct command");
    cr_assert_eq(cb->read_head, strlen(str), "get_command failed to update read_head");

    free(command);
    cb_free(&cb);
}

Test(circle_buffer, unfinished_command)
{
    t_circular_buffer *cb = cb_init(10);
    char *str = "te";
    char *str2 = "st\r\n";
    char *full_str = "test\r\n";

    cb_push(&cb, str);
    char *command = get_command(&cb);
    cr_assert_null(command);
    cb_push(&cb, str2);
    command = get_command(&cb);
    cr_assert_not_null(command);

    cr_assert_str_eq(command, full_str, "get_command failed to get correct command");
    cr_assert_eq(cb->read_head, strlen(full_str), "get_command failed to update read_head");

    free(command);
    cb_free(&cb);
}
