#include <mpd/status.h>
#include <mpd/connection.h>
#include <mpd/mixer.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s volume_adjustment\n", argv[0]);
		return 1;
	}

	unsigned volume_adjustment = atoi(argv[1]);
	unsigned current_volume = 0;
	int volume_percentage;

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
	if (state > 0)
	{
		current_volume = mpd_status_get_volume(status);
		volume_percentage = current_volume + volume_adjustment;
		volume_percentage = volume_percentage < 0 ? 0 : volume_percentage > 100 ? 100 : volume_percentage;

		mpd_send_set_volume(conn, volume_percentage);
	}
	mpd_status_free(status);
	mpd_connection_free(conn);

	if (state > 0)
		return 0;
	return 1;
}
