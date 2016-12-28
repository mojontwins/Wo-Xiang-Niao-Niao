// Vostok Engine MK2 v1.0
// Copyleft 2016 by The Mojon Twins

void camera_do (void) {
	// In the future: change this for something better / more intelligent
	if (autoscroll) {
		//if (prx > 64 && !pkilled) cam_pos ++;
		if (cam_pos >= 4096 - 256) cam_pos = 4096 - 256; else {
			if (prx > prx_advance && !penhit) cam_pos ++;
		}
		safe_landing = (cam_pos == 4096 - 256);
	} else {
		if (pvx) {
			if (prx < CAMERA_MIN + cam_pos) cam_pos = prx - CAMERA_MIN;
			if (prx > CAMERA_MAX + cam_pos) cam_pos = prx - CAMERA_MAX; 	
		} else if (pidlt == ticks) {
			if (prx < 120 + cam_pos) cam_pos --;
			if (prx > 120 + cam_pos) cam_pos ++;
		}

		if (cam_pos < 0) cam_pos = 0;
		if (cam_pos > 4096 - 256) cam_pos = 4096 - 256;
	}
}
