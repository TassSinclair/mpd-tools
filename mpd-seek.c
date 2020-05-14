#include <mpd/status.h>
#include <mpd/connection.h>
#include <mpd/player.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s seek_seconds\n", argv[0]);
		return 1;
	}
	unsigned seek_seconds = atoi(argv[1]);
	unsigned current_time = 0;
	unsigned total_time = 0;
	int seek_to_time;
	struct mpd_connection *conn;
	struct mpd_status *status;
	enum mpd_state state;

	conn = mpd_connection_new(NULL, 0, 0);
	status = mpd_run_status(conn);
	if (!status)
	{
		mpd_status_free(status);
		return 0;
	}
	state = mpd_status_get_state(status);
	if (state > 1)
	{
	        current_time = mpd_status_get_elapsed_time(status);
		total_time = mpd_status_get_total_time(status);

		seek_to_time = current_time + seek_seconds;
		seek_to_time = seek_to_time < 0 ? 0 : seek_to_time >= total_time ? total_time - 1 : seek_to_time;
		mpd_send_seek_current(conn, seek_to_time, false);
	}
	mpd_status_free(status);
	mpd_connection_free(conn);

	if (state > 1)
		return 0;
	return 1;
}
